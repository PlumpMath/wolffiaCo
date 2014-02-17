//
//  maintest.cpp
//  wolffiaCo
//
//  Created by Parker Kane on 17/02/2014.
//  Copyright (c) 2014 Parker Kane. All rights reserved.
//

#include "maintest.h"

#include <stdio.h>

#define __wo_print(arg...) printf(arg);
#define __wo_stringify(arg) #arg

#define assert(message, test) do { if (!(test)) { __wo_print("!! error\t:%i: " message "\n", __LINE__); return true; } } while (0)
#define except(message, test) do { if (!(test)) __wo_print(" - warning\t:%i: " message "\n", __LINE__); } while(0)

#define diag(message, args...) do { __wo_print(" + info\t\t:%i: " message "\n", __LINE__, ##args); } while(0)

#define run(name) do { __wo_print("test: " __wo_stringify(name) "\n"); bool ret = name(); tests_run++; if (ret) return ret; } while (0)

#define ok() do { return false; } while(0)
#define fail(message) do { __wo_print("!! fails\t:%i: " message "\n", __LINE__); return true; } while(0)

int tests_run;

bool Kala() {
    diag("foobar");
    except("doh", false);
    assert("iik", true);
    
    fail("meh");
    
    ok();
}

bool allTests() {
    run(Kala);
    run(Kala);
    
    ok();
}


int main(void) {

    allTests();
    
    return 0;
}

