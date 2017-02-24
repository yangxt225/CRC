/* http://mdfs.net/Info/Comp/Comms/CRC16.htm
*  CRC校验（循环冗余校验）是数据通讯中最常采用的校验方式。在嵌入式软件开发中，经常要用到CRC 算法对各种数据进行校验
*  CRC算法人工计算：
*		CRC校验一般采用多项式除法来计算CRC码。	根据"生成多项式"的位宽w，按照CRC算法的要求，计算前要在原始数据后填上W个0 。
*	 
*	相关博文参阅：http://blog.csdn.net/yxtxiaotian/article/details/52149715。 
*	
* ----------------------------------------------------------------------------
* CRC常见算法描述(编码实现)：
*（1）设置CRC寄存器，并给其赋值为INITIAL_REMAINDER(“余数初始值”)；
*（2）将数据的第一个8-bit字符与CRC寄存器进行异或，并把结果存入CRC寄存器；
*（3）CRC寄存器向左移一位，LSB补零，移出并检查MSB(最高有效位)；
*（4）如果MSB为0，重复第三步；若MSB为1，CRC寄存器与POLYNOMIAL(“除数（多项式）”)相异或；
*（5）重复第3与第4步直到8次移位全部完成。此时一个8-bit数据处理完毕；
*（6）重复第2至第5步直到所有数据全部处理完成；
*（7）最终CRC寄存器的内容与FINAL_XOR_VALUE(“结果异或值”)进行异或操作后即为CRC值。
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
*	TOPBIT : 0x8000，用于取最高位(bit);
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
 * 优化：从效率上考虑，可以先计算出lookup table，存以常量。
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
 * 	@para message, 用来计算的数据  
 * 	@para nBytes, 数据的长度  
 * 	@note This function expects that crcInit() has been called  
 *       first to initialize the CRC lookup table.  
 */  
    
void libCalcCRC(unsigned char * message, unsigned int nBytes, width_t *result)    
{    
    unsigned int offset;    
    unsigned char byte;    
	
	// 初始化CRC常量表
	_crcInit();
	
	// 余数初始化：给CRC寄存器一个初始值.
    width_t remainder = INITIAL_REMAINDER;  
	
    /* Divide the message by the polynomial, a byte at a time. */    
    for( offset = 0; offset < nBytes; offset++)    
    {   
		// remainder 高8bit(1Byte)与message一个字节运算，结果用来检索crcTable
        byte = (remainder >> (WIDTH - 8)) ^ message[offset];   
		// 检索结果 与 remainder剩下的位 运算。循环处理所有字节. 
        remainder = crcTable[byte] ^ (remainder << 8);    
    }    
    /* The final remainder is the CRC result. 
	*  最终CRC寄存器的内容与“结果异或值”进行异或操作后即为CRC值
	*/    
    *result = (remainder ^ FINAL_XOR_VALUE);    
} /* crcCompute() */ 


