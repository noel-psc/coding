#include <stdio.h>
#include <stdint.h>

int main(void)
{
	uint16_t now = 5;
	uint16_t last = 65530;
	printf("%d\n", (int16_t)(uint16_t)(now - last));

	return 0;
}
