//
//  EffectSprite3D.cpp
//  Geometry-Wars
//
//  Created by wang haibo on 15/2/5.
//
//

#include "EffectSprite3D.h"
USING_NS_CC;

EffectSprite3D* EffectSprite3D::create(const std::string& modelPath)
{
    if (modelPath.length() < 4)
        CCASSERT(false, "improper name specified when creating Sprite3D");
    
    auto sprite = new EffectSprite3D();
    if (sprite && sprite->initWithFile(modelPath))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

EffectSprite3D* EffectSprite3D::create(const std::string& modelPath, const std::string& textureFilePath)
{
    auto sprite = new EffectSprite3D();
    if (sprite && sprite->initWithFile(modelPath))
    {
        sprite->autorelease();
        if(textureFilePath.size() > 0)
            sprite->setTexture(textureFilePath);
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

EffectSprite3D::EffectSprite3D()
:m_pDefaultEffect(nullptr)
{
}

EffectSprite3D::~EffectSprite3D()
{
    for(auto effect : m_effects)
    {
        CC_SAFE_RELEASE_NULL(std::get<1>(effect));
    }
    CC_SAFE_RELEASE(m_pDefaultEffect);
}
void EffectSprite3D::setEffect(BaseEffect3D* effect)
{
    if(m_pDefaultEffect != effect) {
        CC_SAFE_RETAIN(effect);
        CC_SAFE_RELEASE(m_pDefaultEffect);
        m_pDefaultEffect = effect;
        CC_SAFE_RETAIN(m_pDefaultEffect);
        setGLProgramState(m_pDefaultEffect->getGLProgramState());
    }
}
static int tuple_sort( const std::tuple<ssize_t,BaseEffect3D*,CustomCommand> &tuple1, const std::tuple<ssize_t,BaseEffect3D*,CustomCommand> &tuple2 )
{
    return std::get<0>(tuple1) < std::get<0>(tuple2);
}

void EffectSprite3D::addEffect(BaseEffect3D* effect, ssize_t order)
{
    if(nullptr == effect) return;
    effect->retain();
    
    m_effects.push_back(std::make_tuple(order,effect,CustomCommand()));
    
    std::sort(std::begin(m_effects), std::end(m_effects), tuple_sort);
}

void EffectSprite3D::eraseEffect(BaseEffect3D* effect)
{
    auto iter = m_effects.begin();
    for (; iter != m_effects.end(); ++iter)
    {
        if(std::get<1>(*iter) != effect) continue;
        else
        {
            CC_SAFE_RELEASE_NULL(std::get<1>(*iter));
            m_effects.erase(iter);
            break;
        }
        
    }
    if(iter == m_effects.end())
        CCLOGWARN("Cannot find the effect in EffectSprite3D");
}
ssize_t EffectSprite3D::getEffectCount() const
{
    return m_effects.size();
}

BaseEffect3D* EffectSprite3D::getEffect(ssize_t index) const
{
    if(index >= getEffectCount()) return nullptr;
    return std::get<1>(*(std::begin(m_effects) + index));
}
void EffectSprite3D::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
    for(auto &effect : m_effects)
    {
        if(std::get<0>(effect) >=0)
            break;
        CustomCommand &cc = std::get<2>(effect);
        cc.func = CC_CALLBACK_0(BaseEffect3D::drawWithSprite3D,std::get<1>(effect),this,transform);
        renderer->addCommand(&cc);
        
    }
    if(!m_pDefaultEffect)
    {
        Sprite3D::draw(renderer, transform, flags);
    }
    else
    {
        _command.init(_globalZOrder);
        _command.func = CC_CALLBACK_0(BaseEffect3D::drawWithSprite3D, m_pDefaultEffect, this, transform);
        renderer->addCommand(&_command);
        if(m_pDefaultEffect->isUseSpriteSelfDraw())
            Sprite3D::draw(renderer, transform, flags);
    }
    
    for(auto &effect : m_effects)
    {
        if(std::get<0>(effect) <=0)
            continue;
        CustomCommand &cc = std::get<2>(effect);
        cc.func = CC_CALLBACK_0(BaseEffect3D::drawWithSprite3D,std::get<1>(effect),this,transform);
        renderer->addCommand(&cc);
        
    }
}
