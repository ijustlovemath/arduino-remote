/*
 * SimpleSender.cpp
 *
 *  Demonstrates sending IR codes in standard format with address and command
 *  An extended example for sending can be found as SendDemo.
 *
 *  Copyright (C) 2020-2021  Armin Joachimsmeyer
 *  armin.joachimsmeyer@gmail.com
 *
 *  This file is part of Arduino-IRremote https://github.com/Arduino-IRremote/Arduino-IRremote.
 *
 *  MIT License
 */
#include <Arduino.h>

/*
 * Define macros for input and output pin etc.
 */
#include "PinDefinitionsAndMore.h"

//#define SEND_PWM_BY_TIMER
//#define USE_NO_SEND_PWM
//#define NO_LED_FEEDBACK_CODE // saves 418 bytes program space

#include <IRremote.hpp>

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(115200);

    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

    /*
     * The IR library setup. That's all!
     */
    IrSender.begin(); // Start with IR_SEND_PIN as send pin and if NO_LED_FEEDBACK_CODE is NOT defined, enable feedback LED at default feedback LED pin

    Serial.print(F("Ready to send IR signals at pin "));
    Serial.println(IR_SEND_PIN);
}

/*
 * Set up the data to be sent.
 * For most protocols, the data is build up with a constant 8 (or 16 byte) address
 * and a variable 8 bit command.
 * There are exceptions like Sony and Denon, which have 5 bit address.
 */
uint16_t sAddress = 0x04;
uint8_t sCommand = 0x2;
uint8_t sRepeats = 1;

/**
 * Useful commands (format address,command):
 * 4,2 - Volume up
 * 4,3 - Volume down
 * 4,8 - Toggle power
 */

int parseHexCommand(char *input, size_t input_size) {
    char *command = input;
    size_t i = 0;
    while(i++ < input_size && *command++ != ',');

    if(command[-1] != ',') {
      Serial.println("[ERROR] input malformatted, should be 'address,command'");
      return -1;
    }
    

    // Assume at this point they sent us a valid hex string...
    sAddress = (uint16_t) strtol(input, NULL, 16);
    sCommand = (uint8_t) strtol(command, NULL, 16);
    return 0;
}

void loop() {

    while(!Serial.available());
    static char input[64];
    size_t charsRead = Serial.readBytesUntil('\n', input, 63);
    
    if(charsRead == 0) {
      Serial.println("[ERROR] timed out on serial read");
      return;
    }

    if(input[charsRead] != 0) {
      Serial.println("[ERROR] input too long and/or clobbered");
      return;
    }

    if(isdigit(input[0])) {
      if(parseHexCommand(input, sizeof(input)))
        return;
    } else {
      // They're trying to send us a text command, see if we have it covered
      #define CASE(text_command, address, command) \
      if(!strcmp(input, text_command)) { \
        sAddress = address; \
        sCommand = command; \
      } \

      CASE("volume up", 0x4, 0x2)
      CASE("volume down", 0x4, 0x3)
      CASE("power", 0x4, 0x8)
      
    }
    // To prevent us clobbering the input buffer with prior inputs, clear it each time
    memset(input, 0, sizeof(input));
    
    Serial.println("[INFO] sending address " + String(sAddress) + " command " + String(sCommand));
    IrSender.sendNEC(sAddress, sCommand, sRepeats);

    delay(2 * RECORD_GAP_MICROS / 1000);  // delay must be greater than 5 ms (RECORD_GAP_MICROS), otherwise the receiver sees it as one long signal
}