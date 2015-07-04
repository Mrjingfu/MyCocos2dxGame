//
//  Player.h
//  MazeJump
//
//  Created by wang haibo on 15/7/3.
//
//

#ifndef __MazeJump__Player__
#define __MazeJump__Player__

class Player : public cocos2d::Sprite3D
{
public:
    typedef enum
    {
        PT_STRENGTH,
        PT_AGILITY,
        PT_FLEXIBLE,
        PT_UNKNOWN
    }
    PlayerType;
protected:
    Player();
public:
    static Player* create(PlayerType type);
    
    float getRadius() const { return m_fRadius; }
    PlayerType getType() const { return m_Type; }
    void setType(PlayerType type);
protected:
    float           m_fRadius;
    PlayerType       m_Type;
};

#endif /* defined(__MazeJump__Player__) */
