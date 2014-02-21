//
//  kernel-example.cpp
//  wolffiaCo
//
//  Created by Timo Reunanen on 19/02/2014.
//  Copyright (c) 2014 Timo Reunanen. All rights reserved.
//
#include <stdio.h>
#include <stdbool.h>

#ifndef __AVR__
# include <time.h>
#endif

#include <wolffia.h>

//////////////////////////////////////////////////////////////////
// Setup wollfia tasks

#define WO_TASK1 fizzbuzz()
#define WO_TASK30 sleep_ms(20)

#define WO_LISTENER1 fizzEvent: fizz(event, data); show_counter()
#define WO_LISTENER2 buzzEvent: buzz(event, data); show_counter()

//////////////////////////////////////////////////////////////////
// Events

enum {
    // High priority events
    fizzEvent,
    buzzEvent,
    
    HIGH_PRIORITY_MARKER,
    
    // Normal priority events
    countEvent
};

//////////////////////////////////////////////////////////////////
// Initialize wolffia

#include <wolffia-init.h>

//////////////////////////////////////////////////////////////////


void fizzbuzz() {
    WO_InitTask();

    static uint16_t counter = 0;

    while (true) {
        counter++;
        
        if(counter != 1) printf(", ");
        
        dispatchEvent(countEvent, 0);
        dispatchEvent(fizzEvent, (counter % 3) == 0);
        dispatchEvent(buzzEvent, (counter % 5) == 0);
        
        yield();
    }
}

void fizz(uint8_t event, uint8_t data) {
    if (!data) return;

    printf("Fizz");
}

void buzz(uint8_t event, uint8_t data) {
    if (!data) return;
    
    printf("Buzz");
}

void show_counter() {
    int hasCount = 0;
    
    WO_InitTask();
    
    static uint8_t evt = 0;
    static uint16_t counter = 0;
    
    while (true) {
        waitEvent(evt);
        
        handleEvent(evt, countEvent) {
            counter++;
        }
        
        handleEvent2(evt, fizzEvent, buzzEvent) {
            if (!getEventData(evt)) {
                hasCount++;
            }
        }
        
        if (hasCount >= 2) {
            printf("%i", counter);
        }
        
        evt++;
    }
}

void sleep_ms(int ms) {
    WO_InitTask();
    
    while (true) {
#if defined(ARDUINO)
#elif defined(__AVR__)
#else
        struct timespec reqtime;
        reqtime.tv_sec = 0;
        reqtime.tv_nsec = ms*1000000;
        nanosleep(&reqtime, NULL);
        fflush(stdout);
#endif
        yield();
    }
}

void setup() {
}

void loop() {
    WO_Run(HIGH_PRIORITY_MARKER);
}

#ifndef ARDUINO
int main(void) {
    
    setup();
    
    while (true) {
        loop();
    }
    
    return 0;
}
#endif