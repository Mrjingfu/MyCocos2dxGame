//
//  ChaosNumber.cpp
//

#include "ChaosNumber.h"

typedef char MATRIX[4][4];

ChaosNumber::ChaosNumber()
{
    m_ValueType = valueNone;
    m_pMatrix = nullptr;
}

ChaosNumber::ChaosNumber(long lValue)
{
    m_ValueType = valueNone;
    m_pMatrix = nullptr;
    SetLongValue(lValue);
}

ChaosNumber::ChaosNumber(int nValue)
{
    m_ValueType = valueNone;
    m_pMatrix = nullptr;
    SetLongValue((long)nValue);
}

ChaosNumber::ChaosNumber(float fValue)
{
    m_ValueType = valueNone;
    m_pMatrix = nullptr;
    SetFloatValue(fValue);
}

ChaosNumber::ChaosNumber(ChaosNumber& another)
{
    if(valueLong == another.GetValueType())
        SetLongValue(another.GetLongValue());
    else if(valueFloat == another.GetValueType())
        SetFloatValue(another.GetFloatValue());
}

ChaosNumber::~ChaosNumber()
{
    m_ValueType = valueNone;
    SafeFreePtr(m_pMatrix);
}


float ChaosNumber::GetFloatValue()
{
    float fRet = 0;
    if (valueLong == m_ValueType)
        fRet = GetLongValue();
    else
        GetValueFromMatric(&fRet);
    
    return fRet;
}

long ChaosNumber::GetLongValue()
{
    int lRet = 0;
    if (valueFloat == m_ValueType)
        lRet = GetFloatValue();
    else
        GetValueFromMatric(&lRet);
    
    return lRet;
}

void ChaosNumber::SetFloatValue(float value)
{
    PutValueToMatrix(&value);
    m_ValueType = valueFloat;
}

void ChaosNumber::SetLongValue(long value)
{
    PutValueToMatrix(&value);
    m_ValueType = valueLong;
}


void ChaosNumber::GenerateOrder()
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

void ChaosNumber::PutValueToMatrix(void * pValue)
{
    if (m_pMatrix)
        SafeFreePtr(m_pMatrix);
    m_pMatrix = (char *)malloc(sizeof(char) * 4 * 4);
    MATRIX *pTempMatrix = (MATRIX *)m_pMatrix;
    char * pTemp = (char *)pValue;
    GenerateOrder();
    for (int i = 0; i < 4; i++)
    {
        m_BytePos[i][1] = abs((rand() % 4));
        (*pTempMatrix)[m_BytePos[i][0]][m_BytePos[i][1]] = pTemp[i];
    }
}

void ChaosNumber::GetValueFromMatric(void * pBuffer)
{
    if (valueNone != m_ValueType)
    {
        char * pTemp = (char *)pBuffer;
        MATRIX * pTempMatrix = (MATRIX *)m_pMatrix;
        for (int i = 0; i < 4; i++)
            pTemp[i] = (*pTempMatrix)[m_BytePos[i][0]][m_BytePos[i][1]];
    }
}

valueType ChaosNumber::GetValueType()
{
    return m_ValueType;
}


ChaosNumber::operator long()
{
    return GetLongValue();
}

ChaosNumber::operator int()
{
    int nRet = (int)GetLongValue();
    return nRet;
}


ChaosNumber::operator float()
{
    return GetFloatValue();
}

ChaosNumber& ChaosNumber::operator=(ChaosNumber& another)
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

ChaosNumber& ChaosNumber::operator=(long lValue)
{
    SetLongValue(lValue);
    return *this;
}

ChaosNumber& ChaosNumber::operator=(int nValue)
{
    SetLongValue((long)nValue);
    return *this;
}

ChaosNumber& ChaosNumber::operator=(float fValue)
{
    SetFloatValue(fValue);
    return *this;
}

long ChaosNumber::operator+(long lValue)
{
    return GetLongValue() + lValue;
}

float ChaosNumber::operator+(float fValue)
{
    return GetFloatValue() + fValue;
}

int ChaosNumber::operator+(int nValue)
{
    int nRet = (int)GetLongValue();
    return nRet + nValue;
}

long ChaosNumber::operator-(long lValue)
{
    return GetLongValue() - lValue;
}

int ChaosNumber::operator-(int nValue)
{
    int nRet = (int)GetLongValue();
    return nRet - nValue;
}

float ChaosNumber::operator-(float fValue)
{
    return GetFloatValue() - fValue;
}

long ChaosNumber::operator*(long lValue)
{
    return GetLongValue() * lValue;
}

int ChaosNumber::operator*(int nValue)
{
    int nRet = (int)GetLongValue();
    return nRet * nValue;
}

float ChaosNumber::operator*(float fValue)
{
    return GetFloatValue() * fValue;
}

long ChaosNumber::operator/(long lValue)
{
    return GetLongValue() / lValue;
}

int ChaosNumber::operator/(int nValue)
{
    int nRet = (int)GetLongValue();
    return nRet / nValue;
}

float ChaosNumber::operator/(float fValue)
{
    return GetFloatValue() / fValue;
}

ChaosNumber& ChaosNumber::operator++()
{
    if (valueLong == m_ValueType)
        SetLongValue(GetLongValue()+1);
    else if(valueFloat == m_ValueType)
        SetFloatValue(GetFloatValue()+1);
    else
        SetLongValue(1);
    
    return *this;
}

ChaosNumber& ChaosNumber::operator--()
{
    if (valueLong == m_ValueType)
        SetLongValue(GetLongValue()-1);
    else if(valueFloat == m_ValueType)
        SetFloatValue(GetFloatValue()-1);
    else
        SetLongValue(-1);
    
    return *this;
}

bool ChaosNumber::operator==(ChaosNumber& another)
{
    bool bRet = false;
    if (valueLong == m_ValueType)
        bRet = GetLongValue() == another.GetLongValue();
    else if (valueFloat == m_ValueType)
        bRet = GetFloatValue() == another.GetFloatValue();
    
    return bRet;
}

bool ChaosNumber::operator==(long lValue)
{
    if (valueNone == m_ValueType)
        return false;
    return GetLongValue() == lValue;
}

bool ChaosNumber::operator==(int nValue)
{
    if (valueNone == m_ValueType)
        return false;
    return GetLongValue() == (long)nValue;
}

bool ChaosNumber::operator==(float fValue)
{
    if (valueNone == m_ValueType)
        return false;
    return GetFloatValue() == fValue;
}

bool ChaosNumber::operator>=(ChaosNumber& another)
{
    bool bRet = false;
    if (valueLong == m_ValueType)
        bRet = GetLongValue() >= another.GetLongValue();
    else if (valueFloat == m_ValueType)
        bRet = GetFloatValue() >= another.GetFloatValue();
    
    return bRet;
}

bool ChaosNumber::operator>=(long lValue)
{
    if (valueNone == m_ValueType)
        return 0 >= lValue;
    return GetLongValue() >= lValue;
}

bool ChaosNumber::operator>=(int nValue)
{
    if (valueNone == m_ValueType)
        return 0 >= nValue;
    return GetLongValue() >= (long)nValue;
}

bool ChaosNumber::operator>=(float fValue)
{
    if (valueNone == m_ValueType)
        return 0 >= fValue;
    return GetFloatValue() >= fValue;
}

bool ChaosNumber::operator<=(ChaosNumber& another)
{
    bool bRet = false;
    if (valueLong == m_ValueType)
        bRet = GetLongValue() <= another.GetLongValue();
    else if (valueFloat == m_ValueType)
        bRet = GetFloatValue() <= another.GetFloatValue();
    
    return bRet;
}

bool ChaosNumber::operator<=(long lValue)
{
    if (valueNone == m_ValueType)
        return 0 <= lValue;
    return GetLongValue() <= lValue;
}

bool ChaosNumber::operator<=(int nValue)
{
    if (valueNone == m_ValueType)
        return 0 <= nValue;
    return GetLongValue() <= (long)nValue;
}

bool ChaosNumber::operator<=(float fValue)
{
    if (valueNone == m_ValueType)
        return 0 <= fValue;
    return GetFloatValue() <= fValue;
}

bool ChaosNumber::operator>(ChaosNumber& another)
{
    bool bRet = false;
    if (valueLong == m_ValueType)
        bRet = GetLongValue() > another.GetLongValue();
    else if (valueFloat == m_ValueType)
        bRet = GetFloatValue() > another.GetFloatValue();
    
    return bRet;
}

bool ChaosNumber::operator>(long lValue)
{
    if (valueNone == m_ValueType)
        return 0 > lValue;
    return GetLongValue() > lValue;
}

bool ChaosNumber::operator>(int nValue)
{
    if (valueNone == m_ValueType)
        return 0 > nValue;
    return GetLongValue() > (long)nValue;
}

bool ChaosNumber::operator>(float fValue)
{
    if (valueNone == m_ValueType)
        return 0 > fValue;
    return GetFloatValue() > fValue;
}

bool ChaosNumber::operator<(ChaosNumber& another)
{
    bool bRet = false;
    if (valueLong == m_ValueType)
        bRet = GetLongValue() < another.GetLongValue();
    else if (valueFloat == m_ValueType)
        bRet = GetFloatValue() < another.GetFloatValue();
    
    return bRet;
}

bool ChaosNumber::operator<(long lValue)
{
    if (valueNone == m_ValueType)
        return 0 < lValue;
    return GetLongValue() < lValue;
}

bool ChaosNumber::operator<(int nValue)
{
    if (valueNone == m_ValueType)
        return 0 < nValue;
    return GetLongValue() < (long)nValue;
}

bool ChaosNumber::operator<(float fValue)
{
    if (valueNone == m_ValueType)
        return 0 < fValue;
    return GetFloatValue() < fValue;
}


