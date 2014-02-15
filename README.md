coroutine.h
===========

Simple coroutine library for tiny devices.

Uses [Label as Values](http://gcc.gnu.org/onlinedocs/gcc/Labels-as-Values.html) extension.

Based on [ProtoThreads](http://dunkels.com/adam/pt/) made by Adam Dunkels

Arduino IDE
-----------

Because Arduino IDE does not support C++11 so `CORO_Begin`, `CORO_Method` and `CORO_End` are not supported.

###### Function example

```
#include <coroutine.h>

int led = 13;

void blink() {
  CORO_StartStatic

  static long time = 0;

  time = millis();

  digitalWrite(led, HIGH);
  yieldUntil(millis() > time+1000);
  
  digitalWrite(led, LOW);
  yieldUntil(millis() > time+2000);
  
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

```
#include <coroutine.h>

int led = 13;

class Blink : coroutine {
public:
  int time;

  Blink() : time(0) {}

  void operator()() {
    CORO_Start

    time = millis();

    digitalWrite(led, HIGH);
    yieldUntil(millis() > time+1000);
  
    digitalWrite(led, LOW);
    yieldUntil(millis() > time+2000);
  
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

```
$ cd ~/Documents/Arduino/libraries/
$ git clone https://github.com/parkerkane/coroutine.h.git coroutine
```

###### Linux
TODO

###### Windows
TODO
