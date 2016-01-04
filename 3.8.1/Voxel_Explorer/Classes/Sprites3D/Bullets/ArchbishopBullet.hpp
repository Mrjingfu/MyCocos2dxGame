//
//  ArchbishopBullet.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 16/1/3.
//
//

#ifndef ArchbishopBullet_hpp
#define ArchbishopBullet_hpp

#include "BaseBullet.hpp"
class ArchbishopBullet : public BaseBullet
{
    ArchbishopBullet();
    virtual ~ArchbishopBullet();
    
    bool createParticleEffect();
public:
    static ArchbishopBullet* create(BaseBoss* pOwner);
};

#endif /* ArchbishopBullet_hpp */
