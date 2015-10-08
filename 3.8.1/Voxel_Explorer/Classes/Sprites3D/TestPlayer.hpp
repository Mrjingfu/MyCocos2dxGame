//
//  TestPlayer.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/8.
//
//

#ifndef TestPlayer_hpp
#define TestPlayer_hpp

#include "cocos2d.h"
class TestPlayer : public cocos2d::Sprite3D
{
public:
    typedef enum {
        PS_IDLE = 0,
        PS_MOVE_LEFT,
        PS_MOVE_RIGHT,
        PS_MOVE_FORWARD,
        PS_MOVE_JUMPLOCAL,
        PS_MOVE_DROP,
        PS_DEATH,
        PS_UNKNOWN
    } PlayerState;
    typedef enum {
        PD_FORWARD = 0,
        PD_LEFT,
        PD_RIGHT,
        RD_UNKNOWN
    } PlayerDir;
protected:
    TestPlayer();
    virtual ~TestPlayer();
public:
    static TestPlayer* create(const std::string& modelPath);
private:
    PlayerState     m_curState;
    PlayerDir       m_dir;
};

#endif /* TestPlayer_hpp */
