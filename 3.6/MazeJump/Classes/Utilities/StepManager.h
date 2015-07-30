//
//  StepManager.h
//  MazeJump
//
//  Created by chuangli  on 15/7/23.
//
//

#ifndef __MazeJump__StepManager__
#define __MazeJump__StepManager__

#include "cocos2d.h"

class StepManager : public cocos2d::Ref
{
protected:

   
    StepManager();
public:
    typedef enum
    {
        LEVEL_LOSE =0,
        LEVEL_WIN,
        LEVEL_UNKNOWN
    }
    LevelType;
    static StepManager* getInstance();
    void setStep(int index,int direction);
    void setLevelStep(int level,int levelStaus);
    cocos2d::ValueVector getLevelWinSteps(int level);
    cocos2d::ValueVector getLevelPromptSteps(int level);
private:
    cocos2d::ValueVector getLevelWinSteps(int level,std::string stepfile);
    cocos2d::ValueVector atVectorValue(int index);
    cocos2d::ValueMap m_levelSteps;
    cocos2d::ValueVector m_Steps;
};


#endif /* defined(__MazeJump__StepManager__) */
