//
//  Bullet.h
//  Geometry-Wars
//
//  Created by wang haibo on 15/3/5.
//
//

#ifndef __Geometry_Wars__Bullet__
#define __Geometry_Wars__Bullet__

#include "GameActor.h"
class Bullet : public GameActor
{
    friend class ActorsManager;
public:
    typedef enum{
        BT_SIMPLE = 0
    } BulletType;
protected:
    Bullet();
    virtual ~Bullet();
    virtual void update(float delta) override;
    
public:
    void loadTexture(const std::string& textureName);
    void setColorMask(const cocos2d::Color3B& mask);
    void setBlendFunc(const cocos2d::BlendFunc& blendFunc);
};

#endif /* defined(__Geometry_Wars__Bullet__) */
