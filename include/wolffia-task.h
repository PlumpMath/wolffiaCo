//
//  wolffia-task.h
//  wolffiaCo
//
//  Created by Timo Reunanen on 19/02/2014.
//  Copyright (c) 2014 Timo Reunanen. All rights reserved.
//

#ifndef wolffiaCo_wolffia_task_h
#define wolffiaCo_wolffia_task_h

#define __woRunTask(task)\
    __woSetupTask(task);\
    __woSetAsCurrent(task);\
    task();

#define WO_InitTask() CORO_Init_Impl(COROData, *CORO_Name(currentCoroData));

#include "wolffia-task-gen.h"

#endif
