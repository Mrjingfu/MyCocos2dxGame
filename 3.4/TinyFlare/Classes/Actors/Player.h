//
//  Player.h
//  Geometry-Wars
//
//  Created by wang haibo on 15/2/5.
//
//

#ifndef __Geometry_Wars__Player__
#define __Geometry_Wars__Player__

#include "GameActor.h"
#include "TwoJoysticks.h"

class Player : public GameActor, public JoystickLeftListener, public JoystickRightListener
{
public:
    typedef enum{
        WT_NORMAL = 0
    } WeaponType;
protected:
    Player();
    virtual ~Player();
public:
    CREATE_FUNC(Player);
    void update(float delta);
    void loadMaskModel(const std::string& texName);
    
    void onJoystickUpdateDirection(TwoJoysticks* joystick, const cocos2d::Vec2& dir);
    void onJoystickUpdateOrientation(TwoJoysticks* joystick, const cocos2d::Vec2& dir);
    void onJoystickPressed(TwoJoysticks* joystick, float pressedTime);
    void onJoystickReleased(TwoJoysticks* joystick, float pressedTime);
    
    cocos2d::Vec2 getFireWorldPos();
    cocos2d::Vec2 getFireLocalPos();
    cocos2d::Vec2 getLeftTailLocalPos();
    cocos2d::Vec2 getRightTailLocalPos();
    void fire(float delta);
    
    virtual void onEnterDead() override;
private:
    bool        m_bScheduledFire;
    cocos2d::Sprite*                m_pMaskModel;
    WeaponType                      m_WeaponType;
    cocos2d::ParticleSystemQuad*    m_pLeftTail;
    cocos2d::ParticleSystemQuad*    m_pRightTail;
};

#endif /* defined(__Geometry_Wars__Player__) */
