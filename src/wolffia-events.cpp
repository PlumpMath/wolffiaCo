//
//  wolffia-events.cpp
//  wolffiaCo
//
//  Created by Timo Reuanen on 19/02/2014.
//  Copyright (c) 2014 Timo Reunanen. All rights reserved.
//

#include "wolffia-events.h"

uint8_t event_position = 0;

event_t event_buffer[Eventbuffer_Mask+1];
