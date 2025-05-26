#include <Arduino.h>
#include <FlexCAN_T4.h>
#include "constants.h"
#include "can_ids.h"
#include "can_bus.h"

/* LED Backpack */ 
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

/**** Global Objects ****/
Adafruit_7segment matrix = Adafruit_7segment();
Can_Bus bus; 

/* Display functions */
void longPrint(String out);

void setup() {
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);

  Wire2.begin();
  bus.setup();

#ifndef __AVR_ATtiny85__
  Serial.begin(9600);
  Serial.println("7 Segment Backpack Test");
#endif
  matrix.begin(0x70, &Wire2); //7-SEG connected to Wire 2
  digitalWrite(LED_2, HIGH);
}

void loop() {

  float filtered_secondary_rpm = bus.msg_values.at(CAN_FILTERED_SECONDARY_RPM);
  float wheel_mph = filtered_secondary_rpm * WHEEL_TO_SECONDARY_RATIO * WHEEL_MPH_PER_RPM; 
}

/* Display Functions */
void longPrint(String out)
{
  int l = out.length();
  for(int i = 0; i <= (l-3); i++)
  {
    String print = out.substring(i,i+4);
    matrix.println(print);
    matrix.writeDisplay();
    delay(500);
  }
  for(int i = l-3; i <= l; i++)
  {
    String print = out.substring(i,l+1);
    print = print + "    ";
    matrix.println(print);
    matrix.writeDisplay();
    delay(500);
  }
 
  delay(1000);
}