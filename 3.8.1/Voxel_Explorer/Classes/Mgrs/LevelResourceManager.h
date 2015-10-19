//
//  PatternsManager.h
//  MazeJump
//
//  Created by wang haibo on 15/7/22.
//
//

#ifndef __MazeJump__PatternsManager__
#define __MazeJump__PatternsManager__

#include "cocos2d.h"
class LevelResourceManager : public cocos2d::Ref
{
    LevelResourceManager();
    ~LevelResourceManager();
public:
    static LevelResourceManager* getInstance();
    bool init(const std::string& file);
    bool initLevelRes(const std::string& type);
    void clearLevelRes(const std::string& type);
    std::string getModelRes(std::string& type);
    std::string getTerrainTileRes(std::string& type);
    
private:
    cocos2d::ValueMap    m_models;
    cocos2d::ValueMap    m_tileds;
    cocos2d::ValueMap    m_LevelRes;
};


#endif /* defined(__MazeJump__PatternsManager__) */
