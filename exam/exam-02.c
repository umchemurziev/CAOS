#include <inttypes.h>
#include <stdio.h>


int main (void)
{
	uint32_t p = 0;
	uint32_t q = 0;
	uint32_t n = 0;
	scanf("%" SCNd32 " %" SCNd32 " %" SCNd32, &p, &q, &n);
	uint32_t ans[1000000] = { p / q };


	uint32_t prev = p;
	for (size_t i = 1; i <= n; ++i)
	{
		p *= 10;
		ans[i] = (p / q) * (prev < q);
		p = p % q;
	}

	if (prev < q)
	{
		p *= 10;
		uint32_t end = p / q;
		ans[n] = ans[n] + 1 * ( end > 5 || ( end == 5 && ans[n] % 2 == 1 ) );

		for (size_t i = n; i > 0; --i)
		{
			if (ans[i] < 10) break;
			++ans[i - 1];
			ans[i] = 0;
		}
	}

	printf("%" PRId32 ".", ans[0]);
	for (size_t i = 1; i <= n; ++i)
	{
		printf("%" PRId32, ans[i]);

	}
	printf("\n");

	return 0;
}
