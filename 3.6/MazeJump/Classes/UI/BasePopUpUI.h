//
//  BasePopUpUI.h
//  MazeJump
//
//
//

#ifndef __MazeJump__BasePopUpUI__
#define __MazeJump__BasePopUpUI__

#include "cocos2d.h"
#include "ui/CocosGUI.h"


class GameInfoUI;
class BasePopUpUI : public cocos2d::Layer
{
protected:
    BasePopUpUI();
    virtual ~BasePopUpUI();
public:
    typedef enum {
        POPUP_VERTICAL = 0,
        POPUP_HORIZONTAL = 1,
    } Popup_Show;
    typedef enum {
        POPUP_START,
        POPUP_SHOP,
        POPUP_CONTINUE,
        POPUP_GLOD_NOT_ENOUGT,
        POPUP_HEART_NOT_ENOUGT,
        POPUP_UNKOWN
    } PopUp_UI;
    
    virtual void onEnter() override;
    virtual void onExit() override;
    void showPopUp(bool isPlayAn,cocos2d::Vec2 = cocos2d::Vec2::ZERO,Popup_Show popupShow = POPUP_VERTICAL,const std::function<void()> &endfunc = nullptr);
    void setShowMaskBg(bool isShowMaskBg);
    void hidePopUp(const std::function<void()> &endfunc = nullptr);
    void setPopUpId(PopUp_UI popId){m_popUpUiId = popId;};
    PopUp_UI getPopUpId(){return m_popUpUiId;};
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) override;
protected:
    cocos2d::Layer* m_maskLayer;
    cocos2d::Layer* m_dialogLayer;
    cocos2d::Layer* m_maskLayerBg;
    Popup_Show m_popupShow;
    PopUp_UI m_popUpUiId;
    bool m_isShowDialog;
    bool m_isPlayAn;
    cocos2d::Vec2 m_pt;
    void onHidePopUpEnd();
};

#endif /* defined(__MazeJump__BasePopUpUI__) */
