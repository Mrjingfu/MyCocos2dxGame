//
//  EffectSprite3D.h
//  Geometry-Wars
//
//  Created by wang haibo on 15/2/5.
//
//

#ifndef __Geometry_Wars__EffectSprite3D__
#define __Geometry_Wars__EffectSprite3D__

#include "cocos2d.h"
#include "BaseEffect3D.h"
class EffectSprite3D : public cocos2d::Sprite3D
{
public:
    static EffectSprite3D* create(const std::string& modelPath);
    static EffectSprite3D* create(const std::string& modelPath, const std::string& textureFilePath);
    void setEffect(BaseEffect3D* effect);
    void addEffect(BaseEffect3D* effect, ssize_t order);
    void eraseEffect(BaseEffect3D* effect);
    ssize_t getEffectCount() const;
    BaseEffect3D* getEffect(ssize_t index) const;
    void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
protected:
    EffectSprite3D();
    virtual ~EffectSprite3D();
    
    std::vector<std::tuple<ssize_t,BaseEffect3D*, cocos2d::CustomCommand>> m_effects;
    BaseEffect3D*     m_pDefaultEffect;
    cocos2d::CustomCommand _command;
};


#endif /* defined(__Geometry_Wars__EffectSprite3D__) */
