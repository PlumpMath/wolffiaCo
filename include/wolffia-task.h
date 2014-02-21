//
//  wolffia-task.h
//  wolffiaCo
//
//  Created by Timo Reunanen on 19/02/2014.
//  Copyright (c) 2014 Timo Reunanen. All rights reserved.
//

#ifndef wolffiaCo_wolffia_task_h
#define wolffiaCo_wolffia_task_h

#define __woCheck_Event(id) __woJmpPos = &&id; if (hasEvents(__woHighEventPos) || hasEvents(__woLowEventPos)) {goto __wo_check_event;} id:;

#define __woRunTask(id, task)\
    task;\
    __woCheck_Event(id)

#define WO_InitTask() CORO_Simple()

#define __woListenerCase(code) case code; break;
#define __woDefaultListenerCase default: break;

#define __woFinalTask

#define __woRun(priority_marker)\
    void *__woJmpPos;\
    uint8_t __woLowEventPos=0, __woHighEventPos=0, event, data;\
    \
    __wo_start:\
    __woRunBlock;\
    \
    goto __wo_start;\
    \
    __wo_check_event:\
    if (hasEvents(__woHighEventPos)){\
        event = getEvent(__woHighEventPos);\
        data = getEventData(__woHighEventPos);\
        __woHighEventPos++;\
        \
        if (event > priority_marker) goto __wo_check_event;\
    \
    } else if (hasEvents(__woLowEventPos)) {\
        event = getEvent(__woLowEventPos);\
        data = getEventData(__woLowEventPos);\
        __woLowEventPos++;\
        \
        if (event < priority_marker) goto __wo_check_event;\
    \
    } else {\
        goto *__woJmpPos;\
    }\
    \
    switch (event) {\
            __woListenerBlock;\
    }\
    \
    goto __wo_check_event;


#include "wolffia-task-gen.h"

#endif
