//
//  GameScene.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/9/24.
//
//

#include "GameScene.h"
#include "VoxelExplorer.h"
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

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    if(!VoxelExplorer::getInstance()->init(this))
        return false;
    return true;
}
bool GameScene::onTouchBegan(Touch *touch, Event *event)
{
    if(!touch)
        return false;
    m_TouchBegin = touch->getLocationInView();
    return true;
}
void GameScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if(!touch)
        return;
    m_TouchEnd = touch->getLocationInView();
    float distanceX = fabsf(m_TouchEnd.x - m_TouchBegin.x);
    float distanceY = fabsf(m_TouchEnd.y - m_TouchBegin.y);
//    if(distanceX>20 && distanceX >= distanceY)
//    {
//        if(m_TouchEnd.x < m_TouchBegin.x)
//            jumpLeft();
//        else if(m_TouchEnd.x > m_TouchBegin.x)
//            jumpRight();
//    }
//    else
//    {
//        if(distanceY>20 && m_TouchEnd.y < m_TouchBegin.y)
//            jumpSuper();
//        else
//            jumpForward();
//    }

}

void GameScene::onTouchEnded(Touch *touch, Event *event)
{
    if(!touch)
        return;
    m_TouchEnd = touch->getLocationInView();
//    float distanceX = fabsf(m_TouchEnd.x - m_TouchBegin.x);
//    float distanceY = fabsf(m_TouchEnd.y - m_TouchBegin.y);
//    if(distanceX>20 && distanceX >= distanceY)
//    {
//        if(m_TouchEnd.x < m_TouchBegin.x)
//            jumpLeft();
//        else if(m_TouchEnd.x > m_TouchBegin.x)
//            jumpRight();
//    }
//    else
//    {
//        if(distanceY>20 && m_TouchEnd.y < m_TouchBegin.y)
//            jumpSuper();
//        else
//            jumpForward();
//    }
}