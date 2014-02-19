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

#ifndef __cplusplus
#define __C__
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

#define CORO_Name(name) __coConcat(__coVar_, name)

#define __coResumePosition() if (__coData->state != NULL) { goto *(__coData->state); }
#define __coLabelPosition() __coLabelize():
#define __coSavePosition() __coData->state = &&__coLabelize()

#define CORO_Define CORO_Define_Impl

#define CORO_DefineStruct(name) struct COROData CORO_Name(name) = { NULL, 0 };

#if defined(__CPP11__) || defined(__C__)
# define CORO_Define_Impl(name) CORO_DefineStruct(name)
#else
# define CORO_Define_Impl(name) CORODataClass CORO_Name(name);
#endif

#define CORO_Init_Impl(dataType, dataValue, ret...)\
    dataType *__coData = &(dataValue);\
    if (__coData->flags & CORO_FLAG_RESET) {\
        __coData->state = NULL;\
        __coData->flags &= ~(CORO_FLAG_RESET | CORO_FLAG_SUSPEND);\
    }\
    if (__coData->flags & CORO_FLAG_SUSPEND) return ret;\
    __coData->flags |= CORO_FLAG_SUSPEND;\
    __coResumePosition();\
    __coSavePosition();\
    __coLabelPosition();


#if defined(__CPP11__) || defined(__C__)
#  define CORO_Init(name, ret...)    CORO_Init_Impl(COROData, CORO_Name(name), ##ret)
#  define CORO_Simple(ret...) static CORO_Define_Impl(__CORO); CORO_Init_Impl(COROData, CORO_Name(__CORO), ##ret)
#else
#  define CORO_Init(name, ret...)    CORO_Init_Impl(CORODataClass, CORO_Name(name), ##ret)
#  define CORO_Simple(ret...) static CORO_DefineStruct(__CORO); CORO_Init_Impl(COROData, CORO_Name(__CORO), ##ret)
#endif

#define yield(val) do { __coData->flags &= ~CORO_FLAG_SUSPEND; __coSavePosition(); return val; __coLabelPosition(); } while(0)

#define yieldWhile(cond, ret...) do { __coSavePosition(); __coLabelPosition(); if(cond) { __coData->flags &= ~CORO_FLAG_SUSPEND; return ret; } } while(0)
#define yieldUntil(cond, ret...) yieldWhile(!(cond), ret)

#include "locks.h"

#endif
