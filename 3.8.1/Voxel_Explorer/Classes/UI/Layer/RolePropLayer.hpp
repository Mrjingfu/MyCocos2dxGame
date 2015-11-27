//
//  RolePropLayer.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/27.
//
//

#ifndef RolePropLayer_hpp
#define RolePropLayer_hpp

#include "CharacterPropLayer.hpp"

class RolePropLayer:public CharacterPropLayer
{
    RolePropLayer();
public:
    CREATE_FUNC(RolePropLayer);
    virtual ~RolePropLayer();
    virtual void updateCharacterBuff() override;
    virtual void updateCharacterProp() override;
    virtual bool addEvents() override;
public:
    void onClickRole(Ref* ref);
};

#endif /* RolePropLayer_hpp */
