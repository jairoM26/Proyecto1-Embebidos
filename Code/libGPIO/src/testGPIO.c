#include <GPIO.h>
#include <stdio.h>

///
/// @file    World.cxx
/// @author  Barthelemy von Haller
///
/// Para verificar la biblioteca deberá crear una aplicación que configure dos gpios de la tarjeta como salida
/// y uno como entrada. La aplicación debe escribir valores binarios (0,1) a uno de los gpio configurados
/// como salidas y en el otro establecer un blink a una frecuencia determinada por una duración de 5 s.
/// Adicionalmente, se debe leer el valor del pin configurado como entrada y presentarlo en pantalla.

int main(int argc, char const *argv[])
{
	//say_hello();
	printf("Setup..\n");
	setup_io();

	int g,rep;

	// Set GPIO pins 7-11 to output
	for (g=7; g<=11; g++)
	{
		pinMode(g,0);// 0 = Output
		//INP_GPIO(g); // must use INP_GPIO before we can use OUT_GPIO
		//OUT_GPIO(g);
	}

	for (rep=0; rep<10; rep++)
	{
		for (g=7; g<=11; g++)
		{
			//GPIO_SET = 1<<g;
			digitalWrite(g, 1);
			sleep(1);
		}
		for (g=7; g<=11; g++)
		{
			//GPIO_CLR = 1<<g;
			digitalWrite(g, 0);			
			sleep(1);
		}
	}

	printf("Done.\n");

	return 0;
}



