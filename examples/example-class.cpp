//
//  example-class.cpp
//  coroutine
//
//  Created by Timo Reunanen on 15/02/2014.
//  Copyright (c) 2014 Timo Reunanen. All rights reserved.
//

#include <coroutine.hpp>

class Func {
public:
    CORO_Define(Test);
    void operator()() {
        CORO_Init(Test);
    }
};

#ifdef FUNC1
Func func1;
#endif
#ifdef FUNC2
Func func2;
#endif
#ifdef FUNC3
Func func3;
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
