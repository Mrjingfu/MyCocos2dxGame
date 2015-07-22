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
class PatternsManager : public cocos2d::Ref
{
    PatternsManager();
    ~PatternsManager();
public:
    static PatternsManager* getInstance();
    bool init(const std::string& file);
    
    cocos2d::ValueVector getPatternTerrainCells(int patternIndex);
    

private:
    cocos2d::ValueVector    m_Patterns;
};


#endif /* defined(__MazeJump__PatternsManager__) */
