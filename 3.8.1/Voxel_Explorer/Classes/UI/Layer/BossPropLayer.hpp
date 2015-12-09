//
//  MonsterPropLayer.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/27.
//
//

#ifndef BossPropLayer_hpp
#define BossPropLayer_hpp

#include "CharacterPropLayer.hpp"
class BaseBoss;
class BossPropLayer:public CharacterPropLayer
{
    BossPropLayer();
public:
    CREATE_FUNC(BossPropLayer);
    virtual ~BossPropLayer();
     virtual bool initUi() override;
    virtual void updateCharacterBuff() override;
    virtual void updateCharacterProp() override;
    virtual bool addEvents() override;
    void setBoss(BaseBoss* boss){m_pBoss = boss;}
private:
    BaseBoss* m_pBoss;
};

#endif /* MonsterPropLayer_hpp */
