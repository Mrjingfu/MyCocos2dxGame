//
//  RunController.cpp
//  MazeJump
//
//  Created by wang haibo on 15/7/22.
//
//

#include "RunController.h"
#include "ui/CocosGUI.h"
#include "MainScene.h"
#include "GameConst.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "UIManager.h"
#include "storage/local-storage/LocalStorage.h"
#include "Particle3D/CCParticleSystem3D.h"
#include "Particle3D/PU/CCPUParticleSystem3D.h"
#include "UtilityHelper.h"
#include "AudioEngine.h"
USING_NS_CC;
using namespace experimental;

RunController* g_pRunControllerInstance = nullptr;
RunController* RunController::getInstance()
{
    if( g_pRunControllerInstance == nullptr )
        g_pRunControllerInstance = new RunController();
    
    return g_pRunControllerInstance;
}
RunController::RunController()
{
    m_pMainLayer        = nullptr;
    m_pTerrainLayer     = nullptr;
    m_pMainCamera       = nullptr;
    m_pMainPlayer       = nullptr;
    m_pCloud1           = nullptr;
    m_pCloud2           = nullptr;
    m_pCloud3           = nullptr;
    m_nDifficultLevel   = 0;
    m_nInitDifficultLevel = 0;
    m_nMaxReachDifficultLevel = 0;
    m_pWhiteLayer   = nullptr;
    m_bInMazeJump   = false;
    m_pRainbow      = nullptr;
    m_pTerrainAmbLight = nullptr;
    m_pTerrainDirectionLight   = nullptr;
    m_GameState = RGS_FROZEN;
    m_bHasShowRainbow = false;
}
RunController::~RunController()
{
}
bool RunController::init(Layer* pMainLayer)
{
    if(pMainLayer == nullptr)
        return false;
    m_pMainLayer = pMainLayer;
    m_nInitDifficultLevel = getDifficultLevel();
//    m_randomColor0 = UtilityHelper::randomColor();
//    m_randomColor1 = UtilityHelper::randomColor();
//    m_randomColor2 = UtilityHelper::randomColor();
//    m_randomColor3 = UtilityHelper::randomColor();
//    m_randomColor4 = UtilityHelper::randomColor();
//    m_randomColor5 = UtilityHelper::randomColor();
//    m_randomColor6 = UtilityHelper::randomColor();
    
    m_randomColor0 = UtilityHelper::randomRedColor();
    m_randomColor1 = UtilityHelper::randomOrangeColor();
    m_randomColor2 = UtilityHelper::randomYellowColor();
    m_randomColor3 = UtilityHelper::randomGreenColor();
    m_randomColor4 = UtilityHelper::randomCyanColor();
    m_randomColor5 = UtilityHelper::randomBlueColor();
    m_randomColor6 = UtilityHelper::randompurpleColor();
    m_sameColor = UtilityHelper::randomColor();
    

    
    m_pWhiteLayer = LayerColor::create(Color4B::WHITE);
    if(!m_pWhiteLayer)
        return false;
    m_pMainLayer->addChild(m_pWhiteLayer);
    EaseExponentialOut* fadeOut = EaseExponentialOut::create(FadeOut::create(1.0f));
    m_pWhiteLayer->runAction(fadeOut);
    
    Skybox* m_pSkyBox = Skybox::create("sky4.png", "sky4.png", "sky4.png", "sky4.png", "sky4.png", "sky4.png");
    if(!m_pSkyBox)
        return false;
    m_pSkyBox->setScale(1000);
    m_pSkyBox->setCameraMask((unsigned short)CameraFlag::USER1);
    m_pSkyBox->setGlobalZOrder(-1);
    m_pMainLayer->addChild(m_pSkyBox);
    
    if(!initCloud())
        return false;
    
    m_pTerrainLayer = TerrainLayer::create();
    if(!m_pTerrainLayer)
        return false;
    m_pTerrainLayer->setCameraMask((unsigned short)CameraFlag::USER1);
    ///focus
    m_pTerrainLayer->setAnchorPoint(Vec2::ZERO);
    m_pMainLayer->addChild(m_pTerrainLayer);
    
    
    m_pMainPlayer = Runner::create();
    if(!m_pMainPlayer)
        return false;
    m_pMainPlayer->setCameraMask((unsigned short)CameraFlag::USER1);
    m_pTerrainLayer->addChild(m_pMainPlayer);
    m_pMainPlayer->setFakeShadow(m_pTerrainLayer);
    //m_pMainPlayer->setRibbonTrail("ribbontrail.png");
    m_pMainPlayer->fadeIn();
    
    auto size = Director::getInstance()->getVisibleSize();
    m_pMainCamera = Camera::createPerspective(60, size.width/size.height, 1, 5000);
    if(!m_pMainCamera)
        return false;
    Vec3 camPos = Vec3(m_pTerrainLayer->getPositionX(),m_pTerrainLayer->getPositionY(),m_pMainPlayer->getPositionZ()) + Vec3(0,80.0f*cosf(M_PI/6.0f),80.0f*sinf(M_PI/6.0f));
    Vec3 lookAt = Vec3(m_pTerrainLayer->getPositionX(),m_pTerrainLayer->getPositionY(),m_pMainPlayer->getPositionZ()) + Vec3(0,0,-30);
    m_pMainCamera->setPosition3D(camPos);
    m_pMainCamera->lookAt(lookAt);
    m_pTerrainLayer->addChild(m_pMainCamera);
    m_pMainCamera->setCameraFlag(CameraFlag::USER1);
    
    AmbientLight* ambLight = AmbientLight::create(Color3B(150, 150, 150));
    ambLight->setLightFlag(LightFlag::LIGHT0);
    m_pMainLayer->addChild(ambLight);

    DirectionLight* directionLight = DirectionLight::create(Vec3(-2, -4, -3), Color3B(158, 158, 158));
    directionLight->setLightFlag(LightFlag::LIGHT0);
    m_pMainLayer->addChild(directionLight);

    m_pTerrainAmbLight = AmbientLight::create(Color3B(150, 150, 150));
    m_pTerrainAmbLight->setLightFlag(LightFlag::LIGHT1);
    m_pMainLayer->addChild(m_pTerrainAmbLight);
    
    m_pTerrainDirectionLight = DirectionLight::create(Vec3(-2, -4, -3), Color3B(158, 158, 158));
    m_pTerrainDirectionLight->setLightFlag(LightFlag::LIGHT1);
    m_pMainLayer->addChild(m_pTerrainDirectionLight);
    
    cocos2d::ui::Button* button = cocos2d::ui::Button::create("button_retry_up.png",
                                                              "button_retry_down.png");
    button->setPosition(Vec2(size.width * 0.8f, size.height * 0.8f));
    button->setPressedActionEnabled(true);
    button->addClickEventListener([=](Ref* sender){
        auto scene = MainScene::createScene();
        Director::getInstance()->replaceScene(scene);
    });
    m_pMainLayer->addChild(button);
    
    
    cocos2d::ui::Button* button2 = cocos2d::ui::Button::create("button_retry_up.png",
                                                              "button_retry_down.png");
    button2->setPosition(Vec2(size.width * 0.8f, size.height * 0.2f));
    button2->setPressedActionEnabled(true);
    button2->addClickEventListener([=](Ref* sender){
        if (m_bHasShowRainbow)
            return;
        showRainbow();
    });
    m_pMainLayer->addChild(button2);
    
    uiLayer = Layer::create();
    m_pMainLayer->addChild(uiLayer);
    UIManager::getInstance()->init(uiLayer);
    UIManager::getInstance()->showInfo(true);
    UIManager::getInstance()->setGameUi(UIManager::UI_GAME);

    
    setGameState(RGS_FROZEN);
    
    m_nBgID = AudioEngine::play2d("mainbg.mp3",true, 0.5);
    return true;
}
void RunController::reset()
{
    m_bInMazeJump = false;
    if(m_pWhiteLayer)
    {
        EaseExponentialOut* fadeOut = EaseExponentialOut::create(FadeOut::create(1.0f));
        m_pWhiteLayer->runAction(fadeOut);
    }
    
    if(m_pTerrainLayer)
        m_pTerrainLayer->reset();
    if(m_pMainPlayer)
        m_pMainPlayer->fadeIn();
    if(m_pMainCamera)
    {
        m_pMainCamera->stopAllActions();
        cameraTrackPlayer();
    }
    
    if (uiLayer) {
        UIManager::getInstance()->init(uiLayer);
        UIManager::getInstance()->showInfo(true);
        UIManager::getInstance()->setGameUi(UIManager::UI_GAME);
    }
    AudioEngine::resume(m_nBgID);
    AudioEngine::play2d("fadeout.wav");
}
void RunController::update(float delta)
{
    if(m_pTerrainLayer)
        m_pTerrainLayer->update(delta);
    if(m_pRainbow&&m_bHasShowRainbow)
        m_pRainbow->update(delta);
    if(m_pMainPlayer)
        m_pMainPlayer->update(delta);
    if(m_pMainPlayer && m_pMainPlayer)
        checkRainbowIsShowOrHide();
}
void RunController::destroy()
{
    AudioEngine::stop(m_nBgID);

    if(m_pRainbow)
    {
        AudioEngine::stop(m_nSpeedupSoundID);
        m_pRainbow->getTrail()->removeNode(m_pRainbow);
        m_bHasShowRainbow = false;
    }

    m_pMainLayer->removeAllChildren();
    m_pMainLayer = nullptr;
    
}
void RunController::setGameState(RunnerGameState state)
{
    if (m_GameState != state)
    {
        m_GameState = state;
        switch (m_GameState) {
            case RGS_NORMAL:
                break;
            case RGS_FROZEN:
                break;
            case RGS_GAMEOVER:
                {
                    CCLOG("gameOver");
                    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_RUNNER_LOSE);
                }
                break;
            default:
                break;
        }
    }
}
int RunController::getDifficultLevel()
{
    m_nDifficultLevel = Value(localStorageGetItem(USER_LAST_LEVEL)).asInt();
    return m_nDifficultLevel;
}
void RunController::setDifficultLevel(int difficult)
{
    m_nDifficultLevel = difficult;
    localStorageSetItem(USER_LAST_LEVEL, Value(m_nDifficultLevel).asString());
    CCLOG("Current Difficult Level %d", m_nDifficultLevel);
    if(m_nDifficultLevel > getMaxDifficultLevel())
        setMaxDifficultLevel(m_nDifficultLevel);
}
int RunController::getMaxDifficultLevel()
{
    m_nMaxReachDifficultLevel = Value(localStorageGetItem(USER_MAX_LEVEL)).asInt();
    return m_nMaxReachDifficultLevel;
}
void RunController::setMaxDifficultLevel(int difficult)
{
    m_nMaxReachDifficultLevel = difficult;
    localStorageSetItem(USER_MAX_LEVEL, Value(m_nMaxReachDifficultLevel).asString());
    CCLOG("Max reach Difficult Level %d", m_nMaxReachDifficultLevel);
}
void RunController::cameraTrackPlayer()
{
    if(m_pMainPlayer && m_pMainCamera)
    {
        Vec3 camPos = Vec3(m_pTerrainLayer->getPositionX(),m_pTerrainLayer->getPositionY(),m_pMainPlayer->getPositionZ()) + Vec3(0,80.0f*cosf(M_PI/6.0f),80.0f*sinf(M_PI/6.0f));
        Vec3 targetLookAt = Vec3(m_pTerrainLayer->getPositionX(),m_pTerrainLayer->getPositionY(),m_pMainPlayer->getPositionZ()) + Vec3(0,0,-30);
        EaseSineOut* moveTo = EaseSineOut::create(MoveTo::create(0.4f, camPos));
        m_pMainCamera->runAction(moveTo);
        if(m_pMainCamera->getPositionZ() - m_pMainPlayer->getPositionZ() > 80.0f*sinf(M_PI/6.0f))
            updateCloud();
    }
}
void RunController::switchToMazeJump()
{
    if(m_pWhiteLayer)
    {
        EaseExponentialOut* fadeIn = EaseExponentialOut::create(FadeIn::create(1.0f));
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(RunController::switchToGameScene, this));
        Sequence* sequence = Sequence::create( fadeIn, callFunc, NULL);
        m_pWhiteLayer->runAction(sequence);
    }
}
void RunController::switchToMenu()
{
    if(m_pWhiteLayer)
    {
        EaseExponentialOut* fadeIn = EaseExponentialOut::create(FadeIn::create(1.0f));
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(RunController::switchToMenuScene, this));
        Sequence* sequence = Sequence::create( fadeIn, callFunc, NULL);
        m_pWhiteLayer->runAction(sequence);
    }
}
void RunController::switchToGameScene()
{
    Scene* scene = GameScene::createScene(getDifficultLevel());
    if(scene)
    {
        m_bInMazeJump = true;
        AudioEngine::pause(m_nBgID);
        Director::getInstance()->pushScene(scene);
    }
}
void RunController::switchToMenuScene()
{
    Scene* scene = MenuScene::createScene();
    if(scene)
        Director::getInstance()->replaceScene(scene);
}
bool RunController::initCloud()
{
    m_pCloud1 = Sprite3D::create("cloud.c3b");
    if(!m_pCloud1)
        return false;
    m_pCloud1->setCameraMask((unsigned short)CameraFlag::USER1);
    m_pCloud1->setLightMask((unsigned int)LightFlag::LIGHT0);
    m_pCloud1->setPositionZ(-200);
    m_pCloud1->setPositionY(-80);
    m_pCloud1->setScaleX(2.5f);
    m_pCloud1->setScaleY(2.5f);
    m_pCloud1->setScaleZ(2.5f);
    m_pCloud1->setForceDepthWrite(true);
    m_pMainLayer->addChild(m_pCloud1);
    
    m_pCloud2 = Sprite3D::create("cloud.c3b");
    if(!m_pCloud2)
        return false;
    m_pCloud2->setCameraMask((unsigned short)CameraFlag::USER1);
    m_pCloud2->setLightMask((unsigned int)LightFlag::LIGHT0);
    m_pCloud2->setPositionZ(-400);
    m_pCloud2->setPositionY(-80);
    m_pCloud2->setOpacity(0);
    m_pCloud2->setScaleX(2.5f);
    m_pCloud2->setScaleY(2.5f);
    m_pCloud2->setScaleZ(2.5f);
    m_pCloud2->setRotation3D(Vec3(0,180,0));
    m_pCloud2->setForceDepthWrite(true);
    m_pMainLayer->addChild(m_pCloud2);
    
    m_pCloud3 = Sprite3D::create("cloud.c3b");
    if(!m_pCloud2)
        return false;
    m_pCloud3->setCameraMask((unsigned short)CameraFlag::USER1);
    m_pCloud3->setLightMask((unsigned int)LightFlag::LIGHT0);
    m_pCloud3->setPositionZ(0);
    m_pCloud3->setPositionY(-80);
    m_pCloud3->setOpacity(0);
    m_pCloud3->setScaleX(2.5f);
    m_pCloud3->setScaleY(2.5f);
    m_pCloud3->setScaleZ(2.5f);
    m_pCloud3->setRotation3D(Vec3(0,180,0));
    m_pCloud3->setForceDepthWrite(true);
    m_pMainLayer->addChild(m_pCloud3);
    return true;
}
void RunController::updateCloud()
{
    if(m_pCloud1 && m_pCloud2 && m_pCloud3 && m_pMainPlayer)
    {
        if(m_pMainPlayer->getPositionZ() == m_pCloud1->getPositionZ() || m_pMainPlayer->getPositionZ() == m_pCloud1->getPositionZ() + m_pTerrainLayer->getCellBaseRadius()*2)
        {
            m_pCloud3->setPosition3D(m_pCloud2->getPosition3D() + Vec3(0,0,-200));
            m_pCloud3->setOpacity(0);
        }
        else if(m_pMainPlayer->getPositionZ() > m_pCloud1->getPositionZ() && m_pMainPlayer->getPositionZ() < m_pCloud3->getPositionZ())
        {
            int opacity =  m_pCloud2->getOpacity()+51;
            if(opacity>=255)
                opacity = 255;
            m_pCloud2->setOpacity(opacity);
        }

        if(m_pMainPlayer->getPositionZ() == m_pCloud2->getPositionZ() || m_pMainPlayer->getPositionZ() == m_pCloud2->getPositionZ() + m_pTerrainLayer->getCellBaseRadius()*2)
        {
            m_pCloud1->setPosition3D(m_pCloud3->getPosition3D() + Vec3(0,0,-200));
            m_pCloud1->setOpacity(0);
        }
        else if(m_pMainPlayer->getPositionZ() > m_pCloud2->getPositionZ() && m_pMainPlayer->getPositionZ() < m_pCloud1->getPositionZ())
        {
            int opacity =  m_pCloud3->getOpacity()+51;
            if(opacity>=255)
                opacity = 255;
            m_pCloud3->setOpacity(opacity);
        }
        
        if(m_pMainPlayer->getPositionZ() == m_pCloud3->getPositionZ() || m_pMainPlayer->getPositionZ() == m_pCloud3->getPositionZ() + m_pTerrainLayer->getCellBaseRadius()*2)
        {
            m_pCloud2->setPosition3D(m_pCloud1->getPosition3D() + Vec3(0,0,-200));
            m_pCloud2->setOpacity(0);
        }
        else if(m_pMainPlayer->getPositionZ() > m_pCloud3->getPositionZ() && m_pMainPlayer->getPositionZ() < m_pCloud2->getPositionZ())
        {
            int opacity =  m_pCloud1->getOpacity()+51;
            if(opacity>=255)
                opacity = 255;
            m_pCloud1->setOpacity(opacity);
        }
    }
}
void RunController::addPlayerExplosion()
{
    if(m_pMainPlayer && m_pMainLayer)
    {
        auto explosion = PUParticleSystem3D::create("explosionSystem.pu");
        explosion->setCameraMask((unsigned short)CameraFlag::USER1);
        explosion->setPosition3D(m_pMainPlayer->getPosition3D());
        m_pMainLayer->addChild(explosion);
        explosion->startParticleSystem();
        m_pMainPlayer->removeFromParentAndCleanup(true);
        m_pMainPlayer = nullptr;
    }
}
void RunController::addDecoratorExplosion(const cocos2d::Vec3& pos)
{
    if(m_pMainPlayer && m_pMainLayer)
    {
        auto explosion = PUParticleSystem3D::create("explosionSystem.pu");
        explosion->setCameraMask((unsigned short)CameraFlag::USER1);
        explosion->setPosition3D(pos);
        m_pMainLayer->addChild(explosion);
        explosion->startParticleSystem();
    }
}
void RunController::pauseBgMusic()
{
    AudioEngine::pause(m_nBgID);
    m_nSpeedupSoundID = AudioEngine::play2d("speedup.wav", true);
}
void RunController::resumeBgMusic()
{
    AudioEngine::stop(m_nSpeedupSoundID);
    AudioEngine::resume(m_nBgID);
}
void RunController::showRainbow()
{
    if(m_bHasShowRainbow)
        return;
    if(m_pMainLayer == nullptr || m_pMainPlayer == nullptr)
        return;
    if(m_pMainPlayer->isSpeedUp())
        return;
    if(m_pMainPlayer->getState() != Runner::RS_IDLE)
        return;

    m_pRainbow = RibbonTrail::create("ribbontrail.png", 42, 3000);
    if(!m_pRainbow)
        return;
    m_pRainbow->setPosition3D(Vec3(0, 20, m_pMainPlayer->getPositionZ()-500));
    m_pRainbow->setCameraMask((unsigned short)CameraFlag::USER1);
    m_pMainLayer->addChild(m_pRainbow);
    m_pRainbow->getTrail()->addNode(m_pRainbow);
        
    EaseSineOut* moveTo = EaseSineOut::create(MoveBy::create(10, Vec3(0,0,3600)));
    m_pRainbow->runAction(moveTo);
    
    if(m_pTerrainAmbLight)
    {
        EaseSineIn* tinyIn = EaseSineIn::create(TintBy::create(1.0f, -150, -150, -150));
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(Runner::setSpeedUp, m_pMainPlayer, true));
        CallFunc* callFunc1 = CallFunc::create(CC_CALLBACK_0(RunController::pauseBgMusic, this));
        Sequence* sequence = Sequence::create(tinyIn, callFunc, callFunc1,NULL);
        m_pTerrainAmbLight->runAction(sequence);
            
        AudioEngine::play2d("rainbowin.wav", false, 2.0f);
    }
    m_bHasShowRainbow = true;
}
void RunController::hideRainbow()
{
    if(m_pRainbow)
    {
        m_pRainbow->getTrail()->removeNode(m_pRainbow);
        if(m_pRainbow->getReferenceCount() > 0)
            m_pRainbow->removeFromParentAndCleanup(true);
        m_pRainbow = nullptr;
    }
    if(m_pMainPlayer)
    {
        m_pMainPlayer->setSpeedUp(false);
        resumeBgMusic();
    }
}
void RunController::checkRainbowIsShowOrHide()
{
    if(m_bHasShowRainbow && m_pMainPlayer->isSpeedUp())
    {
        float playerPosZ = m_pMainPlayer->getPositionZ();
        float rainbowPosZ = m_pRainbow->getPositionZ();
        if(rainbowPosZ - playerPosZ >= 3000)
        {
            AudioEngine::play2d("rainbowout.wav",false, 0.2f);
            if(m_pTerrainAmbLight)
            {
                EaseSineOut* tinyIn = EaseSineOut::create(TintBy::create(1.0f, 150, 150, 150));
                CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(RunController::hideRainbow, this));
                Sequence* sequence = Sequence::create(tinyIn, callFunc,NULL);
                m_pTerrainAmbLight->runAction(sequence);
            }
            m_bHasShowRainbow = false;
        }
    }
}
cocos2d::Color3B RunController::getRandomColorByIndex(int index)
{
    CCASSERT(index<=6 && index>=0, "index must between 0-6");
    if(index == 0)
        return m_randomColor0;
    else if(index == 1)
        return m_randomColor1;
    else if(index == 2)
        return m_randomColor2;
    else if(index == 3)
        return m_randomColor3;
    else if(index == 4)
        return m_randomColor4;
    else if(index == 5)
        return m_randomColor5;
    else if(index == 6)
        return m_randomColor6;
    else
        return m_sameColor;
}