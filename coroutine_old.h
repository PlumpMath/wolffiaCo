//
//  coroutine.h
//  coroutine
//
//  Created by Timo Reunanen on 15/02/2014.
//  Copyright (c) 2014 Timo Reunanen. All rights reserved.
//

#ifndef coroutine_coroutine_h
#define coroutine_coroutine_h

#include <stddef.h>

#define CORO_FLAG_FREEZE    0x01
#define CORO_FLAG_RESET     0x02

#define __coConcat(a,b) __coConcat2(a,b)
#define __coConcat2(a,b) a##b

#define __coLabelize() __coConcat(__coLabel, __LINE__)

#define __coResumePosition() if (__coState != NULL) { goto *__coState; }
#define __coLabelPosition() __coLabelize():
#define __coSavePosition() __coState = &&__coLabelize()
#define __coResetPosition() __coState = NULL;

#define __coClassName(name) __coConcat(__co_class_, name)

#define CORO_Start\
    static void * __coState = NULL;\
    __coResumePosition();\
    __coSavePosition();\
    __coLabelPosition();

#define CORO_StartEx(controller, ret...)\
    static void * __coState = NULL;\
    if (controller & CORO_FLAG_FREEZE) return ret;\
    if (controller & CORO_FLAG_RESET) {\
        __coState = NULL;\
        controller &= ~CORO_FLAG_RESET;\
    }\
    __coResumePosition();\
    __coSavePosition();\
    __coLabelPosition();

#define CORO_Finish __coResetPosition();

#if __cplusplus >= 201103L

// These requires C++11

#define CORO_Begin(name) class __coClassName(name) { public:
#define CORO_Method(ret, args...) ret operator()(args) { CORO_Start;
#define CORO_End(name, copies...) CORO_Finish; } }; __coClassName(name) name, ##copies;

#define CORO_BeginClass(className) class className { public:
#define CORO_EndClass() CORO_Finish; } };

#endif

#define finish(val) do { __coResetPosition(); return val; } while(0)
#define yield(val) do { __coSavePosition(); return val; __coLabelPosition(); } while(0)

#define yieldWhile(cond, ret...) do {__coSavePosition(); __coLabelPosition(); if(cond) return ret;} while(0)
#define yieldUntil(cond, ret...) yieldWhile(!(cond), ret)

///////////////////////////////////////////////////////////////////////////////////////////
// Locks

#define LOCK_1  0x0001
#define LOCK_2  0x0002
#define LOCK_3  0x0004
#define LOCK_4  0x0008
#define LOCK_5  0x0010
#define LOCK_6  0x0020
#define LOCK_7  0x0040
#define LOCK_8  0x0080
#define LOCK_9  0x0100
#define LOCK_10 0x0200
#define LOCK_11 0x0400
#define LOCK_12 0x0800
#define LOCK_13 0x1000
#define LOCK_14 0x2000
#define LOCK_15 0x4000
#define LOCK_16 0x8000

bool lockAcquire(unsigned short id);
void lockRelease(unsigned short id);
bool lockTest(unsigned short id);

#define lockWaitAndAcquire(id, ret...) yieldUntil(lockAcquire(id), ##ret)
#define lockWait(id, ret...) yieldWhile(lockTest(id), ##ret)

#endif