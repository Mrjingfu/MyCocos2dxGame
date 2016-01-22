//
//  Discardlayer.hpp
//  lichuang
//
//  Created by lichuang on 2016/01/07.
//
//

#ifndef Discardlayer_hpp
#define Discardlayer_hpp

#include "PopupUILayer.h"

class DiscardPopupUI : public PopupUILayer
{   
public:
    DiscardPopupUI();
    virtual ~DiscardPopupUI();
    
    CREATE_FUNC(DiscardPopupUI);
    
    virtual bool initUi() override;
    virtual bool addEvents() override;
    void refreshUIView() override;
    void setDiscardItem(int itemId) ;
private:
    void onClickOk(Ref* ref);
    void onClickCancel(Ref* ref);
    void sliderEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
protected:
    
    cocos2d::ui::ImageView * m_pItemIcon;
    cocos2d::ui::Button * m_pOk;;
    cocos2d::ui::Button * m_pCancel;
    cocos2d::ui::TextBMFont * m_pCountText;
    cocos2d::ui::Slider*     m_pItemSlider;
    int m_nItemId;
};

#endif /* Discardlayer_hpp */

