/**
* CRC校验（循环冗余校验）是数据通讯中最常采用的校验方式.
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
void _crcInit(void);    
    
/**  
 * Compute the CRC checksum of a binary message block.  
 * @para message, 用来计算的数据  
 * @para nBytes, 数据的长度  
 * @note This function expects that crcInit() has been called  
 *       first to initialize the CRC lookup table.  
 */    
void libCalcCRC(unsigned char * message, unsigned int nBytes, width_t *result);    

#ifdef __cplusplus
}
#endif   
	
#endif // __CRC_H__    