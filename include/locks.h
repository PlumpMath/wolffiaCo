//
//  locks.h
//  wolffiaCo
//
//  Created by Parker Kane on 19/02/2014.
//  Copyright (c) 2014 Parker Kane. All rights reserved.
//

#ifndef wolffiaCo_locks_h
#define wolffiaCo_locks_h

#include <stdbool.h>

#include "coroutine.h"

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
