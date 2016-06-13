/************************************************************************************
 * Copyright (c) 2015, Intel Corporation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 ************************************************************************************/

/**
* @file mcu_api.h
* @brief Intel MCU API definition.
*
* User can utilize these APIs to control devices that connected with MCU and to
* communicate with host.
*/

#ifndef __MCUAPI_H
#define __MCUAPI_H

#define DBG_FATAL 1
#define DBG_ERROR 2
#define DBG_WARNING 3
#define DBG_INFO 4
#define DBG_DEBUG 5

/**
* Get API version
* @return 100 multiples major version number plus minor version number
*/
int api_version();

/**
* Read the value of one GPIO port
* @param gpio the GPIO port number to be read
* @return the value of the GPIO port. 0 if low voltage and 1 if high voltage
*/
int gpio_read(int gpio);

/**
* Write the value of one GPIO port
* @param gpio the GPIO port number to be written
* @param val the value to be written. 0 for low voltage and 1 for high voltage
*/
void gpio_write(int gpio, int val);

/**
* Setup the direction of one GPIO port
* @param gpio the GPIO port number
* @param direction 0 for input and 1 for output
*/
void gpio_setup(int gpio, int direction);

#define IRQ_NONE	0
#define IRQ_HANDLED	1
/**
* ISR handler definition
* @param irq interrupt request number
* @return return IRQ_HANDLED after irq handled
*/
typedef int (*irq_handler_t)(int irq);

/**
* Register on ISR for one GPIO port
* @param gpio the GPIO port number
* @param int_mode 0 for falling edge and 1 for rising edge
* @param fn the ISR handler
* @return 0 if successful
*/
int gpio_register_interrupt(int gpio, int int_mode, irq_handler_t fn);

/**
* Setup the baud rate of UART
* @param port uart port(1 or 2)
* @param baudrate the baud rate to be set. It can be one of below:
* 115200 | 57600 | 38400 | 28800 | 19200 | 14400 | 9600 | 7200 | 4800
* @return 0 if  successful
*/
int uart_setup(unsigned char port, int baudrate);

/**
* Read the input from UART
* @param port uart port(1 or 2)
* @param buf the buffer point to contain the data
* @param len size of buffer to be read
* @return 0 if successful
*/
int uart_read(unsigned char port, unsigned char *buf, unsigned char len);

/**
* Write one buffer to UART
* @param port uart port(1 or 2)
* @param buf the buffer point that contains the data
* @param len size of buffer
* @return 0 if successful
*/
int uart_write(unsigned char port, unsigned char *buf, unsigned char len);

/**
* Configure the parameters of PWM port
* @param port PWM port(0 - 3)
* @param duty_ns active pulse duration of the PWM waveform, in nanosecond
* @param period_ns the whole period of the PWM waveform, in nanosecond.
* The period value should be between 104 and 218453000 according to the SoC spec.
* @return 0 if successful
*/
int pwm_configure(unsigned char port, int duty_ns, int period_ns);

/**
* Enable the output of PWM
* @param port PWM port(0 - 3)
* @return 0 if successful
*/
int pwm_enable(unsigned char port);

/**
* Disable the output of PWM
* @param port PWM port(0 - 3)
* @return 0 if successful
*/
int pwm_disable(unsigned char port);

/**
* Read the value of one I2C device's register
* @param addr I2C device address
* @param reg register address
* @param buf the buffer point to contain the data
* @param len size of buffer
* @return 0 if successful
*/
int i2c_read(unsigned char addr, unsigned char reg, unsigned char *buf, int len);

/**
* Write the value of one I2C device's register
* @param addr I2C device address
* @param reg register address
* @param buf the buffer point that contains the data
* @param len size of buffer
* @return 0 if successful
*/
int i2c_write(unsigned char addr, unsigned char reg, unsigned char *buf, int len);

/**
* Make application sleep
* @param ticks one tick is 10 ms for Intel MCU
*/
void mcu_sleep(int ticks);

/**
* Pause the application for a period of time
* @param delay_us the number of microsecond to pause
* @note This API does not make application sleep. Always call mcu_sleep() if application
* need sleep for more than one tick (10 ms).
* @return 0 if successful
*/
int mcu_delay(int delay_us);

/**
* Get the number of milliseconds since the MCU boots up.
* @param N/A
* @return the number of milliseconds
* @note This number will overflow (go back to zero) after around 1193 hours.
*/
unsigned long time_ms();

/**
* Get the number of microseconds since the MCU boots up.
* @param N/A
* @return the number of microseconds
* @note This number will overflow (go back to zero) after around 71 minutes.
*/
unsigned long time_us();

/**
* Send raw data to host
* @param buf the buffer point that contains the data
* @param length size of buffer
* @return 0 if successful
* @note
* 1. The maximum value of buffer length is 255.
* 2. Every host_send call will trigger an interrupt to host CPU. So do NOT call it very frequently.
*/
int host_send(unsigned char *buf, int length);

/**
* Receive raw data from host
* @param buf the buffer point to contain the data
* @param length size of buffer
* @return size of data that received
*/
int host_receive(unsigned char *buf, int length);

/**
* Print the debug message to debug console
* @param level one of DBG_XXX defined above
* @param fmt format string 
*/
void debug_print(int level, const char *fmt, ...);

/**
* A simplified version of snprintf
* @note only \%d, \%x, \%s are supported
* @param buf the buffer point to contain the data
* @param size size of buffer
* @param fmt format string 
* @return the number of characters that have been written
*/
int mcu_snprintf(char *buf, unsigned int size, const char *fmt, ...);
#endif
