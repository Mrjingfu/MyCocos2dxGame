//
//  ItemPopupUI.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/26.
//
//

#ifndef EquipItemPopupUI_hpp
#define EquipItemPopupUI_hpp
#include "PopupUILayer.h"


class EquipItemPopupUI : public PopupUILayer{
    
    EquipItemPopupUI();
public:
    CREATE_FUNC(EquipItemPopupUI);
    virtual bool init();
    virtual bool addEvents();
    void updateItemPopup(int itemId);
    virtual ~EquipItemPopupUI();
private:
    void onClickDiscard(Ref* ref);
    void onClickEquip(Ref* ref);
    void displayFrame();
    void itemProperty();
private:
    
    cocos2d::ui::ImageView* m_pItemIcon;
    cocos2d::ui::Text*   m_pItemName;
    cocos2d::ui::Text*   m_pItemlv;
    cocos2d::ui::Text*   m_pItemDesc;
    cocos2d::ui::Text*   m_pItemCount;
    
    cocos2d::ui::Text*  m_pItemType;
    cocos2d::ui::Text*  m_pItemValueNum;
    cocos2d::ui::Text*  m_pItemHp;
    cocos2d::ui::Text*  m_pItemMp;
    cocos2d::ui::Text*  m_pItemLightDis;
    cocos2d::ui::Text*  m_pItemSearchDis;
    cocos2d::ui::Text*  m_pItemMargicFind;
    cocos2d::ui::Text*  m_pItemCriticalStrike;
    cocos2d::ui::Text*  m_pItemBlock;
    cocos2d::ui::Text*  m_pItemDodge;
    
    cocos2d::ui::Button* m_pBtnDiscard;
    cocos2d::ui::Button* m_pBtnEquip;
    
    cocos2d::ui::Layout* m_pBtnItemFrame;
    cocos2d::ui::Layout* m_pPropFrame;
    cocos2d::ui::Layout* m_pDescItemFrame;
    
    
    cocos2d::ui::ImageView* m_pBackGround;
    int m_nItemId;
};

#endif /* EquipItemPopupUI_hpp */
