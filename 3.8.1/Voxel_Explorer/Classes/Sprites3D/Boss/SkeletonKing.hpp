//
//  SkeletonKing.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/22.
//
//

#ifndef SkeletonKing_hpp
#define SkeletonKing_hpp

#include "BaseBoss.hpp"
class SkeletonKing : public BaseBoss
{
    SkeletonKing();
    virtual ~SkeletonKing();
public:
    static SkeletonKing* create(BaseBoss::BossType type);
    
    virtual void onEnter();
    virtual void update(float delta);
    
    virtual void onEnterSkill1Stage();
    virtual void onEnterSkill2Stage();
    virtual void onEnterSkill3Stage();
    virtual void onEnterDeath();
    
    virtual bool isPlayerInsideBossRoom();
    
private:
    float           m_fSkill1Timer;
    bool            m_bInSkill1Stage;
    
    float           m_fSkill3Timer;
    bool            m_bInSkill3Stage;
};

#endif /* SkeletonKing_hpp */
