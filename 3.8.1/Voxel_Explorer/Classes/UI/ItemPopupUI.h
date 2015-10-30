//
//  ItemPopupUI.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/26.
//
//

#ifndef ItemPopupUI_hpp
#define ItemPopupUI_hpp
#include "PopupUILayer.h"

class ItemPopupUI : public PopupUILayer{
    
    ItemPopupUI();
public:
    CREATE_FUNC(ItemPopupUI);
    virtual bool init();
    virtual bool addEvents();
    void updateItemPopup(int itemId);
    virtual ~ItemPopupUI();
private:
    void onClickDrop(Ref* ref);
    void onClickThrow(Ref* ref);
    void onClickEquip(Ref* ref);
    void notifyRolePopup();
private:
    
    cocos2d::ui::ImageView* m_pItemIcon;
    cocos2d::ui::Text*   m_pItemName;
    cocos2d::ui::Text*   m_pItemlv;
    cocos2d::ui::Text*   m_pItemDesc;
    cocos2d::ui::Button* m_pBtnDrop;
    cocos2d::ui::Button* m_pBtnThrow;
    cocos2d::ui::Button* m_pBtnEquip;
    int m_nItemId;
};

#endif /* ItemPopupUI_hpp */
