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


  imu_interface.c

  Created on: Jun 12, 2016
      Author: todd
*/


#define IMU_OWNER
#include "imu_interface.h"
#undef IMU_OWNER

#include "flags.h"
#include "L3G.h"
#include "stdint.h"
#include "mcu_api.h"

int imu_interface_initialize(void)
{
	accum_samples = 0;
	delta_x = 0;
	delta_y = 0;
	delta_z = 0;

	if(l3gd20h_init())
	{
		return L3G_GYRO_INIT_ERROR;
	}

	return SUCCESS;
}

int imu_sample_and_accumulate(void)
{
	int16_t x = 0;
	int16_t y = 0;
	int16_t z = 0;
	if(l3gd20h_read(&x, &y, &z))
	{
		return L3G_GYRO_READ_ERROR;
	}

	delta_x += x;
	delta_y += y;
	delta_z += z;

	accum_samples++;

	return SUCCESS;
}

int imu_get_delta_thetas(void)
{
	char buf[128];
	int len;

	len = mcu_snprintf(buf, 128, "delta_x = %d delta_y = %d delta_z = %d samples = %d\n", delta_x, delta_y, delta_z, accum_samples);
	host_send((unsigned char*)buf, len);

	delta_x = 0;
	delta_y = 0;
	delta_z = 0;
	accum_samples = 0;

	return SUCCESS;
}
