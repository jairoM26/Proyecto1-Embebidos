#include <config.h>
#include <stdio.h>
#include <math.h>

void say_hello(void)
{
puts("Hello World!");
puts("This is " PACKAGE_STRING".");
}


float sum(int a, int b){
	return a+b;
}

float sub(int a, int b){
	return a-b;
}

float mul(int a, int b){
	return a*b;
}

float div(int a, int b){
	return a/b;
}

float squ(int a){
	//return 0.0;
	return sqrt (a);
}

