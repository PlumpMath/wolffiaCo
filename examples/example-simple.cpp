//
//  example-simple.cpp
//  coroutine
//
//  Created by Timo Reunanen on 15/02/2014.
//  Copyright (c) 2014 Timo Reunanen. All rights reserved.
//

#include <coroutine.h>


void func1() {
    CORO_Simple();
}

void func2() {
    CORO_Simple();
}

int main(void) {
    func1();
    func2();
}
