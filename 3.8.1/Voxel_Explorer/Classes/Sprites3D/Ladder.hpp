//
//  Ladder.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/11/25.
//
//

#ifndef Ladder_hpp
#define Ladder_hpp

#include "EffectSprite3D.h"
class Ladder : public EffectSprite3D
{
protected:
    Ladder();
    virtual ~Ladder();
public:
    static Ladder* create();
    
    cocos2d::Vec2 getPosInMap();
    
    void setVisited(bool visited);
};

#endif /* Ladder_hpp */
