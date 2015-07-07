//
//  GameController.cpp
//  MazeJump
//
//  Created by wang haibo on 15/7/4.
//
//

#include "GameController.h"
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
    
    m_pGroundLayer = GroundLayer::create("5x5-6.tmx");
    if(!m_pGroundLayer)
        return false;
    m_pGroundLayer->setCameraMask((unsigned short)CameraFlag::USER1);
    ///focus
    m_pGroundLayer->setAnchorPoint(Vec2::ZERO);
    m_pMainLayer->addChild(m_pGroundLayer);
    
    m_pMainCamera = Camera::create();
    if(!m_pMainCamera)
        return false;
    m_pMainCamera->setPosition3D(Vec3(0,m_pGroundLayer->getGroundRadius()*2.5f*cosf(M_PI/7.0f),m_pGroundLayer->getGroundRadius()*2.5f*sinf(M_PI/7.0f)) + m_pGroundLayer->getOffset());
    m_pMainCamera->lookAt(m_pGroundLayer->getPosition3D() + m_pGroundLayer->getOffset());
    m_pMainLayer->addChild(m_pMainCamera);
    m_pMainCamera->setCameraFlag(CameraFlag::USER1);
    m_pGroundLayer->setCamera(m_pMainCamera);
    
    AmbientLight* ambLight = AmbientLight::create(Color3B(150, 150, 150));
    m_pGroundLayer->addChild(ambLight);
    DirectionLight* directionLight = DirectionLight::create(Vec3(-3, -4, -2), Color3B(128, 128, 128));
    m_pGroundLayer->addChild(directionLight);
    
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