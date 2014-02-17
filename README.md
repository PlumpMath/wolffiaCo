wolffiaCo
=========

wolffiaCo is simple coroutine based aka non preemptive task scheduler library for tiny devices e.g. Attiny85.

Based on [ProtoThreads](http://dunkels.com/adam/pt/) by Adam Dunkels and uses [Label as Values](http://gcc.gnu.org/onlinedocs/gcc/Labels-as-Values.html) extension. 

Arduino IDE
-----------

###### Function example

```C
#include <coroutine.h>

int led = 13;

void blink() {
  CORO_Start

  static long time = 0;

  time = millis();

  while(true) {
    digitalWrite(led, HIGH);
    yieldUntil(millis() > time+1000);
  
    digitalWrite(led, LOW);
    yieldUntil(millis() > time+2000);
  }
  
  CORO_Finish
}

void setup() {                
  pinMode(led, OUTPUT);     
}

void loop() {  
  blink();
}
```

###### Class example

```C++
#include <coroutine.h>

int led = 13;

class Blink {
public:
  int time;

  Blink() : time(0) {}

  void operator()() {
    CORO_Start

    time = millis();

    while(true) {
      digitalWrite(led, HIGH);
      yieldUntil(millis() > time+1000);
  
      digitalWrite(led, LOW);
      yieldUntil(millis() > time+2000);
    }
  
    CORO_Finish
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

### Installation

###### OS X

```bash
$ cd ~/Documents/Arduino/libraries/
$ git clone https://github.com/parkerkane/coroutine.h.git coroutine
```

###### Linux
TODO

###### Windows
TODO
