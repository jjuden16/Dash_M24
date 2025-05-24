#include <Arduino.h>
#include <FlexCAN_T4.h>
#include "const.h"

//LED Backpack
#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_7segment matrix = Adafruit_7segment();

void setup() {
  Wire2.begin();
#ifndef __AVR_ATtiny85__
  Serial.begin(9600);
  Serial.println("7 Segment Backpack Test");
#endif
  matrix.begin(0x70, &Wire2);
  digitalWrite(LED_2, HIGH);
}

void loop() {
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

/*
// Use can1 for pins 20 (TX) and 21 (RX)
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;
CAN_message_t msg;

void setup() {
  Serial.begin(9600);
  while (!Serial);  // Wait for Serial monitor

  can1.begin();
  can1.setBaudRate(250000);  // Set CAN baud rate to 500 kbps

}

void loop() {



  digitalWrite(LED_1, HIGH);
  delay(500);
  digitalWrite(LED_1, LOW);
  Serial.println("LED 1");


  digitalWrite(LED_2, HIGH);
  delay(500);
  digitalWrite(LED_2, LOW);

  digitalWrite(LED_3, HIGH);
  delay(500);
  digitalWrite(LED_3, LOW);

  digitalWrite(LED_4, HIGH);
  delay(500);
  digitalWrite(LED_4, LOW);

  digitalWrite(LED_5, HIGH);
  delay(500);
  digitalWrite(LED_5, LOW);

  digitalWrite(LED_6, HIGH);
  delay(500);
  digitalWrite(LED_6, LOW);
}

*/

