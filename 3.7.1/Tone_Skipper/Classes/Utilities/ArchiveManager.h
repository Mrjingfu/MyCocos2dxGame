//
//  ArchiveManager.h
//  Tone_Skipper
//
//  Created by 创李 on 15/10/5.
//
//

#ifndef __Tone_Skipper__ArchiveManager__
#define __Tone_Skipper__ArchiveManager__

#include "UserRecord.h"
#include "GameConfig.h"
class ArchiveManager
{
    ArchiveManager();
public:
    ~ArchiveManager();
   static ArchiveManager* getInstance();
    void init(int archiveCount);
    
    UserRecord* getUserRecord();
    std::string getDeviceUUid();
    void setChaosValue(eChaoType eType,CChaosNumber nNumber);
    bool changeChaosValue(eChaoType eType,CChaosNumber chageValue);
    int getChaosValue(eChaoType eType);
    void LoadInitData();
    void saveData();
    eStartupType getStartupType();
    std::string getCurrentArchiveName();
private:
    void setFirstSetting();
    UserRecord* mUserRecord;
};

#endif /* defined(__Tone_Skipper__ArchiveManager__) */
