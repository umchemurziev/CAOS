#include <stdio.h>


void myexp(double x, double *r);

int main() {
	double a;
	double b = 0.0;
	myexp(b, &a);
	printf("%lf\n", a);
}
