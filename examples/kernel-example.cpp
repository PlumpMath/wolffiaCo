#include <stdio.h>
#include <unistd.h>

//////////////////////////////////////////////////////////////////
// Setup wollfia tasks

#define WO_TASK1 fizzbuzz
#define WO_TASK2 fizz
#define WO_TASK3 buzz

#define WO_TASK10 sleep

#include <wolffia.h>

//////////////////////////////////////////////////////////////////
// Setup locks

#define fizzLock LOCK_1
#define buzzLock LOCK_2

//////////////////////////////////////////////////////////////////

void fizzbuzz() {
    WO_InitTask();
    
    static int counter = 1;
    
    while (true) {
        if(counter != 1) printf(", ");
        
        if((counter % 3) == 0) lockRelease(fizzLock);
        if((counter % 5) == 0) lockRelease(buzzLock);
        if((counter % 5) != 0 && (counter % 3) != 0) printf("%i", counter);
        
        counter++;
        yield();
    }
}

void fizz() {
    WO_InitTask();
    
    while (true) {
        lockWaitAndAcquire(fizzLock);
        printf("Fizz");
    }
}

void buzz() {
    WO_InitTask();
    
    while (true) {
        lockWaitAndAcquire(buzzLock);
        printf("Buzz");
    }
}

void sleep() {
    WO_InitTask();
    
    while (true) {
#ifdef ARDUINO
        delay(20);
#else
        usleep(20*1000);
        fflush(stdout);
#endif
        yield();
    }
}

int main(void) {
    
    lockAcquire(fizzLock);
    lockAcquire(buzzLock);
    
    WO_RunOS()
    
    return 0;
}