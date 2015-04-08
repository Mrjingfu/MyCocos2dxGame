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
    typedef enum{
        BT_NORMAL = 1<<0,
        BT_ACCEL = 1<<1,
        BT_BOOM = 1<<2,
        BT_MULTI = 1<<3,
        BT_PROTECTED = 1<<4,
        BT_TIME = 1<<5
    } BufferType;
protected:
    Player();
    virtual ~Player();
    void updateBuffer(float delta);
public:
    CREATE_FUNC(Player);
    void update(float delta);
    void loadMaskModel(const std::string& texName);
    void addBuffer(BufferType type);
    void removeBuffer(BufferType type);
    
    void respawn();
    void beginShadow();
    void endShadow();
    
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
    virtual void onExitDead() override;
private:
    bool                            m_bScheduledFire;
    cocos2d::Sprite*                m_pMaskModel;
    WeaponType                      m_WeaponType;
    cocos2d::ParticleSystemQuad*    m_pLeftTail;
    cocos2d::ParticleSystemQuad*    m_pRightTail;
    cocos2d::Node*                  m_pShadowNode;
    int                             m_nBufferType;
    float                           m_fProtectedTime;
    float                           m_fSlowTime;
    float                           m_fFireDelta;
};

#endif /* defined(__Geometry_Wars__Player__) */
