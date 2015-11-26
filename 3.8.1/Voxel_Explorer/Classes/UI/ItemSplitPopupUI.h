//
//  ItemSplitPopupUI.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/26.
//
//

#ifndef ItemSplitPopupUI_hpp
#define ItemSplitPopupUI_hpp

#include "PopupUILayer.h"

class ItemSplitPopupUI: public PopupUILayer{
    ItemSplitPopupUI();
    
public:
    CREATE_FUNC(ItemSplitPopupUI);
    virtual ~ItemSplitPopupUI();
    virtual bool initUi() override;
    virtual bool addEvents() override;
    void updateItemSplit(int itemId,int count );
    
private:
    void onClickOk(Ref* ref);
     void sliderEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
private:
    cocos2d::ui::Button*     m_pBtnOk;
    cocos2d::ui::Slider*     m_pSlider;
    cocos2d::ui::ImageView*  m_pIcon;
    cocos2d::ui::Text*       m_pCount;
};

#endif /* ItemSplitPopupUI_hpp */
