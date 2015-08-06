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

class PopUpAnimCustomListener
{
public:
    virtual void onShowCustoom() = 0;
    virtual void onHideCustoom() = 0;
};


class BasePopUpUI : public cocos2d::ui::Layout
{
protected:
    BasePopUpUI();
    virtual ~BasePopUpUI();
public:
	virtual void onEnter();
	virtual void onExit();
    void showPopUp( cocos2d::Node* layout,PopUpAnimCustomListener* listener = nullptr,const std::function<void()> &func = nullptr);
    void hidePopUp(const std::function<void()> &func = nullptr);
    void setPopUpPosition(cocos2d::Vec2 pt);
    cocos2d::Node* getParent(){return m_parent;};
    cocos2d::Layer* getPopUpLayer(){return  m_dialogLayer;};
    void removePopUp();
protected:
    
    cocos2d::Layer* m_maskLayer;
    cocos2d::Layer* m_dialogLayer;
    cocos2d::Node* m_parent;
    bool m_isShowDialog;
    PopUpAnimCustomListener* m_Listener;

    
};

#endif /* defined(__MazeJump__BasePopUpUI__) */
