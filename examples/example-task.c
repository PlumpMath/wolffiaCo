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
#define WO_TASK2 sleep_ms(20)

//////////////////////////////////////////////////////////////////
// Events
//
// Uses default settings:
// 32 events in buffer, 6bit event ID and 2bit data

enum {
    // High priority events
    countEvent,
    startEvent,
    
    EVENT_PRIORITY_MARKER,
    
    // Normal priority events
    fizzEvent,
    buzzEvent,
};

#define WO_LISTENER1 fizzEvent: fizz(event, data); show_counter(event, data)
#define WO_LISTENER2 buzzEvent: buzz(event, data); show_counter(event, data)

#define WO_LISTENER3 countEvent: show_counter(event, data)
#define WO_LISTENER4 startEvent: show_counter(event, data)

//////////////////////////////////////////////////////////////////
// Initialize wolffia

#include <wolffia-init.h>

//////////////////////////////////////////////////////////////////


void fizzbuzz() {
    WO_InitTask();

    static uint16_t counter = 0;

    while (true) {
        dispatchEvent(startEvent, 0);
        
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

void show_counter(uint8_t event, uint8_t data) {
    static int flags = 0;
    static uint16_t counter = 0;
    
    switch (event) {
        case startEvent:
            flags = 0;
            break;
            
        case countEvent:
            counter++;
            break;
            
        case fizzEvent:
            flags |= data ? 0 : 1;
            break;
            
        case buzzEvent:
            flags |= data ? 0 : 2;
            break;
            
        default:
            break;
    }
    
    if (flags == 0x3) {
        printf("%i", counter);
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
    WO_Start(EVENT_PRIORITY_MARKER);
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