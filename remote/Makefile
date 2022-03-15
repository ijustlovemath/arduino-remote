.PHONY: all

all:
	arduino-cli compile -b arduino:avr:uno

up: all
	arduino-cli upload -b arduino:avr:uno -p /dev/ttyUSB0
