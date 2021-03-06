/*
 * aeb-1.c -- Support for ARM AEB-1 Eval Board
 *
 * Copyright (c) 1998, 1999 Cygnus Support
 *
 * The authors hereby grant permission to use, copy, modify, distribute,
 * and license this software and its documentation for any purpose, provided
 * that existing copyright notices are retained in all copies and that this
 * notice is included verbatim in any distributions. No written agreement,
 * license, or royalty fee is required for any of the authorized uses.
 * Modifications to this software may be copyrighted by their authors
 * and need not follow the licensing terms described here, provided that
 * the new terms are clearly indicated on the first page of each file where
 * they apply.
 */
#include <stdio.h>
#include <bsp/bsp.h>
#include <bsp/cpu.h>
#include <bsp/aeb-1.h>
#include "bsp_if.h"
#include "queue.h"
#include "gdb.h"

#if defined(HAVE_NET)
#error HAVE_NET Not Supported on ARM AEB-1
#endif

/*
 * Enable/Disable separate debug functions
 */
#define DEBUG_UART_CODE      0
#define DEBUG_UART_FUNCTIONS 0
#define DEBUG_LOCAL_ECHO     0

static arm_cpu_data *cpu_data = NULL;

/*
 * Toggle LED for debugging purposes.
 */
void flash_led(int n, int which)
{
    unsigned char led;

    if ((which < 0) || (which > 3))
        return;

    if (cpu_data == NULL)
        cpu_data = bsp_cpu_data();

    /*
     * Make sure the Port C is in Output mode
     */
    if (cpu_data == NULL)
    {
        /*
         * If cpu_data still == NULL, that means we are not
         * far enough in the boot for it to have been initialized
         * yet.  Go ahead and ignore the shadow registers this time
         */
        *LH77790A_PORT_CONTROL_REGISTER = LH77790A_PORT_CTL_MODE_SELECTION | 
                                          LH77790A_PORT_C_4_7_DIRECTION_OUTPUT |
                                          LH77790A_PORT_C_0_3_DIRECTION_OUTPUT;
    } else {
        cpu_data->lh77790a_port_control_shadow |= LH77790A_PORT_CTL_MODE_SELECTION;
        cpu_data->lh77790a_port_control_shadow &= ~(LH77790A_PORT_C_4_7_DIRECTION_INPUT |
                                                    LH77790A_PORT_C_0_3_DIRECTION_INPUT);
        *LH77790A_PORT_CONTROL_REGISTER = cpu_data->lh77790a_port_control_shadow;
    }

    /*
     * Select the right bit in port C
     */
    led = 1 << (7 - which);

    /*
     * Double n so we turn on and off for each count
     */
    n <<= 1;

    while (n--)
    {
        int i;

        *LH77790A_PORT_C ^= led;
        i = 0xffff; while (--i);
    }
}


/*
 * Function prototypes
 */
static void uart_write   (void*, const char*, int);
static int  uart_read    (void*, char*, int);
static void uart_putchar (void*, char);
static int  uart_getchar (void*);
static int  uart_control (void*, int, ...);
#if DEBUG_UART_FUNCTIONS
void uart_putnibble(void*, unsigned char);
void uart_putbyte(void*, unsigned char);
void uart_putword(void*, unsigned short);
void uart_putlong(void*, unsigned long);
void uart_putstring(void *, char *);
void uart_putcharacter(void *, char);
#endif /* DEBUG_UART_FUNCTIONS */

/*
 * Setup the bsp_comm_channel data structure
 */
#define BSP_NUM_COMMS        2
struct bsp_comm_channel _bsp_comm_list[BSP_NUM_COMMS] = 
{
    {
	{ "UART 0", BSP_COMM_SERIAL, BSP_PROTO_NONE },
	{ (void*)UART_BASE_0, uart_write, uart_read,
	  uart_putchar, uart_getchar, uart_control }
    },
    {
	{ "UART 1", BSP_COMM_SERIAL, BSP_PROTO_NONE },
	{ (void*)UART_BASE_1, uart_write, uart_read,
	  uart_putchar, uart_getchar, uart_control }
    },
};
int _bsp_num_comms = sizeof(_bsp_comm_list)/sizeof(_bsp_comm_list[0]);

/*
 * Macros to make finding the registers easier
 */
#define UART_INDEX(base)                 (((unsigned)(base) == UART_BASE_0) ? 0 : 1)
#define UART_BASE_VALID(base)            (((unsigned)(base) == UART_BASE_0) || \
                                          ((unsigned)(base) == UART_BASE_1))
#define UART_RX_HOLDING(base)            REG8_PTR((unsigned)(base) + LH77790A_UART_RX_REG_o)
#define UART_TX_HOLDING(base)            REG8_PTR((unsigned)(base) + LH77790A_UART_TX_REG_o)
#define UART_INT_ENABLE(base)            REG8_PTR((unsigned)(base) + LH77790A_UART_INT_ENABLE_o)
#define UART_INT_STATUS(base)            REG8_PTR((unsigned)(base) + LH77790A_UART_INT_IDENT_o)
#define UART_LINE_CONTROL(base)          REG8_PTR((unsigned)(base) + LH77790A_UART_LINE_CONTROL_o)
#define UART_MODEM_CONTROL(base)         REG8_PTR((unsigned)(base) + LH77790A_UART_MODEM_CONTROL_o)
#define UART_LINE_STATUS(base)           REG8_PTR((unsigned)(base) + LH77790A_UART_LINE_STATUS_o)
#define UART_MODEM_STATUS(base)          REG8_PTR((unsigned)(base) + LH77790A_UART_MODEM_STATUS_o)
#define UART_SCRATCHPAD(base)            REG8_PTR((unsigned)(base) + LH77790A_UART_SCRATCHPAD_o)
#define UART_DIVISOR_LSB(base)           REG8_PTR((unsigned)(base) + LH77790A_UART_LSB_DIV_LATCH_o)
#define UART_DIVISOR_MSB(base)           REG8_PTR((unsigned)(base) + LH77790A_UART_MSB_DIV_LATCH_o)

/*
 * Baud rate selection stuff
 */
static int uart_baud[BSP_NUM_COMMS] = {-1,  -1};
struct _baud {
    int baud;
    unsigned short clock_select_value;
};

const static struct _baud bauds[] = {
    {    50, 30000},
    {    75, 20000},
    {   110, 13636},
    {   134, 11152},
    {   135, 11152},
    {   150, 10000},
    {   300,  5000},
    {   600,  2500},
    {  1200,  1250},
    {  1800,   833},
    {  2000,   750},
    {  2400,   625},
    {  3600,   417},
    {  4800,   313},
    {  7200,   208},
    {  9600,   156},
    { 19200,    78},
    { 38400,    39},
    { 57600,    26},
    {115200,    13},
    {128000,    12},
    {256000,     6},
};

/*
 * UART queuing stuff
 */
#define UART_BUFSIZE 256
static bsp_queue_t uart_queue[BSP_NUM_COMMS];
static char uart_buffer[BSP_NUM_COMMS][UART_BUFSIZE];

/*
 * The currently selected debug port
 */
static volatile unsigned char *uart_dbg_base = NULL;

/*
 * Array of memory region descriptors. We just list RAM and FLASH.
 */
struct bsp_mem_info _bsp_memory_list[] = 
{
    { (void *)0x00000000, (void *)0x00000000, 0, 0x00020000, BSP_MEM_RAM   },
    { (void *)0x00040000, (void *)0x00040000, 0, 0x00040000, BSP_MEM_FLASH },
};

/*
 * Number of memory region descriptors.
 */
int _bsp_num_mem_regions = sizeof(_bsp_memory_list)/sizeof(_bsp_memory_list[0]);

static void
uart_irq_enable(void *base)
{
    if (UART_BASE_VALID(base))
    {
        *UART_INT_ENABLE(base) |= (LH77790A_UART_RX_HOLDING_INT_ENABLE | 
                                   LH77790A_UART_TX_HOLDING_INT_ENABLE);
    }
}


static void
uart_irq_disable(void *base)
{
    if (UART_BASE_VALID(base))
    {
        *UART_INT_ENABLE(base) &= ~(LH77790A_UART_RX_HOLDING_INT_ENABLE | 
                                    LH77790A_UART_TX_HOLDING_INT_ENABLE);
    }
}

static void uart_putchar(void *base, char c)
{
    if (UART_BASE_VALID(base))
    {
        while ((*UART_LINE_STATUS(base) & LH77790A_UART_TX_HOLDING_EMPTY) == 0)
            ;
        *UART_TX_HOLDING(base) = c;
    }
}


static void
uart_write(void *base, const char *buf, int len)
{
    if (UART_BASE_VALID(base))
    {
        while (len-- > 0)
            uart_putchar(base, *buf++);
    }
}

static int
uart_rcvchar(void *base)
{
    if (UART_BASE_VALID(base))
    {
        while ((*UART_LINE_STATUS(base) & LH77790A_UART_RX_DATA_READY) == 0)
            ;
        return(*UART_RX_HOLDING(base));
    }

    return(-1);
}

static int
uart_getchar(void *base)
{
    int c;

    if (UART_BASE_VALID(base))
    {
        uart_irq_disable(base);
        if ((c = _bsp_dequeue(&uart_queue[UART_INDEX(base)])) < 0)
            c = uart_rcvchar(base);
        uart_irq_enable(base);

#if DEBUG_LOCAL_ECHO
        uart_putchar(base, ch);
#endif

        return c;
    }

    return (-1);
}

static int
uart_read(void *base, char *buf, int len)
{
    int ch;

    if (UART_BASE_VALID(base))
    {
        if (len <= 0)
            return 0;

        ch = uart_getchar(base);
        *buf = ch;
        return 1;
    }

    return 0;
}

static int
uart_irq_handler(int irq_nr, void *regs)
{
    unsigned char ch;
    volatile unsigned char *port = 0;
    int return_code = 0;

#if DEBUG_UART_CODE
    bsp_printf("In uart_irq_handler(%d, 0x%08lx)\n", irq_nr, regs);
    _bsp_dump_regs(regs);
    bsp_printf("LH77790A_UART_INT_IDENT_REG_0      = 0x%02x\n", *LH77790A_UART_INT_IDENT_REG_0);
    bsp_printf("LH77790A_UART_INT_IDENT_REG_1      = 0x%02x\n", *LH77790A_UART_INT_IDENT_REG_1);
    bsp_printf("LH77790A_UART_LINE_STATUS_REG_0    = 0x%02x\n", *LH77790A_UART_LINE_STATUS_REG_0);
    bsp_printf("LH77790A_UART_LINE_STATUS_REG_1    = 0x%02x\n", *LH77790A_UART_LINE_STATUS_REG_1);
    bsp_printf("LH77790A_UART_MODEM_STATUS_REG_0   = 0x%02x\n", *LH77790A_UART_MODEM_STATUS_REG_0);
    bsp_printf("LH77790A_UART_MODEM_STATUS_REG_1   = 0x%02x\n", *LH77790A_UART_MODEM_STATUS_REG_1);
#endif /* DEBUG_UART_CODE */
  
    if ((uart_dbg_base == (unsigned char *)UART_BASE_0) &&
        ((LH77790A_UART_NO_PENDING_INT & *UART_INT_STATUS(UART_BASE_0)) == 0)) {
        /*
         * Expected interrupt on Port 0
         */
        port = (unsigned char *)UART_BASE_0;
        return_code = 1;
    } else if ((uart_dbg_base == (unsigned char *)UART_BASE_1) &&
               ((LH77790A_UART_NO_PENDING_INT & *UART_INT_STATUS(UART_BASE_1)) == 0)) {
        /*
         * Expected interrupt on Port 1
         */
        port = (unsigned char *)UART_BASE_1;
        return_code = 1;
    } else {
        /*
         * No data ready.  Not my interrupt
         */
        return_code = 0;
    }
  
    if (return_code != 0)
    {
        while ((LH77790A_UART_PENDING_INT_MASK & *UART_INT_STATUS(port))
               == LH77790A_UART_RX_HOLDING_INT)
        {
            ch = *UART_RX_HOLDING(port);

            /*
             * If we read a Ctrl-C then we need to let
             * GDB handle it.  Return 0 to have the GDB
             * exception processor run.
             */
            if (ch == '\003')
            {
                return_code = 0;
                break;
            }
    
            _bsp_enqueue(&uart_queue[UART_INDEX(port)], ch);
#if DEBUG_LOCAL_ECHO
            uart_putchar(port, ch);
#endif
        }
    }
  
    return return_code;
}

static int
uart_setbaud(void *base, int bps)
{
    int   i;
    const struct _baud *bp;
  
    if (UART_BASE_VALID(base))
    {
        for (i = 0, bp = bauds; i < (sizeof(bauds)/sizeof(bauds[0])); i++, bp++)
        {
            if (bp->baud == bps)
            {
                /*
                 * Enable Baud Divisor Latch
                 */
                *UART_LINE_CONTROL(base) = LH77790A_UART_DIVISOR_LATCH_ENABLE;

                /*
                 * Setup the UART Baud Rate Divisor
                 */
                *UART_DIVISOR_MSB(base) = bp->clock_select_value >> 8;
                *UART_DIVISOR_LSB(base) = bp->clock_select_value & 0xFF;

                /*
                 * Store the state
                 */
                uart_baud[UART_INDEX(base)] = bps;
                return 0;
            }
        }
    }

    return -1;
}

static int
uart_control(void *base, int func, ...)
{
    int                    retval = 0;
    int                    i;
    va_list                ap;
#ifdef NOT_DONE_YET
    static bsp_vec_t       uart_vec;
#endif /* NOT_DONE_YET */

    if (UART_BASE_VALID(base))
    {
        va_start (ap, func);

        switch (func) {
        case COMMCTL_SETBAUD:
            i = va_arg(ap, int);
            retval = uart_setbaud((void *)base, i);
            break;

        case COMMCTL_GETBAUD:
            retval = uart_baud[UART_INDEX(base)];
            break;
        case COMMCTL_INSTALL_DBG_ISR:
            if (uart_dbg_base != base) {
                if (uart_dbg_base == NULL) {
#ifdef NOT_DONE_YET
                    uart_vec.handler = uart_irq_handler;
                    uart_vec.next = NULL;
                    bsp_install_vec(BSP_VEC_INTERRUPT, BSP_68328_IRQ_IRQ1,
                                    BSP_VEC_REPLACE, &uart_vec);
                    bsp_enable_irq(BSP_68328_IRQ_IRQ1);
                    uart_irq_enable(base);
#endif /* NOT_DONE_YET */
                }
                uart_dbg_base = base;
            }
            break;
	
        case COMMCTL_REMOVE_DBG_ISR:
#ifdef NOT_DONE_YET
            uart_irq_disable(base);
            bsp_disable_irq(BSP_68328_IRQ_IRQ1);
            bsp_remove_vec(BSP_VEC_INTERRUPT, BSP_68328_IRQ_IRQ1, &uart_vec);
#endif /* NOT_DONE_YET */
            uart_dbg_base = NULL;
            break;

        default:
            retval = -1;
            break;
        }

        va_end(ap);
    } else {
        retval = -1;
    }

    return retval;
}


#if DEBUG_UART_FUNCTIONS
#else
static
#endif /* DEBUG_UART_FUNCTIONS */
void
init_uart(void *base, int bps)
{
    if (UART_BASE_VALID(base))
    {
        /*
         * Set the baud rate
         */
        uart_setbaud((void *)base, bps);

        /*
         * Set the data and stop bits
         */
        *UART_LINE_CONTROL(base) = LH77790A_UART_DATABITS_8_STOPBITS_1;

        /*
         * Disable all interrupts
         */
        *UART_INT_ENABLE(base) = 0;
    }
}

/*
 * Early initialization of comm channels. Must not rely
 * on interrupts, yet. Interrupt operation can be enabled
 * in _bsp_board_init().
 */
void
_bsp_init_board_comm(void)
{
    if (cpu_data == NULL)
        cpu_data = bsp_cpu_data();

    _bsp_queue_init(&uart_queue[0], uart_buffer[0], sizeof(uart_buffer[0]));
    _bsp_queue_init(&uart_queue[1], uart_buffer[1], sizeof(uart_buffer[1]));

    init_uart((void *)UART_BASE_0, 38400);
    init_uart((void *)UART_BASE_1, 38400);
}


/*
 * Set any board specific debug traps.
 */
void
_bsp_install_board_debug_traps(void)
{
#ifdef NOT_DONE_YET
    /*
     * None
     */
#endif /* NOT_DONE_YET */
}


/*
 * Install any board specific interrupt controllers.
 */
void
_bsp_install_board_irq_controllers(void)
{
#ifdef NOT_DONE_YET
    /*
     * None
     */
#endif /* NOT_DONE_YET */
}

/*
 *  Board specific BSP initialization.
 */
void
_bsp_board_init(void)
{
    /*
     * Override default platform info.
     */
    _bsp_platform_info.cpu = "SHARP LH77790 A/B ARM7DI";
    _bsp_platform_info.board = "AEB-1";
}


#if DEBUG_UART_FUNCTIONS
/*
 * Print out a single Hex digit
 */
void uart_putnibble(void *base, unsigned char printval)
{
    if (printval <= 9)
        uart_putchar(base, printval + '0');
    else if ((printval >= 0xA) && (printval <= 0xF))
        uart_putchar(base, printval - 0xA + 'A');
    else
        uart_putchar(base, '.');
}

/*
 * Print out a byte value
 */
void uart_putbyte(void *base, unsigned char printval)
{
    uart_putnibble(base, (unsigned char)((printval >> 4)  & 0x0000000F));
    uart_putnibble(base, (unsigned char)((printval >> 0)  & 0x0000000F));
}

/*
 * Print out a word value
 */
void uart_putword(void *base, unsigned short printval)
{
    uart_putnibble(base, (unsigned char)((printval >> 12) & 0x0000000F));
    uart_putnibble(base, (unsigned char)((printval >> 8)  & 0x0000000F));
    uart_putnibble(base, (unsigned char)((printval >> 4)  & 0x0000000F));
    uart_putnibble(base, (unsigned char)((printval >> 0)  & 0x0000000F));
}

/*
 * Print out a long value
 */
void uart_putlong(void *base, unsigned long printval)
{
    uart_putnibble(base, (unsigned char)((printval >> 28) & 0x0000000F));
    uart_putnibble(base, (unsigned char)((printval >> 24) & 0x0000000F));
    uart_putnibble(base, (unsigned char)((printval >> 20) & 0x0000000F));
    uart_putnibble(base, (unsigned char)((printval >> 16) & 0x0000000F));
    uart_putnibble(base, (unsigned char)((printval >> 12) & 0x0000000F));
    uart_putnibble(base, (unsigned char)((printval >> 8)  & 0x0000000F));
    uart_putnibble(base, (unsigned char)((printval >> 4)  & 0x0000000F));
    uart_putnibble(base, (unsigned char)((printval >> 0)  & 0x0000000F));
}


/*
 * Print out a NULL terminated string
 */
void uart_putstring(void *base, char *string)
{
    if (string != NULL)
    {
        while (*string != '\0')
        {
            uart_putchar(base, *string);
            string++;
        }
    }
}

/*
 * Print out a single character
 */
void uart_putcharacter(void *base, char c)
{
    uart_putchar(base, c);
}
#endif /* DEBUG_UART_FUNCTIONS */
