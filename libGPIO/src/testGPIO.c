#include <GPIO.h>
#include <stdio.h>

int main(int argc, char **argv)
{
  
 
  // Set up gpi pointer for direct register access
  setup_io();
 
  // Switch GPIO 7..11 to output mode
 

 
  // Set GPIO pins 7-11 to output
  configure_pin(9);
  configure_pin(10);
  configure_pin(11);

  while(1){
	  if (get_pin(9)==0){
		set_pin(10,1);	
	  }
	  if (get_pin(9)==1){
		set_pin(10,0);	
	  }
	  sleep(1);
	  
  } 
  return 0;
}

