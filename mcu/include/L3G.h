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


  L3G.h

  Created on: Jun 12, 2016
      Author: todd
*/

#ifndef L3G_H_
#define L3G_H_

#ifdef EXTERN_FLAG
#undef EXTERN_FLAG
#endif

#ifdef L3G_OWNER
#define EXTERN_FLAG
#else
#define EXTERN_FLAG extern
#endif

#include "stdint.h"

/* the I2C address of L3GD20H */
#define L3GD20H_ADDR    0b1101011
/* the register address of WHOAMI register, which is used to verify
the identity of the device */
#define L3GD20H_WHOAMI          ((unsigned char)0x0F)
#define L3GD20H_WHOAMI_VALUE    ((unsigned char)0xD7)
#define L3GD20H_LOW_ODR         ((unsigned char)0x39)
#define L3GD20H_CTRL1           ((unsigned char)0x20)
#define L3GD20H_CTRL4           ((unsigned char)0x23)
#define L3GD20H_OUT_XL          ((unsigned char)0x28)
#define L3GD20H_OUT_XH          ((unsigned char)0x29)
#define L3GD20H_OUT_YL          ((unsigned char)0x2A)
#define L3GD20H_OUT_YH          ((unsigned char)0x2B)
#define L3GD20H_OUT_ZL          ((unsigned char)0x2C)
#define L3GD20H_OUT_ZH          ((unsigned char)0x2D)

unsigned char l3gd20h_init(void);
unsigned char l3dg20h_enableDefault(void);
unsigned char l3gd20h_read(int16_t* x, int16_t* y, int16_t* z);

#endif /* L3G_H_ */
