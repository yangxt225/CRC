/**
* CRCУ�飨ѭ������У�飩������ͨѶ������õ�У�鷽ʽ.
* 
*/    
    
#ifndef __CRC_H__    
#define __CRC_H__    

#ifdef __cplusplus
extern "C" {
#endif
       
// unsigned short : CRC16��CRC_CCITT��׼.
typedef unsigned short width_t;   

/**  
* The CRC parameters. Currently configured for CCITT.  
* Simply modify these to switch to another CRC Standard.  
* POLYNOMIAL : ����������ʽ��
* INITIAL_REMAINDER : ������ʼֵ
* FINAL_XOR_VALUE : ������ֵ
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
 * @para message, �������������  
 * @para nBytes, ���ݵĳ���  
 * @note This function expects that crcInit() has been called  
 *       first to initialize the CRC lookup table.  
 */    
void libCalcCRC(unsigned char * message, unsigned int nBytes, width_t *result);    

#ifdef __cplusplus
}
#endif   
	
#endif // __CRC_H__    