//
//  ChaosNumber.h
//

#ifndef __TinyFlare___ChaosNumber_h
#define __TinyFlare___ChaosNumber_h

template <typename Type_>
static inline void SafeDeletePtr(Type_ *ptr)
{
    if(ptr)
    {
        free(ptr);
        ptr = NULL;
    }
}

typedef enum _valueType
{
    valueNone = 0,
    valueLong,
    valueFloat
}valueType;

class CChaosNumber
{
public:
    CChaosNumber();
    CChaosNumber(long lValue);
    CChaosNumber(float fValue);
    CChaosNumber(int nValue);
    CChaosNumber(CChaosNumber& another);
    ~CChaosNumber();
    
public:
    float GetFloatValue();
    long  GetLongValue();
    void  SetFloatValue(float value);
    void  SetLongValue(long value);
    valueType GetValueType();
    
public:
    // 重载操作符
    operator long();
    operator float();
    operator int();

    // +, -, *, /, ++, --, ==, >=, <=, >, <
    CChaosNumber& operator=(CChaosNumber& another);
    CChaosNumber& operator=(long lValue);
    CChaosNumber& operator=(int nValue);
    CChaosNumber& operator=(float fValue);
    long operator+(long lValue);
    int operator+(int nValue);
    float operator+(float fValue);
    long operator-(long lValue);
    int operator-(int nValue);
    float operator-(float fValue);
    long operator*(long lValue);
    int operator*(int nValue);
    float operator*(float fValue);
    long operator/(long lValue);
    int operator/(int nValue);
    float operator/(float fValue);
    CChaosNumber& operator++();
    CChaosNumber& operator--();
    bool operator==(CChaosNumber& another);
    bool operator==(long lValue);
    bool operator==(int nValue);
    bool operator==(float fValue);
    bool operator>=(CChaosNumber& another);
    bool operator>=(long lValue);
    bool operator>=(int nValue);
    bool operator>=(float fValue);
    bool operator<=(CChaosNumber& another);
    bool operator<=(long lValue);
    bool operator<=(int nValue);
    bool operator<=(float fValue);
    bool operator>(CChaosNumber& another);
    bool operator>(long lValue);
    bool operator>(int nValue);
    bool operator>(float fValue);
    bool operator<(CChaosNumber& another);
    bool operator<(long lValue);
    bool operator<(int nValue);
    bool operator<(float fValue);
    
private:
    void  GenerateOrder();
    void  PutValueToMatrix(void * pValue);
    void  GetValueFromMatric(void * pBuffer);
    
private:
    char *  m_pMatrix;
    char    m_BytePos[4];
    valueType m_ValueType;
};


#endif
