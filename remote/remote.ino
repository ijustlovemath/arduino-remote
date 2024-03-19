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

#define STARTUP_INFO 1

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(115200);

#if STARTUP_INFO
    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));
#endif
    /*
     * The IR library setup. That's all!
     */
    IrSender.begin(); // Start with IR_SEND_PIN as send pin and if NO_LED_FEEDBACK_CODE is NOT defined, enable feedback LED at default feedback LED pin

#if STARTUP_INFO
    Serial.print(F("Ready to send IR signals at pin "));
    Serial.println(IR_SEND_PIN);
#endif
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
 * from here: https://www.remotecentral.com/cgi-bin/mboard/rc-discrete/thread.cgi?5478
 * Useful commands (format address,command):
 * 4,2 - Volume up
 * 4,3 - Volume down
 * 4,8 - Toggle power
 * 4,e - Set sleep timer
 * 4,ff - press enter
 * 4,43 - menu
 * 4,44 - ok
 * 4,45/46/47/48 - up/down/left/right
 * 4,49 - exit
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

#define CLEAR(buf_) memset((buf_), 0, sizeof((buf_)))

void loop() {

    while(!Serial.available());
    static char input[64];
    
    size_t charsRead = Serial.readBytesUntil('\n', input, 63);
    
    if(charsRead == 0) {
      Serial.println("[ERROR] timed out on serial read");
      return;
    }

    if(input[charsRead] != 0) {
      if (input[charsRead - 1] == '\n' || charsRead == 1) {
   //     Serial.println("[INFO] repeating last command...");
        goto run_command;
      } else {
        Serial.println("[ERROR] input too long and/or clobbered: " + String(input));
        goto clear_fail;
      }
    }

    if(isdigit(input[0])) {
      if(parseHexCommand(input, sizeof(input))) {
        goto clear_fail;
      }
      goto run_command;
    } else {
      // They're trying to send us a text command, see if we have it covered
      int found = 0;
      //Serial.println(String("processing command: ") + String(input));
      #define CASE(text_command, address, command) \
      if(!strncmp(input, text_command, strlen(text_command))) { \
        sAddress = address; \
        sCommand = command; \
        found = 1; \
      } \

      CASE("volume up", 0x4, 0x2)
      CASE("volume down", 0x4, 0x3)
      CASE("power", 0x4, 0x8)
      CASE("menu", 0x4, 0x43)
      CASE("ok", 0x4, 0x44)
      CASE("up", 0x4, 0x45)
      CASE("down", 0x4, 0x46)
      CASE("left", 0x4, 0x47)
      CASE("right", 0x4, 0x48)
      CASE("enter", 0x4, 0xff)
      CASE("exit", 0x4, 0x49)
      if(!found) {
        input[strlen(input) - 1] = 0;
        Serial.println(String("[ERROR] Unknown command: ") + String(input));

        // To prevent us clobbering the input buffer with prior inputs, clear it each time
        // Only clear it here so you can just hit enter to repeat last command
        goto clear_fail;
      }
      goto run_command;
      
    }
clear_fail:
    CLEAR(input);
    return;
    

run_command:
    Serial.println("[INFO] sending address " + String(sAddress) + " command " + String(sCommand));
    IrSender.sendNEC(sAddress, sCommand, sRepeats);

    delay(2 * RECORD_GAP_MICROS / 1000);  // delay must be greater than 5 ms (RECORD_GAP_MICROS), otherwise the receiver sees it as one long signal
}
