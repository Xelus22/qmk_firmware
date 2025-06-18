# RGB_MATRIX_CUSTOM_KB = yes
FLASH_DRIVER = spi
CUSTOM_MATRIX = lite
OPT_DEFS += -Ofast -flto -ffast-math -funroll-loops \
            -fno-tree-vectorize -fno-signed-zeros -fno-math-errno \
            -fno-common -fomit-frame-pointer -falign-functions=16 \
            -falign-loops=16 -falign-jumps=16 -fno-exceptions -fno-unwind-tables
SRC += matrix.c
SRC += adc.c

VIA_ENABLE = yes
