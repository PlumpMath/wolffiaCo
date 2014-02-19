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

#define Event_Size 4
#define Event_Mask (1 << Event_Size)-1

extern uint8_t event_position;

extern uint16_t event_buffer[Event_Mask+1];

#define hasEvents(pos) (event_position != pos)

#define dispatchEvent(evt, data) do { event_buffer[(event_position++) & Event_Mask] = (evt) | ((data) << 8); } while(0)
#define getEvent(pos) (event_buffer[pos & Event_Mask] & 0xFF)
#define getEventData(pos) ((event_buffer[pos & Event_Mask] >> 8) & 0xFF)

#define waitEvent(pos) yieldUntil(hasEvents(pos))

#define handleEvent(pos, event) if (getEvent(pos) == event)
#define handleEvent2(pos, event1, event2) if (getEvent(pos) == event1 || getEvent(pos) == event2)
#define handleEvent3(pos, event1, event2, event3) if (getEvent(pos) == event1 || getEvent(pos) == event2 || getEvent(pos) == event3)
#define handleEvent4(pos, event1, event2, event3, event4) if (getEvent(pos) == event1 || getEvent(pos) == event2 || getEvent(pos) == event3 || getEvent(pos) == event4)
#define handleEvent5(pos, event1, event2, event3, event4, event5) if (getEvent(pos) == event1 || getEvent(pos) == event2 || getEvent(pos) == event3 || getEvent(pos) == event4 || getEvent(pos) == event5)
#define handleEvent6(pos, event1, event2, event3, event4, event5, event6) if (getEvent(pos) == event1 || getEvent(pos) == event2 || getEvent(pos) == event3 || getEvent(pos) == event4 || getEvent(pos) == event5 || getEvent(pos) == event6)
#define handleEvent7(pos, event1, event2, event3, event4, event5, event6, event7) if (getEvent(pos) == event1 || getEvent(pos) == event2 || getEvent(pos) == event3 || getEvent(pos) == event4 || getEvent(pos) == event5 || getEvent(pos) == event6 || getEvent(pos) == event7)
#define handleEvent8(pos, event1, event2, event3, event4, event5, event6, event7, event8) if (getEvent(pos) == event1 || getEvent(pos) == event2 || getEvent(pos) == event3 || getEvent(pos) == event4 || getEvent(pos) == event5 || getEvent(pos) == event6 || getEvent(pos) == event7 || getEvent(pos) == event8)

#endif /* defined(__wolffiaCo__wolffia_events__) */
