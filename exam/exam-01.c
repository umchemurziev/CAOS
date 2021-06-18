#include <stdio.h>


enum
{
	FRONT = 500000000
};

int foo (int n)
{
	if (n >= FRONT)
	{
		n -= FRONT * 2;
	}

	return n;
}

int main (void)
{
	int a = 0;
	int b = 0;
	while (scanf("%d %d", &a, &b) == 2)
	{
		printf("%d\n",
			(a < 0 || b < 0 || a >= FRONT * 2 || b >= FRONT * 2)
			? -1
			: foo(a) - foo(b)
		);
	}

	return 0;
}
