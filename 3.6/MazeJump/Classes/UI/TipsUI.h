//
//  TipsUI.h
//  MazeJump
//
//
//

#ifndef __MazeJump__TipsUI__
#define __MazeJump__TipsUI__

#include "cocos2d.h"
#include "BasePopUpUI.h"
class TipsUI : public BasePopUpUI
{
public:
    typedef enum {
        TIP_GOLD = 0,
        TIP_HEART,
    } TipsType;
    virtual void onEnter();
    virtual void onExit();
    static TipsUI* create(TipsType type);
protected:
    TipsUI(TipsType type);
    virtual ~TipsUI();
    virtual bool init() ;
    cocos2d::ui::Text* tipsTv;
    TipsType m_tipType;
    void onOk(Ref* ref);
    void onCancel(Ref* ref);
    void onhideEndPopup();

    
};

#endif /* defined(__MazeJump__TipsUI__) */
