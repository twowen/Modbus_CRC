#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> /* for mingw32 compiler */

#define CRC_INIT 0xffff
#define CRC_POLY 0xa001

static uint16_t calc_crc16 (uint8_t *data, int data_len)
{
	uint16_t crc = CRC_INIT;
	uint8_t lsb;
	int i;

	if (data == NULL)
		return 0;

	while (data_len--) {
		crc ^= *data++;
		for (i = 0; i < 8; i++) {
			lsb = crc & 0x1;
			crc >>= 1;
			if (lsb)
				crc ^= CRC_POLY;
		}
	}

	return crc;
}

/*
 * e.g. Data: 01 03 00 00 00 06, CRC: C5 C8
 */

int main (int argc, char *argv[])
{
    uint8_t arr[6];
    int i;

    for (i = 0; i < 6; i++)
		arr[i] = strtol(argv[i + 1], NULL, 16);

    printf("CRC value: 0x%04X\n", calc_crc16(arr, sizeof(arr) / sizeof(arr[0])));
    /* The result should be swapped */

    return 0;
}
