/**
* CRC校验算法(CCITT)
* CRC校验（循环冗余校验）是数据通讯中最常采用的校验方式。在嵌入式软件开发中，经常要用到CRC 算法对各种数据进行校验.
* CRC算法人工计算：CRC校验一般采用多项式除法来计算CRC码。根据"生成多项式"的位宽w，按照CRC算法的要求，计算前要在原始数据后填上W个0  
* 
*/    
    
#ifndef __CRC_H__    
#define __CRC_H__    

#ifdef __cplusplus
extern "C" {
#endif
       
// unsigned short : CRC16或CRC_CCITT标准.
typedef unsigned short width_t;   

/**  
* The CRC parameters. Currently configured for CCITT.  
* Simply modify these to switch to another CRC Standard.  
* POLYNOMIAL : 除数（多项式）
* INITIAL_REMAINDER : 余数初始值
* FINAL_XOR_VALUE : 结果异或值
*/    
#define POLYNOMIAL          0x1021    
#define INITIAL_REMAINDER   0xFFFF    
#define FINAL_XOR_VALUE     0x0000     
	   
/**  
 * Initialize the CRC lookup table.  
 * This table is used by crcCompute() to make CRC computation faster.  
 */    
void crcInit(void);    
    
/**  
 * Compute the CRC checksum of a binary message block.  
 * @para message, 用来计算的数据  
 * @para nBytes, 数据的长度  
 * @note This function expects that crcInit() has been called  
 *       first to initialize the CRC lookup table.  
 */    
void crcCompute(unsigned char * message, unsigned int nBytes, width_t *result);    

#ifdef __cplusplus
}
#endif   
	
#endif // __CRC_H__    