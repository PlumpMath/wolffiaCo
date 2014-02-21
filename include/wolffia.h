//
//  wolffia.h
//  wolffiaCo
//
//  Created by Timo Reunanen on 18/02/2014.
//  Copyright (c) 2014 Timo Reunanen. All rights reserved.
//

#ifndef wolffiaCo_wolffia_h
#define wolffiaCo_wolffia_h

#include "coroutine.h"

#include "wolffia-events.h"

#define __woConcat_(a,b) a##b
#define __woConcat(a,b) __woConcat2(a,b)

#define WO_Run(priority_marker) __woRun(priority_marker)

extern COROData *CORO_Name(currentCoroData);

#ifdef __AVR__
# define ATOMIC_BLOCK ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
#else
# define ATOMIC_BLOCK
#endif

#endif
