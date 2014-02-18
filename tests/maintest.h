//
//  maintest.h
//  wolffiaCo
//
//  Created by Parker Kane on 17/02/2014.
//  Copyright (c) 2014 Parker Kane. All rights reserved.
//

#ifndef __wolffiaCo__maintest__
#define __wolffiaCo__maintest__

#include <stdio.h>

#define __wo_print(arg...) printf(arg);
#define __wo_stringify(arg) #arg

#define assert(test, message...) do { if (!(test)) { __wo_print("!! error\t:%i (" __wo_stringify(test) "): " message "\n", __LINE__); return true; } } while (0)
#define except(test, message...) do { if (!(test)) __wo_print(" - warning\t:%i (" __wo_stringify(test) "): " message "\n", __LINE__); } while(0)

#define diag(message, args...) do { __wo_print(" + info\t\t:%i: " message "\n", __LINE__, ##args); } while(0)

#define run(name) do { __wo_print("test: " __wo_stringify(name) "\n"); bool ret = name(); tests_run++; if (ret) return ret; } while (0)

#define ok() do { return false; } while(0)
#define fail(message) do { __wo_print("!! fails\t:%i: " message "\n", __LINE__); return true; } while(0)

extern int tests_run;

#endif /* defined(__wolffiaCo__maintest__) */
