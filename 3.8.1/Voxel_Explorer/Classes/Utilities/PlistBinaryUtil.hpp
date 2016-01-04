//
//  ValueMapBinaryUtil.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 16/1/4.
//
//

#ifndef ValueMapBinaryUtil_hpp
#define ValueMapBinaryUtil_hpp
#include "FileStream.h"
#include "MemoryStream.h"

#define MD5_LEN 16

class PlistBinaryUtil {
    PlistBinaryUtil();
public:
    virtual ~PlistBinaryUtil();
    static PlistBinaryUtil* getInstance();
    
    //获取从文件中获取ValueMap
    cocos2d::ValueMap getValueMapFromFile(const std::string& filename);
    //ValueMap写入文件  isEncrpty 表示是否加密  默认不加密
    bool writeValueMapToFile(cocos2d::ValueMap& dict, const std::string& fullPath,bool isEncrpty = false);
    
    //获取从文件中获取ValueVector
    cocos2d::ValueVector getValueVectorFromFile(const std::string& filename);
    bool writeValueVectorToFile(cocos2d::ValueVector& dict, const std::string& fullPath,bool isEncrpty = false);
    
private:
    
    bool wiriteValueForFile(cocos2d::Value& dict,const std::string& fullPath,bool isEncrpty);
    bool getValueForFile(cocos2d::Value& dict,const std::string& filename);
    
    void wirteValue(FileStream& writeStr,const  cocos2d::Value& avalue);
    void wirteValueType(cocos2d::Value::Type type,FileStream& writeStr,const cocos2d::Value& value);


    //解析map vector intMap等类型
    void parseValueType(MemoryStream& readStream, cocos2d::Value& value);
    //解析基本类型
    cocos2d::Value parseBaseicValueType(cocos2d::Value::Type type, MemoryStream& readStream);
    //解析value
    void parseValue(MemoryStream& readStream,cocos2d::Value& value);
    
    void calculateValueType(int64 &num,cocos2d::Value::Type type,const cocos2d::Value& value);
    //计算value的大小
    void calculateValue(int64 &num,const cocos2d::Value& aValue);
private:
    bool m_bisDebug;
};

#endif /* ValueMapBinaryUtil_hpp */
