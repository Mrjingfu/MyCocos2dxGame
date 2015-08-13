//
//  DeathUI.h
//  MazeJump
//
//
//

#ifndef __MazeJump__DeathUI__
#define __MazeJump__DeathUI__

#include "cocos2d.h"
#include "BasePopUpUI.h"
class DeathPopUpUI : public BasePopUpUI
{
protected:
    DeathPopUpUI();
    virtual ~DeathPopUpUI();
    virtual bool init() ;
public:
    virtual void onEnter();
    virtual void onExit();
    static DeathPopUpUI* create();


};

#endif /* defined(__MazeJump__DeathPopUpUI__) */
