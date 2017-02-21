#include "crc.h"  
#include <string.h>
#include <stdio.h>
  
int main(int argc, char *argv[])  
{  
    int i;  
    unsigned char input[] = "123456789";
	width_t output;
	// 初始化CRC常量表
	crcInit();
	// 计算CRC
	crcCompute(input, strlen((char *)input), &output);

    printf("Before execute CRC: %s\n", input);  
	printf("after execute CRC: %04x\n", output);
  
    return 0;  
}  
