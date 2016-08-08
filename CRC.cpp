/* http://mdfs.net/Info/Comp/Comms/CRC16.htm
/* CRCУ�飨ѭ������У�飩������ͨѶ������õ�У�鷽ʽ����Ƕ��ʽ
��������У�����Ҫ�õ�CRC �㷨�Ը������ݽ���У��
CRC�㷨�˹����㣺
	CRCУ��һ����ö���ʽ����������CRC�롣
	����"���ɶ���ʽ"��λ��w������CRC�㷨��Ҫ�󣬼���ǰҪ��ԭʼ���ݺ�����W��0 ��
	 
	��ز��Ĳ��ģ�http://blog.csdn.net/yxtxiaotian/article/details/52149715�� 
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
 CRC�����㷨����(����ʵ��)��
��1��      ����CRC�Ĵ����������丳ֵΪ��������ʼֵ����
��2��      �����ݵĵ�һ��8-bit�ַ���CRC�Ĵ���������򣬲��ѽ������CRC�Ĵ�����
��3��      CRC�Ĵ���������һλ��LSB���㣬�Ƴ������MSB��
��4��      ���MSBΪ0���ظ�����������MSBΪ1��CRC�Ĵ�����0x31�����
��5��      �ظ���3���4��ֱ��8����λȫ����ɡ���ʱһ��8-bit���ݴ�����ϡ�
��6��      �ظ���2����5��ֱ����������ȫ��������ɡ�
��7��      ����CRC�Ĵ����������롰������ֵ��������������ΪCRCֵ��
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


