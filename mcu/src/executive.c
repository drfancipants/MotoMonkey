/*
The MIT License (MIT)

Copyright (c) 2015 Todd Fanciullo

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.


  executive.c

  Created on: Jun 12, 2016
      Author: todd
*/

#define EXECUTIVE_OWNER
#include "executive.h"
#undef EXECUTIVE_OWNER

#include "flags.h"
#include "mcu_api.h"
#include "mcu_errno.h"

int executive_initialize(void)
{
	int i, j;
	last_time = 0;
	schedule_items = 0;
	frame_counter = 0;
	frame_index = 0;
	for (i = 0; i < LOOP_RATE; i++)
	{
		for (j = 0; j < MAX_SCHED_ITEMS; j++)
		{
			schedfct[i][j] = 0;
		}
	}
	return SUCCESS;
}

int executive_set_schedule_item(int frame_multiplier, int(*callback)(void))
{
	int i;

	if (LOOP_RATE % frame_multiplier)
	{
		return SCHEDULE_ITEM_RATE_ERROR;
	}

	for (i = 0; i < LOOP_RATE; i++)
	{
		if (i%frame_multiplier == 0)
		{
			schedfct[i][schedule_items] = callback;
		}
	}

	schedule_items++;
	return SUCCESS;
}

// Latch the frame start time
unsigned long executive_frame_start(unsigned long current_time)
{
	unsigned long delay;
	start_time = current_time;
	delay = start_time - last_time;
	last_time = start_time;
	return delay;
}

int executive_execute_schedule(void)
{
	int i;
	for (i = 0; i < MAX_SCHED_ITEMS; i++)
	{
		if (schedfct[frame_index][i]) (*schedfct[frame_index][i])();
	}

	frame_index++;
	frame_counter++;
	if (frame_counter % LOOP_RATE == 0) frame_index = 0;

	return SUCCESS;
}


int executive_frame_end(unsigned long current_time)
{
	int delayT_us = LOOP_TIME_US - (int)(current_time - start_time);
	int delayT_frames = delayT_us/10000;
	mcu_sleep(delayT_frames);
	int delayus = (delayT_us) - delayT_frames*10000;
	mcu_delay(delayus);

	return SUCCESS;
}
