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
    void setStep(int index,int direction);
    void setLevelStep(int level);
    cocos2d::ValueVector getLevelSteps(int level);
    void printfStep(int level)
    {
        for (cocos2d::Value  i:getLevelSteps(level)) {
            cocos2d::ValueVector pt =i.asValueVector();
            cocos2d::Value pts = pt[0];
            cocos2d::Value ore = pt[1];
            CCLOG("step 位置:%d,方向:%d",pts.asInt(),ore.asInt());
        }
    }
private:
    cocos2d::ValueMapIntKey m_levelSteps;
    cocos2d::ValueVector m_Steps;
};


#endif /* defined(__MazeJump__StepManager__) */
