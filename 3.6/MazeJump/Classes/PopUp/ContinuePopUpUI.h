//
//  ContinuePopUpUI.h
//  MazeJump
//
//
//

#ifndef __MazeJump__ContinuePopUpUI__
#define __MazeJump__ContinuePopUpUI__

#include "cocos2d.h"
#include "BasePopUpUI.h"
class ContinuePopUpUI : public BasePopUpUI
{
protected:
    ContinuePopUpUI();
    virtual ~ContinuePopUpUI();
    virtual bool init() ;
public:
    virtual void onEnter();
    virtual void onExit();
    static ContinuePopUpUI* create();
    void onContinueGame(Ref* ref);
    void onHideEndPopUp();
    
};

#endif /* defined(__MazeJump__ContinuePopUpUI__) */
