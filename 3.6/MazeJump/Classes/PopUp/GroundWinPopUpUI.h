//
//  GroundWinPopUpUI.h
//  MazeJump
//
//
//

#ifndef __MazeJump__GroundWinPopUpUI__
#define __MazeJump__GroundWinPopUpUI__

#include "cocos2d.h"
#include "BasePopUpUI.h"
class GroundWinPopUpUI : public BasePopUpUI
{
protected:
    GroundWinPopUpUI();
    virtual ~GroundWinPopUpUI();
    virtual bool init() ;
public:
    virtual void onEnter() override;
    virtual void onExit() override;
    static GroundWinPopUpUI* create();


};

#endif /* defined(__MazeJump__GroundWinPopUpUI__) */
