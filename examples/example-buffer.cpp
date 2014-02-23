//
//  example-buffer.cpp
//  wolffiaCo
//
//  Created by Parker Kane on 23/02/2014.
//  Copyright (c) 2014 Parker Kane. All rights reserved.
//

#include <stdio.h>
#include <wolffia.h>

RingBuffer<uint8_t, 32> buffer1;
#ifdef BUF2
RingBuffer<uint8_t, 32> buffer2;
#endif
#ifdef BUF3
RingBuffer<uint8_t, 32> buffer3;
#endif

int main(void) {
    buffer1.put(42);
    
    
    
#ifdef BUF2
    buffer2.put(42);
#endif
#ifdef BUF3
    buffer3.put(42);
#endif
}