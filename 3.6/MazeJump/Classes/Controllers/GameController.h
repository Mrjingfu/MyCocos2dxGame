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
#include "DecoratorLayer.h"
class GameController : public cocos2d::Ref
{
    GameController();
    ~GameController();
public:
    static GameController* getInstance();
    bool init(cocos2d::Layer* pMainLayer);
    void update(float delta);
    void destroy();
private:
    cocos2d::Layer*     m_pMainLayer;
    cocos2d::Skybox*    m_pSkyBox;
    DecoratorLayer*     m_pDecoratorLayer;
    GroundLayer*        m_pGroundLayer;
    cocos2d::Camera*    m_pMainCamera;
};

#endif /* defined(__MazeJump__GameController__) */
