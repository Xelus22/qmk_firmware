# RGB_MATRIX_CUSTOM_KB = yes
FLASH_DRIVER = spi
CUSTOM_MATRIX = lite
OPT_DEFS += -Ofast -ffast-math -funroll-loops

SRC += matrix.c
SRC += adc.c

VIA_ENABLE = yes

MCUFLAGS += -march=armv7e-m \
           -mcpu=cortex-m4 \
           -mfloat-abi=hard \
           -mfpu=fpv4-sp-d16 \
           -mabi=aapcs \
           -mcmodel=small \
           -mstrict-align
