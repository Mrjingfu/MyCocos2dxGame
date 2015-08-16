//
//  GroundRecordPopUpUI.h
//  MazeJump
//
//
//

#ifndef __MazeJump__GroundRecordPopUpUI__
#define __MazeJump__GroundRecordPopUpUI__

#include "cocos2d.h"
#include "BasePopUpUI.h"
class GroundRecordPopUpUI : public BasePopUpUI
{
protected:
    GroundRecordPopUpUI();
    virtual ~GroundRecordPopUpUI();
    virtual bool init() ;
    void onBack(Ref* ref);
    void onHidePopUpEnd();
public:
    virtual void onEnter() override;
    virtual void onExit() override;
    static GroundRecordPopUpUI* create();


};

#endif /* defined(__MazeJump__GroundRecordPopUpUI__) */
