//
//  BaseUI.h
//  MazeJump
//
//
//

#ifndef __MazeJump__BaseUI__
#define __MazeJump__BaseUI__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
class BaseUI : public cocos2d::ui::Layout
{
protected:
    BaseUI();
    virtual ~BaseUI();
public:
	virtual void onEnter();
	virtual void onExit();
    void setShowDilog(bool isShowDialog){m_isShowDialog = isShowDialog;};
    bool isShowDialog(){return m_isShowDialog;};
protected:
    cocos2d::Layer* m_uiLayer;
    cocos2d::Layer* m_maskLayer;
    cocos2d::Layer* m_dialogLayer;
    bool m_isShowDialog;

    
};

#endif /* defined(__MazeJump__BaseUI__) */
