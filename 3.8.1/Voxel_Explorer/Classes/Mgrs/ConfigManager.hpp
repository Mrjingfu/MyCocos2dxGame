//
//  ConfigManager.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 16/3/9.
//
//

#ifndef ConfigManager_hpp
#define ConfigManager_hpp

#include "GameConfig.h"
const std::string ARCHIVE_CONFIG_KEY = "ARCHIVE_CONFIG_KEY";
const std::string ARCHIVE_CONFIG_LANGUAGE_TYPE_KEY = "ARCHIVE_CONFIG_LANGUAGE_TYPE_KEY";
class  ConfigManager{
    
    ConfigManager(){};
public:
    
    ~ConfigManager(){};
    SINGLE_FUNC(ConfigManager);
    virtual bool load(const cocos2d::ValueMap& rootNode );
    virtual bool save(cocos2d::ValueMap& rootNode);
    void setLanguageType(cocos2d::LanguageType type){m_nLanguageType = type;}
    cocos2d::LanguageType getLanguageType() const{return m_nLanguageType;};
private:
    cocos2d::LanguageType m_nLanguageType;

};

#endif /* ConfigManager_hpp */
