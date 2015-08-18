//
//  MenuScene.cpp
//  MazeJump
//
//  Created by wang haibo on 15/6/23.
//
//

#include "MenuScene.h"
#include "MainUI.h"
#include "MainScene.h"
#include "GameConst.h"
#include "UIManager.h"
#include "RoleManager.h"
#include "storage/local-storage/LocalStorage.h"
#include "AudioEngine.h"
#include "NativeBridge.h"
USING_NS_CC;
using namespace experimental;


Scene* MenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MenuScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
MenuScene::MenuScene()
{
    m_pMainCamera           = nullptr;
    m_pSea                  = nullptr;
    m_pSea1                 = nullptr;
    m_pSea2                 = nullptr;
    m_pSea3                 = nullptr;
    m_pStandPlatform        = nullptr;
    m_pRunner               = nullptr;
    m_pRainbow              = nullptr;
    m_pWhiteLayer           = nullptr;
    m_bStartGame            = false;
    m_fTime = 0;
}
// on "init" you need to initialize your instance
bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    this->setAnchorPoint(Vec2::ZERO);
    
    m_pWhiteLayer = LayerColor::create(Color4B::WHITE);
    if(!m_pWhiteLayer)
        return false;
    this->addChild(m_pWhiteLayer,LAYER_WHITE);
    EaseExponentialOut* fadeOut = EaseExponentialOut::create(FadeOut::create(1.0f));
    m_pWhiteLayer->runAction(fadeOut);

    
    Skybox* skyBox = Skybox::create("sky5.png", "sky5.png", "sky5.png", "sky5.png", "sky5.png", "sky5.png");
    if(!skyBox)
        return false;
    skyBox->setScale(1000);
    skyBox->setCameraMask((unsigned short)CameraFlag::USER1);
    skyBox->setGlobalZOrder(-1);
    addChild(skyBox);
    
    m_pSea = EffectSprite3D::create("sea.c3b");
    if(!m_pSea)
        return false;
    
    m_pSea1 = EffectSprite3D::create("sea1.c3b");
    if(!m_pSea1)
        return false;
    m_pSea1->setPositionX(-123);
    m_pSea1->setPositionY(-29);
    m_pSea->addChild(m_pSea1);
    
    m_pSea2 = EffectSprite3D::create("sea2.c3b");
    if(!m_pSea2)
        return false;
    m_pSea2->setPositionX(-123);
    m_pSea2->setPositionY(-35.5);
    m_pSea2->setPositionZ(-123);
    m_pSea->addChild(m_pSea2);
    
    m_pSea3 = EffectSprite3D::create("sea3.c3b");
    if(!m_pSea3)
        return false;
    m_pSea3->setPositionY(-31.5);
    m_pSea3->setPositionZ(-123);
    m_pSea->addChild(m_pSea3);
    
    m_pSea->setCameraMask((unsigned short)CameraFlag::USER1);
    m_pSea->setPositionX(-580);
    m_pSea->setPositionZ(-390);
    m_pSea->setRotation3D(Vec3(0,10,0));
    m_pSea->setScale(8);
    addChild(m_pSea);
    
//    EaseSineInOut* moveTo1 = EaseSineInOut::create(MoveTo::create(10.0f, Vec3(-565, -15, -390)));
//    EaseSineInOut* moveTo2= EaseSineInOut::create(MoveTo::create(10.0f, Vec3(-580, 0, -375)));
//    Sequence* sequence1 = Sequence::create(moveTo1, moveTo2, NULL);
//    RepeatForever* repeat1 = RepeatForever::create(sequence1);
//    m_pSea->runAction(repeat1);

    
    m_pStandPlatform = EffectSprite3D::create("platform_stand.c3b");
    if(!m_pStandPlatform)
        return false;
    m_pStandPlatform->setCameraMask((unsigned short)CameraFlag::USER1);
    m_pStandPlatform->setPositionX(180);
    m_pStandPlatform->setPositionY(30);
    m_pStandPlatform->setPositionZ(95);
    addChild(m_pStandPlatform);
    EaseSineInOut* moveTo3 = EaseSineInOut::create(MoveTo::create(10.0f, Vec3(181, 29, 95)));
    EaseSineInOut* moveTo4= EaseSineInOut::create(MoveTo::create(10.0f, Vec3(180, 30, 95.6)));
    Sequence* sequence2 = Sequence::create(moveTo3, moveTo4, NULL);
    RepeatForever* repeat2 = RepeatForever::create(sequence2);
    m_pStandPlatform->runAction(repeat2);
    
    m_pRunner = Runner::create();
    if(!m_pRunner)
        return false;
    m_pRunner->setCameraMask((unsigned short)CameraFlag::USER1);
    m_pRunner->setOpacity(255);
    m_pRunner->setRotation3D(Vec3(0,-90,0));
    m_pRunner->setPositionX(1);
    m_pRunner->setPositionY(4.6);
    m_pRunner->setPositionZ(2);
    m_pRunner->setScale(0.1875f);
    m_pStandPlatform->addChild(m_pRunner);
    
    
    auto size = Director::getInstance()->getVisibleSize();
    m_pMainCamera = Camera::createPerspective(60, size.width/size.height, 1, 5000);
    if(!m_pMainCamera)
        return false;
    Vec3 camPos = Vec3(200,0,80) + Vec3(0,50.0f*cosf(M_PI/6.0f),50.0f*sinf(M_PI/6.0f));
    Vec3 lookAt = getPosition3D() + Vec3(-50,0,-50);
    m_pMainCamera->setPosition3D(camPos);
    m_pMainCamera->lookAt(lookAt);
    addChild(m_pMainCamera);
    m_pMainCamera->setCameraFlag(CameraFlag::USER1);
    
    AmbientLight* ambLight = AmbientLight::create(Color3B(150, 150, 150));
    m_pSea->addChild(ambLight);
    DirectionLight* directionLight = DirectionLight::create(Vec3(-3, -4, -2), Color3B(158, 158, 158));
    m_pSea->addChild(directionLight);
    
    m_pRainbow = RibbonTrail::create("ribbontrail.png", 70, 2000);
    if(!m_pRainbow)
        return false;
    m_pRainbow->setPosition3D(Vec3(-1100, -35, -800));
    m_pRainbow->setCameraMask((unsigned short)CameraFlag::USER1);
    this->addChild(m_pRainbow);
    m_pRainbow->getTrail()->addNode(m_pRainbow);
    
    Vec3 pos = m_pRainbow->getPosition3D();
    Vec3 target = m_pMainCamera->getPosition3D() + Vec3(0, -25, 0);
    m_dirDist = target - pos;
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto touchListener = EventListenerTouchOneByOne::create();
    if(touchListener == nullptr)
        return false;
    touchListener->onTouchBegan = CC_CALLBACK_2(MenuScene::onTouchBegan, this);
    dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    

    
    return true;
}

void MenuScene::onEnter()
{
    Layer::onEnter();
    scheduleUpdate();
    RoleManager::getInstance()->init();
    
    UIManager::getInstance()->init(this);
    UIManager::getInstance()->setGameUi(UIManager::UI_MAIN);
    AudioEngine::play2d("rainbow.wav", false, 0.5f);
    
    NativeBridge::getInstance()->showRateAppView();
}
void MenuScene::onExit()
{
    unscheduleUpdate();
    UIManager::getInstance()->destory();
    Layer::onExit();
}
void MenuScene::update(float delta)
{
    if(m_pRainbow && m_pMainCamera)
    {
        m_fTime += delta;
        if(m_fTime <=2.0f)
        {
            Vec3 pos = m_pRainbow->getPosition3D();
            Vec3 target = m_pMainCamera->getPosition3D() + Vec3(0, -25, 0);
            pos = pos + m_dirDist*delta*0.5f - Vec3(0, cosf(M_PI*(m_fTime-0.5f))*150*delta, 0);
            m_pRainbow->setPosition3D(pos);
            m_pRainbow->update(delta);
        }
    }
}

bool MenuScene::onTouchBegan(Touch *touch, Event *event)
{
    if(!touch)
        return false;
    if(!m_bStartGame)
    {
        runnerJump();
        m_bStartGame = true;
    }
    return true;
}
void MenuScene::switchToMainScene()
{
    auto scene = MainScene::createScene();
    Director::getInstance()->replaceScene(scene);
}

void MenuScene::fadeOutScene()
{
    if(m_pWhiteLayer)
    {
        EaseExponentialOut* fadeIn = EaseExponentialOut::create(FadeIn::create(1.0f));
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(MenuScene::switchToMainScene, this));
        Sequence* sequence = Sequence::create( fadeIn, callFunc, NULL);
        m_pWhiteLayer->runAction(sequence);
    }
}

void MenuScene::startGame()
{
    int maxLevel = Value(localStorageGetItem(USER_MAX_LEVEL)).asInt();
    if (maxLevel > 0) {
        UIManager::getInstance()->addPopUp(BasePopUpUI::POPUP_START);
        UIManager::getInstance()->showPopUp();
        m_bStartGame=false;
    }else
    {
        fadeOutScene();
    }

}
void MenuScene::runnerJump()
{
    if(m_pRunner)
    {
        EaseSineOut* scaleTo1 = EaseSineOut::create(ScaleTo::create(0.05f, 0.1125, 0.3f, 0.1875));
        EaseSineIn* scaleTo2 = EaseSineIn::create(ScaleTo::create(0.015f, 0.1875, 0.1875,0.1875));
        Sequence* sequenceScale = Sequence::create(scaleTo1, scaleTo2, NULL);
        
        DelayTime* delay = DelayTime::create(0.05f);
        RotateTo* ratateTo = RotateTo::create(0.15f, Vec3(0,0,0));
        Sequence* sequenceRotate = Sequence::create(delay, ratateTo, NULL);
        EaseSineOut* rotateBy = nullptr;
        rotateBy = EaseSineOut::create(RotateBy::create(0.5f, Vec3(-360,0,0)));
        Spawn* spawnRotateBy = Spawn::create(sequenceRotate, rotateBy, NULL);
        
        EaseSineOut* moveUp = EaseSineOut::create(MoveTo::create(0.25f, Vec3(m_pRunner->getPositionX(), m_pRunner->getPositionY() + m_pRunner->getRadius()*4*m_pRunner->getScale(), m_pRunner->getPositionZ())));
        EaseSineIn* moveDown = EaseSineIn::create(MoveTo::create(0.25f, Vec3(m_pRunner->getPositionX(), m_pRunner->getPositionY(), m_pRunner->getPositionZ())));
        Sequence* sequenceJump = Sequence::create(delay, moveUp, moveDown, NULL);
        Spawn* spawn = Spawn::create(sequenceScale, spawnRotateBy, sequenceJump, NULL);
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(MenuScene::startGame,this));
        Sequence* sequence = Sequence::create(spawn, callFunc, NULL);
        m_pRunner->runAction(sequence);
        
        AudioEngine::play2d("superjump.wav", false, 0.3f);
    }
}