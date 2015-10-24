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
    bool init();
    bool initLevelRes();
    void clearLevelRes();
    std::string getTerrainTileRes(const std::string& tileTypeName);
    std::string getDoorRes(const std::string& doorTypeName);
    std::string getMonsterRes(const std::string& monsterTypeName);
    std::string getItemIconRes(const std::string& itemTypeName);
    std::string getItemModelRes(const std::string& itemTypeName);
private:
    cocos2d::ValueMap    m_TerrainTilesResMap;
    cocos2d::ValueMap    m_DoorsResMap;
    cocos2d::ValueMap    m_MonstersResMap;
    cocos2d::ValueMap    m_ItemsResMap;
    
    cocos2d::ValueMap    m_TerrainTilesLevelRes;
    cocos2d::ValueMap    m_DoorsLevelRes;
};


#endif /* defined(__MazeJump__PatternsManager__) */
