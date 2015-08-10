//
//  GameWin.h
//  MazeJump
//
//
//

#ifndef __MazeJump__GameWin__
#define __MazeJump__GameWin__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
class GameWin : public cocos2d::Layer
{
protected:
    GameWin();
    virtual ~GameWin();
    virtual bool init() ;
public:

    static GameWin* create();


};

#endif /* defined(__MazeJump__GameWin__) */
