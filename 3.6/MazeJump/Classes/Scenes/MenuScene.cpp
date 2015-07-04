//
//  MenuScene.cpp
//  MazeJump
//
//  Created by wang haibo on 15/6/23.
//
//

#include "MenuScene.h"
#include "GroundLayer.h"
USING_NS_CC;

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
    m_pMainCamera = nullptr;
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
    GroundLayer* ground = GroundLayer::create("5x5-1.tmx");
    addChild( ground );
    ground->setCameraMask((unsigned short)CameraFlag::USER1);
    
    m_pMainCamera = Camera::create();
    if(!m_pMainCamera)
        return false;
    m_pMainCamera->setPosition3D(Vec3(0,ground->getGroundRadius()*2.5f*cosf(M_PI/7.0f),ground->getGroundRadius()*2.5f*sinf(M_PI/7.0f)) + ground->getOffset());
    m_pMainCamera->lookAt(ground->getPosition3D() + ground->getOffset());
    addChild(m_pMainCamera);
    //if(Director::getInstance()->getZEye() > 640.0f)
    //    m_pMainCamera->setPositionZ(640.0f);
    m_pMainCamera->setCameraFlag(CameraFlag::USER1);
    ground->setCamera(m_pMainCamera);
    
    return true;
}