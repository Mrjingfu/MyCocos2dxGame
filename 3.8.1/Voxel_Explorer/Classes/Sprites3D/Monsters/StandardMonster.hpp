//
//  StandardMonster.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/22.
//
//

#ifndef StandardMonster_hpp
#define StandardMonster_hpp

#include "BaseMonster.hpp"
class StandardMonster : public BaseMonster
{
    StandardMonster();
    virtual ~StandardMonster();
public:
    static StandardMonster* create(BaseMonster::MonsterType type, bool elite = false);
};

#endif /* StandardMonster_hpp */
