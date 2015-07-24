//
//  AlisaMethod.h
//  MazeJump
//
//  Created by wang haibo on 15/7/24.
//
//

#ifndef __MazeJump__AlisaMethod__
#define __MazeJump__AlisaMethod__

#include "cocos2d.h"

class AlisaMethod : public cocos2d::Ref
{
public:
    static AlisaMethod* createWithOnePercent(float percent);
    static AlisaMethod* create(float percent1, ...) CC_REQUIRES_NULL_TERMINATION;
    static AlisaMethod* createWithTwoPercent(float percent1, float percent2);
    static AlisaMethod* createWithVariableList(float percent1, va_list args);
    static AlisaMethod* createWithPercentArray(std::vector<float>& percentArray);
    
    int getRandomIndex();
    void printProbArray();
    void printAlisaArray();
protected:
    bool initWithPercent(float percent);
    bool initWithTwoPercent(float percent1, float percent2);
    bool initWithPercentVariableList(float percent1, va_list args);
    bool initWithPercentArray(std::vector<float>& percentArray);
private:
    std::vector<float>      m_probArray;
    std::vector<int>        m_alisaArray;
};

#endif /* defined(__MazeJump__AlisaMethod__) */
