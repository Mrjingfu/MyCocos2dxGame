//
//  Giant.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/22.
//
//

#ifndef Giant_hpp
#define Giant_hpp

#include "BaseBoss.hpp"
class Giant : public BaseBoss
{
    Giant();
    virtual ~Giant();
public:
    static Giant* create(BaseBoss::BossType type);
    
    virtual void update(float delta);
    
    virtual void onEnterSkill1Stage();
    virtual void onEnterSkill2Stage();
    virtual void onEnterSkill3Stage();
    virtual void onEnterDeath();
    
    virtual bool isPlayerInsideBossRoom();
    
    virtual void attackedByPlayer(bool miss);
private:
    
    float           m_fSkill1Timer;
    bool            m_bInSkill1Stage;
    
    float           m_fSkill2Timer;
    bool            m_bInSkill2Stage;
};

#endif /* Giant_hpp */
