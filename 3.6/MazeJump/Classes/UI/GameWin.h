//
//  GameWin.h
//  MazeJump
//
//
//

#ifndef __MazeJump__GameWin__
#define __MazeJump__GameWin__

#include "cocos2d.h"
#include "BaseUI.h"
class GameWin : public BaseUI
{
protected:
    GameWin();
    virtual ~GameWin();
    virtual bool init() ;
public:
    virtual void onEnter();
    virtual void onExit();
    static GameWin* create();


};

#endif /* defined(__MazeJump__GameWin__) */
