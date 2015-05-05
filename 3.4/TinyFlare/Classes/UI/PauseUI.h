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
    void pressStardustDropLevelAddBtn(Ref* p,TouchEventType eventType);
    void pressItemDropLevelAddBtn(Ref* p,TouchEventType eventType);
    void pressItemEffectLevelAddBtn(Ref* p,TouchEventType eventType);
    void pressRankBtn(Ref* p,TouchEventType eventType);
    void pressRemoveADSBtn(Ref* p,TouchEventType eventType);
    void pressHelpBtn(Ref* p,TouchEventType eventType);
    void pressBackBtn(Ref* p,TouchEventType eventType);
    
    void updateUI();
private:
    //cocos2d::ui::Button*     m_pRankBtn;
    cocos2d::ui::Button*     m_pRemoveADSBtn;
    cocos2d::ui::Button*     m_pHelpBtn;
    cocos2d::ui::Button*     m_pBackBtn;
    
    cocos2d::ui::Text*          m_pStardustDropLevelText;
    cocos2d::ui::ImageView*     m_pStardustDropLevel1;
    cocos2d::ui::ImageView*     m_pStardustDropLevel2;
    cocos2d::ui::ImageView*     m_pStardustDropLevel3;
    cocos2d::ui::ImageView*     m_pStardustDropLevel4;
    cocos2d::ui::ImageView*     m_pStardustDropLevel5;
    cocos2d::ui::Button*        m_pStardustDropLevelAdd;
    
    cocos2d::ui::Text*          m_pItemDropLevelText;
    cocos2d::ui::ImageView*     m_pItemDropLevel1;
    cocos2d::ui::ImageView*     m_pItemDropLevel2;
    cocos2d::ui::ImageView*     m_pItemDropLevel3;
    cocos2d::ui::ImageView*     m_pItemDropLevel4;
    cocos2d::ui::ImageView*     m_pItemDropLevel5;
    cocos2d::ui::Button*        m_pItemDropLevelAdd;
    
    cocos2d::ui::Text*          m_pItemEffectLevelText;
    cocos2d::ui::ImageView*     m_pItemEffectLevel1;
    cocos2d::ui::ImageView*     m_pItemEffectLevel2;
    cocos2d::ui::ImageView*     m_pItemEffectLevel3;
    cocos2d::ui::ImageView*     m_pItemEffectLevel4;
    cocos2d::ui::ImageView*     m_pItemEffectLevel5;
    cocos2d::ui::Button*        m_pItemEffectLevelAdd;
    
    
    cocos2d::ui::ImageView*     m_pPanelBg;
    cocos2d::ui::Text*          m_pPlayText;
};

#endif /* defined(__TinyFlare__PauseUI__) */
