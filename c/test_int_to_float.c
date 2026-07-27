#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef union {
    uint8_t bytes[4];
    float value;
} FloatConverter;

int main(void)
{
	uint8_t t = 0;
	float f = 0.0;
	uint8_t data[4] = {0xaa, 0xaa, 0xaa, 0x00};
	FloatConverter converter;
	memcpy(converter.bytes, &data[0], 4);
	f = converter.value;

	printf("%f\n", f);

	uint8_t *pdata = &converter.bytes[0];
	converter.value = 1.23;
	printf("%x %x %x %x\n", pdata[0], pdata[1], pdata[2], pdata[3]);

	return 0;
}
