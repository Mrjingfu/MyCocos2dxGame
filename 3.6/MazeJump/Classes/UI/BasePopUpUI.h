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
        POPUP_UNKOWN
    } PopUp_UI;
    
    void showPopUp(Popup_Show popupShow = POPUP_VERTICAL,const std::function<void()> &func = nullptr);
    void hidePopUp(const std::function<void()> &func = nullptr);
    void setPopUpId(PopUp_UI popId){m_popUpUiId = popId;};
    PopUp_UI getPopUpId(){return m_popUpUiId;};

protected:
    
    Popup_Show m_popupShow;
    PopUp_UI m_popUpUiId;
};

#endif /* defined(__MazeJump__BasePopUpUI__) */
