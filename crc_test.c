#include "crc.h"  
#include <string.h>
#include <stdio.h>
  
int main(int argc, char *argv[])  
{  
    int i;  
    unsigned char input[] = "123456789";
	width_t output;
	// º∆À„CRC
	CalcCRC(input, strlen((char *)input), &output);

    printf("Before execute CRC: %s\n", input);  
	printf("after execute CRC: %04x\n", output);
  
    return 0;  
}  
