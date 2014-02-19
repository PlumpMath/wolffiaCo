//
//  wolffia-task.h
//  wolffiaCo
//
//  Created by Timo Reunanen on 19/02/2014.
//  Copyright (c) 2014 Timo Reunanen. All rights reserved.
//

#ifndef wolffiaCo_wolffia_task_h
#define wolffiaCo_wolffia_task_h

#define __woSetupTask(task) static CORO_DefineStruct(task)
#define __woSetAsCurrent(id) CORO_Name(currentCoroData) = &CORO_Name(id)

#define __woRunTask(id, task)\
    __woSetAsCurrent(id);\
    task

#define WO_InitTask() CORO_Init_Impl(COROData, *CORO_Name(currentCoroData))

#include "wolffia-task-gen.h"

#endif
