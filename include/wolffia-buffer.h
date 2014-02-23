//
//  wolffia-buffer.h
//  wolffiaCo
//
//  Created by Timo Reunanen on 19/02/2014.
//  Copyright (c) 2014 Timo Reunanen. All rights reserved.
//

#ifndef __wolffiaCo__wolffia_buffer__
#define __wolffiaCo__wolffia_buffer__

#include <stdint.h>

#ifdef __AVR__
# include <util/atomic.h>
#endif

typedef uint8_t bufpos_t;

template<class T, uint8_t S>
class RingBuffer {
public:
    RingBuffer() : position(0) {}
    
    inline T& operator[](bufpos_t idx) {
        return buffer[idx & (S-1)];
    }

    inline bufpos_t next() {
#ifdef __AVR__
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
#endif
        {
            return position++;
        }
    }
    inline bool hasData(bufpos_t pos) {
        return pos != position;
    }
    
    inline void put(T data) { buffer[next()] = data; }
    
    inline uint8_t size(bufpos_t pos) {
        return position - pos;
    }
    
    inline bool overflow(bufpos_t pos) {
        return size(pos) > S;
    }
    
private:
    T buffer[S];
    bufpos_t position;
};

#endif /* defined(__wolffiaCo__wolffia_buffer__) */
