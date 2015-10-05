/********************************************************************
	created:	2013/09/10
	filename: 	XXTEA.h
	author:		reedhong
	
	purpose:	
*********************************************************************/

#ifndef __Reedhong_XXTEA_H__
#define __Reedhong_XXTEA_H__


/*!	\fn XXTEA_encrypt(const unsigned char * pInputBuffer, 
*                      unsigned char * pOutputBuffer)
*	\brief Encrypt source data with XXTEA algorithm.
*
*	\param pInputBuffer Buffer of input data.
*  \param pOutputBuffer Buffer to output encrypt data. Function won't check
*          buffer overflow. User should provide buffer with enough size.
*  \param nLength Byte size of data in input buffer. Caution : It's must be
*          eight bytes aligned. Otherwise may cause unknown error.
*  \param pUserDefineKey User defined encrypt key. It should be contain 
*          more than four 32bit interger, otherwise may cause unknown error.
*          This param set to NULL to use default encrypt key.
*	\return If pOutputBuffer pointer is NULL, function will return buffer 
*              size needed to contain output data.
*          Otherwise return value is the encrypt data size.
*/
size_t XXTEA_encrypt(const unsigned char * pInputBuffer, unsigned char * pOutputBuffer, size_t nLength, unsigned int const * pUserDefineKey);



/*!	\fn XXTEA_decrypt(const unsigned char * pInputBuffer, 
    *                      unsigned char * pOutputBuffer)
    *	\brief Decrypt source data with XXTEA algorithm.
    *
    *	\param pInputBuffer Buffer of input data.
    *  \param pOutputBuffer Buffer to output encrypt data. Function won't check
    *          buffer overflow. Buffer should be same or bigger than input 
    *          buffer. If decrypt data is string, user must alloc the terminate
    *          charator memory and set it to 0.
    *  \param nLength Byte size of data in input buffer. Caution : It's must be
    *          eight bytes aligned. Otherwise may cause unknown error.
    *  \param pUserDefineKey User defined encrypt key. It should be contain 
    *          more than four 32bit interger, otherwise may cause unknown error.
    *          This param set to NULL to use default encrypt key.
    *	\return If nLength is not eight bytes aligned, the input data is bad,
    *          return false, otherwise return true.
    */
bool XXTEA_decrypt(const unsigned char * pInputBuffer, unsigned char * pOutputBuffer, size_t nLength, unsigned int const  * pUserDefineKey);


#endif