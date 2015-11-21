//
//  SmallPortal.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/11/20.
//
//

#ifndef SmallPortal_hpp
#define SmallPortal_hpp

#include "BasePortal.hpp"
class SmallPortal : public BasePortal
{
    SmallPortal();
    virtual ~SmallPortal();
public:
    static SmallPortal* create(bool canUse);
    
    virtual bool createCenterModel(bool canUse, OutlineEffect3D* outline);
};

#endif /* SmallPortal_hpp */
