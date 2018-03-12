#include <GPIO.h>

void say_hello(void)
{
	printf("Hello World!!\n");
}


void setup_io()
{
   /* open /dev/mem */
   if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) {
      printf("can't open /dev/mem \n");
      exit(-1);
   }
 
   /* mmap GPIO */
   gpio_map = mmap(
      NULL,             //Any adddress in our space will do
      BLOCK_SIZE,       //Map length
      PROT_READ|PROT_WRITE,// Enable reading & writting to mapped memory
      MAP_SHARED,       //Shared with other processes
      mem_fd,           //File to map
      GPIO_BASE         //Offset to GPIO peripheral
   );
 
   close(mem_fd); //No need to keep mem_fd open after mmap
 
   if (gpio_map == MAP_FAILED) {
      printf("mmap error %d\n", (int)gpio_map);//errno also set!
      exit(-1);
   }
 
   // Always use volatile pointer!
   gpio = (volatile unsigned *)gpio_map;
 
 
} // setup_io

//Or use #define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))
int pinMode(int pin, int MODE)
{
	if(MODE==0)//Output
	{
		*(gpio+((pin)/10)) &= ~(7<<(((pin)%10)*3));
		*(gpio+((pin)/10)) |=  (1<<(((pin)%10)*3));
		return 1;
	}
	else if(MODE==1)//Input
	{
		*(gpio+((pin)/10)) &= ~(7<<(((pin)%10)*3));
		return 1;
	}
	else
	{
		return 0;
	}
}

int digitalWrite(int pin, int value)
{
	*(gpio+7)=value;
	return 1;
}

int digitalRead(int pin)
{
	return (*(gpio+13)&(1<<pin));
}

int blink(int pin,int freq,int duration)
{
	return 1;
}

