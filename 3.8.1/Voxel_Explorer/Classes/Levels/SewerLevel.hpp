//
//  SewerLevel.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/23.
//
//

#ifndef SewerLevel_hpp
#define SewerLevel_hpp

#include "StandardLevel.h"
class SewerLevel : public StandardLevel
{
public:
    SewerLevel();
    
    virtual bool createMonsters();
    virtual bool createItems();
};

#endif /* SewerLevel_hpp */
