//
//  Archbishop.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/22.
//
//

#ifndef Archbishop_hpp
#define Archbishop_hpp

#include "BaseBoss.hpp"
class Archbishop : public BaseBoss
{
    Archbishop();
    virtual ~Archbishop();
public:
    static Archbishop* create(BaseBoss::BossType type);
    
    virtual void update(float delta);
    virtual void onEnterTracking();
    virtual void onEnterSkill1Stage();
    virtual void onEnterSkill2Stage();
    virtual void onEnterSkill3Stage();
    virtual void onEnterDeath();
    
    virtual bool isPlayerInsideBossRoom();
    
    virtual void handleAttackStyle(const cocos2d::Vec2& playerPos, const cocos2d::Vec3& dir);
private:
    float           m_fSkill2Timer;
    bool            m_bInSkill2Stage;
};

#endif /* Archbishop_hpp */
