//
//  Logo.cpp
//  TinyFlare
//
//  Created by wang haibo on 15/4/14.
//
//

#include "Logo.h"
#include "ShatterAction.h"
#include "TinyFlare.h"
USING_NS_CC;

Scene* Logo::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Logo::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
Logo::Logo()
{
}
// on "init" you need to initialize your instance
bool Logo::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    auto size = Director::getInstance()->getVisibleSize();
    
    m_pLogo = ShatterSprite::create("logo.png");
    if(!m_pLogo)
        return false;
    float scale = size.height / 640.0f;
    m_pLogo->setPosition(size.width*0.5f, size.height*0.5f);
    m_pLogo->setCascadeColorEnabled(true);
    m_pLogo->setOpacity(0);
    m_pLogo->setScale(scale);
    addChild(m_pLogo);
    
    EaseSineOut* easeOut = EaseSineOut::create(FadeIn::create(1.5f));
    DelayTime* delay = DelayTime::create(1.0f);
    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(Logo::beginShatter, this));
    
    Sequence* sequence = Sequence::create( easeOut, delay, callFunc, NULL);
    m_pLogo->runAction(sequence);
    
    ParticleSystemQuad* explosion= ParticleSystemQuad::create("flare.plist");
    if(explosion)
    {
        explosion->setPosition(170, 215);
        explosion->setScale(0.3f);
        explosion->setDuration(0.5f);
        m_pLogo->addChild(explosion);
    }
    
    return true;
}
void Logo::beginShatter()
{
    m_pLogo->setOpacity(0);
    m_pLogo->stopAllActions();
    ShatterAction* shatterAction = ShatterAction::create(0.5f);
    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(Logo::endShatter, this));
    DelayTime* delay = DelayTime::create(0.3f);
    Sequence* sequence = Sequence::create(shatterAction, delay, callFunc, NULL);
    m_pLogo->runAction(sequence);
}
void Logo::endShatter()
{
    auto scene = TinyFlare::createScene();
    Director::getInstance()->replaceScene(scene);
}