//
//  ArchiveManager.h
//  Tone_Skipper
//
//  Created by 创李 on 15/10/5.
//
//

#ifndef __TinyFlare__ArchiveManager__
#define __TinyFlare__ArchiveManager__

#include "UserRecord.h"
#include "GameConfig.h"
#include "FileStream.h"
#include "MemoryStream.h"
class iArchive
{
   virtual bool load(const cocos2d::ValueMap& archiveNode ) = 0;
   virtual bool save(cocos2d::ValueMap& archiveNode) = 0;
protected:
    
   bool hasKey(std::string key,const cocos2d::ValueMap& rootNode )
   {
       auto iter = rootNode.find(key);
       if (iter!= rootNode.end()) {
           return true;
       }
       return false;
   }
    
};

class ArchiveManager
{
    ArchiveManager();
public:
    ~ArchiveManager();
    SINGLE_FUNC(ArchiveManager);
    bool isExistArchive();
    bool restartArchive();
    bool loadGame();
    bool loadGameAchieve();
    bool saveGameAchieve();
    bool saveGame();
private:
    std::string getStringValueMap(cocos2d::ValueMap& dict,const std::string& fullPath);

};

#endif /* defined(__TinyFlare__ArchiveManager__) */
