//
//  ShatterAction.h
//  TinyFlare
//
//  Created by wang haibo on 15/4/14.
//
//

#ifndef __TinyFlare__ShatterAction__
#define __TinyFlare__ShatterAction__

#include "cocos2d.h"
class ShatterAction : public cocos2d::ActionInterval
{
    ShatterAction();
    virtual ~ShatterAction();
public:
    static ShatterAction* create(float duration);
    virtual void stop();
    virtual void startWithTarget(cocos2d::Node* target);
    virtual void update(float time);
protected:
    float m_fTimeFoe;
    float m_fTimeCur;
    float m_fGrowSpeedOfTargetR;
    
};


#endif /* defined(__TinyFlare__ShatterAction__) */
