//
//  StandardDoor.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/13.
//
//

#ifndef StandardDoor_hpp
#define StandardDoor_hpp

#include "BaseDoor.hpp"
class StandardDoor : public BaseDoor
{
    StandardDoor();
    ~StandardDoor();
public:
    static StandardDoor* create();
    
    virtual bool createFakeDoor(TerrainTile::TileType type);
};
#endif /* StandardDoor_hpp */
