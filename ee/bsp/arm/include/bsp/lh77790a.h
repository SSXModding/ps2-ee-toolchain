/*
 * lh77790a.h -- CPU specific header for Cygnus BSP.
 *   Sharp LH77790A
 *
 * Copyright (c) 1998 Cygnus Support
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

#ifndef __LH77790A_H__
#define __LH77790A_H__ 1

#ifdef __ASSEMBLER__

#define REG8_VAL(a)  (a)
#define REG16_VAL(a) (a)
#define REG32_VAL(a) (a)

#define REG8_PTR(a)  (a)
#define REG16_PTR(a) (a)
#define REG32_PTR(a) (a)

#else /* __ASSEMBLER__ */

/*
 * Note, the 16 bit registers are done as 32 bit ptrs because
 * according to the LH77790A FAQ, if we don't do it that way,
 * the compiler might write the value via 2 byte writes and 
 * put invalid data there.
 */
#define REG8_VAL(a)  ((unsigned char)(a))
#define REG16_VAL(a) ((unsigned short)(a))
#define REG32_VAL(a) ((unsigned int)(a))

#define REG8_PTR(a)  ((volatile unsigned char *)(a))
#define REG16_PTR(a) ((volatile unsigned long *)(a))
#define REG32_PTR(a) ((volatile unsigned long *)(a))

#endif /* __ASSEMBLER__ */

/*
 * Sharp LH77790A Cache Register Definitions
 */
#define LH77790A_CACHE_REGISTER               REG8_PTR(0xFFFFA400)

/*
 * Sharp LH77790A Cache Bit Field Definitions
 */
#define LH77790A_INVALIDATE_MODE_DISABLED     REG8_VAL(0x0 << 3)
#define LH77790A_INVALIDATE_MODE_ENABLED      REG8_VAL(0x1 << 3)
#define LH77790A_FLUSH_MODE_DISABLED          REG8_VAL(0x0 << 2)
#define LH77790A_FLUSH_MODE_ENABLED           REG8_VAL(0x1 << 2)
#define LH77790A_SRAM_MODE_DISABLED           REG8_VAL(0x0 << 1)
#define LH77790A_SRAM_MODE_ENABLED            REG8_VAL(0x1 << 1)
#define LH77790A_CACHE_MODE_DISABLED          REG8_VAL(0x0 << 0)
#define LH77790A_CACHE_MODE_ENABLED           REG8_VAL(0x1 << 0)

/*
 * Sharp LH77790A Cache Entry Status Bit Field Definitions
 */
#define LH77790A_CACHE_ENTRY_INVALID          REG32_VAL(0x0 << 31)
#define LH77790A_CACHE_ENTRY_VALID            REG32_VAL(0x1 << 31)
#define LH77790A_CACHE_ENTRY_UNMODIFIED       REG32_VAL(0x0 << 30)
#define LH77790A_CACHE_ENTRY_MODIFIED         REG32_VAL(0x0 << 30)

/*
 * Sharp LH77790A Local SRAM Register
 */
#define LH77790A_LOCAL_SRAM_REGISTER          REG8_PTR(0xFFFFA404)

/*
 * Sharp LH77790A Local SRAM Bit Field Definitions
 */
#define LH77790A_LOCAL_SRAM_DISABLE           REG8_VAL(0x0 << 0)
#define LH77790A_LOCAL_SRAM_ENABLE            REG8_VAL(0x1 << 0)
#define LH77790A_LOCAL_SRAM_LOCATION_LOW      REG8_VAL(0x0 << 1)
#define LH77790A_LOCAL_SRAM_LOCATION_HIGH     REG8_VAL(0x1 << 1)

/*
 * Sharp LH77790A Memory Segment Register Definitions
 */
#define LH77790A_MEM_SEG_BASE                 0xFFFFA000

#define LH77790A_MEM_SEG_START0               REG32_PTR(LH77790A_MEM_SEG_BASE + 0x00)
#define LH77790A_MEM_SEG_START1               REG32_PTR(LH77790A_MEM_SEG_BASE + 0x04)
#define LH77790A_MEM_SEG_START2               REG32_PTR(LH77790A_MEM_SEG_BASE + 0x08)
#define LH77790A_MEM_SEG_START3               REG32_PTR(LH77790A_MEM_SEG_BASE + 0x0C)
#define LH77790A_MEM_SEG_START4               REG32_PTR(LH77790A_MEM_SEG_BASE + 0x10)
#define LH77790A_MEM_SEG_START5               REG32_PTR(LH77790A_MEM_SEG_BASE + 0x14)
#define LH77790A_MEM_SEG_START6               REG32_PTR(LH77790A_MEM_SEG_BASE + 0x18)
#define LH77790A_MEM_SEG_START7               REG32_PTR(LH77790A_MEM_SEG_BASE + 0x1C)

#define LH77790A_MEM_SEG_STOP0                REG32_PTR(LH77790A_MEM_SEG_BASE + 0x20)
#define LH77790A_MEM_SEG_STOP1                REG32_PTR(LH77790A_MEM_SEG_BASE + 0x24)
#define LH77790A_MEM_SEG_STOP2                REG32_PTR(LH77790A_MEM_SEG_BASE + 0x28)
#define LH77790A_MEM_SEG_STOP3                REG32_PTR(LH77790A_MEM_SEG_BASE + 0x2C)
#define LH77790A_MEM_SEG_STOP4                REG32_PTR(LH77790A_MEM_SEG_BASE + 0x30)
#define LH77790A_MEM_SEG_STOP5                REG32_PTR(LH77790A_MEM_SEG_BASE + 0x34)
#define LH77790A_MEM_SEG_STOP6                REG32_PTR(LH77790A_MEM_SEG_BASE + 0x38)
#define LH77790A_MEM_SEG_STOP7                REG32_PTR(LH77790A_MEM_SEG_BASE + 0x3C)

#define LH77790A_MEM_SEG_SDR0                 REG16_PTR(LH77790A_MEM_SEG_BASE + 0x40)
#define LH77790A_MEM_SEG_SDR1                 REG16_PTR(LH77790A_MEM_SEG_BASE + 0x44)
#define LH77790A_MEM_SEG_SDR2                 REG16_PTR(LH77790A_MEM_SEG_BASE + 0x48)
#define LH77790A_MEM_SEG_SDR3                 REG16_PTR(LH77790A_MEM_SEG_BASE + 0x4C)
#define LH77790A_MEM_SEG_SDR4                 REG16_PTR(LH77790A_MEM_SEG_BASE + 0x50)
#define LH77790A_MEM_SEG_SDR5                 REG16_PTR(LH77790A_MEM_SEG_BASE + 0x54)
#define LH77790A_MEM_SEG_SDR6                 REG16_PTR(LH77790A_MEM_SEG_BASE + 0x58)
#define LH77790A_MEM_SEG_SDR7                 REG16_PTR(LH77790A_MEM_SEG_BASE + 0x5C)
#define LH77790A_MEM_SEG_SDR8                 REG16_PTR(LH77790A_MEM_SEG_BASE + 0x60)

/*
 * Sharp LH77790A Memory Segment Register Bit Field Definitions
 */
#define LH77790A_MEM_SEG_START_ADDRESS(x)     REG32_VAL((x) & 0xFFFFFF00)
#define LH77790A_MEM_SEG_STOP_ADDRESS(x)      REG32_VAL((x) & 0xFFFFFF00)

#define LH77790A_MEM_SEG_SYS_PRIVILEGE_NONE   REG16_VAL(0x0 << 13)
#define LH77790A_MEM_SEG_SYS_PRIVILEGE_RO     REG16_VAL(0x1 << 13)
#define LH77790A_MEM_SEG_SYS_PRIVILEGE_WO     REG16_VAL(0x2 << 13)
#define LH77790A_MEM_SEG_SYS_PRIVILEGE_RW     REG16_VAL(0x3 << 13)
                                                               
#define LH77790A_MEM_SEG_USER_PRIVILEGE_NONE  REG16_VAL(0x0 << 11)
#define LH77790A_MEM_SEG_USER_PRIVILEGE_RO    REG16_VAL(0x1 << 11)
#define LH77790A_MEM_SEG_USER_PRIVILEGE_WO    REG16_VAL(0x2 << 11)
#define LH77790A_MEM_SEG_USER_PRIVILEGE_RW    REG16_VAL(0x3 << 11)
                                                               
#define LH77790A_MEM_SEG_NONCACHEABLE         REG16_VAL(0x0 << 10)
#define LH77790A_MEM_SEG_CACHEABLE            REG16_VAL(0x1 << 10)

#define LH77790A_MEM_SEG_32BIT_MODE           REG16_VAL(0x0 << 8)
#define LH77790A_MEM_SEG_16BIT_MODE           REG16_VAL(0x1 << 8)
                                                              
#define LH77790A_MEM_SEG_SELECT_BANK_0        REG16_VAL(0x1 << 0)
#define LH77790A_MEM_SEG_SELECT_BANK_1        REG16_VAL(0x1 << 1)
#define LH77790A_MEM_SEG_SELECT_BANK_2        REG16_VAL(0x1 << 2)
#define LH77790A_MEM_SEG_SELECT_BANK_3        REG16_VAL(0x1 << 3)
#define LH77790A_MEM_SEG_SELECT_BANK_4        REG16_VAL(0x1 << 4)
#define LH77790A_MEM_SEG_SELECT_BANK_5        REG16_VAL(0x1 << 5)
#define LH77790A_MEM_SEG_SELECT_BANK_6        REG16_VAL(0x1 << 6)
#define LH77790A_MEM_SEG_SELECT_BANK_7        REG16_VAL(0x1 << 7)

/*
 * Sharp LH77790A Bank Configuration Register Definitions
 */
#define LH77790A_BANK_CONFIG_BASE             0xFFFFA100

#define LH77790A_BANK_CONFIG_BCR0             REG16_PTR(LH77790A_BANK_CONFIG_BASE + 0x00)
#define LH77790A_BANK_CONFIG_BCR1             REG16_PTR(LH77790A_BANK_CONFIG_BASE + 0x04)
#define LH77790A_BANK_CONFIG_BCR2             REG16_PTR(LH77790A_BANK_CONFIG_BASE + 0x08)
#define LH77790A_BANK_CONFIG_BCR3             REG16_PTR(LH77790A_BANK_CONFIG_BASE + 0x0C)
#define LH77790A_BANK_CONFIG_BCR4             REG16_PTR(LH77790A_BANK_CONFIG_BASE + 0x10)
#define LH77790A_BANK_CONFIG_BCR5             REG16_PTR(LH77790A_BANK_CONFIG_BASE + 0x14)
#define LH77790A_BANK_CONFIG_BCR6a            REG16_PTR(LH77790A_BANK_CONFIG_BASE + 0x18)
#define LH77790A_BANK_CONFIG_BCR7a            REG16_PTR(LH77790A_BANK_CONFIG_BASE + 0x1C)
#define LH77790A_BANK_CONFIG_BCR6b            REG8_PTR(LH77790A_BANK_CONFIG_BASE + 0x20)
#define LH77790A_BANK_CONFIG_BCR7b            REG8_PTR(LH77790A_BANK_CONFIG_BASE + 0x24)
#define LH77790A_BANK_CONFIG_DRR              REG16_PTR(LH77790A_BANK_CONFIG_BASE + 0x28)

/*
 * Sharp LH77790A Bank Configuration Register Bit Field Definitions
 */
#define LH77790A_BANK_SRAM_BUS_SIZE_8_BITS    REG16_VAL(0x0 << 15)
#define LH77790A_BANK_SRAM_BUS_SIZE_16_BITS   REG16_VAL(0x1 << 15)
#define LH77790A_BANK_SRAM_WAIT_STATES_0      REG16_VAL(0x0 << 12)
#define LH77790A_BANK_SRAM_WAIT_STATES_1      REG16_VAL(0x1 << 12)
#define LH77790A_BANK_SRAM_WAIT_STATES_2      REG16_VAL(0x2 << 12)
#define LH77790A_BANK_SRAM_WAIT_STATES_3      REG16_VAL(0x3 << 12)
#define LH77790A_BANK_SRAM_WAIT_STATES_4      REG16_VAL(0x4 << 12)
#define LH77790A_BANK_SRAM_WAIT_STATES_5      REG16_VAL(0x5 << 12)
#define LH77790A_BANK_SRAM_WAIT_STATES_6      REG16_VAL(0x6 << 12)
#define LH77790A_BANK_SRAM_WAIT_STATES_7      REG16_VAL(0x7 << 12)
#define LH77790A_BANK_SRAM_ECE_CE5_HIGH       REG16_VAL(0x1 << 11)
#define LH77790A_BANK_SRAM_ECE_CE5_LOW        REG16_VAL(0x1 << 10)
#define LH77790A_BANK_SRAM_ECE_CE4_HIGH       REG16_VAL(0x1 << 9)
#define LH77790A_BANK_SRAM_ECE_CE4_LOW        REG16_VAL(0x1 << 8)
#define LH77790A_BANK_SRAM_ECE_CE3_HIGH       REG16_VAL(0x1 << 7)
#define LH77790A_BANK_SRAM_ECE_CE3_LOW        REG16_VAL(0x1 << 6)
#define LH77790A_BANK_SRAM_ECE_CE2_HIGH       REG16_VAL(0x1 << 5)
#define LH77790A_BANK_SRAM_ECE_CE2_LOW        REG16_VAL(0x1 << 4)
#define LH77790A_BANK_SRAM_ECE_CE1_HIGH       REG16_VAL(0x1 << 3)
#define LH77790A_BANK_SRAM_ECE_CE1_LOW        REG16_VAL(0x1 << 2)
#define LH77790A_BANK_SRAM_ECE_CE0_HIGH       REG16_VAL(0x1 << 1)
#define LH77790A_BANK_SRAM_ECE_CE0_LOW        REG16_VAL(0x1 << 0)

#define LH77790A_BANK_DRAM_BUS_SIZE_8_BITS    REG16_VAL(0x0 << 15)
#define LH77790A_BANK_DRAM_BUS_SIZE_16_BITS   REG16_VAL(0x1 << 15)
#define LH77790A_BANK_DRAM_FCAS_0             REG16_VAL(0x0 << 12)
#define LH77790A_BANK_DRAM_FCAS_1             REG16_VAL(0x1 << 12)
#define LH77790A_BANK_DRAM_FCAS_2             REG16_VAL(0x2 << 12)
#define LH77790A_BANK_DRAM_FCAS_3             REG16_VAL(0x3 << 12)
#define LH77790A_BANK_DRAM_FCAS_4             REG16_VAL(0x4 << 12)
#define LH77790A_BANK_DRAM_FCAS_5             REG16_VAL(0x5 << 12)
#define LH77790A_BANK_DRAM_FCAS_6             REG16_VAL(0x6 << 12)
#define LH77790A_BANK_DRAM_FCAS_7             REG16_VAL(0x7 << 12)
#define LH77790A_BANK_DRAM_ECAS_CAS5_HIGH     REG16_VAL(0x1 << 11)
#define LH77790A_BANK_DRAM_ECAS_CAS5_LOW      REG16_VAL(0x1 << 10)
#define LH77790A_BANK_DRAM_ECAS_CAS4_HIGH     REG16_VAL(0x1 << 9)
#define LH77790A_BANK_DRAM_ECAS_CAS4_LOW      REG16_VAL(0x1 << 8)
#define LH77790A_BANK_DRAM_ECAS_CAS3_HIGH     REG16_VAL(0x1 << 7)
#define LH77790A_BANK_DRAM_ECAS_CAS3_LOW      REG16_VAL(0x1 << 6)
#define LH77790A_BANK_DRAM_ECAS_CAS2_HIGH     REG16_VAL(0x1 << 5)
#define LH77790A_BANK_DRAM_ECAS_CAS2_LOW      REG16_VAL(0x1 << 4)
#define LH77790A_BANK_DRAM_ECAS_CAS1_HIGH     REG16_VAL(0x1 << 3)
#define LH77790A_BANK_DRAM_ECAS_CAS1_LOW      REG16_VAL(0x1 << 2)
#define LH77790A_BANK_DRAM_ECAS_CAS0_HIGH     REG16_VAL(0x1 << 1)
#define LH77790A_BANK_DRAM_ECAS_CAS0_LOW      REG16_VAL(0x1 << 0)

#define LH77790A_BANK_DRAM_BCAS_1_5_CYCLES    REG8_VAL(0x0 << 5)
#define LH77790A_BANK_DRAM_BCAS_2_5_CYCLES    REG8_VAL(0x2 << 5)
#define LH77790A_BANK_DRAM_BCAS_3_5_CYCLES    REG8_VAL(0x3 << 5)
#define LH77790A_BANK_DRAM_REFRESH_INACTIVE   REG8_VAL(0x0 << 4)
#define LH77790A_BANK_DRAM_REFRESH_ACTIVE     REG8_VAL(0x1 << 4)
#define LH77790A_BANK_DRAM_SIZE_0             REG8_VAL(0x0 << 1)
#define LH77790A_BANK_DRAM_SIZE_1             REG8_VAL(0x1 << 1)
#define LH77790A_BANK_DRAM_SIZE_2             REG8_VAL(0x2 << 1)
#define LH77790A_BANK_DRAM_SIZE_3             REG8_VAL(0x3 << 1)
#define LH77790A_BANK_DRAM_SIZE_4             REG8_VAL(0x4 << 1)
#define LH77790A_BANK_DRAM_PAGE_MODE_NORMAL   REG8_VAL(0x0 << 0)
#define LH77790A_BANK_DRAM_PAGE_MODE_PAGE     REG8_VAL(0x1 << 0)


/*
 * Sharp LH77790A Clock and Power Management Register Definitions
 */
#define LH77790A_CPMU_BASE                    0xFFFFAC00
#define LH77790A_CPMU_PCSR                    REG32_VALUE(LH77790A_CPMU_BASE + 0x04)
#define LH77790A_CPMU_U0CCR                   REG32_VALUE(LH77790A_CPMU_BASE + 0x08)
#define LH77790A_CPMU_U1CCR                   REG32_VALUE(LH77790A_CPMU_BASE + 0x0C)
#define LH77790A_CPMU_U2CCR                   REG32_VALUE(LH77790A_CPMU_BASE + 0x10)
#define LH77790A_CPMU_CT0CCR                  REG32_VALUE(LH77790A_CPMU_BASE + 0x18)
#define LH77790A_CPMU_CT1CCR                  REG32_VALUE(LH77790A_CPMU_BASE + 0x1C)
#define LH77790A_CPMU_CT2CCR                  REG32_VALUE(LH77790A_CPMU_BASE + 0x20)
#define LH77790A_CPMU_CCCR                    REG8_VALUE(LH77790A_CPMU_BASE + 0x28)

/*
 * Sharp LH77790A Peripheral Clock Select Register Bit Field Definitions
 */
#define LH77790A_PCSR_UART0_CLKSRC_INTERNAL   REG32_VALUE(0x0 << 0)
#define LH77790A_PCSR_UART0_CLKSRC_EXTERNAL   REG32_VALUE(0x1 << 0)
#define LH77790A_PCSR_UART1_CLKSRC_INTERNAL   REG32_VALUE(0x0 << 1)
#define LH77790A_PCSR_UART1_CLKSRC_EXTERNAL   REG32_VALUE(0x1 << 1)
#define LH77790A_PCSR_UART2_CLKSRC_INTERNAL   REG32_VALUE(0x0 << 2)
#define LH77790A_PCSR_UART2_CLKSRC_EXTERNAL   REG32_VALUE(0x1 << 2)
#define LH77790A_PCSR_CNTTMR0_CLKSRC_INTERNAL REG32_VALUE(0x0 << 3)
#define LH77790A_PCSR_CNTTMR0_CLKSRC_EXTERNAL REG32_VALUE(0x1 << 3)
#define LH77790A_PCSR_CNTTMR1_CLKSRC_INTERNAL REG32_VALUE(0x0 << 4)
#define LH77790A_PCSR_CNTTMR1_CLKSRC_EXTERNAL REG32_VALUE(0x1 << 4)
#define LH77790A_PCSR_CNTTMR2_CLKSRC_INTERNAL REG32_VALUE(0x0 << 5)
#define LH77790A_PCSR_CNTTMR2_CLKSRC_EXTERNAL REG32_VALUE(0x1 << 5)
#define LH77790A_PCSR_LCD_CLK_DISABLE         REG32_VALUE(0x0 << 6)
#define LH77790A_PCSR_LCD_CLK_ENABLE          REG32_VALUE(0x1 << 6)
#define LH77790A_PCSR_PWM_CLK_DISABLE         REG32_VALUE(0x0 << 7)
#define LH77790A_PCSR_PWM_CLK_ENABLE          REG32_VALUE(0x1 << 7)
#define LH77790A_PCSR_SIR_CLK_DISABLE         REG32_VALUE(0x0 << 8)
#define LH77790A_PCSR_SIR_CLK_ENABLE          REG32_VALUE(0x1 << 8)

/*
 * Sharp LH77790A Clock Control Register Bit Field Definitions
 */
#define LH77790A_CCR_HALTED                   REG32_VALUE(0x000)
#define LH77790A_CCR_XCLK                     REG32_VALUE(0x001)
#define LH77790A_CCR_XCLK_DIV_2               REG32_VALUE(0x002)
#define LH77790A_CCR_XCLK_DIV_4               REG32_VALUE(0x004)
#define LH77790A_CCR_XCLK_DIV_8               REG32_VALUE(0x008)
#define LH77790A_CCR_XCLK_DIV_16              REG32_VALUE(0x010)
#define LH77790A_CCR_XCLK_DIV_32              REG32_VALUE(0x020)
#define LH77790A_CCR_XCLK_DIV_64              REG32_VALUE(0x040)
#define LH77790A_CCR_XCLK_DIV_128             REG32_VALUE(0x080)
#define LH77790A_CCR_XCLK_DIV_256             REG32_VALUE(0x100)

/*
 * Sharp LH77790A Core Clock Control Register Bit Field Definitions
 */
#define LH77790A_CORE_CCR_HALTED              REG8_VALUE(0x00)
#define LH77790A_CORE_CCR_XCLK                REG8_VALUE(0x01)
#define LH77790A_CORE_CCR_XCLK_DIV_2          REG8_VALUE(0x02)
#define LH77790A_CORE_CCR_XCLK_DIV_4          REG8_VALUE(0x04)
#define LH77790A_CORE_CCR_XCLK_DIV_8          REG8_VALUE(0x08)
#define LH77790A_CORE_CCR_XCLK_DIV_16         REG8_VALUE(0x10)
#define LH77790A_CORE_CCR_XCLK_DIV_32         REG8_VALUE(0x20)
#define LH77790A_CORE_CCR_XCLK_DIV_64         REG8_VALUE(0x40)
#define LH77790A_CORE_CCR_XCLK_DIV_128        REG8_VALUE(0x80)


/*
 * Sharp LH77790A UART Register Base Definitions
 */
#define	LH77790A_UART_BASE_0                  0xFFFF0000
#define	LH77790A_UART_BASE_1                  0xFFFF0400
#define	LH77790A_UART_BASE_2                  0xFFFF0800

/*
 * Sharp LH77790A UART Register Offsets
 */
#define LH77790A_UART_RX_REG_o                0x00
#define LH77790A_UART_TX_REG_o                0x00
#define LH77790A_UART_LSB_DIV_LATCH_o         0x00
#define LH77790A_UART_INT_ENABLE_o            0x04
#define LH77790A_UART_MSB_DIV_LATCH_o         0x04
#define LH77790A_UART_INT_IDENT_o             0x08
#define LH77790A_UART_LINE_CONTROL_o          0x0C
#define LH77790A_UART_MODEM_CONTROL_o         0x10
#define LH77790A_UART_LINE_STATUS_o           0x14
#define LH77790A_UART_MODEM_STATUS_o          0x18
#define LH77790A_UART_SCRATCHPAD_o            0x1C

/*
 * Sharp LH77790A UART Register Definitions
 */
#define LH77790A_UART_RX_REG_0                REG8_PTR(LH77790A_UART_BASE_0 + LH77790A_UART_RX_REG_o)
#define LH77790A_UART_TX_REG_0                REG8_PTR(LH77790A_UART_BASE_0 + LH77790A_UART_TX_REG_o)
#define LH77790A_UART_LSB_DIV_LATCH_0         REG8_PTR(LH77790A_UART_BASE_0 + LH77790A_UART_LSB_DIV_LATCH_o)
#define LH77790A_UART_INT_ENABLE_REG_0        REG8_PTR(LH77790A_UART_BASE_0 + LH77790A_UART_INT_ENABLE_o)
#define LH77790A_UART_MSB_DIV_LATCH_0         REG8_PTR(LH77790A_UART_BASE_0 + LH77790A_UART_MSB_DIV_LATCH_o)
#define LH77790A_UART_INT_IDENT_REG_0         REG8_PTR(LH77790A_UART_BASE_0 + LH77790A_UART_INT_IDENT_o)
#define LH77790A_UART_LINE_CONTROL_REG_0      REG8_PTR(LH77790A_UART_BASE_0 + LH77790A_UART_LINE_CONTROL_o)
#define LH77790A_UART_MODEM_CONTROL_REG_0     REG8_PTR(LH77790A_UART_BASE_0 + LH77790A_UART_MODEM_CONTROL_o)
#define LH77790A_UART_LINE_STATUS_REG_0       REG8_PTR(LH77790A_UART_BASE_0 + LH77790A_UART_LINE_STATUS_o)
#define LH77790A_UART_MODEM_STATUS_REG_0      REG8_PTR(LH77790A_UART_BASE_0 + LH77790A_UART_MODEM_STATUS_o)
#define LH77790A_UART_SCRATCHPAD_0            REG8_PTR(LH77790A_UART_BASE_0 + LH77790A_UART_SCRATCHPAD_o)

#define LH77790A_UART_RX_REG_1                REG8_PTR(LH77790A_UART_BASE_1 + LH77790A_UART_RX_REG_o)
#define LH77790A_UART_TX_REG_1                REG8_PTR(LH77790A_UART_BASE_1 + LH77790A_UART_TX_REG_o)
#define LH77790A_UART_LSB_DIV_LATCH_1         REG8_PTR(LH77790A_UART_BASE_1 + LH77790A_UART_LSB_DIV_LATCH_o)
#define LH77790A_UART_INT_ENABLE_REG_1        REG8_PTR(LH77790A_UART_BASE_1 + LH77790A_UART_INT_ENABLE_o)
#define LH77790A_UART_MSB_DIV_LATCH_1         REG8_PTR(LH77790A_UART_BASE_1 + LH77790A_UART_MSB_DIV_LATCH_o)
#define LH77790A_UART_INT_IDENT_REG_1         REG8_PTR(LH77790A_UART_BASE_1 + LH77790A_UART_INT_IDENT_o)
#define LH77790A_UART_LINE_CONTROL_REG_1      REG8_PTR(LH77790A_UART_BASE_1 + LH77790A_UART_LINE_CONTROL_o)
#define LH77790A_UART_MODEM_CONTROL_REG_1     REG8_PTR(LH77790A_UART_BASE_1 + LH77790A_UART_MODEM_CONTROL_o)
#define LH77790A_UART_LINE_STATUS_REG_1       REG8_PTR(LH77790A_UART_BASE_1 + LH77790A_UART_LINE_STATUS_o)
#define LH77790A_UART_MODEM_STATUS_REG_1      REG8_PTR(LH77790A_UART_BASE_1 + LH77790A_UART_MODEM_STATUS_o)
#define LH77790A_UART_SCRATCHPAD_1            REG8_PTR(LH77790A_UART_BASE_1 + LH77790A_UART_SCRATCHPAD_o)

#define LH77790A_UART_RX_REG_2                REG8_PTR(LH77790A_UART_BASE_2 + LH77790A_UART_RX_REG_o)
#define LH77790A_UART_TX_REG_2                REG8_PTR(LH77790A_UART_BASE_2 + LH77790A_UART_TX_REG_o)
#define LH77790A_UART_LSB_DIV_LATCH_2         REG8_PTR(LH77790A_UART_BASE_2 + LH77790A_UART_LSB_DIV_LATCH_o)
#define LH77790A_UART_INT_ENABLE_REG_2        REG8_PTR(LH77790A_UART_BASE_2 + LH77790A_UART_INT_ENABLE_o)
#define LH77790A_UART_MSB_DIV_LATCH_2         REG8_PTR(LH77790A_UART_BASE_2 + LH77790A_UART_MSB_DIV_LATCH_o)
#define LH77790A_UART_INT_IDENT_REG_2         REG8_PTR(LH77790A_UART_BASE_2 + LH77790A_UART_INT_IDENT_o)
#define LH77790A_UART_LINE_CONTROL_REG_2      REG8_PTR(LH77790A_UART_BASE_2 + LH77790A_UART_LINE_CONTROL_o)
#define LH77790A_UART_MODEM_CONTROL_REG_2     REG8_PTR(LH77790A_UART_BASE_2 + LH77790A_UART_MODEM_CONTROL_o)
#define LH77790A_UART_LINE_STATUS_REG_2       REG8_PTR(LH77790A_UART_BASE_2 + LH77790A_UART_LINE_STATUS_o)
#define LH77790A_UART_MODEM_STATUS_REG_2      REG8_PTR(LH77790A_UART_BASE_2 + LH77790A_UART_MODEM_STATUS_o)
#define LH77790A_UART_SCRATCHPAD_2            REG8_PTR(LH77790A_UART_BASE_2 + LH77790A_UART_SCRATCHPAD_o)

/*
 * Sharp LH77790A UART Interrupt Enable Register Bit fields
 */
#define LH77790A_UART_RX_HOLDING_INT_ENABLE   REG8_VAL(0x01)
#define LH77790A_UART_TX_HOLDING_INT_ENABLE   REG8_VAL(0x02)
#define LH77790A_UART_RX_LINE_STAT_INT_ENABLE REG8_VAL(0x04)
#define LH77790A_UART_MODEM_STAT_INT_ENABLE   REG8_VAL(0x08)

/*
 * Sharp LH77790A UART Interrupt Identification Register Bit fields
 */
#define LH77790A_UART_PENDING_INT_MASK        REG8_VAL(0x07)
#define LH77790A_UART_NO_PENDING_INT          REG8_VAL(0x01)
#define LH77790A_UART_RX_LINE_STAT_INT        REG8_VAL(0x06)
#define LH77790A_UART_RX_HOLDING_INT          REG8_VAL(0x04)
#define LH77790A_UART_TX_HOLDING_INT          REG8_VAL(0x02)
#define LH77790A_UART_MODEM_STAT_INT          REG8_VAL(0x00)

/*
 * Sharp LH77790A UART Line Control Register Bit fields
 */
#define LH77790A_UART_DATABITS_STOPBITS_MASK  REG8_VAL(0x07)
#define LH77790A_UART_DATABITS_5_STOPBITS_1   REG8_VAL(0x00)
#define LH77790A_UART_DATABITS_6_STOPBITS_1   REG8_VAL(0x01)
#define LH77790A_UART_DATABITS_7_STOPBITS_1   REG8_VAL(0x02)
#define LH77790A_UART_DATABITS_8_STOPBITS_1   REG8_VAL(0x03)
#define LH77790A_UART_DATABITS_5_STOPBITS_1_5 REG8_VAL(0x04)
#define LH77790A_UART_DATABITS_6_STOPBITS_2   REG8_VAL(0x05)
#define LH77790A_UART_DATABITS_7_STOPBITS_2   REG8_VAL(0x06)
#define LH77790A_UART_DATABITS_8_STOPBITS_2   REG8_VAL(0x07)
#define LH77790A_UART_PARITY_DISABLE          REG8_VAL(0x00)
#define LH77790A_UART_PARITY_ENABLE           REG8_VAL(0x08)
#define LH77790A_UART_PARITY_MODE_MASK        REG8_VAL(0x30)
#define LH77790A_UART_PARITY_ODD              REG8_VAL(0x00)
#define LH77790A_UART_PARITY_EVEN             REG8_VAL(0x10)
#define LH77790A_UART_PARITY_FORCE_1          REG8_VAL(0x20)
#define LH77790A_UART_PARITY_FORCE_0          REG8_VAL(0x30)
#define LH77790A_UART_CLEAR_BREAK             REG8_VAL(0x00)
#define LH77790A_UART_SET_BREAK               REG8_VAL(0x40)
#define LH77790A_UART_DIVISOR_LATCH_ENABLE    REG8_VAL(0x80)

/*
 * Sharp LH77790A UART Modem Control Register Bit fields
 */
#define LH77790A_UART_DTR_FORCE_HIGH          REG8_VAL(0x00)
#define LH77790A_UART_DTR_FORCE_LOW           REG8_VAL(0x01)
#define LH77790A_UART_RTS_FORCE_HIGH          REG8_VAL(0x00)
#define LH77790A_UART_RTS_FORCE_LOW           REG8_VAL(0x02)
#define LH77790A_UART_OUT1_FORCE_HIGH         REG8_VAL(0x00)
#define LH77790A_UART_OUT1_FORCE_LOW          REG8_VAL(0x04)
#define LH77790A_UART_OUT2_FORCE_HIGH         REG8_VAL(0x00)
#define LH77790A_UART_OUT2_FORCE_LOW          REG8_VAL(0x08)
#define LH77790A_UART_NORMAL_MODE             REG8_VAL(0x00)
#define LH77790A_UART_LOOPBACK_MODE           REG8_VAL(0x10)

/*
 * Sharp LH77790A UART Line Status Register Bit fields
 */
#define LH77790A_UART_RX_DATA_READY           REG8_VAL(0x01)
#define LH77790A_UART_OVERRUN_ERROR           REG8_VAL(0x02)
#define LH77790A_UART_PARITY_ERROR            REG8_VAL(0x04)
#define LH77790A_UART_FRAMING_ERROR           REG8_VAL(0x08)
#define LH77790A_UART_BREAK_INTERRUPT         REG8_VAL(0x10)
#define LH77790A_UART_TX_HOLDING_EMPTY        REG8_VAL(0x20)
#define LH77790A_UART_TX_EMPTY                REG8_VAL(0x40)

/*
 * Sharp LH77790A UART Modem Status Register Bit fields
 */
#define LH77790A_UART_DELTA_CTS               REG8_VAL(0x01)
#define LH77790A_UART_DELTA_DSR               REG8_VAL(0x02)
#define LH77790A_UART_DELTA_RI                REG8_VAL(0x04)
#define LH77790A_UART_DELTA_CD                REG8_VAL(0x08)
#define LH77790A_UART_CTS                     REG8_VAL(0x10)
#define LH77790A_UART_DSR                     REG8_VAL(0x20)
#define LH77790A_UART_RI                      REG8_VAL(0x40)
#define LH77790A_UART_DCD                     REG8_VAL(0x80)


/*
 * Sharp LH77790A Programmable Peripheral Interface Register Definitions
 */
#define	LH77790A_PPI_BASE                     0xFFFF1C00
#define LH77790A_PORT_A                       REG8_PTR(LH77790A_PPI_BASE + 0x00)
#define LH77790A_PORT_B                       REG8_PTR(LH77790A_PPI_BASE + 0x04)
#define LH77790A_PORT_C                       REG8_PTR(LH77790A_PPI_BASE + 0x08)
#define LH77790A_PORT_CONTROL_REGISTER        REG8_PTR(LH77790A_PPI_BASE + 0x0C)

/*
 * Sharp LH77790A Parallel Port Bit Field Definitions
 */
#define LH77790A_PORT_CTL_SET_RESET_PORT_C    REG8_VAL(0x0 << 7)
#define LH77790A_PORT_CTL_MODE_SELECTION      REG8_VAL(0x1 << 7)
#define LH77790A_PORT_A_MODE_0                REG8_VAL(0x0 << 5)
#define LH77790A_PORT_A_MODE_1                REG8_VAL(0x1 << 5)
#define LH77790A_PORT_A_MODE_2                REG8_VAL(0x2 << 5)
#define LH77790A_PORT_A_DIRECTION_OUTPUT      REG8_VAL(0x0 << 4)
#define LH77790A_PORT_A_DIRECTION_INPUT       REG8_VAL(0x1 << 4)
#define LH77790A_PORT_C_4_7_DIRECTION_OUTPUT  REG8_VAL(0x0 << 3)
#define LH77790A_PORT_C_4_7_DIRECTION_INPUT   REG8_VAL(0x1 << 3)
#define LH77790A_PORT_B_MODE_0                REG8_VAL(0x0 << 2)
#define LH77790A_PORT_B_MODE_1                REG8_VAL(0x1 << 2)
#define LH77790A_PORT_B_DIRECTION_OUTPUT      REG8_VAL(0x0 << 1)
#define LH77790A_PORT_B_DIRECTION_INPUT       REG8_VAL(0x1 << 1)
#define LH77790A_PORT_C_0_3_DIRECTION_OUTPUT  REG8_VAL(0x0 << 0)
#define LH77790A_PORT_C_0_3_DIRECTION_INPUT   REG8_VAL(0x1 << 0)
#define LH77790A_PORT_C_RESET_BIT             REG8_VAL(0x0 << 0)
#define LH77790A_PORT_C_SET_BIT               REG8_VAL(0x1 << 0)
#define LH77790A_PORT_C_BIT_0                 REG8_VAL(0x0 << 1)
#define LH77790A_PORT_C_BIT_1                 REG8_VAL(0x1 << 1)
#define LH77790A_PORT_C_BIT_2                 REG8_VAL(0x2 << 1)
#define LH77790A_PORT_C_BIT_3                 REG8_VAL(0x3 << 1)
#define LH77790A_PORT_C_BIT_4                 REG8_VAL(0x4 << 1)
#define LH77790A_PORT_C_BIT_5                 REG8_VAL(0x5 << 1)
#define LH77790A_PORT_C_BIT_6                 REG8_VAL(0x6 << 1)
#define LH77790A_PORT_C_BIT_7                 REG8_VAL(0x7 << 1)

#endif /* __LH77790A_H__ */
