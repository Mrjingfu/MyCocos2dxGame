/********************************************************************
	created:	2013/09/10
	filename: 	xor.h
	author:		reedhong
	
	purpose:	
*********************************************************************/

#ifndef __Reedhong_xor_H__
#define __Reedhong_xor_H__

/* Encrypt 加密函数
	@param	memptr			[in/out]要加密的内存空间数据
			memlen			[in]数据长度
*/
void xor_encrypt(char* memptr, int memlen);



/* Decrypt 解密函数
	@param	memptr			[in/out]要解密的内存空间数据
			memlen			[in]数据长度
			algorithmType	[in]解密算法
*/
void xor_decrypt(char* memptr, int memlen);


#endif