//
//  MonsterPropLayer.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/27.
//
//

#ifndef NpcPropLayer_hpp
#define NpcPropLayer_hpp

#include "CharacterPropLayer.hpp"
class BaseMonster;
class NpcPropLayer:public CharacterPropLayer
{
    NpcPropLayer();
public:
    CREATE_FUNC(NpcPropLayer);
    virtual ~NpcPropLayer();
     virtual bool initUi() override;
    virtual void updateCharacterBuff() override;
    virtual void updateCharacterProp() override;
    virtual bool addEvents() override;
    
private:
   
};

#endif /* NpcPropLayer_hpp */
