//
//  main.cpp
//  coroutine
//
//  Created by Timo Reunanen on 15/02/2014.
//  Copyright (c) 2014 Timo Reunanen. All rights reserved.
//

#include <stdio.h>

#include "coroutine.h"

///////////////////////////////////////////////////
CORO_Begin(even)
int counter=0;

CORO_Method(int) {
    while(true) {
        counter++;
        
        if(counter & 1) yield(counter+1);
    }
}
CORO_End(even)
///////////////////////////////////////////////////

///////////////////////////////////////////////////
CORO_Begin(odd)
int counter=0;

CORO_Method(int) {
    while(counter++ & 1);
    
    finish(counter);
}
CORO_End(odd)
///////////////////////////////////////////////////

///////////////////////////////////////////////////
CORO_BeginClass(WhileTest)
int counter = 0;

inline bool tester() {
    return counter >= 20;
}

CORO_Method(int) {
    printf("+");
    
    yieldUntil(tester(), 0);
    
    printf("_");
    
    finish(1);
}
CORO_EndClass()

WhileTest whileTest;
///////////////////////////////////////////////////

///////////////////////////////////////////////////
CORO_Begin(voidTest);
CORO_Method(void) {
    printf("a");
    yield();
    
    printf("b");
    yield();
    
    printf("c");
    finish();
}
CORO_End(voidTest, voidTest2)
///////////////////////////////////////////////////

///////////////////////////////////////////////////
CORO_Begin(fibb)
int a=1, b=0;

CORO_Method(int) {
    while(true) {
        yield(a=a+b);
        yield(b=a+b);
    }
}
CORO_End(fibb, fibb2)
///////////////////////////////////////////////////

///////////////////////////////////////////////////
class Fibb {
public:
    int a=1, b=0;
    
    int operator()();
};

int Fibb::operator()() {
    CORO_Start
    
    while(true) {
        yield(a=a+b);
        yield(b=a+b);
    }
    
    CORO_Finish
}
Fibb fibb3;
///////////////////////////////////////////////////

///////////////////////////////////////////////////
int fibb4() {
    CORO_Start
    
    static int a=1, b=0;
    
    while(true) {
        yield(a=a+b);
        yield(b=a+b);
    }
    
    CORO_Finish;
}
///////////////////////////////////////////////////

int main(int argc, const char * argv[])
{
    printf("odds: ");
    for(int i=0; i < 20; i++) {
        printf("%i ", odd());
    }
    printf("\n");
    
    printf("evens: ");
    for(int i=0; i < 20; i++) {
        printf("%i ", even());
    }
    printf("\n");
    printf("fibb: ");
    for(int i=0; i < 20; i++) {
        printf("%i ", fibb());
    }
    printf("\n");
    printf("fibb2: ");
    for(int i=0; i < 20; i++) {
        printf("%i ", fibb2());
    }
    printf("\n");
    printf("fibb3: ");
    for(int i=0; i < 20; i++) {
        printf("%i ", fibb3());
    }
    printf("\n");
    printf("fibb4: ");
    for(int i=0; i < 20; i++) {
        printf("%i ", fibb4());
    }
    printf("\n");
    
    for(int i=0; i < 10; i++) {
        voidTest();
        voidTest2();
        printf(".");
    }
    printf("\n");

    int i;
    do {
        printf("%i", (i = whileTest()));
        whileTest.counter++;
    } while (i==0);
    
    printf("\n");
    
    return 0;
}