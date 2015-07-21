//
//  LevelsManager.h
//  MazeJump
//
//  Created by wang haibo on 15/7/20.
//
//

#ifndef __MazeJump__LevelsManager__
#define __MazeJump__LevelsManager__

#include "cocos2d.h"
class LevelsManager : public cocos2d::Ref
{
    LevelsManager();
    ~LevelsManager();
public:
    static LevelsManager* getInstance();
    bool init(const std::string& file);
    
    std::string getCurrentLevelName();
    cocos2d::Color4F getCurrentLevelFogColor();
    std::string getCurrentLevelSkyTextureName();
    std::string getCurrentLevelPlatformModelName();
    
    int getCurrentLevel() const { return m_nCurrentLevel; }
    void setCurrentLevel(int currentLevel);
    int getMaxReachLevel() const { return m_nMaxReachLevel; }
private:
    void setMaxReachLevel(int maxReachLevel);
private:
    cocos2d::ValueVector    m_Levels;
    int                     m_nMaxReachLevel;
    int                     m_nCurrentLevel;
};


#endif /* defined(__MazeJump__LevelsManager__) */
