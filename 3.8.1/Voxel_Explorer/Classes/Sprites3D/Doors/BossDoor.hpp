//
//  BossDoor.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/12/5.
//
//

#ifndef BossDoor_hpp
#define BossDoor_hpp

#include "BaseDoor.hpp"
class BossDoor : public BaseDoor
{
    BossDoor();
    virtual ~BossDoor();
public:
    static BossDoor* create(bool show);
    
    virtual bool createFakeDoor();
};

#endif /* BossDoor_hpp */
