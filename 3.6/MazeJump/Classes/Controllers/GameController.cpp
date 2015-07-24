//
//  GameController.cpp
//  MazeJump
//
//  Created by wang haibo on 15/7/4.
//
//

#include "GameController.h"
#include "LevelsManager.h"
#include "CocosGUI.h"
USING_NS_CC;

GameController* g_pGameControllerInstance = nullptr;
GameController* GameController::getInstance()
{
    if( g_pGameControllerInstance == nullptr )
        g_pGameControllerInstance = new GameController();
    
    return g_pGameControllerInstance;
}
GameController::GameController()
{
    m_pMainLayer        = nullptr;
    m_pSkyBox           = nullptr;
    m_pGroundLayer      = nullptr;
    m_pMainCamera       = nullptr;

}
GameController::~GameController()
{
}
bool GameController::init(Layer* pMainLayer)
{
    if(pMainLayer == nullptr)
        return false;
    m_pMainLayer = pMainLayer;
    
    if (!createMap(false)) {
        return false;
    }
    
    auto size = Director::getInstance()->getVisibleSize();
    cocos2d::ui::Button* button = cocos2d::ui::Button::create("button_retry_up.png",
                                    "button_retry_down.png");
    button->setPosition(Vec2(size.width * 0.8f, size.height * 0.8f));
    button->setPressedActionEnabled(true);
    button->addClickEventListener([=](Ref* sender){
        
    });
    m_pMainLayer->addChild(button);
    return true;
}
void GameController::update(float delta)
{

}
void GameController::destroy()
{
    m_pMainLayer->removeAllChildren();
    m_pMainLayer = nullptr;
}

bool GameController::createMap(bool _playing)
{

    if (m_pSkyBox) {
         m_pMainLayer->removeChild(m_pSkyBox);
    }
   
    m_pMainLayer->removeChild(m_pGroundLayer);
    m_pMainLayer->removeChild(m_pMainCamera);
    std::string skyTexName = LevelsManager::getInstance()->getCurrentLevelSkyTextureName();
    std::string skyTexTop = skyTexName + "_t.png";
    std::string skyTexBottom = skyTexName + "_b.png";
    std::string skyTex = skyTexName + ".png";
    m_pSkyBox = Skybox::create(skyTex, skyTex, skyTex, skyTex, skyTex, skyTex);
    if(!m_pSkyBox)
        return false;
    m_pSkyBox->setScale(1000);
    m_pSkyBox->setCameraMask((unsigned short)CameraFlag::USER1);
    m_pMainLayer->addChild(m_pSkyBox);
    
    ParticleSystemQuad* starfield= ParticleSystemQuad::create("starfield.plist");
    if(!starfield)
    {
        CCLOG("Load explosion particle system failed! file: starfield.plist");
        return false;
    }
    starfield->setStartSize(5.0f);
    starfield->setStartSizeVar(3.0f);
    starfield->setGravity(Vec2(-40.0f, 0));
    m_pMainLayer->addChild(starfield);
    
    
    
    m_pGroundLayer = GroundLayer::create(LevelsManager::getInstance()->getCurrentLevelName(),_playing);
    if(!m_pGroundLayer)
        return false;
    m_pGroundLayer->setCameraMask((unsigned short)CameraFlag::USER1);
    ///focus
    m_pGroundLayer->setAnchorPoint(Vec2::ZERO);
    m_pMainLayer->addChild(m_pGroundLayer);
    
    auto size = Director::getInstance()->getVisibleSize();
    m_pMainCamera = Camera::createPerspective(90, size.width/size.height, 1, 5000);
    if(!m_pMainCamera)
        return false;
    m_pMainCamera->setPosition3D(Vec3(0,-m_pGroundLayer->getGroundRadius()*2.5f*cosf(M_PI),-m_pGroundLayer->getGroundRadius()*2.5f*sinf(M_PI)) + m_pGroundLayer->getOffset());
    m_pMainCamera->lookAt(m_pGroundLayer->getPosition3D() + m_pGroundLayer->getOffset());
    m_pMainLayer->addChild(m_pMainCamera);
    m_pMainCamera->setCameraFlag(CameraFlag::USER1);
    m_pGroundLayer->setCamera(m_pMainCamera);
    
    AmbientLight* ambLight = AmbientLight::create(Color3B(150, 150, 150));
    m_pMainLayer->addChild(ambLight);
    DirectionLight* directionLight = DirectionLight::create(Vec3(-3, -4, -2), Color3B(158, 158, 158));
    m_pMainLayer->addChild(directionLight);
    return true;
}