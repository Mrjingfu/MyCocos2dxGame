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
    std::string getTerrainTileRes(const std::string& tileTypeName);
    std::string getDoorRes(const std::string& doorTypeName);
    std::string getMonsterModelRes(const std::string& monsterTypeName);
    std::string getMonsterIconRes(const std::string& monsterTypeName);
    std::string getItemIconRes(const std::string& itemTypeName);
    std::string getItemModelRes(const std::string& itemTypeName);
    std::string getDungeonSoundEffectRes(const std::string& soundTypeName);
    std::string getMonsterSoundEffectRes(const std::string& monsterTypeName, const std::string& soundTypeName);
    std::string getCommonSoundEffectRes(const std::string& soundTypeName);
    std::string getBackgroundMusicRes(const std::string& bgMusicTypeName);
    
    std::string getParticles3DRes(const std::string& particles3DTypeName);
private:
    cocos2d::ValueMap    m_TerrainTilesResMap;
    cocos2d::ValueMap    m_DoorsResMap;
    cocos2d::ValueMap    m_MonstersResMap;
    cocos2d::ValueMap    m_ItemsResMap;
    cocos2d::ValueMap    m_DungeonSoundsResMap;
    cocos2d::ValueMap    m_MonsterSoundsResMap;
    cocos2d::ValueMap    m_CommonSoundsResMap;
    cocos2d::ValueMap    m_MusicsResMap;
    cocos2d::ValueMap    m_Particles3DResMap;
    
    cocos2d::ValueMap    m_TerrainTilesLevelRes;
    cocos2d::ValueMap    m_DoorsLevelRes;
    cocos2d::ValueMap    m_DungeonSoundsLevelRes;
    cocos2d::ValueMap    m_MusicsLevelRes;
};


#endif /* defined(__MazeJump__PatternsManager__) */
