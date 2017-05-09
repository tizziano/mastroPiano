# Arduino-Makefile template. Refer to https://github.com/sudar/Arduino-Makefile
#
#  Copyright 2016 tiziano <tiziano.detogni@gmail.com>
#
#  rev. 10.jul.2016
#
#  Un file make personalizzato per compilare "progetti" con l'ambiente 
#  di sviluppo Arduino. Utilizza il make sudar.
#
#
#  Progetto: 
#
# directory make di sistema
MAKE_DIR=$(HOME)/.local/lib/arduino_mk-151
MAKE_FILE=Arduino.mk
#
# Anche se non usi la liberia arduino, indica comunque dove si troverebbe l'IDE
ARDUINO_DIR = $(HOME)/.local/share/arduino-1.6.4

# su xubuntu 16.04 il compilatore gcc-avr è più aggiornato (4.9.2)
AVR_TOOLS_DIR =/usr
# in automatico troverebbe /usr/etc/avrdude.conf !!!
AVRDUDE_CONF=/etc/avrdude.conf
#
# compila tutto nella directory /tmp
OBJDIR = /tmp/build-$(BOARD_TAG)
#
# project specific file
#
include $(MAKE_DIR)/boards/ArduinoNano-328.mk
#
include $(MAKE_DIR)/$(MAKE_FILE)
