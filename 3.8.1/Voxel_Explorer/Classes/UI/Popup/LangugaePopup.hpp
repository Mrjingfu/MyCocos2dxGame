//
//  LangugaePopup.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 16/3/9.
//
//

#ifndef LangugaePopup_hpp
#define LangugaePopup_hpp

#include "PopupUILayer.h"

class LangugaePopup : public PopupUILayer{
    
    LangugaePopup();
public:
    CREATE_FUNC(LangugaePopup);
    virtual ~LangugaePopup();
    bool initUi() override;
    bool addEvents() override;
    void refreshUIView() override;
private:
    void onSelectRadioZh(cocos2d::ui::RadioButton* radioButton, cocos2d::ui::RadioButton::EventType);
    void onSelectRadioEn(cocos2d::ui::RadioButton* radioButton, cocos2d::ui::RadioButton::EventType);
    void swtichToLogoScene();
private:
    cocos2d::ui::RadioButtonGroup* m_pRadioGroup;
};

#endif /* LangugaePopup_hpp */
