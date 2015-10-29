//
//  Layer3D.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/29.
//
//

#include "Layer3D.hpp"
#include "VoxelExplorer.h"
#include "GameUILayer.h"
USING_NS_CC;

Scene* Layer3D::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Layer3D::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
// on "init" you need to initialize your instance
bool Layer3D::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto touchListener = EventListenerTouchOneByOne::create();
    if(touchListener == nullptr)
        return false;
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(Layer3D::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(Layer3D::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(Layer3D::onTouchEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    return true;
}
bool Layer3D::onTouchBegan(Touch *touch, Event *event)
{
    if(!touch)
        return false;
    m_TouchBegin = touch->getLocationInView();
    prepareToJump();
    return true;
}
void Layer3D::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if(!touch)
        return;
    m_TouchEnd = touch->getLocationInView();
    float distanceX = fabsf(m_TouchEnd.x - m_TouchBegin.x);
    float distanceY = fabsf(m_TouchEnd.y - m_TouchBegin.y);
    if(distanceX >= distanceY)
    {
        if(distanceX>5)
        {
            if(m_TouchEnd.x < m_TouchBegin.x)
                rotateToLeft();
            else if(m_TouchEnd.x > m_TouchBegin.x)
                rotateToRight();
        }
    }
    else
    {
        if(distanceY>5)
        {
            if(m_TouchEnd.y < m_TouchBegin.y)
                rotateToForward();
            else
                rotateToBack();
        }
    }
    
}

void Layer3D::onTouchEnded(Touch *touch, Event *event)
{
    if(!touch)
        return;
    m_TouchEnd = touch->getLocationInView();
    excuteToJump();
}
void Layer3D::prepareToJump()
{
    Player* player = VoxelExplorer::getInstance()->getPlayer();
    if(player && player->getState() == Player::PS_IDLE)
        player->setState(Player::PS_PREPARE_TO_JUMP);
}
void Layer3D::rotateToForward()
{
    Player* player = VoxelExplorer::getInstance()->getPlayer();
    if(player && player->getState() == Player::PS_PREPARE_TO_JUMP)
        player->rotateToForward();
}
void Layer3D::rotateToBack()
{
    Player* player = VoxelExplorer::getInstance()->getPlayer();
    if(player && player->getState() == Player::PS_PREPARE_TO_JUMP)
        player->rotateToBack();
}
void Layer3D::rotateToLeft()
{
    Player* player = VoxelExplorer::getInstance()->getPlayer();
    if(player && player->getState() == Player::PS_PREPARE_TO_JUMP)
        player->rotateToLeft();
}
void Layer3D::rotateToRight()
{
    Player* player = VoxelExplorer::getInstance()->getPlayer();
    if(player && player->getState() == Player::PS_PREPARE_TO_JUMP)
        player->rotateToRight();
}
void Layer3D::excuteToJump()
{
    Player* player = VoxelExplorer::getInstance()->getPlayer();
    if(player && (player->getState() == Player::PS_PREPARE_TO_JUMP))
    {
        if(VoxelExplorer::getInstance()->checkMovable())
            player->setState(Player::PS_JUMPMOVE);
        else
            player->setState(Player::PS_JUMPLOCAL);
    }
}