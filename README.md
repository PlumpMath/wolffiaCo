wolffiaCo
=========

Simple stackless coroutine based non preemptive task scheduler library for tiny devices e.g. [Atmel's Attiny](http://www.atmel.com/products/microcontrollers/avr/tinyavr.aspx) family.

wolffiaCo name comes from [wolffia](http://en.wikipedia.org/wiki/Wolffia) which is genus which includes smallest flowering plants on Earth.

Based on [ProtoThreads](http://dunkels.com/adam/pt/) by Adam Dunkels and uses [Label as Values](http://gcc.gnu.org/onlinedocs/gcc/Labels-as-Values.html) extension. 

### Installation

###### OS X

```bash
$ cd ~/Documents/Arduino/libraries/
$ git clone https://github.com/parkerkane/wolffiaCo.git
```

###### Linux
TODO

###### Windows

```
$ cd "My Documents\Arduino\libraries"
$ git clone https://github.com/parkerkane/wolffiaCo.git
```

More information about installing libraries can found from Arduino's [websites](http://arduino.cc/en/Guide/Libraries) or from [Adafruit](http://learn.adafruit.com/adafruit-all-about-arduino-libraries-install-use).



Arduino IDE
-----------

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
