//
//  MonsterPropLayer.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/27.
//
//

#ifndef MonsterPropLayer_hpp
#define MonsterPropLayer_hpp

#include "CharacterPropLayer.hpp"
class BaseMonster;
class MonsterPropLayer:public CharacterPropLayer
{
    MonsterPropLayer();
public:
    CREATE_FUNC(MonsterPropLayer);
    virtual ~MonsterPropLayer();
     virtual bool initUi() override;
    virtual void updateCharacterBuff() override;
    virtual void updateCharacterProp() override;
    virtual bool addEvents() override;
    void setMonster(BaseMonster* monster){m_pMonster = monster;}
private:
    BaseMonster* m_pMonster;
};

#endif /* MonsterPropLayer_hpp */
