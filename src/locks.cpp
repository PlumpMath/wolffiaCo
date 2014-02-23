//
//  coroutine.cpp
//  wolffiaCo
//
//  Created by Timo Reunanen on 15/02/2014.
//  Copyright (c) 2014 Timo Reunanen. All rights reserved.
//

#if defined(__AVR__)
# include <avr/interrupt.h>
# define CLEARI cli()
# define SETI sei()
#else
# define CLEARI
# define SETI
#endif

#include <coroutine.h>

unsigned short __coroutine_locks = 0;

bool lockAcquire(unsigned short id) {
    if (lockTest(id)) return false;
    
    CLEARI;
    __coroutine_locks |= id;
    SETI;
    
    return true;
}

void lockRelease(unsigned short id) {
    CLEARI;
    __coroutine_locks &= ~id;
    SETI;
}

bool lockTest(unsigned short id) {
    bool ret;
    CLEARI;
    ret = (__coroutine_locks & id) == id;
    SETI;
    return ret;
}