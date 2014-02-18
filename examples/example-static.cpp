//
//  example-static.cpp
//  wolffiaCo
//
//  Created by Timo Reunanen on 15/02/2014.
//  Copyright (c) 2014 Timo Reunanen. All rights reserved.
//

#include <coroutine.h>

#ifdef FUNC1
CORO_Define(Func1)
void func1() {
    CORO_Init(Func1);
}
#endif

#ifdef FUNC2
CORO_Define(Func2)
void func2() {
    CORO_Init(Func2);
}
#endif

#ifdef FUNC3
CORO_Define(Func3)
void func3() {
    CORO_Init(Func3);
}
#endif

int main(void) {
#ifdef FUNC1
    func1();
#endif
    
#ifdef FUNC2
    func2();
#endif
    
#ifdef FUNC3
    func3();
#endif
    return 0;
    
}