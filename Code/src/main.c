#include <say.h>

int main(int argc, char const *argv[])
{
	float rAdd = sum(50,10);
	float rSub = sub(50,10);
	float rMul = mul(50,10);
	float rDiv = div(50,10);
	float rSqr = squ(100);	
	printf("50+10: %f\n",rAdd);
	printf("50-10: %f\n",rSub);
	printf("50*10: %f\n",rMul);	
	printf("50/10: %f\n",rDiv);
	printf("100^(1/2): %f\n",rSqr);
		
	return 0;
}
