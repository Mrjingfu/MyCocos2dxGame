//
//  PausePopUpUI.h
//  MazeJump
//
//
//

#ifndef __MazeJump__PausePopUpUI__
#define __MazeJump__PausePopUpUI__

#include "cocos2d.h"
#include "BasePopUpUI.h"
class PausePopUpUI : public BasePopUpUI
{
protected:
    PausePopUpUI();
    virtual ~PausePopUpUI();
    virtual bool init() ;
public:
    virtual void onEnter();
    virtual void onExit();
    static PausePopUpUI* create();

    void onHome(Ref* ref);
    void onShop(Ref* ref);
    void onContinue(Ref* ref);

};

#endif /* defined(__MazeJump__PausePopUpUI__) */
