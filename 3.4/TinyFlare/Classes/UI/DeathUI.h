//
//  DeathUI.h
//  TinyFlare
//
//  Created by wang haibo on 15/4/27.
//
//

#ifndef __TinyFlare__DeathUI__
#define __TinyFlare__DeathUI__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
class DeathUI : public cocos2d::ui::Layout
{
protected:
    DeathUI();
    virtual ~DeathUI();
    virtual bool init() override;
public:
    static DeathUI* create();
private:
    void pressContinueGameBtn(Ref* p,TouchEventType eventType);
    void pressRemoveADSBtn(Ref* p,TouchEventType eventType);
//    void pressRankBtn(Ref* p,TouchEventType eventType);
//    void pressShareBtn(Ref* p,TouchEventType eventType);
    void pressBackBtn(Ref* p,TouchEventType eventType);
    
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *unused_event);
    
    virtual void updateGoodBalance(cocos2d::EventCustom *event);
private:
    cocos2d::ui::Button*     m_pPlayGameBtn;
    cocos2d::ui::Button*     m_pRemoveADSBtn;
//    cocos2d::ui::Button*     m_pRankBtn;
//    cocos2d::ui::Button*     m_pShareBtn;
    cocos2d::ui::Button*     m_pBackBtn;
    
    cocos2d::ui::ImageView*     m_pMenuBg;
    cocos2d::ui::Text*          m_pGameTitle;
    cocos2d::ui::Text*          m_pPlayText;
    
    cocos2d::EventListener *goodBalanceChangedHandler;
};

#endif /* defined(__TinyFlare__DeathUI__) */
