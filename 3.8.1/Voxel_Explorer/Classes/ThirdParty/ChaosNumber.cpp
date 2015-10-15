/********************************************************************
	created:	2013/09/09
	filename: 	ChaosNumber.h
	author:		XiaoFeng on 12-3-29, modified by reedhong 
	
	purpose:	
*********************************************************************/

#include <iostream>
#include <ctime>
using namespace std;

#include "cocos2d.h"
using namespace cocos2d;
#include "ChaosNumber.h"

typedef char MATRIX[4][4];
CChaosNumber::CChaosNumber()
{
    m_ValueType = valueNone;
    m_pMatrix = NULL;
}

CChaosNumber::CChaosNumber(const long lValue)
{
    m_ValueType = valueNone;
    m_pMatrix = NULL;
    SetLongValue(lValue);
}

CChaosNumber::CChaosNumber(const int nValue)
{
    m_ValueType = valueNone;
    m_pMatrix = NULL;
    SetLongValue((long)nValue);
}

CChaosNumber::CChaosNumber(const float fValue)
{
    m_ValueType = valueNone;
    m_pMatrix = NULL;
    SetFloatValue(fValue);
}

CChaosNumber::CChaosNumber(const CChaosNumber& another)
{
	m_pMatrix = NULL;
	if(valueLong == another.GetValueType())
        SetLongValue(another.GetLongValue());
    else if(valueFloat == another.GetValueType())
        SetFloatValue(another.GetFloatValue());
}

CChaosNumber::~CChaosNumber()
{
    m_ValueType = valueNone;
    CC_SAFE_DELETE_ARRAY(m_pMatrix);
}


float CChaosNumber::GetFloatValue() const 
{
    float fRet = 0;
    if (valueLong == m_ValueType)
        fRet = GetLongValue();
    else
        GetValueFromMatric(&fRet);

    return fRet;
}

long CChaosNumber::GetLongValue() const 
{
    int lRet = 0;
    if (valueFloat == m_ValueType)
        lRet = GetFloatValue();
    else
        GetValueFromMatric(&lRet);

    return lRet;
}

void CChaosNumber::SetFloatValue(float value)
{
    PutValueToMatrix(&value);
    m_ValueType = valueFloat;
}

void CChaosNumber::SetLongValue(long value)
{
    PutValueToMatrix(&value);
    m_ValueType = valueLong;
}


void CChaosNumber::GenerateOrder()
{
//    srand(time(NULL));
    char cTemp = abs((rand() % 4));
    m_BytePos[0][0] = cTemp;

    while (cTemp == m_BytePos[0][0])
        cTemp = abs((rand() % 4));
    m_BytePos[1][0] = cTemp;

    while (cTemp == m_BytePos[0][0] || cTemp == m_BytePos[1][0])
        cTemp = abs((rand() % 4));
    m_BytePos[2][0] = cTemp;

    m_BytePos[3][0] = (1+2+3) - m_BytePos[0][0] - m_BytePos[1][0] - m_BytePos[2][0];
}

void CChaosNumber::PutValueToMatrix(void * pValue) 
{
    if (m_pMatrix)
        CC_SAFE_DELETE_ARRAY(m_pMatrix);
    m_pMatrix =  new char[sizeof(char)*4*4];
    MATRIX *pTempMatrix = (MATRIX *)m_pMatrix;
    char * pTemp = (char *)pValue;
    GenerateOrder();
    for (int i = 0; i < 4; i++)
    {
        m_BytePos[i][1] = abs((rand() % 4));
        (*pTempMatrix)[m_BytePos[i][0]][m_BytePos[i][1]] = pTemp[i];
    }
}

void CChaosNumber::GetValueFromMatric(void * pBuffer) const 
{
    if (valueNone != m_ValueType)
    {
        char * pTemp = (char *)pBuffer;
        MATRIX * pTempMatrix = (MATRIX *)m_pMatrix;
        for (int i = 0; i < 4; i++)
            pTemp[i] = (*pTempMatrix)[m_BytePos[i][0]][m_BytePos[i][1]];
    }
}

valueType CChaosNumber::GetValueType() const
{
    return m_ValueType;
}


CChaosNumber::operator long()
{
    return GetLongValue();
}

CChaosNumber::operator int()
{
    int nRet = (int)GetLongValue();
    return nRet;
}


CChaosNumber::operator float()
{
    return GetFloatValue();
}

CChaosNumber& CChaosNumber::operator=(CChaosNumber& another)
{
    if (&another != this)
    {
        if(valueLong == another.GetValueType())
            SetLongValue(another.GetLongValue());
        else if(valueFloat == another.GetValueType())
            SetFloatValue(another.GetFloatValue());
    }

    return *this;
}

CChaosNumber& CChaosNumber::operator=(long lValue)
{
    SetLongValue(lValue);
    return *this;
}

CChaosNumber& CChaosNumber::operator=(int nValue)
{
    SetLongValue((long)nValue);
    return *this;
}

CChaosNumber& CChaosNumber::operator=(float fValue)
{
    SetFloatValue(fValue);
    return *this;
}
CChaosNumber& CChaosNumber::operator +=(int lValue)
{
	int nRet = (int)GetLongValue();
	int result = nRet + lValue;
	SetLongValue((long)result);
	return *this;
}
long CChaosNumber::operator+(long lValue)
{
    return GetLongValue() + lValue;
}

float CChaosNumber::operator+(float fValue)
{
    return GetFloatValue() + fValue;
}

int CChaosNumber::operator+(int nValue)
{
    int nRet = (int)GetLongValue();
    return nRet + nValue;
}

long CChaosNumber::operator-(long lValue)
{
    return GetLongValue() - lValue;
}

int CChaosNumber::operator-(int nValue)
{
    int nRet = (int)GetLongValue();
    return nRet - nValue;
}

float CChaosNumber::operator-(float fValue)
{
    return GetFloatValue() - fValue;
}

long CChaosNumber::operator*(long lValue)
{
    return GetLongValue() * lValue;
}

int CChaosNumber::operator*(int nValue)
{
    int nRet = (int)GetLongValue();
    return nRet * nValue;
}

float CChaosNumber::operator*(float fValue)
{
    return GetFloatValue() * fValue;
}

long CChaosNumber::operator/(long lValue)
{
    return GetLongValue() / lValue;
}

int CChaosNumber::operator/(int nValue)
{
    int nRet = (int)GetLongValue();
    return nRet / nValue;
}

float CChaosNumber::operator/(float fValue)
{
    return GetFloatValue() / fValue;
}

CChaosNumber& CChaosNumber::operator++()
{
    if (valueLong == m_ValueType)
        SetLongValue(GetLongValue()+1);
    else if(valueFloat == m_ValueType)
        SetFloatValue(GetFloatValue()+1);
    else
        SetLongValue(1);

    return *this;
}

CChaosNumber& CChaosNumber::operator--()
{
    if (valueLong == m_ValueType)
        SetLongValue(GetLongValue()-1);
    else if(valueFloat == m_ValueType)
        SetFloatValue(GetFloatValue()-1);
    else
        SetLongValue(-1);
    
    return *this;
}

bool CChaosNumber::operator==(CChaosNumber& another)
{
    bool bRet = false;
    if (valueLong == m_ValueType)
        bRet = GetLongValue() == another.GetLongValue();
    else if (valueFloat == m_ValueType)
        bRet = GetFloatValue() == another.GetFloatValue();

    return bRet;
}

bool CChaosNumber::operator==(long lValue)
{
    if (valueNone == m_ValueType)
        return false;
    return GetLongValue() == lValue;
}

bool CChaosNumber::operator==(int nValue)
{
    if (valueNone == m_ValueType)
        return false;
    return GetLongValue() == (long)nValue;
}

bool CChaosNumber::operator==(float fValue)
{
    if (valueNone == m_ValueType)
        return false;
    return GetFloatValue() == fValue;
}

bool CChaosNumber::operator>=(CChaosNumber& another)
{
    bool bRet = false;
    if (valueLong == m_ValueType)
        bRet = GetLongValue() >= another.GetLongValue();
    else if (valueFloat == m_ValueType)
        bRet = GetFloatValue() >= another.GetFloatValue();
    
    return bRet;
}

bool CChaosNumber::operator>=(long lValue)
{
    if (valueNone == m_ValueType)
        return 0 >= lValue;
    return GetLongValue() >= lValue;
}

bool CChaosNumber::operator>=(int nValue)
{
    if (valueNone == m_ValueType)
        return 0 >= nValue;
    return GetLongValue() >= (long)nValue;
}

bool CChaosNumber::operator>=(float fValue)
{
    if (valueNone == m_ValueType)
        return 0 >= fValue;
    return GetFloatValue() >= fValue;
}

bool CChaosNumber::operator<=(CChaosNumber& another)
{
    bool bRet = false;
    if (valueLong == m_ValueType)
        bRet = GetLongValue() <= another.GetLongValue();
    else if (valueFloat == m_ValueType)
        bRet = GetFloatValue() <= another.GetFloatValue();
    
    return bRet;
}

bool CChaosNumber::operator<=(long lValue)
{
    if (valueNone == m_ValueType)
        return 0 <= lValue;
    return GetLongValue() <= lValue;
}

bool CChaosNumber::operator<=(int nValue)
{
    if (valueNone == m_ValueType)
        return 0 <= nValue;
    return GetLongValue() <= (long)nValue;
}

bool CChaosNumber::operator<=(float fValue)
{
    if (valueNone == m_ValueType)
        return 0 <= fValue;
    return GetFloatValue() <= fValue;
}

bool CChaosNumber::operator>(CChaosNumber& another)
{
    bool bRet = false;
    if (valueLong == m_ValueType)
        bRet = GetLongValue() > another.GetLongValue();
    else if (valueFloat == m_ValueType)
        bRet = GetFloatValue() > another.GetFloatValue();
    
    return bRet;
}

bool CChaosNumber::operator>(long lValue)
{
    if (valueNone == m_ValueType)
        return 0 > lValue;
    return GetLongValue() > lValue;
}

bool CChaosNumber::operator>(int nValue)
{
    if (valueNone == m_ValueType)
        return 0 > nValue;
    return GetLongValue() > (long)nValue;
}

bool CChaosNumber::operator>(float fValue)
{
    if (valueNone == m_ValueType)
        return 0 > fValue;
    return GetFloatValue() > fValue;
}

bool CChaosNumber::operator<(CChaosNumber& another)
{
    bool bRet = false;
    if (valueLong == m_ValueType)
        bRet = GetLongValue() < another.GetLongValue();
    else if (valueFloat == m_ValueType)
        bRet = GetFloatValue() < another.GetFloatValue();
    
    return bRet;
}

bool CChaosNumber::operator<(long lValue)
{
    if (valueNone == m_ValueType)
        return 0 < lValue;
    return GetLongValue() < lValue;
}

bool CChaosNumber::operator<(int nValue)
{
    if (valueNone == m_ValueType)
        return 0 < nValue;
    return GetLongValue() < (long)nValue;
}

bool CChaosNumber::operator<(float fValue)
{
    if (valueNone == m_ValueType)
        return 0 < fValue;
    return GetFloatValue() < fValue;
}



