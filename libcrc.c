/* http://mdfs.net/Info/Comp/Comms/CRC16.htm
*  CRCУ�飨ѭ������У�飩������ͨѶ������õ�У�鷽ʽ����Ƕ��ʽ��������У�����Ҫ�õ�CRC �㷨�Ը������ݽ���У��
*  CRC�㷨�˹����㣺
*		CRCУ��һ����ö���ʽ����������CRC�롣	����"���ɶ���ʽ"��λ��w������CRC�㷨��Ҫ�󣬼���ǰҪ��ԭʼ���ݺ�����W��0 ��
*	 
*	��ز��Ĳ��ģ�http://blog.csdn.net/yxtxiaotian/article/details/52149715�� 
*	
* ----------------------------------------------------------------------------
* CRC�����㷨����(����ʵ��)��
*��1������CRC�Ĵ����������丳ֵΪINITIAL_REMAINDER(��������ʼֵ��)��
*��2�������ݵĵ�һ��8-bit�ַ���CRC�Ĵ���������򣬲��ѽ������CRC�Ĵ�����
*��3��CRC�Ĵ���������һλ��LSB���㣬�Ƴ������MSB(�����Чλ)��
*��4�����MSBΪ0���ظ�����������MSBΪ1��CRC�Ĵ�����POLYNOMIAL(������������ʽ����)�����
*��5���ظ���3���4��ֱ��8����λȫ����ɡ���ʱһ��8-bit���ݴ�����ϣ�
*��6���ظ���2����5��ֱ����������ȫ��������ɣ�
*��7������CRC�Ĵ�����������FINAL_XOR_VALUE(��������ֵ��)������������ΪCRCֵ��
 ----------------------------------------------------------
	uint16_t crc16_CCITT(unsigned char *input, int num, uint16_t remainder)    
	{    
		int i;    
		remainder = 0xffff;
		for (; num > 0; num--)             					 // Step through bytes in memory    
		{    
			remainder = remainder ^ (*input++ << 8);    	 // Fetch byte from memory, XOR into CRC top byte    
			for (i = 0; i < 8; i++)            				 // Prepare to rotate 8 bits     
			{    
				if (remainder & 0x8000)           			 // b15 is set...     
					remainder = (remainder << 1) ^ 0x1021;    // rotate and XOR with polynomic     
				else                        				  // b15 is clear...     
					remainder <<= 1;               			   // just rotate     
			}                            					 // Loop for 8 bits     
			remainder ^= 0x0000;              			    // Ensure CRC remains 16-bit value     
		}                              						 // Loop until num=0     
		return (remainder);                   				 // Return updated CRC     
	} 
 ----------------------------------------------------------
*/
    
#include "libcrc.h"   
 
/**  
* The CRC parameters. the configured for CRC16.  
* Simply modify these to switch to another CRC Standard. 
------------------------------------------
	#define POLYNOMIAL          0x8005  
	#define INITIAL_REMAINDER   0x0000  
	#define FINAL_XOR_VALUE     0x0000  
*/ 
    
/**  
* The width of the CRC calculation and result.  
* Modify the typedef for an 8 or 32-bit CRC standard.  
* 	---------------------------------------------
* 	WIDTH : 16;
*	TOPBIT : 0x8000������ȡ���λ(bit);
*/    

#define WIDTH (8 * sizeof(width_t))    
#define TOPBIT (1 << (WIDTH - 1))    

/**  
* An array containing the pre-computed intermediate result for each  
* possible byte of input. This is used to speed up the computation.  
*/    
static width_t crcTable[256];    
    
/**  
 * Initialize the CRC lookup table.  
 * This table is used by crcCompute() to make CRC computation faster.
 * �Ż�����Ч���Ͽ��ǣ������ȼ����lookup table�����Գ�����
 */    
void _crcInit(void)    
{    
    width_t remainder;    
    width_t dividend;    
    int bit;    
    /* Perform binary long division, a bit at a time. */    
    for(dividend = 0; dividend < 256; dividend++)    
    {    
        /* Initialize the remainder.  */    
        remainder = dividend << (WIDTH - 8);    
        /* Shift and XOR with the polynomial.   */    
        for(bit = 0; bit < 8; bit++)    
        {    
            /* Try to divide the current data bit.  */    
            if(remainder & TOPBIT)    
            {    
                remainder = (remainder << 1) ^ POLYNOMIAL;    
            }    
            else    
            {    
                remainder = remainder << 1;    
            }    
        }    
        /* Save the result in the table. */    
        crcTable[dividend] = remainder;    
    }    
} /* crcInit() */    
    
/**  
 * Compute the CRC checksum of a binary message block.  
 * 	@para message, �������������  
 * 	@para nBytes, ���ݵĳ���  
 * 	@note This function expects that crcInit() has been called  
 *       first to initialize the CRC lookup table.  
 */  
    
void libCalcCRC(unsigned char * message, unsigned int nBytes, width_t *result)    
{    
    unsigned int offset;    
    unsigned char byte;    
	
	// ��ʼ��CRC������
	_crcInit();
	
	// ������ʼ������CRC�Ĵ���һ����ʼֵ.
    width_t remainder = INITIAL_REMAINDER;  
	
    /* Divide the message by the polynomial, a byte at a time. */    
    for( offset = 0; offset < nBytes; offset++)    
    {   
		// remainder ��8bit(1Byte)��messageһ���ֽ����㣬�����������crcTable
        byte = (remainder >> (WIDTH - 8)) ^ message[offset];   
		// ������� �� remainderʣ�µ�λ ���㡣ѭ�����������ֽ�. 
        remainder = crcTable[byte] ^ (remainder << 8);    
    }    
    /* The final remainder is the CRC result. 
	*  ����CRC�Ĵ����������롰������ֵ��������������ΪCRCֵ
	*/    
    *result = (remainder ^ FINAL_XOR_VALUE);    
} /* crcCompute() */ 


