//
//  coroutine.h
//  wolffiaCo
//
//  Created by Timo Reunanen on 17/02/2014.
//  Copyright (c) 2014 Timo Reunanen. All rights reserved.
//

#ifndef wolffiaCo_coroutine_h
#define wolffiaCo_coroutine_h

#if __cplusplus >= 201103L
#define __CPP11__
#endif

#include <stddef.h>

struct COROData {
    void *state;
    unsigned char flags;
};

#ifndef __CPP11__

class CORODataClass {
public:
    void *state;
    unsigned char flags;
    
    CORODataClass() : state(NULL), flags(0) {}
};

#endif

#define CORO_FLAG_SUSPEND   0x01
#define CORO_FLAG_RESET     0x02

#define __coConcat(a,b) __coConcat2(a,b)
#define __coConcat2(a,b) a##b

#define __coLabelize() __coConcat(__coLabel_, __LINE__)

#define __coName(name) __coConcat(__coVar_, name)

#define __coResumePosition() if (__coData->state != NULL) { goto *(__coData->state); }
#define __coLabelPosition() __coLabelize():
#define __coSavePosition() __coData->state = &&__coLabelize()

#ifdef __CPP11__
# define CORO_Define(name) struct COROData __coName(name) = { .state = NULL, .flags = 0};
#else
# define CORO_Define(name) CORODataClass __coName(name);
# define CORO_DefineStruct(name) struct COROData __coName(name) = { .state = NULL, .flags = 0};
#endif

#define CORO_Init_Impl(dataType, name, ret...)\
    dataType *__coData = &(__coName(name));\
    if (__coData->flags & CORO_FLAG_RESET) {\
        __coData->state = NULL;\
        __coData->flags &= ~(CORO_FLAG_RESET | CORO_FLAG_SUSPEND);\
    }\
    if (__coData->flags & CORO_FLAG_SUSPEND) return ret;\
    __coData->flags |= CORO_FLAG_SUSPEND;\
    __coResumePosition();\
    __coSavePosition();\
    __coLabelPosition();


#ifdef __CPP11__
#  define CORO_Init(name, ret...) CORO_Init_Impl(COROData, name, ##ret)
#  define CORO_Simple(ret...) static CORO_Define(__CORO); CORO_Init_Impl(COROData, __CORO, ##ret)
#else
#  define CORO_Init(name, ret...) CORO_Init_Impl(CORODataClass, name, ##ret)
#  define CORO_Simple(ret...) static CORO_DefineStruct(__CORO); CORO_Init_Impl(COROData, __CORO, ##ret)
#endif

#define yield(val) do { __coData->flags &= ~CORO_FLAG_SUSPEND; __coSavePosition(); return val; __coLabelPosition(); } while(0)

#define yieldWhile(cond, ret...) do { __coSavePosition(); __coLabelPosition(); if(cond) { __coData->flags &= ~CORO_FLAG_SUSPEND; return ret; } } while(0)
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
