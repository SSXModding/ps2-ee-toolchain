SCRIPT_NAME=elf
OUTPUT_FORMAT="elf32-littlemips"
BIG_OUTPUT_FORMAT="elf32-bigmips"
LITTLE_OUTPUT_FORMAT="elf32-littlemips"
TEXT_START_ADDR=0xa0020000
MAXPAGESIZE=0x40000
INITIAL_READONLY_SECTIONS='.reginfo : { *(.reginfo) }'
OTHER_TEXT_SECTIONS='*(.mips16.fn.*) *(.mips16.call.*)'
OTHER_GOT_SYMBOLS='
  _gp = ALIGN(16) + 0x7ff0;
'
OTHER_GOT_SECTIONS='
  .lit8 : { *(.lit8) }
  .lit4 : { *(.lit4) }
'
TEXT_START_SYMBOLS='_ftext = . ;'
DATA_START_SYMBOLS='_fdata = . ;'
OTHER_BSS_SYMBOLS='_fbss = .;'
EXECUTABLE_SYMBOLS='_DYNAMIC_LINK = 0;'
OTHER_SECTIONS='
  .gptab.sdata : { *(.gptab.data) *(.gptab.sdata) }
  .gptab.sbss : { *(.gptab.bss) *(.gptab.sbss) }
'
ARCH="mips:5900"
MACHINE=
TEMPLATE_NAME=elf32
GENERATE_SHLIB_SCRIPT=yes
DYNAMIC_LINK=false
EMBEDDED=yes
