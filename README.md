coroutine.h
===========

Simple coroutine library for tiny devices.

Uses [Label as Values](http://gcc.gnu.org/onlinedocs/gcc/Labels-as-Values.html) extension.

Based on [ProtoThreads](http://dunkels.com/adam/pt/) made by Adam Dunkels

Arduino IDE
-----------

Because Arduino IDE does not support C++11 only `CORO_StartStatic`, `CORO_Finish`, `yield`, `yieldWhile`, `yieldUntil` and `finnish` are supported.

###### Example

```
void blink() {
  CORO_StartStatic

  static long time = 0;

  time = millis();

  digitalWrite(led, HIGH);
  yieldUntil(millis() > time+10);
  
  digitalWrite(led, LOW);
  yieldUntil(millis() > time+2000);
  
  CORO_Finish
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