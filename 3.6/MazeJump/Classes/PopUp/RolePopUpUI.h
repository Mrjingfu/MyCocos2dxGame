//
//  PausePopUpUI.h
//  MazeJump
//
//
//

#ifndef __MazeJump__RolePopUpUI__
#define __MazeJump__RolePopUpUI__

#include "cocos2d.h"
#include "BasePopUpUI.h"

class RoleItem :public cocos2d::ui::Layout
{
public:
    static RoleItem* create(std::string _roleId,int preice,std::string _roleImg,std::string _rolModel,bool _isLock,std::string _roleSound);
    bool getIsLock(){return m_isLock;};
    void setLock(bool _isLock);
    int getPrice(){return m_price;}
    std::string getRoleId(){return m_roleId;}
    virtual bool init(std::string _roleId,int preice,std::string _roleImg,std::string _rolModel,bool _isLock,std::string _roleSound);
protected:
    RoleItem();
    ~RoleItem();
private:
    std::string m_roleId;
    std::string m_roleModel;
    std::string m_roleSound;
    bool m_isLock;
    int  m_price;
    cocos2d::ui::ImageView* m_itemNormalImg;
    cocos2d::ui::ImageView* m_itemLockImg;
};

class RolePopUpUI : public BasePopUpUI
{
protected:
    RolePopUpUI();
    virtual ~RolePopUpUI();
    cocos2d::Label* m_lockTv;
    cocos2d::Layer* m_lockLayer;
    RoleItem* m_currentRoleItem;
    bool m_isShowLockBtn;
    bool m_isNowShowLockBtn;
public:
    virtual bool init() ;
    virtual void onEnter();
    virtual void onExit();
    void onBack(Ref* Ref);
    void onLock(Ref* ref);
    void selectedItemEvent(cocos2d::Ref* sender, cocos2d::ui::ListView::EventType type);
    static RolePopUpUI* create();
    void showLockButton(int price);
    void hideLockButton(const std::function<void()> &endfunc = nullptr);
    void onHideLockEnd();
    void onShowLockEnd();
    void onHideShowLockCall(int price);
};

#endif /* defined(__MazeJump__RolePopUpUI__) */
