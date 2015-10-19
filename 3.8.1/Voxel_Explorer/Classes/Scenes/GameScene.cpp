//
//  GameScene.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/9/24.
//
//

#include "GameScene.h"
#include "VoxelExplorer.h"
#include "MainUiLayer.h"
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
    
    auto mainUi = MainUiLayer::create();
    mainUi->load("Scene.csb");
    VoxelExplorer::getInstance()->get2DLayer()->addChild(mainUi);
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto touchListener = EventListenerTouchOneByOne::create();
    if(touchListener == nullptr)
        return false;
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    return true;
}
bool GameScene::onTouchBegan(Touch *touch, Event *event)
{
    if(!touch)
        return false;
    m_TouchBegin = touch->getLocationInView();
    prepareToJump();
    return true;
}
void GameScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
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

void GameScene::onTouchEnded(Touch *touch, Event *event)
{
    if(!touch)
        return;
    m_TouchEnd = touch->getLocationInView();
    excuteToJump();
}
void GameScene::prepareToJump()
{
    Player* player = VoxelExplorer::getInstance()->getPlayer();
    if(player && player->getState() == Player::PS_IDLE)
        player->setState(Player::PS_PREPARE_TO_JUMP);
}
void GameScene::rotateToForward()
{
    Player* player = VoxelExplorer::getInstance()->getPlayer();
    if(player && player->getState() == Player::PS_PREPARE_TO_JUMP)
        player->rotateToForward();
}
void GameScene::rotateToBack()
{
    Player* player = VoxelExplorer::getInstance()->getPlayer();
    if(player && player->getState() == Player::PS_PREPARE_TO_JUMP)
        player->rotateToBack();
}
void GameScene::rotateToLeft()
{
    Player* player = VoxelExplorer::getInstance()->getPlayer();
    if(player && player->getState() == Player::PS_PREPARE_TO_JUMP)
        player->rotateToLeft();
}
void GameScene::rotateToRight()
{
    Player* player = VoxelExplorer::getInstance()->getPlayer();
    if(player && player->getState() == Player::PS_PREPARE_TO_JUMP)
        player->rotateToRight();
}
void GameScene::excuteToJump()
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