/********************************************************************
	created:	2013/09/10
	filename: 	xor.cpp
	author:		reedhong
	
	purpose:	
*********************************************************************/

#include <cmath>
#include <cstring>
#include <cstdlib>
using namespace std;

#include "xor.h"




static void XOR( char *data, char *key, int datalen, int keylen)
{
	for (int i=0; i<datalen; i++)
		*(data+i) ^= *(key+i%keylen);
}


//移位(pos>0 右移pos位, pos<0 左移|pos|位)
static void MOVE( char *data, int datalen, int pos )
{
	if (pos == 0 || datalen == 0 || pos%datalen == 0)
		return;

	int realpos = abs(pos);
	while (realpos > datalen)
		realpos -= datalen;

	char* tmp = new char[realpos];
	char* ptr;
	if (pos > 0)
	{
		memcpy( tmp, data+datalen-realpos, realpos );
		ptr = data+datalen-1;
		for (; ptr>data+realpos-1; ptr--)
			*ptr = *(ptr-realpos);
		memcpy( data, tmp, realpos );
	}
	else
	{
		memcpy( tmp, data, realpos );
		ptr = data;
		for (; ptr<data+datalen-realpos; ptr++)
			*ptr = *(ptr+realpos);
		memcpy( data + datalen - realpos, tmp, realpos );
	}
	delete[] tmp;
}

void xor_encrypt(char* memptr, int memlen,const char* dekey)
{
	if (memlen == 0 || !memptr)
		return;

	char key1[XOR_KEY1_LEN];
	memcpy(key1,KT_ECRP_KEY1,XOR_KEY1_LEN);
	MOVE( memptr, memlen,MOVE_POS1);		
	XOR( memptr, key1, memlen, XOR_KEY1_LEN );
	char key2[XOR_KEY2_LEN];
    //modified by lichuang
    memcpy(key2,dekey,XOR_KEY2_LEN);
//	memcpy(key2,KT_ECRP_KEY2,XOR_KEY2_LEN);
	MOVE( memptr, memlen,-MOVE_POS2);
	XOR( memptr, key2, memlen, XOR_KEY2_LEN );

}

void xor_decrypt(char* memptr, int memlen,const char* dekey)
{
	if (memlen == 0 || !memptr)
		return;

	char key2[XOR_KEY2_LEN];
    //modified by lichuang
    memcpy(key2,dekey,XOR_KEY2_LEN);
//	memcpy(key2,KT_ECRP_KEY2,XOR_KEY2_LEN);	
	XOR( memptr, key2, memlen, XOR_KEY2_LEN );
	MOVE( memptr, memlen,MOVE_POS2);	

	char key1[XOR_KEY1_LEN];
	memcpy(key1,KT_ECRP_KEY1,XOR_KEY1_LEN);
	XOR( memptr, key1, memlen, XOR_KEY1_LEN );
	MOVE( memptr, memlen,-MOVE_POS1);	
}