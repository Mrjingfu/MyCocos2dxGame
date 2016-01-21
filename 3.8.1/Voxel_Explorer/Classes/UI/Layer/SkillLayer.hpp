//
//  Skilllayer.hpp
//  lichuang
//
//  Created by lichuang on 2016/01/13.
//
//

#ifndef SkillLayer_hpp
#define SkillLayer_hpp

#include "WrapperUILayer.h"

class SkillLayer : public WrapperUILayer
{   
public:
    SkillLayer();
    virtual ~SkillLayer();
    
    CREATE_FUNC(SkillLayer);
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual bool initUi() override;
    virtual bool addEvents() override;
    virtual void refreshUIView() override;
    virtual void refreshSkillView(bool isRloadEquip = false);
private:
    void onTouchBlood(Ref*,Widget::TouchEventType);
    void onTouchMagic(Ref*,Widget::TouchEventType);
    void onTouchSkill(Ref*,Widget::TouchEventType);
    void skillProgressAction();
    void bloodProgressAction();
    void magicProgressAction();
    
    void onEventRoleUserPotion(cocos2d::EventCustom *sender);//使用药水物品
    
protected:

    cocos2d::ui::ImageView * m_pSkill;
    cocos2d::ui::ImageView * m_pMagicPotion;
    cocos2d::ui::ImageView * m_pBloodPotion;
    cocos2d::ui::ImageView * m_pMagicPotionMask;
    cocos2d::ui::ImageView * m_pBloodPotionMask;
    cocos2d::ProgressTimer * m_pMagicProgress;
    cocos2d::ProgressTimer * m_pBloodProgress;
    cocos2d::ProgressTimer*  m_pSkillProgress;
    float m_fCoolTime;
    bool m_bIsUseSkill;
    int m_nMagicPotionId;
    int m_nBloodPotionId;
    bool m_bIsRloadEquip;
    bool m_bIsUseBloodPotion;
    bool m_bIsUseMagicPotion;
};

#endif /* SkillLayer_hpp */

