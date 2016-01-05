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
#include "PlayerProperty.hpp"
#include "RandomEventMgr.hpp"
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
    if (!gameMap.empty()) {
        std::string debugPath = cocos2d::FileUtils::getInstance()->getWritablePath()+"Debug.plist";
        CCLOG("LOADGAME:%s",getStringValueMap(gameMap,debugPath).c_str());
    }else
        CCLOGERROR("SAVEGAME  gamemap is null");

#endif

    //加载游戏数据
    if(!RandomDungeon::getInstance()->load(gameMap))
    {
        CCLOGERROR("RandomDungeon load failed!");
        return false;
    }
    if(!RandomEventMgr::getInstance()->load(gameMap))
    {
        CCLOGERROR("RandomEventMgr load failed!");
        return false;
    }
    if (!PlayerProperty::getInstance()->load(gameMap))
    {
        CCLOGERROR("PlayerProperty load failed!");
        return false;
    }
    if (!StatisticsManager::getInstance()->load(gameMap)) {
        CCLOGERROR("StatisticsManager load failed");
        return false;
    }
    if (!AchievementManager::getInstance()->load(gameMap)) {
        CCLOGERROR("AchievementManager load failed");
        return false;
    }

    return true;
}
bool  ArchiveManager::saveGame()
{
    ValueMap map;
    
    //存储游戏数据
    if (!PlayerProperty::getInstance()->save(map))
    {
        CCLOGERROR("PlayerProperty save failed");
        return false;
    }
    if (!StatisticsManager::getInstance()->save(map))
    {
        CCLOGERROR("StatisticsManager save failed");
        return false;
    }
    if(!AchievementManager::getInstance()->save(map))
    {
        CCLOGERROR("AchievementManager save failed");
        return false;
    }
    
    
#if COCOS2D_DEBUG==1
    if (!map.empty()) {
        std::string debugPath = cocos2d::FileUtils::getInstance()->getWritablePath()+"Debug.plist";
        CCLOG("SAVEGAME:%s",getStringValueMap(map,debugPath).c_str());
    }else
        CCLOGERROR("SAVEGAME  gamemap is null");
#endif
    
   std::string path = cocos2d::FileUtils::getInstance()->getWritablePath()+ sArchiveName;
    if ( !PlistBinaryUtil::getInstance()->writeValueMapToFile(map, path,true)) {
        CCLOGERROR("wirte Gamemap failed");
        return false;
    }
    
    return true;
}
std::string ArchiveManager::getStringValueMap(cocos2d::ValueMap& dict,const std::string &fullPath)
{
    std::string result;

    FileUtils::getInstance()->writeValueMapToFile(dict, fullPath);

    ssize_t size;
    const unsigned char* content = cocos2d::FileUtils::getInstance()->getFileData(fullPath.c_str(), "rb", &size);
    if (size <= 0 )
    {
        CCLOGERROR("file content is null");
        return result;
    }
    std::string sRet((char*)content,size);
    CC_SAFE_DELETE_ARRAY(content);
    return sRet;
}



