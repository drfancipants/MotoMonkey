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


  mcu_main.c

  Created on: Jun 12, 2016
      Author: todd
*/

#include "mcu_api.h"
#include "mcu_errno.h"

#include "flags.h"
#include "executive.h"
#include "user_util.h"
#include "imu_interface.h"

int mcu_main()
{
	int error;

	// Initialize the executive
	error = executive_initialize();
	if (error)
	{
		debug_print(DBG_ERROR, "executive initialize failure - error %d\n", error);
		return error;
	}

	// Set executive schedule
	error = executive_set_schedule_item(100, user_util_toggle_led);
	if (error)
	{
		debug_print(DBG_ERROR, "executive toggle led set schedule failure - error %d\n", error);
		return error;
	}

	error = executive_set_schedule_item(1, imu_sample_and_accumulate);
	if (error)
	{
		debug_print(DBG_ERROR, "executive imu sample set schedule failure - error %d\n", error);
		return error;
	}

	error = executive_set_schedule_item(5, imu_get_delta_thetas);
	if (error)
	{
		debug_print(DBG_ERROR, "executive imu sample set schedule failure - error %d\n", error);
		return error;
	}

	// Initialize schedule items
	user_util_initialize();
	imu_interface_initialize();

	while (1)
	{
		//user_util_send_time(executive_frame_start(time_us()));
		executive_frame_start(time_us());

		executive_execute_schedule();

    	error = executive_frame_end(time_us());
    	if (error)
    	{
    		debug_print(DBG_ERROR, "executive frame end failure - error %d\n", error);
    		return error;
    	}
	}
	return error;
}
