//
//  fizzbuzz.cpp
//  wolffiaCo
//
//  Created by Timo Reunanen on 18/02/2014.
//  Copyright (c) 2014 Timo Reunanen. All rights reserved.
//

#include "fizzbuzz.h"

void FizzBuzz::stats() {
    printf("FizzBuzz stats:\n");
    printf(" Fizz: %i\n Buzz: %i\n Counter: %i\n", fizzCount, buzzCount, counterCount);
}

void FizzBuzz::operator()() {
    
    // Because cross protected scopes, we need to have temporary variables before CORO_Init.
    // As in, flag will be always set to false when you run this method.
    bool flag = false;
    
    // Initialize Coroutine
    CORO_Init(Runner);
    
    counter = 0;
    first = true;
    
    while(true) {
        counter++;
        
        // Print comma only if it's not first time
        if (!first) {
            printf(", ");
            
        }
        first = false;
        
        // Test if it's fizz or buzz
        flag = fizz() | buzz();
        
        // Because it was not either fizz or buzz we show counter
        if (!flag) {
            printf("%i", counter);
            
            counterCount++;
        }
        
        yield();
    }
}

bool FizzBuzz::fizz() {
    
    // Initialize Coroutine with false as default return value
    CORO_Init(Fizz, false);
    
    while(true) {
        yield(false); // Not yet
        yield(false); // Not yet
        
        printf("Fizz");
        fizzCount++;
        
        yield(true); // FIZZ
    }
}

bool FizzBuzz::buzz() {
    
    // Initialize Coroutine with false as default return value
    CORO_Init(Buzz, false);
    
    while(true) {
        yield(false); // Not yet
        yield(false); // Not yet
        yield(false); // Not yet
        yield(false); // Not yet
        
        printf("Buzz");
        buzzCount++;
        
        yield(true); // BUZZ
    }
}

