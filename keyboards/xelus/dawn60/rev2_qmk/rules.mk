# MCU name
MCU = STM32L433

# Bootloader selection
BOOTLOADER = stm32-dfu

# Do not put the microcontroller into power saving mode
# when we get USB suspend event. We want it to keep updating
# backlight effects.
# OPT_DEFS += -DNO_SUSPEND_POWER_DOWN

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes        # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = yes           # USB Nkey Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output
FAUXCLICKY_ENABLE = no      # Use buzzer to emulate clicky switches
RGBLIGHT_ENABLE = yes       # Enable WS2812 RGB underlight. - We have custom RGB underglow
WS2812_DRIVER = spi

# EEPROM_DRIVER = i2c

# RGB_MATRIX_ENABLE = yes     # Enable RGB matrix effects.
# RGB_MATRIX_DRIVER = custom  # Enable RGB matrix effects.
# RGB_MATRIX_CUSTOM_KB = yes

# COMMON_VPATH += $(DRIVER_PATH)/issi

# # project specific files
# SRC +=  drivers/led/issi/is31fl3731.c \
#         ws2812.c

# QUANTUM_LIB_SRC += i2c_master.c

