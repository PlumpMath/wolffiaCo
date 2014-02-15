//
//  example-static.cpp
//  coroutine
//
//  Created by Timo Reunanen on 15/02/2014.
//  Copyright (c) 2014 Timo Reunanen. All rights reserved.
//

#include <coroutine.h>

#ifdef FUNC1
void func() {
    CORO_Start
    

    
    CORO_Finish
}
#endif

#ifdef FUNC2
void func2() {
    CORO_Start
    
    
    
    CORO_Finish
}
#endif

#ifdef FUNC3
void func3() {
    CORO_Start
    
    
    
    CORO_Finish
}
#endif

int main(void) {
#ifdef FUNC1
    func();
#endif
    
#ifdef FUNC2
    func2();
#endif
    
#ifdef FUNC3
    func3();
#endif
    return 0;
    
}