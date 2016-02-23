//
//  KoboldLeader.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/12/5.
//
//

#ifndef KoboldLeader_hpp
#define KoboldLeader_hpp

#include "BaseBoss.hpp"
class KoboldLeader : public BaseBoss
{
    KoboldLeader();
    virtual ~KoboldLeader();
public:
    static KoboldLeader* create(BaseBoss::BossType type);
    
    virtual void update(float delta);
    virtual void onEnterTracking();
    virtual void onEnterSkill1Stage();
    virtual void onEnterSkill2Stage();
    virtual void onEnterSkill3Stage();
    virtual void onEnterDeath();
    
    virtual bool isPlayerInsideBossRoom();
    
    virtual void handleAttackStyle(const cocos2d::Vec2& playerPos, const cocos2d::Vec3& dir);
private:
    float           m_fSkill3Timer;
    bool            m_bInSkill3Stage;
};

#endif /* KoboldLeader_hpp */
