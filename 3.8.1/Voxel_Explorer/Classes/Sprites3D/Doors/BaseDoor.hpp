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

typedef enum{
    DOT_STANDARD,
    DOT_BOSS,
    DOT_MAX
} DoorOpenType;
extern const char* DOOR_MODEL_NAMES[];
class BaseDoor : public Actor
{
public:
    typedef enum{
        DS_UNKNOWN,
        DS_CLOSED,
        DS_OPENED,
        DS_LOCKED,
        DS_HIDE,
        DS_MAX
    } DoorState;
protected:
    BaseDoor();
    virtual ~BaseDoor();
    
    virtual bool createFakeDoor() = 0;
    
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
    
    virtual void setActorDir( ActorDir dir ) override;
    
    virtual void setVisited(bool visited) override;
    
    virtual std::string getDesc() override;
    
    bool isMagicLocked() const { return m_bMagicLocked; }
    void setMagicLocked(bool magicLocked) { m_bMagicLocked = magicLocked; }
    
    bool getOpenType() const { return m_OpenType; }
protected:
    DoorState   m_DoorState;
    DoorState   m_DoorLastState;
    cocos2d::Sprite3D*      m_pFakeDoor;
    DoorOpenType            m_OpenType;
    bool                    m_bMagicLocked;
};

#endif /* BaseDoor_hpp */
