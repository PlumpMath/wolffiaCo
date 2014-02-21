//
//  wolffia-events.h
//  wolffiaCo
//
//  Created by Timo Reunanen on 19/02/2014.
//  Copyright (c) 2014 Timo Reunanen. All rights reserved.
//

#ifndef __wolffiaCo__wolffia_events__
#define __wolffiaCo__wolffia_events__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define Eventbuffer_Size 5
#define Eventbuffer_Mask ((1 << Eventbuffer_Size)-1)

#ifdef WO_USE_WIDE_EVENTS
typedef uint16_t event_t;

#define Event_DefaultSize 8

#else
typedef uint8_t event_t;

#define Event_DefaultSize 6

#endif

#ifndef Event_Size
# define Event_Size Event_DefaultSize
#endif

#define Event_Mask ((1 << Event_Size)-1)


extern uint8_t event_position;

extern event_t event_buffer[Eventbuffer_Mask+1];

#define hasEvents(pos) (event_position != (pos))

#define dispatchEvent(evt, data)\
    do {\
        int pos;\
        __WO_ATOMIC_BLOCK { pos = event_position; event_position++; }\
        event_buffer[(pos) & Eventbuffer_Mask] = (evt) | ((data) << Event_Size);\
    } while(0)

#define getEvent(pos) (event_buffer[pos & Eventbuffer_Mask] & Event_Mask)
#define getEventData(pos) ((event_buffer[pos & Eventbuffer_Mask] >> Event_Size) & Event_Mask)

#define waitEvent(pos) yieldUntil(hasEvents(pos))

#define handleEvent(pos, event) if (getEvent(pos) == event)
#define handleEvent2(pos, event1, event2) if (getEvent(pos) == event1 || getEvent(pos) == event2)
#define handleEvent3(pos, event1, event2, event3) if (getEvent(pos) == event1 || getEvent(pos) == event2 || getEvent(pos) == event3)
#define handleEvent4(pos, event1, event2, event3, event4) if (getEvent(pos) == event1 || getEvent(pos) == event2 || getEvent(pos) == event3 || getEvent(pos) == event4)
#define handleEvent5(pos, event1, event2, event3, event4, event5) if (getEvent(pos) == event1 || getEvent(pos) == event2 || getEvent(pos) == event3 || getEvent(pos) == event4 || getEvent(pos) == event5)
#define handleEvent6(pos, event1, event2, event3, event4, event5, event6) if (getEvent(pos) == event1 || getEvent(pos) == event2 || getEvent(pos) == event3 || getEvent(pos) == event4 || getEvent(pos) == event5 || getEvent(pos) == event6)
#define handleEvent7(pos, event1, event2, event3, event4, event5, event6, event7) if (getEvent(pos) == event1 || getEvent(pos) == event2 || getEvent(pos) == event3 || getEvent(pos) == event4 || getEvent(pos) == event5 || getEvent(pos) == event6 || getEvent(pos) == event7)
#define handleEvent8(pos, event1, event2, event3, event4, event5, event6, event7, event8) if (getEvent(pos) == event1 || getEvent(pos) == event2 || getEvent(pos) == event3 || getEvent(pos) == event4 || getEvent(pos) == event5 || getEvent(pos) == event6 || getEvent(pos) == event7 || getEvent(pos) == event8)

#ifdef __cplusplus
}
#endif

    
#endif /* defined(__wolffiaCo__wolffia_events__) */
