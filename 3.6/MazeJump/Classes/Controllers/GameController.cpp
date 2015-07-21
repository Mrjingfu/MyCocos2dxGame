//
//  GameController.cpp
//  MazeJump
//
//  Created by wang haibo on 15/7/4.
//
//

#include "GameController.h"
#include "LevelsManager.h"
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
    m_pDecoratorLayer   = nullptr;
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
    m_pSkyBox = Skybox::create("sky1.png", "sky1.png", "sky1_t.png", "sky1_b.png", "sky1.png", "sky1.png");
    if(!m_pSkyBox)
        return false;
    m_pSkyBox->setScale(1000);
    m_pSkyBox->setCameraMask((unsigned short)CameraFlag::USER1);
    pMainLayer->addChild(m_pSkyBox);
    
    Sequence* sequence = Sequence::create(EaseSineOut::create(RotateBy::create(10, 5)), EaseSineOut::create(RotateBy::create(20, -10)), EaseSineOut::create(RotateBy::create(10, 5)), nullptr);
    RepeatForever* repeat = RepeatForever::create(sequence);
    m_pSkyBox->runAction(repeat);
    m_pDecoratorLayer = DecoratorLayer::create("castle.obj", Color4F(255.0f/255.0f, 149.0f/225.0f, 148.0f/255.0f,1.0f));
    if(!m_pDecoratorLayer)
        return false;
    m_pDecoratorLayer->setCameraMask((unsigned short)CameraFlag::USER1);
    ///focus
    m_pDecoratorLayer->setAnchorPoint(Vec2::ZERO);
    m_pMainLayer->addChild(m_pDecoratorLayer);
    
    m_pGroundLayer = GroundLayer::create(LevelsManager::getInstance()->getCurrentLevelName());
    if(!m_pGroundLayer)
        return false;
    m_pGroundLayer->setCameraMask((unsigned short)CameraFlag::USER1);
    ///focus
    m_pGroundLayer->setAnchorPoint(Vec2::ZERO);
    m_pMainLayer->addChild(m_pGroundLayer);
    
    auto size = Director::getInstance()->getVisibleSize();
    m_pMainCamera = Camera::createPerspective(60, size.width/size.height, 1, 5000);
    if(!m_pMainCamera)
        return false;
    m_pMainCamera->setPosition3D(Vec3(0,m_pGroundLayer->getGroundRadius()*2.5f*cosf(M_PI/7.0f),m_pGroundLayer->getGroundRadius()*2.5f*sinf(M_PI/7.0f)) + m_pGroundLayer->getOffset());
    m_pMainCamera->lookAt(m_pGroundLayer->getPosition3D() + m_pGroundLayer->getOffset());
    m_pMainLayer->addChild(m_pMainCamera);
    m_pMainCamera->setCameraFlag(CameraFlag::USER1);
    m_pGroundLayer->setCamera(m_pMainCamera);
    
    AmbientLight* ambLight = AmbientLight::create(Color3B(150, 150, 150));
    m_pMainLayer->addChild(ambLight);
    DirectionLight* directionLight = DirectionLight::create(Vec3(-3, -4, -2), Color3B(128, 128, 128));
    m_pMainLayer->addChild(directionLight);
    
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