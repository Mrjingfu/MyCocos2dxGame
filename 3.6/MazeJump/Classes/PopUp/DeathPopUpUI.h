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

private:
    void onHome(Ref* ref);
    void onShop(Ref* ref);
    void onAgiain(Ref* ref);
    void onRevive(Ref* ref);
};

#endif /* defined(__MazeJump__DeathPopUpUI__) */
