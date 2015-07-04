//
//  GameScene.cpp
//  MazeJump
//
//  Created by wang haibo on 15/6/23.
//
//

#include "GameScene.h"
#include "GroundLayer.h"
USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
GameScene::GameScene()
{
    m_pMainCamera = nullptr;
}
// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    GroundLayer* ground = GroundLayer::create("5x5-1.tmx");
    ground->setPosition(Vec2(0,-20));
    addChild( ground );
    ground->setCameraMask((unsigned short)CameraFlag::USER1);
    
    m_pMainCamera = Camera::create();
    if(!m_pMainCamera)
        return false;
    m_pMainCamera->setPosition3D(Vec3(0,-500*cosf(M_PI/3),500*sinf(M_PI/3)));
    m_pMainCamera->lookAt(ground->getPosition3D());
    addChild(m_pMainCamera);
    //if(Director::getInstance()->getZEye() > 640.0f)
    //    m_pMainCamera->setPositionZ(640.0f);
    m_pMainCamera->setCameraFlag(CameraFlag::USER1);
    
    
    
    return true;
}