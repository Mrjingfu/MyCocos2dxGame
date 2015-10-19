

#ifndef __TinyFlare_ChaosNumber_h
#define __TinyFlare_ChaosNumber_h

enum valueType
{
	valueNone = 0,
	valueLong,
	valueFloat
};

class CChaosNumber
{
public:
    CChaosNumber();
    ~CChaosNumber();
    CChaosNumber(const long lValue);
    CChaosNumber(const float fValue);
    CChaosNumber(const int nValue);
    CChaosNumber(const CChaosNumber& another);

public:
    float GetFloatValue() const ;
    long  GetLongValue() const ;
    void  SetFloatValue(float value);
    void  SetLongValue(long value);
    valueType GetValueType() const;

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

	//成就那边频繁需要+=，故重写 [17/11/2014/CYN]
	CChaosNumber& operator+=(int lValue);

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

public:
    void  GenerateOrder();
    void  PutValueToMatrix(void * pValue);
    void  GetValueFromMatric(void * pBuffer) const; 

private:
    char *  m_pMatrix;
    char    m_BytePos[4][2];
    valueType m_ValueType;
};

#endif
