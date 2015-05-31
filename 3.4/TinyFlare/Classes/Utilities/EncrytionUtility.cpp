//
//  EncrytionUtility.cpp
//  TinyFlare
//
//  Created by wang haibo on 14-8-22.
//
//

#include "EncrytionUtility.h"
USING_NS_CC;

bool EncrytionUtility::getBoolForKey(const char* pKey)
{
#ifdef COCOS2D_DEBUG
    return UserDefault::getInstance()->getBoolForKey(pKey);
#else
    std::string key = pKey;
    strXor(key, 0, (int)(key.length()-1), PACKAGE_NAME);
    std::string value = UserDefault::getInstance()->getStringForKey(key.c_str());
    strXor(value, 0, (int)(value.length()-1), PACKAGE_NAME);
    return Value(value).asBool();
#endif
}
bool EncrytionUtility::getBoolForKey(const char* pKey, bool defaultValue)
{
#ifdef COCOS2D_DEBUG
    return UserDefault::getInstance()->getBoolForKey(pKey, defaultValue);
#else
    std::string key = pKey;
    strXor(key, 0, (int)(key.length()-1), PACKAGE_NAME);
    std::string strDefault = Value(defaultValue).asString();
    strXor(strDefault, 0, (int)(strDefault.length()-1), PACKAGE_NAME);
    std::string value = UserDefault::getInstance()->getStringForKey(key.c_str(),strDefault);
    strXor(value, 0, (int)(value.length()-1), PACKAGE_NAME);
    return Value(value).asBool();
#endif
}
int EncrytionUtility::getIntegerForKey(const char* pKey)
{
#ifdef COCOS2D_DEBUG
    return UserDefault::getInstance()->getIntegerForKey(pKey);
#else
    std::string key = pKey;
    strXor(key, 0, (int)(key.length()-1), PACKAGE_NAME);
    std::string value = UserDefault::getInstance()->getStringForKey(key.c_str());
    strXor(value, 0, (int)(value.length()-1), PACKAGE_NAME);
    return Value(value).asInt();
#endif
}
int EncrytionUtility::getIntegerForKey(const char* pKey, int defaultValue)
{
#ifdef COCOS2D_DEBUG
    return UserDefault::getInstance()->getIntegerForKey(pKey,defaultValue);
#else
    std::string key = pKey;
    strXor(key, 0, (int)(key.length()-1), PACKAGE_NAME);
    std::string strDefault = Value(defaultValue).asString();
    strXor(strDefault, 0, (int)(strDefault.length()-1), PACKAGE_NAME);
    std::string value = UserDefault::getInstance()->getStringForKey(key.c_str(),strDefault);
    strXor(value, 0, (int)(value.length()-1), PACKAGE_NAME);
    return Value(value).asInt();
#endif
}
float EncrytionUtility::getFloatForKey(const char* pKey)
{
#ifdef COCOS2D_DEBUG
    return UserDefault::getInstance()->getFloatForKey(pKey);
#else
    std::string key = pKey;
    strXor(key, 0, (int)(key.length()-1), PACKAGE_NAME);
    std::string value = UserDefault::getInstance()->getStringForKey(key.c_str());
    strXor(value, 0, (int)(value.length()-1), PACKAGE_NAME);
    return Value(value).asFloat();
#endif
}
float EncrytionUtility::getFloatForKey(const char* pKey, float defaultValue)
{
#ifdef COCOS2D_DEBUG
    return UserDefault::getInstance()->getFloatForKey(pKey,defaultValue);
#else
    std::string key = pKey;
    strXor(key, 0, (int)(key.length()-1), PACKAGE_NAME);
    std::string strDefault = Value(defaultValue).asString();
    strXor(strDefault, 0, (int)(strDefault.length()-1), PACKAGE_NAME);
    std::string value = UserDefault::getInstance()->getStringForKey(key.c_str(),strDefault);
    strXor(value, 0, (int)(value.length()-1), PACKAGE_NAME);
    return Value(value).asFloat();
#endif
}
double EncrytionUtility::getDoubleForKey(const char* pKey)
{
#ifdef COCOS2D_DEBUG
    return UserDefault::getInstance()->getDoubleForKey(pKey);
#else
    std::string key = pKey;
    strXor(key, 0, (int)(key.length()-1), PACKAGE_NAME);
    std::string value = UserDefault::getInstance()->getStringForKey(key.c_str());
    strXor(value, 0, (int)(value.length()-1), PACKAGE_NAME);
    return Value(value).asDouble();
#endif
}
double EncrytionUtility::getDoubleForKey(const char* pKey, double defaultValue)
{
#ifdef COCOS2D_DEBUG
    return UserDefault::getInstance()->getDoubleForKey(pKey,defaultValue);
#else
    std::string key = pKey;
    strXor(key, 0, (int)(key.length()-1), PACKAGE_NAME);
    std::string strDefault = Value(defaultValue).asString();
    strXor(strDefault, 0, (int)(strDefault.length()-1), PACKAGE_NAME);
    std::string value = UserDefault::getInstance()->getStringForKey(key.c_str(),strDefault);
    strXor(value, 0, (int)(value.length()-1), PACKAGE_NAME);
    return Value(value).asDouble();
#endif
}
std::string EncrytionUtility::getStringForKey(const char* pKey)
{
#ifdef COCOS2D_DEBUG
    return UserDefault::getInstance()->getStringForKey(pKey);
#else
    std::string key = pKey;
    strXor(key, 0, (int)(key.length()-1), PACKAGE_NAME);
    std::string value = UserDefault::getInstance()->getStringForKey(key.c_str());
    strXor(value, 0, (int)(value.length()-1), PACKAGE_NAME);
    return value;
#endif
}
std::string EncrytionUtility::getStringForKey(const char* pKey, const std::string & defaultValue)
{
#ifdef COCOS2D_DEBUG
    return UserDefault::getInstance()->getStringForKey(pKey,defaultValue);
#else
    std::string key = pKey;
    strXor(key, 0, (int)(key.length()-1), PACKAGE_NAME);
    std::string strDefault = defaultValue;
    strXor(strDefault, 0, (int)(strDefault.length()-1), PACKAGE_NAME);
    std::string value = UserDefault::getInstance()->getStringForKey(key.c_str(),strDefault);
    strXor(value, 0, (int)(value.length()-1), PACKAGE_NAME);
    return value;
#endif
}


void EncrytionUtility::setBoolForKey(const char* pKey, bool value)
{
#ifdef COCOS2D_DEBUG
    UserDefault::getInstance()->setBoolForKey(pKey,value);
#else
    std::string key = pKey;
    strXor(key, 0, (int)(key.length()-1), PACKAGE_NAME);
    std::string strValue = Value(value).asString();
    strXor(strValue, 0, (int)(strValue.length()-1), PACKAGE_NAME);
    UserDefault::getInstance()->setStringForKey(key.c_str(), strValue);
#endif
    UserDefault::getInstance()->flush();
}
void EncrytionUtility::setIntegerForKey(const char* pKey, int value)
{
#ifdef COCOS2D_DEBUG
    UserDefault::getInstance()->setIntegerForKey(pKey,value);
#else
    std::string key = pKey;
    strXor(key, 0, (int)(key.length()-1), PACKAGE_NAME);
    std::string strValue = Value(value).asString();
    strXor(strValue, 0, (int)(strValue.length()-1), PACKAGE_NAME);
    UserDefault::getInstance()->setStringForKey(key.c_str(), strValue);
#endif
    UserDefault::getInstance()->flush();
}
void EncrytionUtility::setFloatForKey(const char* pKey, float value)
{
#ifdef COCOS2D_DEBUG
    UserDefault::getInstance()->setFloatForKey(pKey,value);
#else
    std::string key = pKey;
    strXor(key, 0, (int)(key.length()-1), PACKAGE_NAME);
    std::string strValue = Value(value).asString();
    strXor(strValue, 0, (int)(strValue.length()-1), PACKAGE_NAME);
    UserDefault::getInstance()->setStringForKey(key.c_str(), strValue);
#endif
    UserDefault::getInstance()->flush();
}
void EncrytionUtility::setDoubleForKey(const char* pKey, double value)
{
#ifdef COCOS2D_DEBUG
    UserDefault::getInstance()->setDoubleForKey(pKey,value);
#else
    std::string key = pKey;
    strXor(key, 0, (int)(key.length()-1), PACKAGE_NAME);
    std::string strValue = Value(value).asString();
    strXor(strValue, 0, (int)(strValue.length()-1), PACKAGE_NAME);
    UserDefault::getInstance()->setStringForKey(key.c_str(), strValue);
#endif
    UserDefault::getInstance()->flush();
}
void EncrytionUtility::setStringForKey(const char* pKey, const std::string & value)
{
#ifdef COCOS2D_DEBUG
    UserDefault::getInstance()->setStringForKey(pKey,value);
#else
    std::string key = pKey;
    strXor(key, 0, (int)(key.length()-1), PACKAGE_NAME);
    std::string strValue = Value(value).asString();
    strXor(strValue, 0, (int)(strValue.length()-1), PACKAGE_NAME);
    UserDefault::getInstance()->setStringForKey(key.c_str(), strValue);
#endif
    UserDefault::getInstance()->flush();
}

bool EncrytionUtility::strXor(std::string& stream, int begin, int end, const char* secret)
{
    if (begin<0 || end>=stream.length() || begin>end || strlen(secret) == 0)
        return false;
    
    int keyLength = (int)strlen(secret);
    int j = 0;
    for (int i=begin; i<=end; i++)
    {
        if (j>=keyLength)
        {
            j = 0;
        }
        stream[i] = stream[i] ^ secret[j];
        if(stream[i] == '\0')
        {
            stream[i] = secret[j];
        }
        j++;
    }
    
    return true;
}