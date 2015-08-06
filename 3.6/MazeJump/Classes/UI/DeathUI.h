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
class DeathUI : public BasePopUpUI
{
protected:
    DeathUI();
    virtual ~DeathUI();
    virtual bool init() ;
public:
    virtual void onEnter();
    virtual void onExit();
    static DeathUI* create();


};

#endif /* defined(__MazeJump__DeathUI__) */
