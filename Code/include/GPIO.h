
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define BCM2708_PERI_BASE        0x3F000000
#define GPIO_BASE                (BCM2708_PERI_BASE + 0x200000) /* GPIO controller */
 
#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)
void say_hello(void);

int  mem_fd;
void *gpio_map;
 
// I/O access
volatile unsigned *gpio;

#define GET_GPIO(g) (*(gpio+13)&(1<<g)) // 0 if LOW, (1<<g) if HIGH
 
#define GPIO_PULL *(gpio+37) // Pull up/pull down
#define GPIO_PULLCLK0 *(gpio+38) // Pull up/pull down clock

// Set up a memory regions to access GPIO
void setup_io();

//Permite establecer el modo (entrada/salida) de un pin específico (número de pin/gpio)
int pinMode(int pin, int MODE);

//Permite escribir un valor de 0 o 1 en el pin especı́fico configurado como salida.
int digitalWrite(int pin, int value);

//Permite leer el estado (0,1) de un pin digital
int digitalRead(int pin);

//Permite generar un blink (establecer y desestablecer un valor binario) en un pin a una frecuencia determinada, por un tiempo de duración determinado.
int blink(int pin,int freq,int duration);



