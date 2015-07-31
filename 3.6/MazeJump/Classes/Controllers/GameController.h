//
//  GameController.h
//  MazeJump
//
//  Created by wang haibo on 15/7/4.
//
//

#ifndef __MazeJump__GameController__
#define __MazeJump__GameController__

#include "cocos2d.h"
#include "GroundLayer.h"
class GameController : public cocos2d::Ref
{
    GameController();
    ~GameController();
public:
    static GameController* getInstance();
    bool init(cocos2d::Layer* pMainLayer,int difficultLevel);
    void update(float delta);
    void destroy();
    int randomLevel(int difficultLevel);
    
    void switchToRainbowRun();
private:
    void switchToMainScene();
private:
    cocos2d::Layer*     m_pMainLayer;
    cocos2d::Skybox*    m_pSkyBox;
    GroundLayer*        m_pGroundLayer;
    cocos2d::Camera*    m_pMainCamera;
    bool createMap(bool _playing,int level);
    
    cocos2d::LayerColor*        m_pWhiteLayer;
};

#endif /* defined(__MazeJump__GameController__) */
