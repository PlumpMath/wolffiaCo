//
//  example.cpp
//  wolffiaCo
//
//  Created by Parker Kane on 17/02/2014.
//  Copyright (c) 2014 Parker Kane. All rights reserved.
//

#include <stdio.h>

#include "coroutine.hpp"

CORO_Define(Fibb)
int fibb() {
    
    CORO_Init(Fibb, -1);
    
    static int a, b;
    
    a = 1;
    b = 0;
    
    while(true) {
        yield(a=a+b);
        yield(b=b+a);
    }
}

int fibb2() {
    CORO_Simple(-1);
    
    static int a = 1, b = 0;
    
    while(true) {
        yield(a=a+b);
        yield(b=b+a);
    }
}

class Fibb {
public:
    int a,b;
    
    CORO_Define(Fibb)
    int operator()() {
        CORO_Init(Fibb, -1);
        
        a = 1;
        b = 0;
        
        while(true) {
            yield(a=a+b);
            yield(b=b+a);
        }
    }
};
Fibb fibb3, fibb4;

int main(void) {
 
    for(int i=0; i < 20; i++) {
        printf("%i ", fibb());
    }
    printf("\n");
    for(int i=0; i < 20; i++) {
        printf("%i ", fibb2());
    }
    printf("\n");
    for(int i=0; i < 20; i++) {
        printf("%i ", fibb3());
    }
    printf("\n");
    for(int i=0; i < 20; i++) {
        printf("%i ", fibb4());
    }
    printf("\n");
    
    return 0;
}