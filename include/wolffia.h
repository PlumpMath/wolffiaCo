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

#define __woConcat_(a,b) a##b
#define __woConcat(a,b) __woConcat2(a,b)

#include "wolffia-task.h"

#define WO_Run() __woRun()

extern COROData *CORO_Name(currentCoroData);

#endif
