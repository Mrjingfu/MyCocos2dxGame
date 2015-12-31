/********************************************************************
	created:	2013/09/10
	filename: 	XXTEA.cpp
	author:		reedhong
	
	purpose:	
*********************************************************************/

#include <cmath>
#include <cstring>
#include <cstdlib>
using namespace std;
#include "XXTEA.h"
const unsigned int  s_DefaultEncryptKey[4] = {0x474DC837, 0xBB085D81, 0xE39E718F, 0x31A91527};
#define XXTEA_ALIGNMENT_BYTES   8



#define DELTA 0x9e3779b9
#define MX (((z>>5^y<<2) + (y>>3^z<<4)) ^ ((sum^y) + (key[(p&3)^e] ^ z)))
static void btea(unsigned int *v, int n, unsigned int const key[4])
{
	unsigned int y, z, sum;
	unsigned p, rounds, e;
	if (n > 1)                      // Coding Part
	{
		rounds = 6 + 52/n;
		sum = 0;
		z = v[n-1];
		do
		{
			sum += DELTA;
			e = (sum >> 2) & 3;
			for (p=0; p<n-1; p++)
			{
				y = v[p+1]; 
				z = v[p] += MX;
			}
			y = v[0];
			z = v[n-1] += MX;
		} while (--rounds);
	}
	else if (n < -1)                // Decoding Part
	{
		n = -n;
		rounds = 6 + 52/n;
		sum = rounds*DELTA;
		y = v[0];
		do
		{
			e = (sum >> 2) & 3;
			for (p=n-1; p>0; p--)
			{
				z = v[p-1];
				y = v[p] -= MX;
			}
			z = v[n-1];
			y = v[0] -= MX;
		} while ((sum -= DELTA) != 0);
	}
}

size_t XXTEA_encrypt(const unsigned char * pInputBuffer, 
									   unsigned char * pOutputBuffer, 
									   size_t nLength, 
									   unsigned int const * pUserDefineKey)
{
	size_t nResult = 0;
	if (pInputBuffer && pOutputBuffer && nLength > 0)
	{
		nResult = 2* nLength / XXTEA_ALIGNMENT_BYTES+ (nLength % XXTEA_ALIGNMENT_BYTES ? 1 : 0);
		memset(pOutputBuffer, 0, nResult * 8);
		memcpy(pOutputBuffer, pInputBuffer, nLength);
		unsigned int const * pnKey = pUserDefineKey ? (unsigned int const *)pUserDefineKey : s_DefaultEncryptKey;
		btea((unsigned int *)pOutputBuffer, (int)nResult, pnKey);

		nResult *= 4;
	}
	else if(nLength > 0)
		nResult = ((nLength / XXTEA_ALIGNMENT_BYTES) + 
		(nLength % XXTEA_ALIGNMENT_BYTES ? 1 : 0)) * XXTEA_ALIGNMENT_BYTES;

	return nResult;
}


bool XXTEA_decrypt(const unsigned char * pInputBuffer, 
									 unsigned char * pOutputBuffer, 
									 size_t nLength, 
									unsigned int const * pUserDefineKey)
{
	if(nLength % 4)
		return false;

	bool result = false;

	if(pInputBuffer && pOutputBuffer && nLength > 0)
	{
		int nSize = (nLength / XXTEA_ALIGNMENT_BYTES) * 2+ (nLength % XXTEA_ALIGNMENT_BYTES ? 1 : 0);
		memset(pOutputBuffer, 0, nLength);
		memcpy(pOutputBuffer, pInputBuffer, nLength);
		unsigned int const * pnKey = pUserDefineKey ? (unsigned int const *)pUserDefineKey : s_DefaultEncryptKey;
		btea((unsigned int *)pOutputBuffer, -nSize, pnKey);
		result = true;
	}

	return result;
}