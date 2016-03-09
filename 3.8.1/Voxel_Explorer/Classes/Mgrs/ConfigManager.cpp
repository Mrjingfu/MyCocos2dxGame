//
//  ConfigManager.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 16/3/9.
//
//

#include "ConfigManager.hpp"
bool ConfigManager::load(const cocos2d::ValueMap& rootNode )
{
    //没有存档时
    if (rootNode.find(ARCHIVE_CONFIG_KEY) == rootNode.end())
    {
        m_nLanguageType = cocos2d::Application::getInstance()->getCurrentLanguage();
        return true;
    }
    //加载存档
    cocos2d::ValueMap m_vConfigs = rootNode.at(ARCHIVE_CONFIG_KEY).asValueMap();
    
    m_nLanguageType = (cocos2d::LanguageType)m_vConfigs.at(ARCHIVE_CONFIG_LANGUAGE_TYPE_KEY).asInt();
    return true;
    
}
bool ConfigManager::save(cocos2d::ValueMap& rootNode)
{
    cocos2d::ValueMap m_vConfigs;
    
    m_vConfigs.insert(cocos2d::ValueMap::value_type(ARCHIVE_CONFIG_LANGUAGE_TYPE_KEY,cocos2d::Value((int)m_nLanguageType)));
    
    rootNode.insert(cocos2d::ValueMap::value_type(ARCHIVE_CONFIG_KEY,cocos2d::Value(m_vConfigs)));
    
    return true;
}