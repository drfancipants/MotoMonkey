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


  executive.h

  Created on: Jun 12, 2016
      Author: todd
*/

#ifndef EXECUTIVE_H_
#define EXECUTIVE_H_

#ifdef EXTERN_FLAG
#undef EXTERN_FLAG
#endif

#ifdef EXECUTIVE_OWNER
#define EXTERN_FLAG
#else
#define EXTERN_FLAG extern
#endif

#define LOOP_RATE 100 //Hz
#define LOOP_TIME_US 1000000/LOOP_RATE // us
#define MAX_SCHED_ITEMS 10


int executive_initialize(void);
unsigned long executive_frame_start(unsigned long current_time);
int executive_frame_end(unsigned long current_time);
int executive_set_schedule_item(int frame_multiplier, int(*callback)(void));
int executive_execute_schedule(void);

unsigned long start_time;
unsigned long last_time;
int schedule_items;
int (*schedfct[LOOP_RATE][MAX_SCHED_ITEMS])(void);
unsigned long frame_counter;
unsigned int frame_index;


#endif /* EXECUTIVE_H_ */
