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

void FizzBuzz::operator()(int counter) {
    
    // Because cross protected scopes, we need to have temporary variables before CORO_Init.
    // As in, flag will be always set to false when you run this method.
    bool flag = false;
    
    // Initialize Coroutine
    CORO_Init(Runner);
    
    while(true) {
        // Test if it's fizz or buzz
        flag = fizz(counter) | buzz(counter);
        
        // Because it was not either fizz or buzz we show counter
        if (!flag) {
            printf("%i", counter);
            
            counterCount++;
        }
        
        printf(", ");
        
        yield();
    }
}

bool FizzBuzz::fizz(int counter) {
    
    // Initialize Coroutine with false as default return value
    CORO_Init(Fizz, false);
    
    while(true) {
        if ((counter % 3) == 0) {
            printf("Fizz");
            
            fizzCount++;
            
            // Because it's fizz we tell main loop not to test others
            yield(true);
        }
        
        // It was not fizz, tell main loop to test others
        yield(false);
    }
}

bool FizzBuzz::buzz(int counter) {
    
    // Initialize Coroutine with false as default return value
    CORO_Init(Buzz, false);
    
    while(true) {
        if ( (counter % 5) == 0) {
            printf("Buzz");
            
            buzzCount++;
            
            // Because it's buzz we tell main loop not to test others
            yield(true);
        }
        
        // It was not buzz, tell main loop to test others
        yield(false);
    }
}

