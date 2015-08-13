//
//  TipsPopUpUI.h
//  MazeJump
//
//
//

#ifndef __MazeJump__TipsPopUpUI__
#define __MazeJump__TipsPopUpUI__

#include "cocos2d.h"
#include "BasePopUpUI.h"
class TipsPopUpUI : public BasePopUpUI
{
public:
    typedef enum {
        TIP_GOLD = 0,
        TIP_HEART,
    } TipsType;
    virtual void onEnter();
    virtual void onExit();
    static TipsPopUpUI* create(TipsType type);
protected:
    TipsPopUpUI(TipsType type);
    virtual ~TipsPopUpUI();
    virtual bool init() ;
    cocos2d::ui::Text* tipsTv;
    TipsType m_tipType;
    void onOk(Ref* ref);
    void onCancel(Ref* ref);
    void onhideEndPopup();

    
};

#endif /* defined(__MazeJump__TipsPopUpUI__) */
