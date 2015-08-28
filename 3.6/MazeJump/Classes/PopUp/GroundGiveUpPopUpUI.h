//
//  GroundGiveUpPopUpUI.h
//  MazeJump
//
//
//

#ifndef __MazeJump__GroundGiveUpPopUpUI__
#define __MazeJump__GroundGiveUpPopUpUI__

#include "cocos2d.h"
#include "BasePopUpUI.h"
class GroundGiveUpPopUpUI : public BasePopUpUI
{
protected:
    GroundGiveUpPopUpUI();
    virtual ~GroundGiveUpPopUpUI();
    virtual bool init() ;
    void onBack(Ref* ref);
    void onOK(Ref* ref);
public:
    virtual void onEnter() override;
    virtual void onExit() override;
    static GroundGiveUpPopUpUI* create();


};

#endif /* defined(__MazeJump__GroundGiveUpPopUpUI__) */
