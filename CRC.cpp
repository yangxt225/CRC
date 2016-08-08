/* http://mdfs.net/Info/Comp/Comms/CRC16.htm
/* CRC校验（循环冗余校验）是数据通讯中最常采用的校验方式。在嵌入式
软件开发中，经常要用到CRC 算法对各种数据进行校验
CRC算法人工计算：
	CRC校验一般采用多项式除法来计算CRC码。
	根据"生成多项式"的位宽w，按照CRC算法的要求，计算前要在原始数据后填上W个0 。
	 
	相关博文参阅：http://blog.csdn.net/yxtxiaotian/article/details/52149715。 
*/ 
#include <stdint.h>
#include <stdio.h>

#define POLY        0x1021  // CRC_CCITT

/**  
 * Calculating CRC-16 in 'C'  
 * @para addr, start of data  
 * @para num, length of data  
 * @para crc, incoming CRC  
 */ 
 /*
 CRC常见算法描述(编码实现)：
（1）      设置CRC寄存器，并给其赋值为“余数初始值”。
（2）      将数据的第一个8-bit字符与CRC寄存器进行异或，并把结果存入CRC寄存器。
（3）      CRC寄存器向左移一位，LSB补零，移出并检查MSB。
（4）      如果MSB为0，重复第三步；若MSB为1，CRC寄存器与0x31相异或。
（5）      重复第3与第4步直到8次移位全部完成。此时一个8-bit数据处理完毕。
（6）      重复第2至第5步直到所有数据全部处理完成。
（7）      最终CRC寄存器的内容与“结果异或值”进行异或操作后即为CRC值。
 */   
uint16_t crc16(unsigned char *addr, int num, uint16_t crc)    
{    
    int i;    
    for (; num > 0; num--)              /* Step through bytes in memory */    
    {    
        crc = crc ^ (*addr++ << 8);     /* Fetch byte from memory, XOR into CRC top byte*/    
        for (i = 0; i < 8; i++)             /* Prepare to rotate 8 bits */    
        {    
            if (crc & 0x8000)            /* b15 is set... */    
                crc = (crc << 1) ^ POLY;    /* rotate and XOR with polynomic */    
            else                          /* b15 is clear... */    
                crc <<= 1;                  /* just rotate */    
        }                             /* Loop for 8 bits */    
        crc ^= 0x0000;                  /* Ensure CRC remains 16-bit value */    
    }                               /* Loop until num=0 */    
    return(crc);                    /* Return updated CRC */    
}    

int main()
{
	unsigned char data1[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};    
	unsigned char data2[] = {'5', '6', '7', '8', '9'};    
	unsigned short c1, c2;    
	c1 = crc16(data1, 9, 0xffff);    
	c2 = crc16(data1, 4, 0xffff);    
	c2 = crc16(data2, 5, c2);    
	printf("%04x\n", c1);    
	printf("%04x\n", c2);   
}


