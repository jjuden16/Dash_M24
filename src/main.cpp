#include <Arduino.h>
#include <FlexCAN_T4.h>
#include "constants.h"
#include "can_ids.h"
#include "can_bus.h"

/* LED Backpack */ 
#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

/**** Global Objects ****/
Adafruit_7segment matrix = Adafruit_7segment();
Can_Bus bus; 

void setup() {
  Wire2.begin();
  bus.setup();

#ifndef __AVR_ATtiny85__
  Serial.begin(9600);
  Serial.println("7 Segment Backpack Test");
#endif
  matrix.begin(0x70, &Wire2);
  digitalWrite(LED_2, HIGH);

}

void loop() {

  float filtered_secondary_rpm = bus.msg_values.at(CAN_FILTERED_SECONDARY_RPM);
  float wheel_mph = filtered_secondary_rpm * WHEEL_TO_SECONDARY_RATIO * WHEEL_MPH_PER_RPM; 

  // try to print a number thats too long
  matrix.print(10000, DEC);
  matrix.writeDisplay();
  delay(500);

  // print a hex number
  matrix.print(0xBEEF, HEX);
  matrix.writeDisplay();
  delay(500);

  // print a floating point 
  matrix.print(12.34);
  matrix.writeDisplay();
  delay(500);

  // print a string message
  matrix.print("7SEG");
  matrix.writeDisplay();
  delay(10000);
  
  // print with print/println
  for (uint16_t counter = 0; counter < 9999; counter++) {
    matrix.println(counter);
    matrix.writeDisplay();
    delay(10);
  }

  // method #2 - draw each digit
  uint16_t blinkcounter = 0;
  boolean drawDots = false;
  for (uint16_t counter = 0; counter < 9999; counter ++) {
    matrix.writeDigitNum(0, (counter / 1000), drawDots);
    matrix.writeDigitNum(1, (counter / 100) % 10, drawDots);
    matrix.drawColon(drawDots);
    matrix.writeDigitNum(3, (counter / 10) % 10, drawDots);
    matrix.writeDigitNum(4, counter % 10, drawDots);
   
    blinkcounter+=50;
    if (blinkcounter < 500) {
      drawDots = false;
    } else if (blinkcounter < 1000) {
      drawDots = true;
    } else {
      blinkcounter = 0;
    }
    matrix.writeDisplay();
    delay(10);
  }
}