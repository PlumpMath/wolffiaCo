//
//  example.cpp
//  wolffiaCo
//
//  Created by Timo Reunanen on 17/02/2014.
//  Copyright (c) 2014 Timo Reunanen. All rights reserved.
//

#include <stdio.h>

#include "coroutine.h"
#include "fizzbuzz.h"

int odd() {
    CORO_Simple(-1);
    
    static int v = -1;
    
    while(true) {
        yield(v+=2);
    }
}

int even() {
    CORO_Simple(-1);
    
    static int v = 0;
    
    while(true) {
        yield(v+=2);
    }
}

CORO_Define(Fibb)
int fibb() {
    // Initialize Coroutine
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
    
    // Define attributes for Fibb coroutine.
    CORO_Define(Fibb)
    int operator()() {
        // Initialize Coroutine
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

FizzBuzz fizzbuzz;

int main(void) {
 
    for(int i=0; i < 10; i++) {
        printf("%i ", odd());
        printf("%i ", even());
    }
    printf("\n");
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
    printf("\n\n");
    for(int i=0; i < 40; i++) {
        fizzbuzz();
    }
    printf("\n\n");
    fizzbuzz.stats();
    
    return 0;
}