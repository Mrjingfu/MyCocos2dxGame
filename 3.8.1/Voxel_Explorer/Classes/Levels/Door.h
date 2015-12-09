//
//  Door.h
//  Voxel_Explorer
//
//  Created by wang haibo on 15/9/24.
//
//

#ifndef __Voxel_Explorer__Door__
#define __Voxel_Explorer__Door__

#include "cocos2d.h"
class Door : public cocos2d::Ref
{
    Door();
    virtual ~Door();
public:
    typedef enum{
        DT_EMPTY,
        DT_PASSAGE,
        DT_TUNNEL,
        DT_STANDARD,
        DT_UNLOCKED,
        DT_LOCKED,
        DT_HIDDEN,
        DT_BARRICADE,
        DT_ARENA,
        DT_LOCKED_EXIT,
        DT_MAX
    }
    DOOR_TYPE;
    
    static Door* create();
    virtual bool init();
    
    DOOR_TYPE getDoorType() const;
    void setDoorType(DOOR_TYPE type);
    
    cocos2d::Vec2 getPos() const;
    void setPos(const cocos2d::Vec2& pos);
    
protected:
    DOOR_TYPE           m_Type;
    cocos2d::Vec2       m_Pos;
};

#endif /* defined(__Voxel_Explorer__Door__) */
