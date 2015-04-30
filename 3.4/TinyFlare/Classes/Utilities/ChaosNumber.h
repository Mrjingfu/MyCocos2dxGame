//
//  ChaosNumber.h
//

#ifndef __TinyFlare___ChaosNumber_h
#define __TinyFlare___ChaosNumber_h

template <typename Type_>
static inline void SafeFreePtr(Type_ *ptr)
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

class ChaosNumber
{
public:
    ChaosNumber();
    ~ChaosNumber();
    ChaosNumber(long lValue);
    ChaosNumber(float fValue);
    ChaosNumber(int nValue);
    ChaosNumber(ChaosNumber& another);
        
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
    ChaosNumber& operator=(ChaosNumber& another);
    ChaosNumber& operator=(long lValue);
    ChaosNumber& operator=(int nValue);
    ChaosNumber& operator=(float fValue);
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
    ChaosNumber& operator++();
    ChaosNumber& operator--();
    bool operator==(ChaosNumber& another);
    bool operator==(long lValue);
    bool operator==(int nValue);
    bool operator==(float fValue);
    bool operator>=(ChaosNumber& another);
    bool operator>=(long lValue);
    bool operator>=(int nValue);
    bool operator>=(float fValue);
    bool operator<=(ChaosNumber& another);
    bool operator<=(long lValue);
    bool operator<=(int nValue);
    bool operator<=(float fValue);
    bool operator>(ChaosNumber& another);
    bool operator>(long lValue);
    bool operator>(int nValue);
    bool operator>(float fValue);
    bool operator<(ChaosNumber& another);
    bool operator<(long lValue);
    bool operator<(int nValue);
    bool operator<(float fValue);
        
private:
    void  GenerateOrder();
    void  PutValueToMatrix(void * pValue);
    void  GetValueFromMatric(void * pBuffer);
        
private:
    char *  m_pMatrix;
    char    m_BytePos[4][2];
    valueType m_ValueType;
};

#endif
