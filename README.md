#### Experiemental project

For now it's only recommended to test this project because newer version/commit might easily broke your code.

wolffiaCo
=========

Simple stackless coroutine based non preemptive task scheduler for tiny devices e.g. [Atmel's Attiny](http://www.atmel.com/products/microcontrollers/avr/tinyavr.aspx) family.

wolffiaCo name comes from [wolffia](http://en.wikipedia.org/wiki/Wolffia) which is genus which includes smallest flowering plants on Earth.

Based on [ProtoThreads](http://dunkels.com/adam/pt/) by Adam Dunkels and uses [Label as Values](http://gcc.gnu.org/onlinedocs/gcc/Labels-as-Values.html) extension. 

### Installation

1. Get latests [release](https://github.com/parkerkane/wolffiaCo/raw/master/arduino/wolffiaCo.zip) or bleeding edge [develop release](https://github.com/parkerkane/wolffiaCo/raw/develop/arduino/wolffiaCo.zip)
2. In Arduino go `Sketch > Import library... > Add library...`
3. Locate `wolffiaCo.zip`
4. Test run with `File > Examples > wolffiaCo > blink` example

More information about installing libraries can found from Arduino's [websites](http://arduino.cc/en/Guide/Libraries) or from [Adafruit](http://learn.adafruit.com/adafruit-all-about-arduino-libraries-install-use).

Arduino
-------

Because everybody loves blinking leds, here is few examples how to use this library.

###### Task example

```C
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
```

###### Function example

```C
#include <coroutine.h>

int led = 13;

void blink() {
  CORO_Simple();

  static long time = 0;

  time = millis();

  while(true) {
    digitalWrite(led, HIGH);
    yieldUntil(millis() > time+1000);
  
    digitalWrite(led, LOW);
    yieldUntil(millis() > time+2000);
  }
}

void setup() {                
  pinMode(led, OUTPUT);     
}

void loop() {  
  blink();
}
```

###### Class example

```Cpp
#include <coroutine.h>

int led = 13;

class Blink {
public:
  int time;

  Blink() : time(0) {}

  CORO_Define(Blink);
  void operator()() {
    CORO_Init(Blink);

    time = millis();

    while(true) {
      digitalWrite(led, HIGH);
      yieldUntil(millis() > time+1000);
  
      digitalWrite(led, LOW);
      yieldUntil(millis() > time+2000);
    }
  }
};
Blink blink;

void setup() {                
  pinMode(led, OUTPUT);     
}

void loop() {  
  blink();
}
```

###### Locks example
```C
#include <coroutine.h>
 
int led = 13;

#define onLock  LOCK_1
#define offLock LOCK_2

void blink() {
  CORO_Simple();

  static long time = 0;

  while(true) {
    time=millis();
    
    lockRelease(onLock);
    yieldUntil(millis() > time+1000);
    
    lockRelease(offLock);
    yieldUntil(millis() > time+2000);
  }
}

void blinkOn() {
  CORO_Simple();
  
  while(true) {
    lockWaitAndAcquire(onLock);

    digitalWrite(led, HIGH);
  }
}

void blinkOff() {
  CORO_Simple();
  
  while(true) {
    lockWaitAndAcquire(offLock);
    
    digitalWrite(led, LOW);
  }
}

void setup() {                
  pinMode(led, OUTPUT);    
 
  lockAcquire(onLock); 
  lockAcquire(offLock); 
}

// the loop routine runs over and over again forever:
void loop() {  
  blink();
  blinkOn();
  blinkOff();
}
```
