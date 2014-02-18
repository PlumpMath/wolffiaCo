//
//  maintest.cpp
//  wolffiaCo
//
//  Created by Timo Reunanen on 17/02/2014.
//  Copyright (c) 2014 Timo Reunanen. All rights reserved.
//

#include <coroutine.h>

#include "maintest.h"

int tests_run;

namespace simple {
    void test() {
        CORO_Simple();
    }
    
    bool coroSimple() {
        test();
        
        ok();
    }
    
    int testRet() {
        CORO_Simple(-1);
        
        yield(0);
        yield(1);
        
        return 2;
    }
    
    bool coroSimpleWithReturn() {
        
        assert(testRet() == 0);
        assert(testRet() == 1);
        assert(testRet() == 2);
        
        assert(testRet() == -1);
        assert(testRet() == -1);
        assert(testRet() == -1);
        assert(testRet() == -1);
        
        ok();
    }

    int fibbTest() {
        CORO_Simple(-1);
        
        static int a=1, b=0;
        
        while(true) {
            yield(a=a+b);
            yield(b=b+a);
        }
    }
    
    bool coroSimpleFibb() {
        assert(fibbTest() == 1);
        assert(fibbTest() == 1);
        assert(fibbTest() == 2);
        assert(fibbTest() == 3);
        assert(fibbTest() == 5);
        assert(fibbTest() == 8);
        assert(fibbTest() == 13);
        assert(fibbTest() == 21);
        assert(fibbTest() == 34);
        assert(fibbTest() == 55);
        
        ok();
    }
    
    bool all() {
        run(coroSimple);
        run(coroSimpleWithReturn);
        run(coroSimpleFibb);
        
        ok();
    }

}

namespace function {
    CORO_Define(Test);
    void test() {
        CORO_Init(Test);
    }
    
    bool coroFunction() {
        test();
        
        ok();
    }
    
    CORO_Define(TestRet);
    int testRet() {
        CORO_Init(TestRet, -1);
        
        yield(0);
        yield(1);
        
        return 2;
    }
    
    bool coroFunctionWithReturn() {
        
        assert(testRet() == 0);
        assert(testRet() == 1);
        assert(testRet() == 2);
        
        assert(testRet() == -1);
        assert(testRet() == -1);
        assert(testRet() == -1);
        assert(testRet() == -1);
        
        ok();
    }
    
    CORO_Define(Fibb);
    int fibbTest() {
        CORO_Init(Fibb, -1);
        
        static int a=1, b=0;
        
        while(true) {
            yield(a=a+b);
            yield(b=b+a);
        }
    }
    
    bool coroFunctionFibb() {
        assert(fibbTest() == 1);
        assert(fibbTest() == 1);
        assert(fibbTest() == 2);
        assert(fibbTest() == 3);
        assert(fibbTest() == 5);
        assert(fibbTest() == 8);
        assert(fibbTest() == 13);
        assert(fibbTest() == 21);
        assert(fibbTest() == 34);
        assert(fibbTest() == 55);
        
        ok();
    }
    
    bool all() {
        run(coroFunction);
        run(coroFunctionWithReturn);
        run(coroFunctionFibb);
        
        ok();
    }
    
}

namespace klass {
    
    class Test {
    public:
        Test() : a(1), b(0) {}
        
        void test() {
            CORO_Init(Test);
        }
        
        int testRet() {
            CORO_Init(TestRet, -1);
            
            yield(0);
            yield(1);
            
            return 2;
        }

        int fibbTest() {
            CORO_Init(Fibb, -1);
            
            static int a=1, b=0;
            
            while(true) {
                yield(a=a+b);
                yield(b=b+a);
            }
        }
    private:
        CORO_Define(Test);
        CORO_Define(TestRet);
        CORO_Define(Fibb);
        
        int a,b;
    };
    
    Test testInst;
    
    
    bool coroClass() {
        testInst.test();
        
        ok();
    }
    
    bool coroClassWithReturn() {
        
        assert(testInst.testRet() == 0);
        assert(testInst.testRet() == 1);
        assert(testInst.testRet() == 2);
        
        assert(testInst.testRet() == -1);
        assert(testInst.testRet() == -1);
        assert(testInst.testRet() == -1);
        assert(testInst.testRet() == -1);
        
        ok();
    }
    
    
    bool coroClassFibb() {
        assert(testInst.fibbTest() == 1);
        assert(testInst.fibbTest() == 1);
        assert(testInst.fibbTest() == 2);
        assert(testInst.fibbTest() == 3);
        assert(testInst.fibbTest() == 5);
        assert(testInst.fibbTest() == 8);
        assert(testInst.fibbTest() == 13);
        assert(testInst.fibbTest() == 21);
        assert(testInst.fibbTest() == 34);
        assert(testInst.fibbTest() == 55);
        
        ok();
    }
    
    bool all() {
        run(coroClass);
        run(coroClassWithReturn);
        run(coroClassFibb);
        
        ok();
    }
    
}

int main(void) {
    simple::all();
    function::all();
    klass::all();
    
    printf("%i tests done.\n", tests_run);
    
    return 0;
}

