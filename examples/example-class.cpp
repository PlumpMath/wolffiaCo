//
//  example-class.cpp
//  coroutine
//
//  Created by Parker Kane on 15/02/2014.
//  Copyright (c) 2014 Parker Kane. All rights reserved.
//

#include <coroutine.h>

CORO_BeginClass(Func)
CORO_Method(void){
    
}
CORO_EndClass()

Func func1, func2;

int main(void) {
    func1();
    func2();
    
    return 0;
}
