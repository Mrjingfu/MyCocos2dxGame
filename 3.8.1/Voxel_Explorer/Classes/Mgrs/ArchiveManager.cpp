//
//  ArchiveManager.cpp
//  Tone_Skipper
//
//  Created by 创李 on 15/10/5.
//
//

#include "ArchiveManager.h"
#include "CCCrypto.h"
#include "UtilityHelper.h"
#include "StatisticsManager.hpp"
#include "AchievementManager.h"
#include "PlistBinaryUtil.hpp"
USING_NS_CC;
ArchiveManager::ArchiveManager()
{
    
}
ArchiveManager::~ArchiveManager()
{
   
}

bool  ArchiveManager::loadGame()
{
    
    std::string path = cocos2d::FileUtils::getInstance()->getWritablePath()+sArchiveName;
    
    ValueMap gameMap = PlistBinaryUtil::getInstance()->getValueMapFromFile(path);

#if COCOS2D_DEBUG==1
    //!!!!!!!!打包一定记得检查
    std::string debugPath = cocos2d::FileUtils::getInstance()->getWritablePath()+"Debug.plist";
    CCLOG("LOADGAME:%s",getStringValueMap(gameMap,debugPath).c_str());
#endif
    if (gameMap.empty()) {
        CCLOG("gamemap is null");
        return false;
    }

    //加载游戏数据
    if (!StatisticsManager::getInstance()->load(gameMap)) {
        return false;
    }
    if (!AchievementManager::getInstance()->load(gameMap)) {
        return false;
    }
   

    return true;
}
void  ArchiveManager::saveGame()
{
    ValueMap map;
    
    //存储游戏数据
    StatisticsManager::getInstance()->save(map);
    AchievementManager::getInstance()->save(map);
    
    std::string path = cocos2d::FileUtils::getInstance()->getWritablePath()+ sArchiveName;
#if COCOS2D_DEBUG==1
    std::string debugPath = cocos2d::FileUtils::getInstance()->getWritablePath()+"Debug.plist";
    CCLOG("SAVEGAME:%s",getStringValueMap(map,debugPath).c_str());
#endif
    PlistBinaryUtil::getInstance()->writeValueMapToFile(map, path,true);
    
}
std::string ArchiveManager::getStringValueMap(cocos2d::ValueMap& dict,const std::string &fullPath)
{
    std::string result;

    FileUtils::getInstance()->writeValueMapToFile(dict, fullPath);

    ssize_t size;
    const unsigned char* content = cocos2d::FileUtils::getInstance()->getFileData(fullPath.c_str(), "rb", &size);
    if (size <= 0 )
    {
        CCLOG("file content is null");
        return result;
    }
    
    std::string sRet((char*)content,size);
    CC_SAFE_DELETE_ARRAY(content);
    return sRet;
}



