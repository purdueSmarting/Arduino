#include <VirtualWire.h>
#include "VirtualWire_Config.h"

const int TX_DIO_Pin = 12; // default 12
const int TX_UV_OUTPUT_Pin = 2; // UV sensor Trig pin
const int TX_UV_INPUT_Pin = 3; // UV sensor Echo pin

void setup(){
  Serial.begin(9600);
  Serial.println("Ready to transmit messages!");

  // UV Sensor
  pinMode(TX_UV_OUTPUT_Pin, OUTPUT);
  pinMode(TX_UV_INPUT_Pin, INPUT); 
  
  vw_set_tx_pin(TX_DIO_Pin); // Initialize TX pin
  vw_setup(2000); // Transfer speed : 2000 bits per sec
}

char message[100];

void loop(){
  long duration, cm;

  digitalWrite(2, HIGH); // Trig signal on
  delayMicroseconds(10); // 10us
  digitalWrite(2, LOW); // Trig signal off

  duration = pulseIn(3, HIGH);
  cm = microsecondsToCentimeters(duration);

  Serial.print(cm);
  Serial.println("cm");

  itoa(cm, message, 10); // important! : convert int to char
  send(message);
  
  delay(1000);
}

// send char data
void send (char *message){
  digitalWrite(13, true); // LED ON
  vw_send((uint8_t *)message, sizeof(message));
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(13, false); // LED OFF
}

// convert duration to centimeter
long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  
  return microseconds / 29 / 2;
} 
