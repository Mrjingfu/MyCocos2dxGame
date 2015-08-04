//
//  GameLose.h
//  MazeJump
//
//
//

#ifndef __MazeJump__GameLose__
#define __MazeJump__GameLose__

#include "cocos2d.h"
#include "BaseUI.h"
class GameLose : public BaseUI
{
protected:
    GameLose();
    virtual ~GameLose();
    virtual bool init() ;
public:
    virtual void onEnter();
    virtual void onExit();
    static GameLose* create();


};

#endif /* defined(__MazeJump__GameLose__) */
