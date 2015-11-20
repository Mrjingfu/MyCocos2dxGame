//
//  StandardPortal.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/11/20.
//
//

#ifndef StandardPortal_hpp
#define StandardPortal_hpp

#include "BasePortal.hpp"
class StandardPortal : public BasePortal
{
    StandardPortal();
    virtual ~StandardPortal();
public:
    static StandardPortal* create(bool canUse);
    
    virtual bool createCenterModel(bool canUse, OutlineEffect3D* outline);
};

#endif /* StandardPortal_hpp */
