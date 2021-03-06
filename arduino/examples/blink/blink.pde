/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
#include <coroutine.h>
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;


void blink() {
  CORO_Simple();

  static long time = 0;

  while(true) {
    time = millis();

    digitalWrite(led, HIGH);
    yieldUntil(millis() > time+1000);
    
    digitalWrite(led, LOW);
    yieldUntil(millis() > time+2000);
  }
}

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {  
  blink();
}