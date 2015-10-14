//
//  BaseDoor.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/14.
//
//

#ifndef BaseDoor_hpp
#define BaseDoor_hpp

#include "Actor.hpp"
#include "TerrainTile.hpp"
class BaseDoor : public Actor
{
public:
    typedef enum{
        DS_CLOSED,
        DS_OPENED,
        DS_LOCKED,
        DS_HIDE,
        DS_MAX
    } DoorState;
protected:
    BaseDoor();
    ~BaseDoor();
    
    virtual bool createFakeDoor(TerrainTile::TileType type) = 0;
    
    virtual void onEnterClosed();
    virtual void onExitClosed();
    
    virtual void onEnterOpened();
    virtual void onExitOpened();
    
    virtual void onEnterLocked();
    virtual void onExitLocked();
    
    virtual void onEnterHide();
    virtual void onExitHide();
public:
    DoorState getDoorState() const;
    void setDoorState(DoorState state);
protected:
    DoorState   m_DoorState;
    cocos2d::Sprite3D*      m_pFakeDoor;
};

#endif /* BaseDoor_hpp */
