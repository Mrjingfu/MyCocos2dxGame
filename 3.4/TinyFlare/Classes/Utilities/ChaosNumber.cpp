//
//  ChaosNumber.cpp
//

#include "ChaosNumber.h"

CChaosNumber::CChaosNumber()
{
    m_ValueType = valueNone;
    m_pMatrix = NULL;
}

CChaosNumber::CChaosNumber(long lValue)
{
    m_ValueType = valueNone;
    m_pMatrix = NULL;
    SetLongValue(lValue);
}

CChaosNumber::CChaosNumber(float fValue)
{
    m_ValueType = valueNone;
    m_pMatrix = NULL;
    SetFloatValue(fValue);
}

CChaosNumber::CChaosNumber(int nValue)
{
    m_ValueType = valueNone;
    m_pMatrix = NULL;
    SetLongValue((long)nValue);
}

CChaosNumber::CChaosNumber(CChaosNumber& another)
{
    if(valueLong == another.GetValueType())
        SetLongValue(another.GetLongValue());
    else if(valueFloat == another.GetValueType())
        SetFloatValue(another.GetFloatValue());
}

CChaosNumber::~CChaosNumber()
{
    m_ValueType = valueNone;
    SafeDeletePtr(m_pMatrix);
}


float CChaosNumber::GetFloatValue()
{
    float fRet = 0;
    if (valueLong == m_ValueType)
        fRet = GetLongValue();
    else
        GetValueFromMatric(&fRet);

    return fRet;
}

long CChaosNumber::GetLongValue()
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
    srand(time(NULL));
    char cTemp = abs((rand() % 4));
    m_BytePos[0] = cTemp;

    while (cTemp == m_BytePos[0])
        cTemp = abs((rand() % 4));
    m_BytePos[1] = cTemp;

    while (cTemp == m_BytePos[0] || cTemp == m_BytePos[1])
        cTemp = abs((rand() % 4));
    m_BytePos[2] = cTemp;

    m_BytePos[3] = (1+2+3) - m_BytePos[0] - m_BytePos[1] - m_BytePos[2];
}

void CChaosNumber::PutValueToMatrix(void * pValue)
{
    if (m_pMatrix)
        SafeDeletePtr(m_pMatrix);
    m_pMatrix = (char *)malloc(sizeof(char) * 4);
    char * pTemp = (char *)pValue;
    GenerateOrder();
    for (int i = 0; i < 4; i++)
        m_pMatrix[m_BytePos[i]] = pTemp[i];
}

void CChaosNumber::GetValueFromMatric(void * pBuffer)
{
    if (valueNone != m_ValueType)
    {
        char * pTemp = (char *)pBuffer;
        for (int i = 0; i < 4; i++)
            pTemp[i] = m_pMatrix[m_BytePos[i]];
    }
}

valueType CChaosNumber::GetValueType()
{
    return m_ValueType;
}


CChaosNumber::operator long()
{
    return GetLongValue();
}

CChaosNumber::operator float()
{
    return GetFloatValue();
}

CChaosNumber::operator int()
{
    int nRet = (int)GetLongValue();
    return nRet;
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



