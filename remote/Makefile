.PHONY: all

all:
	arduino-cli compile -b arduino:avr:uno

term: up
	TERM=linux minicom -D /dev/ttyUSB0

up: all
	arduino-cli upload -b arduino:avr:uno -p /dev/ttyUSB0
