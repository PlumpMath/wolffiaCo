#include <wolffia.h>

//////////////////////////////////////////////////////////////////
// Setup wollfia tasks

#define WO_TASK1 blinker()

//////////////////////////////////////////////////////////////////
// Events
//
// Uses default settings:
// 32 events in buffer, 6bit event ID and 2bit data

enum {
    // High priority events
    setupEvent,
  
    EVENT_PRIORITY_MARKER,
    
    // Normal priority events
    blinkOnEvent,
    blinkOffEvent,
};

#define WO_LISTENER1 setupEvent: setupListener(event, data)

#define WO_LISTENER2 blinkOnEvent: blinkOnListener(event, data)
#define WO_LISTENER3 blinkOffEvent: blinkOffListener(event, data)

//////////////////////////////////////////////////////////////////
// Initialize wolffia

#include <wolffia-init.h>

//////////////////////////////////////////////////////////////////
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

void setupListener(uint8_t event, uint8_t data) {
  pinMode(led, OUTPUT); 
}

void blinkOnListener(uint8_t event, uint8_t data) {
  digitalWrite(led, HIGH);
}

void blinkOffListener(uint8_t event, uint8_t data) {
  digitalWrite(led, LOW);
}

void blinker() {
  WO_InitTask();
  
  static long time;
  
  while(true) {
    time = millis();
 
    dispatchEvent(blinkOnEvent, 0);   
    yieldUntil(millis() > time+1000);

    dispatchEvent(blinkOffEvent, 0);   
    yieldUntil(millis() > time+2000);
  }
}

void setup() {
  dispatchEvent(setupEvent, 0);  
}

void loop() {
  
  WO_Run(EVENT_PRIORITY_MARKER);
  
}
