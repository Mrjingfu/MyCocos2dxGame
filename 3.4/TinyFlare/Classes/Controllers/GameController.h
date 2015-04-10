//
//  GameController.h
//  TinyFlare
//
//  Created by wang haibo on 15/3/12.
//
//

#ifndef __TinyFlare__GameController__
#define __TinyFlare__GameController__

#include "cocos2d.h"
#include "TwoJoysticks.h"
#include "Player.h"
#include "EnemiesGenerator.h"
typedef enum {
    GS_SPLASH = 0,
    GS_MENU,
    GS_LEVEL_FROZEN,
    GS_GAME,
    GS_PAUSE,
    GS_DEBUG,
    GS_UNKNOWN
} GameState;

class GameController : public cocos2d::Ref
{
    GameController();
    ~GameController();
public:
    static GameController* getInstance();
    bool init(cocos2d::Layer* pMainLayer);
    void update(float delta);
    void destroy();
    
    void setGameState(GameState state);
    
    Player* getPlayer() const;
    cocos2d::Layer* getGameLayer() const;
    cocos2d::Camera* getActorCamera() const;
    EnemiesGenerator* getEnemiesGenerator() const;
    
    cocos2d::Size getBoundSize() const;
    
    cocos2d::Vec2 getPlayerPos();
    cocos2d::Vec2 getPlayerOrientation();
    
    void checkBounce(GameActor* actor);
private:
    void onEnterSplash();
    void onExitSplash();
    
    void onEnterMenu();
    void onExitMenu();
    
    void onEnterGame();
    void onExitGame();
    
    void onEnterPause();
    void onExitPause();
    
    void onEnterDebug();
    void onExitDebug();
    
    void gameStart();
    void gamePause();
    void gameEnd();
private:
    cocos2d::Layer*     m_pGameLayer;
    EnemiesGenerator*   m_pEnemiesGenerator;
    cocos2d::Camera*    m_pActorCamera;
    TwoJoysticks*       m_pTwoJoysticks;
    cocos2d::Layer*     m_pMainLayer;
    Player*             m_pPlayer;
    GameState           m_curGameState;
    cocos2d::Size       m_BoundSize;
    
    float               m_fRespawnTime;
};


#endif /* defined(__TinyFlare__GameController__) */
