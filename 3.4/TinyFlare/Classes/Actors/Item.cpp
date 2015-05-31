//
//  Item.cpp
//  TinyFlare
//
//  Created by wang haibo on 15/4/7.
//
//

#include "Item.h"
#include "ActorsManager.h"
USING_NS_CC;

Item::Item()
{
    m_pModel = nullptr;
    m_pBoundModel = nullptr;
    m_ItemType = IT_UNKNOWN;
    m_fLifeTime = 10.0f;
    m_bHasBeginFadeOut = false;
}
Item::~Item()
{
}
void Item::update(float delta)
{
    m_fLifeTime -= delta;
    if(m_fLifeTime < 5.0f)
    {
        if(!m_bHasBeginFadeOut)
        {
            FadeOut* fadeOut = FadeOut::create(0.5f);
            FadeIn* fadeIn = FadeIn::create(0.5f);
            EaseSineOut* easeOut1 = EaseSineOut::create(fadeOut);
            EaseSineOut* easeOut2 = EaseSineOut::create(fadeIn);
            Sequence* sequence = Sequence::create(easeOut1, easeOut2, NULL);
            RepeatForever* repeatForever = RepeatForever::create(sequence);
            runAction(repeatForever);
            m_bHasBeginFadeOut = true;
        }
        if(m_fLifeTime <= 0.0f)
        {
            setActorState(ActorState::AS_DEAD);
            m_fLifeTime = 0.0f;
            ActorsManager::getInstance()->eraseItem(this);
        }
    }
}
void Item::loadTexture(const std::string& textureName)
{
    m_pModel = Sprite::createWithSpriteFrameName(textureName);
    if(!m_pModel)
        CCLOGERROR("Load Item texture %s failed!", textureName.c_str());
    m_pModel->setScale(0.2f);
    addChild(m_pModel);
    
    RotateBy* rotateBy = RotateBy::create(0.5f, Vec3(0, 180, 0));
    DelayTime* delayTime = DelayTime::create(1.0f);
    RotateBy* rotateBy2 = RotateBy::create(0.5f, Vec3(0, -180, 0));
    Sequence* sequence = Sequence::create(rotateBy, delayTime, rotateBy2, NULL);
    RepeatForever* repeatForever = RepeatForever::create(sequence);
    m_pModel->runAction(repeatForever);
    
    m_pBoundModel = Sprite::createWithSpriteFrameName("bound.png");
    if(m_pBoundModel == nullptr)
        CCLOGERROR("Load bound model bound.png failed!");
    m_pBoundModel->setScale(0.2f);
    addChild(m_pBoundModel);
    caculateRadius();
}