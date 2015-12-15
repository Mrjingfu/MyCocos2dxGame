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
    virtual void onEnterSkill1();
    virtual void onEnterSkill2();
    virtual void onEnterSkill3();
    virtual void onEnterDeath();
    
    virtual bool isPlayerInsideBossRoom();
    
private:
    float           m_fSkill2Timer;
    bool            m_bInSkill2Stage;
};

#endif /* Archbishop_hpp */
