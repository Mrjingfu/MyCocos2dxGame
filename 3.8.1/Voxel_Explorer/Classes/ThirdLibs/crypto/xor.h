/********************************************************************
	created:	2013/09/10
	filename: 	xor.h
	author:		reedhong
	
	purpose:	
*********************************************************************/

#ifndef __Reedhong_xor_H__
#define __Reedhong_xor_H__

const int XOR_KEY1_LEN = 13;
#define KT_ECRP_KEY1 "e30ddb77251ab"

const int XOR_KEY2_LEN = 23;
#define KT_ECRP_KEY2 "db1ef22ed6d9c2c4191f86e"

const int MOVE_POS1 = 133;
const int MOVE_POS2 = 71;

/* Encrypt 加密函数
	@param	memptr			[in/out]要加密的内存空间数据
			memlen			[in]数据长度
*/
void xor_encrypt(char* memptr, int memlen, const char* dekey = KT_ECRP_KEY2);



/* Decrypt 解密函数
	@param	memptr			[in/out]要解密的内存空间数据
			memlen			[in]数据长度
			algorithmType	[in]解密算法
*/
void xor_decrypt(char* memptr, int memlen,const char* dekey = KT_ECRP_KEY2);


#endif