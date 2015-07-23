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
    static StepManager* getInstance();
    void setStep(int index);
    void setLevelStep(int level);
    cocos2d::ValueVector getLevelSteps(int level);
    void printfStep(int level)
    {
        for (cocos2d::Value  i:getLevelSteps(level)) {
            CCLOG("step:%d",i.asInt());
        }
    }
private:
    cocos2d::ValueMapIntKey m_levelSteps;
    cocos2d::ValueVector m_Steps;
};


#endif /* defined(__MazeJump__StepManager__) */
