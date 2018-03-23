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
 * @brief libGPIO header file.
 *
 */

/** @brief DIR
**/
#define BCM2708_PERI_BASE        0x3F000000
//GPIO controller
#define GPIO_BASE                (BCM2708_PERI_BASE + 0x200000) 
 
#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)


// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y)
#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpio+((g)/10)) |=  (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))
 
#define GPIO_SET *(gpio+7)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR *(gpio+10) // clears bits which are 1 ignores bits which are 0
 
#define GET_GPIO(g) (*(gpio+13)&(1<<g)) // 0 if LOW, (1<<g) if HIGH
 
#define GPIO_PULL *(gpio+37) // Pull up/pull down
#define GPIO_PULLCLK0 *(gpio+38) // Pull up/pull down clock

int  mem_fd;
void *gpio_map;
 
// I/O access
volatile unsigned *gpio;

// 0 if LOW, (1<<g) if HIGH
#define GET_GPIO(g) (*(gpio+13)&(1<<g)) 
// Pull up/pull down
#define GPIO_PULL *(gpio+37)
// Pull up/pull down clock
#define GPIO_PULLCLK0 *(gpio+38)

#define BCM2708_PERI_BASE        0x3F000000
#define GPIO_BASE                (BCM2708_PERI_BASE + 0x200000) /* GPIO controller */

#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)
 
// I/O access
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

//Permite escribir un valor de 0 o 1 en el pin especı́fico configurado como salida.
void set_pin(int pin,int value);

//Permite leer el estado (0,1) de un pin digital
int get_pin(int pin);

//Permite generar un blink (establecer y desestablecer un valor binario) en un pin a una frecuencia determinada, por un tiempo de duración determinado.
int blink(int pin,int freq,int duration);

#endif


