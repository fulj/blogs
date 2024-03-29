#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double Add(double x, double y){
	return x+y;
}
double Sub(double x, double y){
	return x-y;	
}
double Mul(double x, double y){
	return x*y;	
}
double Div(double x, double y){
	return x/y;
}
double (*funcTable[5])(double, double)
		= {Add , Sub, Mul, Div, pow};

char *msgTable[5] = {"Sum", "Difference", "Product", "Quotient","Power"};

int main()
{
	int i;
	double x = 0, y = 0;
	printf("Enter two operands for some arithmetic:\n");
	if(scanf("%1f %1f", &x, &y)!=2)
		printf("Invalid input.\n");
	for(i =0; i<5; ++i)
		printf("%10s: %6.2f\n", msgTable[i], funcTable[i](x, y));
	return 0;
}
