//
//  ContinueUI.h
//  MazeJump
//
//
//

#ifndef __MazeJump__ContinueUI__
#define __MazeJump__ContinueUI__

#include "cocos2d.h"
#include "BasePopUpUI.h"
class ContinueUI : public BasePopUpUI
{
protected:
    ContinueUI();
    virtual ~ContinueUI();
    virtual bool init() ;
public:
    virtual void onEnter();
    virtual void onExit();
    static ContinueUI* create();
    void onContinueGame(Ref* ref);
    void onHideEndPopUp();
    
};

#endif /* defined(__MazeJump__ContinueUI__) */
