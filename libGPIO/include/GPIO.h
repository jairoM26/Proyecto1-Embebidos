#ifndef _GPIO_H
#define _GPIO_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

/**
 * @file GPIO.h
 * @author Abraham, David, Jairo
 * @date 21 Marzo 2018
 * @brief libGPIO header file. Based in the Gert van Loo & Dom version
 	How to access GPIO registers from C-code on the Raspberry-Pi
 *
 */

/** @brief Base DIR for the BCM2708 device**/
#define BCM2708_PERI_BASE 0x3F000000

/** @brief Base direction inside the BCM2708 for the GPIO, this is for the Raspberry Pi 3 **/
#define GPIO_BASE (BCM2708_PERI_BASE + 0x200000) 
 
#define PAGE_SIZE (4*1024)
/** @brief writing size **/
#define BLOCK_SIZE (4*1024)

/** @brief GPIO setup macro. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y). This is used to configure as input**/
#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
/** @brief GPIO setup macro. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y). This is used to configure as output**/
#define OUT_GPIO(g) *(gpio+((g)/10)) |=  (1<<(((g)%10)*3))
/** @brief alternative function **/
#define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))
 
/** @brief write in the GPIO number. Sets bits which are 1 ignores bits which are 0**/
#define GPIO_SET *(gpio+7)  // 
/** @brief Clears bits which are 1 ignores bits which are 0 **/
#define GPIO_CLR *(gpio+10)
 /** @brief read in the GPIO number**/
#define GET_GPIO(g) (*(gpio+13)&(1<<g)) // 0 if LOW, (1<<g) if HIGH
/** @brief Pull up/pull down **/ 
#define GPIO_PULL *(gpio+37)
/** @brief Pull up/pull down clock**/
#define GPIO_PULLCLK0 *(gpio+38) 

/** @brief Use to read with open("/dev/mem", O_RDWR|O_SYNC) )**/
int  mem_fd;
/** @brief mmap the GPIO **/
void *gpio_map;
 
/** @brief I/O access */
volatile unsigned *gpio;

/** @brief   Set up a memory regions to access GPIO
 Make shure to use it at the begining of your code.
 @author 	Abraham, David, Jairo
 @return void.
**/
void setup_io();

/** @brief   Permite establecer el modo (entrada/salida) de un pin específico (número de pin/gpio)
 @author 	Abraham, David, Jairo
 @param pin Number of the GPIO
 @param MODE 0 for Output, 1 for Input			
 @return int 0 if success.
**/
void configure_pin(int pin);

/** @brief   Permite escribir un valor de 0 o 1 en el pin especı́fico configurado como salida.
 @author 	Abraham, David, Jairo
 @param pin Number of the GPIO
 @param value 0 for Low, 1 for High			
 @return null.
**/
void set_pin(int pin,int value);


/** @brief   Permite leer el estado (0,1) de un pin digital
 @author 	Abraham, David, Jairo
 @param pin Number of the GPIO
 @return int 0 if success.
**/
int get_pin(int pin);

/** @brief   Permite generar un blink (establecer y desestablecer un valor binario) en un pin a una frecuencia determinada, por un tiempo de duración determinado.
 @author 	Abraham, David, Jairo
 @param pin Number of the GPIO
 @param freq in hertz
 @param duration in seconds			
 @return int 0 if success.
**/
int blink(int pin,int freq,int duration);

#endif


