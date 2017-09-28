/* Originally posted on www.bbangpan.com
Program Description: 433/315Mhz transmitter(FS1000A or XY-FS) test code

Needed library : VirtualWire http://www.airspayce.com/mikem/arduino/VirtualWire/index.html

DataPin : 12 to 433/315Mhz transmitter DATA(near GND)

Tested on : Arduino 1.0.6, Arduino UNO R3, VirtualWire

Inspired by http://www.buildcircuit.com/how-to-use-rf-module-with-arduino/

Copyright (c) 2015 www.bbangpan.com. All rights reserved.

This program can be used for any non-commercial purpose freely. */

#include <VirtualWire.h>
#include "VirtualWire_Config.h"

const int TX_DIO_Pin = 12; // default 12
int index = 0;

void setup(){
  Serial.begin(9600);
  Serial.println("Ready to transmit messages!");
  vw_set_tx_pin(TX_DIO_Pin); // Initialize TX pin
  vw_setup(2000); // Transfer speed : 2000 bits per sec
}

int num = 0;
char message[100];

void loop(){
  itoa(num, message, 10);
  send(message);
//  send(num);
  Serial.println(num);
  num++;

  if(num > 99) {
    num = 0;
  }
  
  delay(1000);
}

void send (char *message){
  digitalWrite(13, true); // LED ON
  vw_send((uint8_t *)message, sizeof(message));
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(13, false); // LED OFF
}
