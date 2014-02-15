//
//  example-simple.cpp
//  coroutine
//
//  Created by Timo Reunanen on 15/02/2014.
//  Copyright (c) 2014 Timo Reunanen. All rights reserved.
//

#include "coroutine.h"

CORO_Begin(func1)
CORO_Method(void)
{
}
CORO_End(func1, func2)

int main(void) {
    func1();
    func2();
}
