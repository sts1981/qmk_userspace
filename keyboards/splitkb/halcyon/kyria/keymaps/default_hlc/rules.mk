ifdef HLC_TFT_DISPLAY
  SRC += display.c \
         graphics/arrow-all.qgf.c \
         graphics/keyboard.qgf.c \
         graphics/monitor.qgf.c \
         graphics/mouse.qgf.c \
         graphics/numeric.qgf.c \
         graphics/script-outline.qgf.c \
         graphics/symbol.qgf.c \
         graphics/tools.qgf.c \
endif

COMMAND_ENABLE = no
CONSOLE_ENABLE = no
MAGIC_ENABLE = no

BOOTMAGIC_ENABLE = yes
CAPS_WORD_ENABLE = yes
COMBO_ENABLE = yes
DYNAMIC_TAPPING_TERM_ENABLE = yes
ENCODER_MAP_ENABLE = yes
#LAYER_LOCK_ENABLE = yes
LEADER_ENABLE = yes
MOUSEKEY_ENABLE = yes
TAP_DANCE_ENABLE = yes

# This adds module functionality to your keyboard (files found in users/halcyon_modules)
USER_NAME := halcyon_modules
