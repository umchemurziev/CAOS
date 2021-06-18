#include <inttypes.h>
#include <stdio.h>


int main (void)
{
	uint32_t align = 0;
	uint32_t pad = 0;
	uint32_t size = 0;

	uint32_t cnt = 0;
	uint32_t sz = 0;

	while (scanf("%" SCNd32 " %" SCNd32, &align, &pad) == 2)
	{
		size = size * (size > pad) + pad * (pad > size);
		sz += align;
		++cnt;
	}

	uint32_t ans = cnt * size;

	printf("%" PRId32 " ", ans);
	printf("%" PRId32 "\n", ans - sz);

	return 0;
}
