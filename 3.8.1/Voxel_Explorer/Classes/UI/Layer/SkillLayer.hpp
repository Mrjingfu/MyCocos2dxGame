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
    
    virtual bool initUi() override;
    virtual bool addEvents() override;
    virtual void refreshUIView() override;
    virtual void refreshSkillView();
private:
    void onTouchBlood(Ref*,Widget::TouchEventType);
    void onTouchMagic(Ref*,Widget::TouchEventType);
    void onTouchSkill(Ref*,Widget::TouchEventType);
    void skillProgressAction();
protected:

    cocos2d::ui::ImageView * m_pSkill;
    cocos2d::ui::ImageView * m_pMagicPotion;
    cocos2d::ui::ImageView * m_pBloodPotion;
    cocos2d::ui::ImageView * m_pMagicPotionMask;
    cocos2d::ui::ImageView * m_pBloodPotionMask;
    cocos2d::ProgressTimer*  m_pSkillProgress;
    float m_fCoolTime;
    bool m_bIsUseSkill;
    int m_nMagicPotionId;
    int m_nBloodPotionId;
};

#endif /* SkillLayer_hpp */

