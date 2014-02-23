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

#ifdef __AVR__
# include <avr/interrupt.h>
# define __WO_ATOMIC_BLOCK(command) cli(); command; sei()
#else
# define __WO_ATOMIC_BLOCK(command) command
#endif

#endif
