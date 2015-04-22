//
//  PauseUI.h
//  TinyFlare
//
//  Created by wang haibo on 15/4/22.
//
//

#ifndef __TinyFlare__PauseUI__
#define __TinyFlare__PauseUI__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
class PauseUI : public cocos2d::ui::Layout
{
protected:
    PauseUI();
    virtual ~PauseUI();
    virtual bool init() override;
public:
    static PauseUI* create();
    void beginToPause();
    void endToPause();
private:
    void pressRankBtn(Ref* p,TouchEventType eventType);
    void pressRemoveADSBtn(Ref* p,TouchEventType eventType);
    void pressHelpBtn(Ref* p,TouchEventType eventType);
    void pressBackBtn(Ref* p,TouchEventType eventType);
private:
    cocos2d::ui::Button*     m_pRankBtn;
    cocos2d::ui::Button*     m_pRemoveADSBtn;
    cocos2d::ui::Button*     m_pHelpBtn;
    cocos2d::ui::Button*     m_pBackBtn;
    
    
    cocos2d::ui::ImageView*     m_pPanelBg;
    cocos2d::ui::Text*          m_pPlayText;
};

#endif /* defined(__TinyFlare__PauseUI__) */
