#include <wolffia.h>

//////////////////////////////////////////////////////////////////
// Setup wollfia tasks
//
// Tasks are called all the time in a loop

#define WO_TASK1 blinker()

// Because we need to update coroutines state, we need send bogus event for listener
#define WO_TASK2 blinkListener(ignoreMe)

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
    blinkEvent,
    blinkOnEvent,
    blinkOffEvent,
    
    ignoreMe, // Like name says.. Just ignore it :)
};

#define WO_LISTENER1 setupEvent: setupListener(event, data)

#define WO_LISTENER2 blinkEvent: blinkListener(event) // We only need event id not data
#define WO_LISTENER3 blinkOnEvent: blinkOnListener() // Event and data are optionals
#define WO_LISTENER4 blinkOffEvent: blinkOffListener()

//////////////////////////////////////////////////////////////////
// Initialize wolffia

#include <wolffia-init.h>

//////////////////////////////////////////////////////////////////
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

void setupListener(uint8_t event, uint8_t data) {
  pinMode(led, data); 
}

void blinkListener(uint8_t event) {
  WO_InitTask();
  
  static long time;
  
  while(true) {
    yieldUntil(event == blinkEvent);
    
    time = millis() + 1000;    

    dispatchEvent(blinkOnEvent, 0);   
    
    yieldUntil(millis() > time);
    
    dispatchEvent(blinkOffEvent, 0);   
  }
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
    time = millis() + 2000;
 
    dispatchEvent(blinkEvent, 0);

    yieldUntil(millis() > time);    
  }
}

void setup() {
  dispatchEvent(setupEvent, OUTPUT);  
}

void loop() {
  
  WO_Run(EVENT_PRIORITY_MARKER);
  
}
