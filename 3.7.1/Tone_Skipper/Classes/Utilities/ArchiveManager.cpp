//
//  ArchiveManager.cpp
//  Tone_Skipper
//
//  Created by 创李 on 15/10/5.
//
//

#include "ArchiveManager.h"

ArchiveManager::ArchiveManager()
{
    mUserRecord = nullptr;
}
ArchiveManager::~ArchiveManager()
{
   
}
void ArchiveManager::init(int archiveCount)
{
    CCLOG(" ArchiveManager::init");
    mUserRecord = nullptr;
    mUserRecord = new UserRecord();
    setFirstSetting();
    eStartupType type = getStartupType();
    if (eStartupFirstInstall == type) {
        CCLOG("start game first");
        setFirstSetting();
        LoadInitData();
        saveData();
    }else{
        mUserRecord->load(archiveCount);
    }
    
}

ArchiveManager* ArchiveManager::getInstance()
{
    static ArchiveManager instance;
    return &instance;
}
void ArchiveManager::LoadInitData()
{
    if (mUserRecord) {
        mUserRecord->init();
    }
}
void ArchiveManager::saveData()
{
    if (mUserRecord) {
        mUserRecord->save();
    }
}

UserRecord* ArchiveManager::getUserRecord()
{
    return mUserRecord;
}
std::string ArchiveManager::getDeviceUUid()
{
    if (mUserRecord) {
        return mUserRecord->mDeciveUid;
    }
    return "";
}

void ArchiveManager::setChaosValue(eChaoType eType, CChaosNumber nNumber)
{
    if (mUserRecord) {
        mUserRecord->mChaosValues[eType] = nNumber;
    }
}
bool ArchiveManager::changeChaosValue(eChaoType eType, CChaosNumber chageValue)
{
    if (mUserRecord) {
        CChaosNumber oldVal = getChaosValue(eType);
        CChaosNumber newVal = (long)oldVal+(long)chageValue;
        if (newVal < 0) {
            return false;
        }
        setChaosValue(eType, newVal);
        return true;
    }
    return false;
}
int ArchiveManager::getChaosValue(eChaoType eType)
{
    if (mUserRecord) {
        return mUserRecord->mChaosValues[eType];
    }
    return 0;
}
eStartupType ArchiveManager::getStartupType()
{
    bool havePlayedGame = cocos2d::UserDefault::getInstance()->getBoolForKey(sHavePlayedGame);
    if (!havePlayedGame) {
        return eStartupFirstInstall;
    }
    return eStartupNormal;
}
void ArchiveManager::setFirstSetting()
{
    cocos2d::UserDefault::getInstance()->setBoolForKey(sHavePlayedGame, true);
}
