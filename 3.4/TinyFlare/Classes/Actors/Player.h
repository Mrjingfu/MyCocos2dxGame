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
#include "ChaosNumber.h"
class Player : public GameActor, public JoystickLeftListener, public JoystickRightListener
{
public:
    typedef enum{
        WT_NORMAL = 0
    } WeaponType;
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
    
    void beginShadow();
    void endShadow();
    void beginMulti();
    void endMulti();
    void removeMulti();
    void beginProtected();
    void endProtected();
    void removeProtected();
    
    void onJoystickUpdateDirection(TwoJoysticks* joystick, const cocos2d::Vec2& dir);
    void onJoystickUpdateOrientation(TwoJoysticks* joystick, const cocos2d::Vec2& dir);
    void onJoystickPressed(TwoJoysticks* joystick, float pressedTime);
    void onJoystickReleased(TwoJoysticks* joystick, float pressedTime);
    
    cocos2d::Vec2 getFireWorldPos(const cocos2d::Vec2& orient);
    cocos2d::Vec2 getFireLocalPos(const cocos2d::Vec2& orient);
    cocos2d::Vec2 getLeftTailLocalPos();
    cocos2d::Vec2 getRightTailLocalPos();
    void fire(float delta);
    
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual void onEnterDead() override;
    virtual void onExitDead() override;
private:
    bool                            m_bScheduledFire;
    cocos2d::Sprite*                m_pMaskModel;
    WeaponType                      m_WeaponType;
    cocos2d::ParticleSystemQuad*    m_pLeftTail;
    cocos2d::ParticleSystemQuad*    m_pRightTail;
    cocos2d::Node*                  m_pShadowNode;
    cocos2d::Sprite*                m_pMultiNode;
    cocos2d::Sprite*                m_pProtectedNode;
    float                           m_fProtectedTime;
    float                           m_fMultiTime;
    float                           m_fSlowTime;
    float                           m_fFireDelta;
    CChaosNumber                    m_nBoomBulletNum;
};

#endif /* defined(__Geometry_Wars__Player__) */
