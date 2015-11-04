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
    void onClickDiscard(Ref* ref);
    void onClickUser(Ref* ref);


private:
    
    cocos2d::ui::ImageView* m_pItemIcon;
    cocos2d::ui::Text*   m_pItemName;
    cocos2d::ui::Text*   m_pItemlv;
    cocos2d::ui::Text*   m_pItemDesc;
    cocos2d::ui::Text*   m_pItemCount;
    cocos2d::ui::Text*   m_pItemType;
    cocos2d::ui::Text*   m_pItemValueNum;

    cocos2d::ui::Button* m_pBtnDiscard;
    cocos2d::ui::Button* m_pBtnUse;

    cocos2d::ui::Layout* m_pBtnItemFrame;
    cocos2d::ui::Layout* m_pPropFrame;
    cocos2d::ui::Layout* m_pDescItemFrame;
    

    cocos2d::ui::ImageView* m_pBackGround;
    int m_nItemId;
};

#endif /* ItemPopupUI_hpp */
