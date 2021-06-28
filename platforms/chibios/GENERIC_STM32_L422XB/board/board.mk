# List of all the board related files.
BOARDSRC = $(CHIBIOS)/os/hal/boards/ELGO422_L422KB/board.c

# Required include directories
BOARDINC = $(CHIBIOS)/os/hal/boards/ELGO422_L422KB

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)
