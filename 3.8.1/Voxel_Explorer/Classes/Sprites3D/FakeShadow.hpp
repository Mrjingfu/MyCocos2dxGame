//
//  FakeShadow.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/11/25.
//
//

#ifndef FakeShadow_hpp
#define FakeShadow_hpp

#include "EffectSprite3D.h"
class FakeShadow : public EffectSprite3D
{
protected:
    FakeShadow();
    virtual ~FakeShadow();
public:
    static FakeShadow* create();
    
    cocos2d::Vec2 getPosInMap();
    
    void setVisited(bool visited);
};

#endif /* FakeShadow_hpp */
