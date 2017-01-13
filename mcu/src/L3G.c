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


  L3G.c

  Created on: Jun 12, 2016
      Author: todd
*/

#define L3G_OWNER
#include "L3G.h"
#undef L3G_OWNER

#include "mcu_api.h"

/*
Enables the L3G's gyro. Also:
- Sets gyro full scale (gain) to default power-on value of +/- 250 dps
  (specified as +/- 245 dps for L3GD20H).
- Selects 200 Hz ODR (output data rate). (Exact rate is specified as 189.4 Hz
  for L3GD20H and 190 Hz for L3GD20.)
Note that this function will also reset other settings controlled by
the registers it writes to.
*/
unsigned char l3dg20h_enableDefault(void)
{
	unsigned char data = 0x00;
	// 0x00 = 0b00000000
    // Low_ODR = 0 (low speed ODR disabled)
	if (i2c_write(L3GD20H_ADDR, L3GD20H_LOW_ODR, &data, 1))
	{
		debug_print(DBG_ERROR, "l3gd20h_i2c_write low odr failed...");
		        return 0Xff;
	}

    // 0x00 = 0b00000000
    // FS = 00 (+/- 250 dps full scale)
	if (i2c_write(L3GD20H_ADDR, L3GD20H_CTRL4, &data, 1))
	{
		debug_print(DBG_ERROR, "l3gd20h_i2c_write ctrl4 failed...");
		        return 0Xff;
	}

    // 0x6F = 0b01101111
    // DR = 01 (200 Hz ODR); BW = 10 (50 Hz bandwidth); PD = 1 (normal mode); Zen = Yen = Xen = 1 (all axes enabled)
    data = 0x6F;
	if (i2c_write(L3GD20H_ADDR, L3GD20H_CTRL1, &data, 1))
	{
		debug_print(DBG_ERROR, "l3gd20h_i2c_write ctrl1 failed...");
		        return 0Xff;
	}

	return 0x00;
}

unsigned char l3gd20h_init(void)
{
    unsigned char id;
    int res;

    // Get the device ID
    res = i2c_read(L3GD20H_ADDR, L3GD20H_WHOAMI, &id, 1);
    if (res)
    {
        debug_print(DBG_ERROR, "l3gd20h_i2c_read whoami failed...");
        return 0Xff;
    }

    // Check the device ID
    if (id != L3GD20H_WHOAMI_VALUE)
    {
        debug_print(DBG_ERROR, "wrong chip ID 0x%x, expected 0x%x\n",
                    id, L3GD20H_WHOAMI_VALUE);
        return 0xff;
    }

    // Enable the default values
    if (l3dg20h_enableDefault())
    {
    	debug_print(DBG_ERROR, "enable default values failed\n");
    	return 0xff;
    }
    return id;
}

unsigned char l3gd20h_read(int16_t* x, int16_t* y, int16_t* z)
{
	unsigned char xl, xh, yl, yh, zl, zh;

	if(i2c_read(L3GD20H_ADDR, L3GD20H_OUT_XL, &xl, 1)) return 0xff;
	if(i2c_read(L3GD20H_ADDR, L3GD20H_OUT_XH, &xh, 1)) return 0xff;
	if(i2c_read(L3GD20H_ADDR, L3GD20H_OUT_YL, &yl, 1)) return 0xff;
	if(i2c_read(L3GD20H_ADDR, L3GD20H_OUT_YH, &yh, 1)) return 0xff;
	if(i2c_read(L3GD20H_ADDR, L3GD20H_OUT_ZL, &zl, 1)) return 0xff;
	if(i2c_read(L3GD20H_ADDR, L3GD20H_OUT_ZH, &zh, 1)) return 0xff;

	*x = (int16_t)(xh << 8 | xl);
	*y = (int16_t)(yh << 8 | yl);
	*z = (int16_t)(zh << 8 | zl);

	return 0x00;
}
