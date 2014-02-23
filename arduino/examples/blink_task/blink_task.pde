#include <wolffia.h>

//////////////////////////////////////////////////////////////////
// Setup wollfia tasks
//
// Tasks are called all the time in a loop

#define WO_TASK1 blinker()

//////////////////////////////////////////////////////////////////
// Events
//
// Event listeners are only called when you dispatch an event
//
// Uses default settings:
// 32 events in buffer, 4bit event ID and 4bit data

enum {
    // High priority events
    setupEvent,
  
    EVENT_PRIORITY_MARKER,
    
    // Normal priority events
    blinkOnEvent,
    blinkOffEvent,
};

#define WO_LISTENER1 setupEvent: setupListener(event, data)

#define WO_LISTENER2 blinkOnEvent: blinkOnListener() // event and data are optionals
#define WO_LISTENER3 blinkOffEvent: blinkOffListener()

//////////////////////////////////////////////////////////////////
// Initialize wolffia

#include <wolffia-init.h>

//////////////////////////////////////////////////////////////////
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

void setupListener(uint8_t event, uint8_t data) {
  // Event data tells which we use
  pinMode(led, data); 
}

void blinkOnListener() {
  digitalWrite(led, HIGH);
}

void blinkOffListener() {
  digitalWrite(led, LOW);
}

void blinker() {
  // Initialize wolffia task, here we check last known state
  // and jump back there
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
  // Dispatch setupEvent with OUTPUT as data for listener
  dispatchEvent(setupEvent, OUTPUT);  
}

void loop() {
  // Run the main loop
  WO_Start(EVENT_PRIORITY_MARKER);
}
