//
//  coroutine.cpp
//  coroutine
//
//  Created by Timo Reunanen on 15/02/2014.
//  Copyright (c) 2014 Timo Reunanen. All rights reserved.
//

#include "coroutine.h"

unsigned short __coroutine_locks = 0;

bool lockAcquire(unsigned short id) {
    
    if ((__coroutine_locks & id) == id) return false;
    
    __coroutine_locks |= id;
    
    return true;
}

void lockRelease(unsigned short id) {
    __coroutine_locks &= ~id;
}
