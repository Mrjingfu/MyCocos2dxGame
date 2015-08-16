//
//  GroundLosePopUpUI.h
//  MazeJump
//
//
//

#ifndef __MazeJump__GroundLosePopUpUI__
#define __MazeJump__GroundLosePopUpUI__

#include "cocos2d.h"
#include "BasePopUpUI.h"
class GroundLosePopUpUI : public BasePopUpUI
{
protected:
    GroundLosePopUpUI();
    virtual ~GroundLosePopUpUI();
    virtual bool init() ;
    void onBack(Ref* ref);
    void onHidePopUpEnd();
    void onHelpRecover(Ref* ref);
public:
    virtual void onEnter() override;
    virtual void onExit() override;
    static GroundLosePopUpUI* create();


};

#endif /* defined(__MazeJump__GameLose__) */
