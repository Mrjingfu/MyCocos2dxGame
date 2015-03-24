//
//  GameController.cpp
//  TinyFlare
//
//  Created by wang haibo on 15/3/12.
//
//

#include "GameController.h"
#include "ActorsManager.h"

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
    m_pGameLayer        = nullptr;
    m_pPlayer           = nullptr;
    m_pTwoJoysticks     = nullptr;
    m_pActorCamera      = nullptr;
    m_BoundSize         = Size(2048, 1536);
    m_pEnemiesGenerator = nullptr;
    m_curGameState      = GS_UNKNOWN;
}
GameController::~GameController()
{
}
bool GameController::init(Layer* pMainLayer)
{
    if(pMainLayer == nullptr)
        return false;
    m_pMainLayer = pMainLayer;
    
    m_pEnemiesGenerator = EnemiesGenerator::create();
    if(m_pEnemiesGenerator)
        m_pMainLayer->addChild(m_pEnemiesGenerator);
    
    auto size = Director::getInstance()->getWinSize();
    
    m_pGameLayer = Layer::create();
    if(!m_pGameLayer)
        return false;
    m_pGameLayer->setAnchorPoint(Vec2::ZERO);
    m_pMainLayer->addChild(m_pGameLayer);
    
    Sprite* bgSprite = Sprite::create("bg.png");
    if(!bgSprite)
        return false;
    bgSprite->setScale(2.0);
    m_pGameLayer->addChild(bgSprite);
    
    m_pPlayer = Player::create();
    if(!m_pPlayer)
        return false;
    m_pPlayer->loadModel("playermain.png");
    m_pPlayer->loadMaskModel("playermask.png");
    m_pGameLayer->addChild(m_pPlayer);
    
    m_pActorCamera = Camera::create();
    if(!m_pActorCamera)
        return false;
    m_pGameLayer->addChild(m_pActorCamera);
    m_pActorCamera->setPosition(m_pPlayer->getPosition());
    if(Director::getInstance()->getZEye() > 640.0f);
        m_pActorCamera->setPositionZ(640.0f);
    m_pActorCamera->setCameraFlag(CameraFlag::USER1);
    m_pGameLayer->setCameraMask((unsigned short)CameraFlag::USER1);
    
    if(!ActorsManager::getInstance()->init(m_pGameLayer))
        return false;
    
    m_pTwoJoysticks = TwoJoysticks::create("joystick_bg1.png", "joystick1.png", "joystick_bg2.png", "joystick2.png");
    if(!m_pTwoJoysticks)
        return false;
    m_pTwoJoysticks->setJoystickLeftListener(m_pPlayer);
    m_pTwoJoysticks->setJoystickRightListener(m_pPlayer);
    m_pMainLayer->addChild(m_pTwoJoysticks);
    
    setGameState(GS_DEBUG);
    
    return true;
}
void GameController::update(float delta)
{
    if(m_pActorCamera && m_pPlayer)
    {
        if(m_pPlayer->getActorState() != ActorState::AS_DEAD)
        {
            Vec2 camPos = m_pActorCamera->getPosition();
            Vec2 camVelocity = m_pPlayer->getVelocity()*0.8f;
            camPos += camVelocity;
            CCLOG("camPos %f, %f", camPos.x, camPos.y);
            m_pActorCamera->setPosition(camPos);
        
            checkBounce(m_pPlayer);
        }
    }
    ActorsManager::getInstance()->update(delta);
}
void GameController::destroy()
{
    ActorsManager::getInstance()->destroy();
}
void GameController::setGameState(GameState state)
{
    if (m_curGameState == state)
        return;
    ///处理上一个状态退出逻辑
    switch (m_curGameState) {
        case GameState::GS_SPLASH:
            onExitSplash();
            break;
        case GameState::GS_MENU:
            onExitMenu();
            break;
        case GameState::GS_GAME:
            onExitGame();
            break;
        case GameState::GS_PAUSE:
            onEnterPause();
            break;
        case GameState::GS_DEBUG:
            onExitDebug();
            break;
        default:
            break;
    }
    
    m_curGameState = state;
    ///处理下一个状态进入逻辑
    switch (m_curGameState) {
        case GameState::GS_SPLASH:
            onEnterSplash();
            break;
        case GameState::GS_MENU:
            onEnterMenu();
            break;
        case GameState::GS_GAME:
            onEnterGame();
            break;
        case GameState::GS_PAUSE:
            onEnterPause();
            break;
        case GameState::GS_DEBUG:
            onEnterDebug();
            break;
        default:
            break;
    }
}


Player* GameController::getPlayer() const
{
    return m_pPlayer;
}
Layer* GameController::getGameLayer() const
{
    return m_pGameLayer;
}
Camera* GameController::getActorCamera() const
{
    return m_pActorCamera;
}
EnemiesGenerator* GameController::getEnemiesGenerator() const
{
    return m_pEnemiesGenerator;
}
Size GameController::getBoundSize() const
{
    return m_BoundSize;
}
Vec2 GameController::getPlayerPos()
{
    if(m_pPlayer)
        return m_pPlayer->getPosition();
    return Vec2::ZERO;
}
cocos2d::Vec2 GameController::getPlayerOrientation()
{
    if(m_pPlayer)
        return m_pPlayer->getOrientation();
    return Vec2::ZERO;
}
void GameController::checkBounce(GameActor* actor)
{
    if(actor == nullptr)
        return;
    Vec2 newPos = actor->getPosition();
    Vec2 velocity = actor->getVelocity();
    float minX = newPos.x - actor->getRadius();
    float maxX = newPos.x + actor->getRadius();
    float minY = newPos.y - actor->getRadius();
    float maxY = newPos.y + actor->getRadius();
    float boundX = m_BoundSize.width*0.5f;
    float boundY = m_BoundSize.height*0.5f;
    bool bounced = false;
    if (minX <= -boundX + actor->getMaxSpeed() || maxX >= boundX - actor->getMaxSpeed() ){
        velocity.x = - velocity.x;
        bounced = true;
    }
    if( minY <= -boundY + actor->getMaxSpeed() || maxY >= boundY - actor->getMaxSpeed() ){
        velocity.y = - velocity.y;
        bounced = true;
    }
    actor->setBounce(bounced);
    if(bounced)
        actor->setVelocity(velocity);
}
void GameController::onEnterSplash()
{
}
void GameController::onExitSplash()
{
}

void GameController::onEnterMenu()
{
}
void GameController::onExitMenu()
{
}

void GameController::onEnterGame()
{
    
}
void GameController::onExitGame()
{
}

void GameController::onEnterPause()
{
}
void GameController::onExitPause()
{
}

void GameController::onEnterDebug()
{
    if(m_pEnemiesGenerator)
    {
        m_pEnemiesGenerator->generateEnemiesByTime(Enemy::ET_DIAMOND, 1.0f);
        m_pEnemiesGenerator->generateEnemiesByNum(Enemy::ET_TRIANGLE_COLORED, 5.0f, 1);
    }
}
void GameController::onExitDebug()
{
}