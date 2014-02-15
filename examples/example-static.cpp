//
//  example-static.cpp
//  coroutine
//
//  Created by Parker Kane on 15/02/2014.
//  Copyright (c) 2014 Parker Kane. All rights reserved.
//

#include <coroutine.h>

void func() {
    CORO_StaticStart
    
    
    
    CORO_Finish
}

void func2() {
    CORO_StaticStart
    
    
    
    CORO_Finish
}

int main(void) {
    func();
    func2();
    return 0;
    
}