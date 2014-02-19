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

#define __woConcat2(a,b) a##b
#define __woConcat(a,b) __woConcat2(a,b)

#define __woSetupTask(task) static CORO_DefineStruct(task)
#define __woSetAsCurrent(task) CORO_Name(currentCoroData) = &CORO_Name(task)

#include "wolffia-task.h"

extern COROData *CORO_Name(currentCoroData);

#endif
