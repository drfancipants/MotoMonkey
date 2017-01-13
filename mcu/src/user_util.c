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


  user_util.c

  Created on: Jun 12, 2016
      Author: todd
*/

#include "flags.h"
#include "mcu_api.h"

#define USER_UTIL_OWNER
#include "user_util.h"
#undef USER_UTIL_OWNER

int user_util_initialize(void)
{
    toggle_sw = 0;
    gpio_setup(STATUS_LED_GPIO, 1);
	return SUCCESS;
}

int user_util_toggle_led(void)
{
	// Do something
	gpio_write(STATUS_LED_GPIO, toggle_sw);
	toggle_sw = toggle_sw == 0 ? 1:0;

	return SUCCESS;
}

int user_util_send_time(unsigned long time)
{
	char buf[64];
	int len;
	len = mcu_snprintf(buf, 64, "time = %d\n", time);
	host_send((unsigned char*)buf, len);

	return SUCCESS;
}
