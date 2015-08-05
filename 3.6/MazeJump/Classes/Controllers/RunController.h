//
//  RunController.h
//  MazeJump
//
//  Created by wang haibo on 15/7/22.
//
//

#ifndef __MazeJump__RunController__
#define __MazeJump__RunController__

#include "cocos2d.h"
#include "TerrainLayer.h"
#include "Runner.h"
#include "GameUI.h"
class RunController : public cocos2d::Ref
{
    RunController();
    ~RunController();
public:
    typedef enum {
        RGS_NORMAL = 0,
        RGS_FROZEN,
        RGS_GAMEOVER
    } RunnerGameState;
    static RunController* getInstance();
    bool init(cocos2d::Layer* pMainLayer);
    void reset();
    void update(float delta);
    void destroy();
    
    TerrainLayer* getTerrainLayer() const { return m_pTerrainLayer; }
    cocos2d::Camera* getMainCamera() const { return m_pMainCamera; }
    Runner* getMainPlayer() const { return m_pMainPlayer; }
    GameUI* getGameUiLayer()const {return m_gameUI;}
    RunnerGameState getGameState() const { return m_GameState; }
    void setGameState(RunnerGameState state);

    int getInitDifficultLevel() const { return m_nInitDifficultLevel; }
    int getDifficultLevel();
    void setDifficultLevel(int difficult);

    int getMaxDifficultLevel();
    void setMaxDifficultLevel(int difficult);
    
    void cameraTrackPlayer();
    
    void switchToMazeJump();
    void switchToMenu();
    
    bool isInMazeJump() const { return m_bInMazeJump; }
    
    void addPlayerExplosion();
private:
    void switchToGameScene();
    void switchToMenuScene();
    bool initCloud();
    void updateCloud();
private:
    cocos2d::Layer*     m_pMainLayer;
    TerrainLayer*       m_pTerrainLayer;
    cocos2d::Camera*    m_pMainCamera;
    Runner*             m_pMainPlayer;
    cocos2d::Sprite3D*           m_pCloud1;
    cocos2d::Sprite3D*           m_pCloud2;
    cocos2d::Sprite3D*           m_pCloud3;
    
    int             m_nInitDifficultLevel;
    int             m_nDifficultLevel;
    int             m_nMaxReachDifficultLevel;
    
    cocos2d::LayerColor*        m_pWhiteLayer;
    bool            m_bInMazeJump;
    
    RunnerGameState m_GameState;
    GameUI* m_gameUI;
};

#endif /* defined(__MazeJump__RunController__) */
