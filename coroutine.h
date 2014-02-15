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

class coroutine {
public:
    void * __coPosition;
    
    coroutine() : __coPosition(NULL) {
    }
private:
};

#define __coConcat(a,b) __coConcat2(a,b)
#define __coConcat2(a,b) a##b

#define __coLabelize() __coConcat(__coLabel, __LINE__)

#define __coResumePosition if (__coPosition != NULL) { goto *__coPosition; }
#define __coLabelPosition() __coLabelize():
#define __coSavePosition() __coPosition = &&__coLabelize()
#define __coResetPosition() __coPosition = NULL;

#define __coClassName(name) __coConcat(__co_class_, name)

#define CORO_Start __coResumePosition; __coSavePosition(); __coLabelPosition();
#define CORO_StaticStart static void * __coPosition = NULL; CORO_Start;

#define CORO_Finish __coResetPosition();

#define CORO_Begin(name) class __coClassName(name) : coroutine { public: __coClassName(name)() = default;
#define CORO_Method(ret, args...) ret operator()(args) { CORO_Start;
#define CORO_End(name, copies...) CORO_Finish; } }; __coClassName(name) name, ##copies;

#define finish(val) do { __coResetPosition(); return val; } while(0)
#define yield(val) do { __coSavePosition(); return val; __coLabelPosition(); } while(0)

#define yieldWhile(cond, ret...) do {__coSavePosition(); __coLabelPosition(); if(cond) return ret;} while(0)
#define yieldUntil(cond, ret...) yieldWhile(!(cond), ret)

#endif