//
//  coroutine.cpp
//  wolffiaCo
//
//  Created by Timo Reunanen on 15/02/2014.
//  Copyright (c) 2014 Timo Reunanen. All rights reserved.
//

#if defined(__AVR__) && !defined(ARDUINO)
#include <util/atomic.h>
#endif

#include <coroutine.h>

unsigned short __coroutine_locks = 0;

bool lockAcquire(unsigned short id) {

#if defined(__AVR__) && !defined(ARDUINO)
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
#endif
    {
        if ((__coroutine_locks & id) == id) return false;
        
        __coroutine_locks |= id;
        
        return true;
    }
}

void lockRelease(unsigned short id) {
#if defined(__AVR__) && !defined(ARDUINO)
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
#endif
    {
        __coroutine_locks &= ~id;
    }
}

bool lockTest(unsigned short id) {
#if defined(__AVR__) && !defined(ARDUINO)
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
#endif
    {
        return (__coroutine_locks & id) == id;
    }
}