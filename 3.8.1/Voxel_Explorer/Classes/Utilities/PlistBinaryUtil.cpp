//
//  ValueMapBinaryUtil.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 16/1/4.
//
//

#include "PlistBinaryUtil.hpp"
#include "CCCrypto.h"
#include "UtilityHelper.h"
USING_NS_CC;

PlistBinaryUtil::PlistBinaryUtil()
{
    m_bisDebug = false;
}
PlistBinaryUtil::~PlistBinaryUtil()
{
    
}
PlistBinaryUtil* PlistBinaryUtil::getInstance()
{
    static PlistBinaryUtil instance;
    return &instance;
}


cocos2d::ValueMap PlistBinaryUtil::getValueMapFromFile(const std::string& filename)
{
    cocos2d::ValueMap resultMap;
    cocos2d::Value valueParse(resultMap);
    if (!getValueForFile(valueParse, filename)) {
        return resultMap;
    }
    resultMap = valueParse.asValueMap();
    
    return resultMap;
    
}
bool PlistBinaryUtil::writeValueMapToFile(cocos2d::ValueMap& dict, const std::string& fullPath,bool isEncrpty)
{
    if (dict.empty()) {
        CCLOG("dict is empty");
        return false;
    }
    cocos2d::Value tempValue = Value(dict);
    
    if(!wiriteValueForFile(tempValue,cocos2d::FileUtils::getInstance()->getSuitableFOpen(fullPath),isEncrpty))
        return false;
    
    return true;
}

cocos2d::ValueVector PlistBinaryUtil::getValueVectorFromFile(const std::string& filename)
{
    cocos2d::ValueVector resultVector;
    cocos2d::Value valueParse(resultVector);
    if (!getValueForFile(valueParse, filename)) {
        return resultVector;
    }
    resultVector = valueParse.asValueVector();
  
    
    return resultVector;
}


bool PlistBinaryUtil::writeValueVectorToFile(cocos2d::ValueVector& dict, const std::string& fullPath,bool isEncrpty)
{
    if (dict.empty()) {
        CCLOG("dict is empty");
        return false;
    }
    cocos2d::Value tempValue = Value(dict);
    if(!wiriteValueForFile(tempValue,cocos2d::FileUtils::getInstance()->getSuitableFOpen(fullPath),isEncrpty))
         return false;
    return true;
}
bool PlistBinaryUtil::wiriteValueForFile(cocos2d::Value& dict,const std::string& fullPath,bool isEncrpty)
{
    
    FileStream writeStr(fullPath.c_str(),"wb");
    writeStr.writeBool(isEncrpty);
    wirteValue(writeStr, dict);
    writeStr.close();
    
    if (!isEncrpty) {
        return true;
    }
    
    if (!cocos2d::FileUtils::getInstance()->isFileExist(fullPath))
    {
        CCLOG("FILE is not exist!");
        return false;
    }
    ssize_t size;
    const unsigned char* content = cocos2d::FileUtils::getInstance()->getFileData(fullPath.c_str(), "rb", &size);
    if (size <= 0 )
    {
        CCLOG("file content is null");
        return false;
    }
    
    MemoryStream wirtestStream((char*)content,size);
    wirtestStream.readBool();
    
    int sourceLentgh = size - wirtestStream.tell();
    char sourceContent[sourceLentgh];
    memset(sourceContent, 0, sourceLentgh);
    wirtestStream.read(sourceContent, sourceLentgh);
    wirtestStream.close();
   
    unsigned char	m_md5[MD5_LEN];
    CCCrypto::md5((void*)sourceContent, sourceLentgh, m_md5);
    std::string hex;
    UtilityHelper::getHexDigest(m_md5, MD5_LEN, hex);
    if (m_bisDebug)
        CCLOG(" md5=%s, begin", hex.c_str());

    //加密Base64
    char encodeStr[sourceLentgh*2];
    memset(encodeStr, 0, sourceLentgh*2);
    int encodelength = CCCrypto::encodeBase64(sourceContent, sourceLentgh,encodeStr,sourceLentgh*2);
    
    char encodeOutStr[encodelength];
    memset(encodeOutStr, 0, encodelength);
    memcpy(encodeOutStr, encodeStr,encodelength);
    if (m_bisDebug)
        CCLOG("save encodeBase64:%s",encodeOutStr);
    
    
    //加密 encryptXOR
    CCCrypto::encryptXOR((char*)encodeOutStr, encodelength,hex.c_str());
    if (m_bisDebug)
        CCLOG("save encryptXOR:%s",encodeOutStr);
    
    
    FileStream dewriteStr(fullPath.c_str(),"wb");
    //写加密标志
    dewriteStr.writeBool(isEncrpty);
    //encryptXOR 秘钥md5
    dewriteStr.writeString(hex);
    //加密后的base64长度
    dewriteStr.write64le(encodelength);
    //写数据
    dewriteStr.write(encodeOutStr, encodelength);
    dewriteStr.close();
    return true;
    
}
bool PlistBinaryUtil::getValueForFile(cocos2d::Value& dict,const std::string& filename)
{

    const std::string fullPath =  cocos2d::FileUtils::getInstance()->fullPathForFilename(filename.c_str());
    
    if (fullPath.empty()) {
        CCLOG("filename is not exist");
        return false;
    }
    
    if (!cocos2d::FileUtils::getInstance()->isFileExist(fullPath))
    {
        CCLOG("FILE is not exist!");
        return false;
    }
    ssize_t size;
    const unsigned char* content = cocos2d::FileUtils::getInstance()->getFileData(fullPath.c_str(), "rb", &size);
    if (size <= 0 )
    {
        CCLOG("file content is null");
        return false;
    }
    MemoryStream readStream((const char *)content,size);
    bool isEncrpty = readStream.readBool();
    if (isEncrpty) {
        //加密过需要解密

        //解密秘钥
        std::string encrtyKey = readStream.readString();
        
        //加密后的base64长度
        int64 base64Length = readStream.read64le();
        
        
        char  base64Datas[base64Length];
        memset(base64Datas, 0, base64Length);
        readStream.read(base64Datas, base64Length);
        if (m_bisDebug)
            CCLOG("parse encryptXOR:%s",base64Datas);
        
        //解密XOR
        CCCrypto::decryptXOR(base64Datas, base64Length,encrtyKey.c_str());
        if (m_bisDebug)
            CCLOG("parse base64:%s",base64Datas);
        
        
        //解密base64
        char dencodeStr[base64Length*2];
        memset(dencodeStr, 0, base64Length*2);
        int dencodelength = CCCrypto::decodeBase64(base64Datas,dencodeStr,base64Length*2);
        
        char dencodeOutStr[dencodelength];
        memset(dencodeOutStr, 0, dencodelength);
        memcpy(dencodeOutStr, dencodeStr,dencodelength);
        
        //对比md5
        unsigned char	m_md5[MD5_LEN];
        CCCrypto::md5((void *)dencodeOutStr, dencodelength, m_md5);
        std::string hex;
        UtilityHelper::getHexDigest(m_md5, MD5_LEN, hex);

         if (encrtyKey.compare(hex)!=0)
         {
             CCLOG("md5 error %s",filename.c_str());
             return false;
         }
        
        MemoryStream paseseStream((const char *)dencodeOutStr,dencodelength);
        
        while (!paseseStream.eof()) {
            parseValue(paseseStream,dict);
        }
        
        if (m_bisDebug)
            CCLOG("resultVector:%s",dict.getDescription().c_str());
        
        CC_SAFE_DELETE_ARRAY(content);
        readStream.close();
        paseseStream.close();
    }else
    {
        while (!readStream.eof()) {
            parseValue(readStream,dict);
        }
        if (m_bisDebug)
            CCLOG("resultVector:%s",dict.getDescription().c_str());
        
        CC_SAFE_DELETE_ARRAY(content);
        readStream.close();

    }

    return true;
}



void  PlistBinaryUtil::wirteValue(FileStream& writeStr,const  cocos2d::Value& avalue)
{
    cocos2d::Value::Type type = avalue.getType();
    if (type == cocos2d::Value::Type::VECTOR) {
        for (auto iter = avalue.asValueVector().begin(); iter != avalue.asValueVector().end(); iter++)
        {
            cocos2d::Value itemValue = *iter;
            writeStr.write32le((int)itemValue.getType());
            if (m_bisDebug) {
                 CCLOG("WIRITE VECTOR type:%d",itemValue.getType());
            }
            wirteValueType(itemValue.getType(),writeStr,itemValue);
        }
        
    }else if(type == cocos2d::Value::Type::MAP)
    {
        for (auto iter = avalue.asValueMap().begin(); iter != avalue.asValueMap().end(); iter++)
        {
            cocos2d::Value itemValue = iter->second;
            if (m_bisDebug) {
                CCLOG("WIRITE MAP type:%d",itemValue.getType());
                CCLOG("WIRITE MAP key:%s",iter->first.c_str());
            }

            writeStr.write32le((int)itemValue.getType());
            writeStr.writeString(iter->first);
            wirteValueType(itemValue.getType(),writeStr,itemValue);
        }
        
    }else if(type == cocos2d::Value::Type::INT_KEY_MAP)
    {
        for (auto iter = avalue.asIntKeyMap().begin(); iter !=  avalue.asIntKeyMap().end(); iter++)
        {
            cocos2d::Value itemValue = iter->second;
             if (m_bisDebug) {
                 CCLOG("WIRITE INT_KEY_MAP type:%d",itemValue.getType());
                 CCLOG("WIRITE INT_KEY_MAP key:%d",iter->first);
             }
            writeStr.write32le((int)itemValue.getType());
            writeStr.write32le(iter->first);
            
            wirteValueType(itemValue.getType(),writeStr,itemValue);
        }
    }
    
}

void PlistBinaryUtil::wirteValueType(cocos2d::Value::Type type,FileStream& writeStr,const cocos2d::Value& value)
{
    
    switch (type)
    {
        case cocos2d::Value::Type::BYTE:
            if (m_bisDebug)
                CCLOG("WIRITE TYPE:%d",type);
            writeStr.write8(value.asByte());
            break;
        case cocos2d::Value::Type::INTEGER:
            if (m_bisDebug)
                CCLOG("WIRITE TYPE:%d",type);
            writeStr.write32le(value.asInt());
            break;
        case cocos2d::Value::Type::FLOAT:
            if (m_bisDebug)
                CCLOG("WIRITE TYPE:%d",type);
            writeStr.writef(value.asFloat());
            break;
        case cocos2d::Value::Type::DOUBLE:
        {
            if (m_bisDebug)
                CCLOG("WIRITE TYPE:%d",type);
            double f = value.asDouble();
            writeStr.write(&f, sizeof(double));
        }
            break;
        case cocos2d::Value::Type::BOOLEAN:
            if (m_bisDebug)
                CCLOG("WIRITE TYPE:%d",type);
            writeStr.writeBool(value.asBool());
            break;
        case cocos2d::Value::Type::STRING:
            if (m_bisDebug)
                CCLOG("WIRITE TYPE:%d",type);
            writeStr.writeString(value.asString());
            break;
        case cocos2d::Value::Type::VECTOR:
        case cocos2d::Value::Type::MAP:
        case cocos2d::Value::Type::INT_KEY_MAP:
        {
            
            int64 valueSize =  0 ;
            //计算列表大小 记录列表大小
            calculateValue(valueSize, value);
            if (m_bisDebug)
                CCLOG("WIRITE valueSize:%lld",valueSize);
            writeStr.write64le(valueSize);
            if (valueSize!=0) {
                wirteValue(writeStr, value);
            }
        }
            break;
            
        default:
            break;
    }
}
void  PlistBinaryUtil::parseValueType(MemoryStream& readStream,cocos2d::Value& nodeValue)
{
    int64 valueSize = readStream.read64le();
    if (m_bisDebug)
        CCLOG("PARSE valueSize:%llu",valueSize);
    if (valueSize != 0)
    {
        char tempVector[valueSize];
        memset(tempVector, 0, valueSize);
        
        readStream.read(tempVector, valueSize);
        MemoryStream tempStream(tempVector,valueSize);
        
        while (!tempStream.eof()) {
            parseValue(tempStream, nodeValue);
        }
        
    }
    
}
cocos2d::Value PlistBinaryUtil::parseBaseicValueType(cocos2d::Value::Type type, MemoryStream& readStream)
{
    if (m_bisDebug)
        CCLOG("PARSE TYPE:%d",type);
    cocos2d::Value readValue;
    switch (type) {
        case cocos2d::Value::Type::BYTE:
            readValue = readStream.read8();
            break;
        case cocos2d::Value::Type::INTEGER:
            readValue = readStream.read32le();
            break;
        case cocos2d::Value::Type::FLOAT:
            readValue = readStream.readf();
            break;
        case cocos2d::Value::Type::DOUBLE:
        {
            double dvalue;
            readStream.read(&dvalue, sizeof(double));
            readValue = dvalue;
        }
            break;
        case cocos2d::Value::Type::BOOLEAN:
            readValue = readStream.readBool();
            break;
        case cocos2d::Value::Type::STRING:
            readValue =  readStream.readString();
            break;
        default:
            break;
    }
    return readValue;
}
void  PlistBinaryUtil::parseValue(MemoryStream& readStream,cocos2d::Value& value)
{
    cocos2d::Value::Type type = (cocos2d::Value::Type)readStream.read32le();
    cocos2d::Value key;
    cocos2d::Value currentValue;
    //只有map才有key 所以需要读入key vector不需要读取key
    if (value.getType()==cocos2d::Value::Type::MAP)
    {
        key= readStream.readString();
        if (m_bisDebug)
            CCLOG("PARSE MAP key:%s",key.asString().c_str());
    }else if (value.getType() == cocos2d::Value::Type::INT_KEY_MAP)
    {
        key= readStream.read32le();
        if (m_bisDebug)
            CCLOG("PARSE INT_KEY_MAP key:%s",key.asString().c_str());
    }
    
    if (type == cocos2d::Value::Type::VECTOR)
    {
        if (m_bisDebug)
            CCLOG("PARSE VECTOR type:%d",type);
        
        if (currentValue.getType() == cocos2d::Value::Type::NONE) {
            cocos2d::ValueVector tempValue;
            currentValue = tempValue;
            parseValueType(readStream, currentValue);
        }
        
    }else if(type == cocos2d::Value::Type::MAP)
    {
        if (m_bisDebug)
            CCLOG("PARSE MAP type:%d",type);
        if (currentValue.getType() == cocos2d::Value::Type::NONE) {
            cocos2d::ValueMap tempValue;
            currentValue = tempValue;
            parseValueType(readStream, currentValue);
        }
        
    }else if(type == cocos2d::Value::Type::INT_KEY_MAP)
    {
        if (m_bisDebug)
            CCLOG("PARSE INT_KEY_MAP type:%d",type);
        if (currentValue.getType() == cocos2d::Value::Type::NONE) {
            cocos2d::ValueMapIntKey tempValue;
            currentValue = tempValue;
            parseValueType(readStream, currentValue);
        }
        
    }else{
        
        currentValue = parseBaseicValueType(type,readStream);
        
    }
    
    if (currentValue.getType() != cocos2d::Value::Type::NONE) {
        if (value.getType() == cocos2d::Value::Type::VECTOR)
        {
            value.asValueVector().push_back( currentValue);
        }else if(value.getType() == cocos2d::Value::Type::MAP)
        {
            value.asValueMap().insert(cocos2d::ValueMap::value_type(key.asString(),currentValue));
        }else if(value.getType() == cocos2d::Value::Type::INT_KEY_MAP)
        {
            value.asIntKeyMap().insert(cocos2d::ValueMapIntKey::value_type(key.asInt(),currentValue));
        }
        
    }
    
    
    
}

void PlistBinaryUtil::calculateValueType(int64 &num,cocos2d::Value::Type type,const cocos2d::Value& value)
{
    //    CCLOG("WIRITE TYPE:%d",type);
    switch (type)
    {
        case cocos2d::Value::Type::BYTE:
            num+=1;
            break;
        case cocos2d::Value::Type::INTEGER:
            num+=4;
            break;
        case cocos2d::Value::Type::FLOAT:
            num+=sizeof(float);
            break;
        case cocos2d::Value::Type::DOUBLE:
            num+=sizeof(double);
            break;
        case cocos2d::Value::Type::BOOLEAN:
            num+=1;
            break;
        case cocos2d::Value::Type::STRING:
            num+=4;
            num+=value.asString().length();
            break;
        case cocos2d::Value::Type::VECTOR:
        case cocos2d::Value::Type::MAP:
        case cocos2d::Value::Type::INT_KEY_MAP:
            
            num+=sizeof(int64);
            calculateValue(num, value);
            break;
            
        default:
            break;
    }
    
}
void PlistBinaryUtil::calculateValue(int64 &num,const cocos2d::Value& aValue)
{
    cocos2d::Value::Type type = aValue.getType();
    
    if (cocos2d::Value::Type::VECTOR == type) {
        
        for (auto iter = aValue.asValueVector().begin(); iter != aValue.asValueVector().end(); iter++)
        {
            cocos2d::Value itemValue = *iter;
            num+= 4;
            calculateValueType(num,itemValue.getType(),itemValue);
        }
    }else if (cocos2d::Value::Type::MAP == type)
    {
        for (auto iter = aValue.asValueMap().begin(); iter != aValue.asValueMap().end(); iter++)
        {
            cocos2d::Value itemValue = iter->second;
            num+= 4;
            num+=4;
            num+= iter->first.length();
            //            CCLOG("key:%s",iter->first.c_str());
            calculateValueType(num,itemValue.getType(),itemValue);
        }
        
    }else if (cocos2d::Value::Type::INT_KEY_MAP == type)
    {
        for (auto iter = aValue.asIntKeyMap().begin(); iter != aValue.asIntKeyMap().end(); iter++)
        {
            cocos2d::Value itemValue = iter->second;
            num+=sizeof((int)itemValue.getType());
            num+=sizeof(iter->first);
            calculateValueType(num,itemValue.getType(),itemValue);
        }
    }
}
