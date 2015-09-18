//
//  LogoScene.cpp
//  Tone_Skipper
//
//  Created by wang haibo on 15/9/17.
//
//

#include "LogoScene.h"
#include "GameScene.h"
USING_NS_CC;

Scene* LogoScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LogoScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
LogoScene::LogoScene()
{
    m_NodeRoot1      = nullptr;
    m_pT0            = nullptr;
    m_pI0            = nullptr;
    m_pN0            = nullptr;
    m_pY0            = nullptr;
    m_pF0            = nullptr;
    m_pL0            = nullptr;
    m_pA0            = nullptr;
    m_pR0            = nullptr;
    m_pE0            = nullptr;
    
    m_NodeRoot2      = nullptr;
    m_pT1            = nullptr;
    m_pI1            = nullptr;
    m_pN1            = nullptr;
    m_pY1            = nullptr;
    m_pF1            = nullptr;
    m_pL1            = nullptr;
    m_pA1            = nullptr;
    m_pR1            = nullptr;
    m_pE1            = nullptr;
}
// on "init" you need to initialize your instance
bool LogoScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    auto size = Director::getInstance()->getVisibleSize();
    
    m_NodeRoot1 = Node::create();
    if(!m_NodeRoot1)
        return false;
    m_NodeRoot1->setPosition(Vec2(size.width*0.5f, size.height*0.5f));
    m_NodeRoot1->setCascadeOpacityEnabled(true);
    addChild(m_NodeRoot1,1);
    
    DelayTime* delay1 = DelayTime::create(0.3f);
    DelayTime* delay2 = DelayTime::create(0.05f);
    EaseSineIn* rotateTo = EaseSineIn::create(RotateTo::create(0.05f, Vec3(0, 0, 0)));
    FadeIn* fadeIn = FadeIn::create(0.025);
    EaseSineOut* fadeOut = EaseSineOut::create(FadeOut::create(1.0f));
    Spawn* spawn = Spawn::create(fadeIn, rotateTo, NULL);
    
    m_pT0 = Sprite::create("t_0.png");
    if(!m_pT0)
        return false;
    m_pT0->getTexture()->setAliasTexParameters();
    m_pT0->setPositionX(-m_pT0->getContentSize().width*5);
    m_pT0->setRotation3D(Vec3(0, 100.5, 0));
    m_pT0->setOpacity(0);
    m_NodeRoot1->addChild(m_pT0);
    
    m_pI0 = Sprite::create("i_0.png");
    if(!m_pI0)
        return false;
    m_pI0->getTexture()->setAliasTexParameters();
    m_pI0->setPositionX(-m_pI0->getContentSize().width*4.25f);
    m_pI0->setRotation3D(Vec3(0, 100, 0));
    m_pI0->setOpacity(0);
    m_NodeRoot1->addChild(m_pI0);
    
    m_pN0 = Sprite::create("n_0.png");
    if(!m_pN0)
        return false;
    m_pN0->getTexture()->setAliasTexParameters();
    m_pN0->setPositionX(-m_pN0->getContentSize().width*3.5f);
    m_pN0->setRotation3D(Vec3(0, 99, 0));
    m_pN0->setOpacity(0);
    m_NodeRoot1->addChild(m_pN0);
    
    m_pY0 = Sprite::create("y_0.png");
    if(!m_pY0)
        return false;
    m_pY0->getTexture()->setAliasTexParameters();
    m_pY0->setPositionX(-m_pY0->getContentSize().width*2.4f);
    m_pY0->setRotation3D(Vec3(0, 96, 0));
    m_pY0->setOpacity(0);
    m_NodeRoot1->addChild(m_pY0);
    
    m_pF0 = Sprite::create("f_0.png");
    if(!m_pF0)
        return false;
    m_pF0->getTexture()->setAliasTexParameters();
    m_pF0->setPositionX(-m_pF0->getContentSize().width*0.5f);
    m_pF0->setRotation3D(Vec3(0, 93, 0));
    m_pF0->setOpacity(0);
    m_NodeRoot1->addChild(m_pF0);
    
    m_pL0 = Sprite::create("l_0.png");
    if(!m_pL0)
        return false;
    m_pL0->getTexture()->setAliasTexParameters();
    m_pL0->setPositionX(m_pL0->getContentSize().width*0.35f);
    m_pL0->setRotation3D(Vec3(0, 90, 0));
    m_pL0->setOpacity(0);
    m_NodeRoot1->addChild(m_pL0);
    
    m_pA0 = Sprite::create("a_0.png");
    if(!m_pA0)
        return false;
    m_pA0->getTexture()->setAliasTexParameters();
    m_pA0->setPositionX(m_pA0->getContentSize().width*1.3f);
    m_pA0->setRotation3D(Vec3(0, 87, 0));
    m_pA0->setOpacity(0);
    m_NodeRoot1->addChild(m_pA0);
    
    m_pR0 = Sprite::create("r_0.png");
    if(!m_pR0)
        return false;
    m_pR0->getTexture()->setAliasTexParameters();
    m_pR0->setPositionX(m_pR0->getContentSize().width*2.3f);
    m_pR0->setRotation3D(Vec3(0, 84, 0));
    m_pR0->setOpacity(0);
    m_NodeRoot1->addChild(m_pR0);
    
    m_pE0 = Sprite::create("e_0.png");
    if(!m_pE0)
        return false;
    m_pE0->getTexture()->setAliasTexParameters();
    m_pE0->setPositionX(m_pE0->getContentSize().width*3.3f);
    m_pE0->setRotation3D(Vec3(0, 81, 0));
    m_pE0->setOpacity(0);
    m_NodeRoot1->addChild(m_pE0);
    
    Sequence* sequence1 = Sequence::create(delay1, spawn, NULL);
    m_pT0->runAction(sequence1);
    Sequence* sequence2 = Sequence::create(delay1, delay2, spawn, NULL);
    m_pI0->runAction(sequence2);
    Sequence* sequence3 = Sequence::create(delay1, delay2, delay2, spawn, NULL);
    m_pN0->runAction(sequence3);
    Sequence* sequence4 = Sequence::create(delay1, delay2, delay2,delay2, spawn, NULL);
    m_pY0->runAction(sequence4);
    Sequence* sequence5 = Sequence::create(delay1, delay2, delay2, delay2, delay1, spawn, NULL);
    m_pF0->runAction(sequence5);
    Sequence* sequence6 = Sequence::create(delay1, delay2, delay2, delay2, delay1, delay2, spawn, NULL);
    m_pL0->runAction(sequence6);
    Sequence* sequence7 = Sequence::create(delay1, delay2, delay2, delay2, delay1, delay2, delay2,spawn, NULL);
    m_pA0->runAction(sequence7);
    Sequence* sequence8 = Sequence::create(delay1, delay2, delay2, delay2, delay1, delay2, delay2,delay2, spawn, NULL);
    m_pR0->runAction(sequence8);
    Sequence* sequence9 = Sequence::create(delay1, delay2, delay2, delay2, delay1, delay2, delay2,delay2, delay2, spawn, NULL);
    m_pE0->runAction(sequence9);
    
    CallFunc* callback = CallFunc::create(CC_CALLBACK_0(LogoScene::createColorLogo, this));
    CallFunc* callback1 = CallFunc::create(CC_CALLBACK_0(LogoScene::precache, this));
    Sequence* sequence10 = Sequence::create(delay1, delay2, delay2, delay2, delay1, delay2, delay2,delay2, delay2, callback, delay1, fadeOut, callback1, NULL);
    m_NodeRoot1->runAction(sequence10);
    
    return true;
}
void LogoScene::onEnter()
{
    Layer::onEnter();
    scheduleUpdate();
}
void LogoScene::onExit()
{
    unscheduleUpdate();
    Layer::onExit();
}
void LogoScene::update(float delta)
{
    if(m_pT1)
        m_pT1->setHue(m_pT1->getHue() + M_PI*delta);
    if(m_pI1)
        m_pI1->setHue(m_pI1->getHue() + M_PI*delta);
    if(m_pN1)
        m_pN1->setHue(m_pN1->getHue() + M_PI*delta);
    if(m_pY1)
        m_pY1->setHue(m_pY1->getHue() + M_PI*delta);
    
    if(m_pF1)
        m_pF1->setHue(m_pF1->getHue() + M_PI*delta);
    if(m_pL1)
        m_pL1->setHue(m_pL1->getHue() + M_PI*delta);
    if(m_pA1)
        m_pA1->setHue(m_pA1->getHue() + M_PI*delta);
    if(m_pR1)
        m_pR1->setHue(m_pR1->getHue() + M_PI*delta);
    if(m_pE1)
        m_pE1->setHue(m_pE1->getHue() + M_PI*delta);
}
void LogoScene::precache()
{
    if(m_NodeRoot2)
    {
        DelayTime* delay = DelayTime::create(1.0f);
        EaseSineOut* fadeOut = EaseSineOut::create(FadeOut::create(1.0f));
        CallFunc* callback = CallFunc::create(CC_CALLBACK_0(LogoScene::endcache, this));
        Sequence* sequence = Sequence::create(delay, fadeOut, callback, NULL);
        m_NodeRoot2->runAction(sequence);
    }
}
void LogoScene::endcache()
{
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(scene);
}
void LogoScene::createColorLogo()
{
    auto size = Director::getInstance()->getVisibleSize();
    m_NodeRoot2 = Node::create();
    if(!m_NodeRoot2)
        return;
    m_NodeRoot2->setPosition(Vec2(size.width*0.5f, size.height*0.5f));
    m_NodeRoot2->setCascadeOpacityEnabled(true);
    addChild(m_NodeRoot2);
    
    m_pT1 = HueSprite::create("t_1.png");
    if(!m_pT1)
        return;
    m_pT1->setPositionX(-m_pT1->getContentSize().width*5);
    m_NodeRoot2->addChild(m_pT1);
    
    m_pI1 = HueSprite::create("i_1.png");
    if(!m_pI1)
        return;
    m_pI1->setPositionX(-m_pI1->getContentSize().width*4.25f);
    m_NodeRoot2->addChild(m_pI1);
    
    m_pN1 = HueSprite::create("n_1.png");
    if(!m_pN1)
        return;
    m_pN1->setPositionX(-m_pN1->getContentSize().width*3.5f);
    m_NodeRoot2->addChild(m_pN1);
    
    m_pY1 = HueSprite::create("y_1.png");
    if(!m_pY1)
        return;
    m_pY1->setPositionX(-m_pY1->getContentSize().width*2.4f);
    m_NodeRoot2->addChild(m_pY1);
    
    m_pF1 = HueSprite::create("f_1.png");
    if(!m_pF1)
        return;
    m_pF1->setPositionX(-m_pF1->getContentSize().width*0.5f);
    m_NodeRoot2->addChild(m_pF1);
    
    m_pL1 = HueSprite::create("l_1.png");
    if(!m_pL1)
        return;
    m_pL1->setPositionX(m_pL1->getContentSize().width*0.35f);
    m_NodeRoot2->addChild(m_pL1);
    
    m_pA1 = HueSprite::create("a_1.png");
    if(!m_pA1)
        return;
    m_pA1->setPositionX(m_pA1->getContentSize().width*1.3f);
    m_NodeRoot2->addChild(m_pA1);
    
    m_pR1 = HueSprite::create("r_1.png");
    if(!m_pR1)
        return;
    m_pR1->setPositionX(m_pR1->getContentSize().width*2.3f);
    m_NodeRoot2->addChild(m_pR1);
    
    m_pE1 = HueSprite::create("e_1.png");
    if(!m_pE1)
        return;
    m_pE1->setPositionX(m_pE1->getContentSize().width*3.3f);
    m_NodeRoot2->addChild(m_pE1);
}