//
//  GameLose.h
//  MazeJump
//
//
//

#ifndef __MazeJump__GameLose__
#define __MazeJump__GameLose__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
class GameLose : public cocos2d::ui::Layout
{
protected:
    GameLose();
    virtual ~GameLose();
    virtual bool init() ;
public:

    static GameLose* create();


};

#endif /* defined(__MazeJump__GameLose__) */
