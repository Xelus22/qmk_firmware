# RGB_MATRIX_CUSTOM_KB = yes
FLASH_DRIVER = spi
CUSTOM_MATRIX = lite
# OPT = 2

SRC += matrix.c
SRC += adc.c
SRC += lib/analogModes.c
SRC += lib/analogConfig.c
SRC += lib/calibration.c
