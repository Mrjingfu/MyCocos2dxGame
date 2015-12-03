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
#include "PickableItemProperty.hpp"
class ItemMoneyLayer;
class NoteUi;
class CChaosNumber;
class ItemPopupUI : public PopupUILayer{
protected:
    ItemPopupUI();
public:
    CREATE_FUNC(ItemPopupUI);
    virtual bool initUi() override;
    virtual bool addEvents() override;
    virtual void updateItemPopup(int itemId);
    virtual ~ItemPopupUI();
protected:
    virtual void closePopup() override;
    virtual PickableItemProperty* getItemIdProperty()const;
    virtual void initButtonFrame();
    void addItemProp(std::string propStr,cocos2d::Color3B fontColor=cocos2d::Color3B::WHITE,cocos2d::ui::LinearLayoutParameter* parmLayout = nullptr);
   
    void noEquipFrame(bool isEquip);//不可装备对话框 isEquip 是否显示装备按钮
private:
   
    void onClickDiscard(Ref* ref);
    void onClickEquip(Ref* ref);
    void onClickUser(Ref* ref);
    void IdentifyEquiipFrame();
    void itemFrame();

    
protected:
    
    cocos2d::ui::ImageView* m_pItemIcon;
    cocos2d::ui::Text*   m_pItemName;
    cocos2d::ui::Text*   m_pItemlv;
    cocos2d::ui::Text*   m_pItemEquipDist;
    cocos2d::ui::Text*   m_pItemNotIden;
    NoteUi*   m_pItemDesc;

    cocos2d::ui::Text*  m_pItemType;               //类型
    cocos2d::ui::Text*  m_pItemIdentifyDesc;
    cocos2d::ui::Button* m_pBtnDiscard;
    cocos2d::ui::Button* m_pBtnEquip;
    cocos2d::ui::Layout* m_pAttrFrame;
    cocos2d::ui::Layout* m_pItemPropFrame;
    cocos2d::ui::Layout* m_pButtonFrame;
    cocos2d::ui::ImageView* m_pBackGround;
    ItemMoneyLayer* m_pItemMoneyLayer;
    int m_nItemId;
};

#endif /* EquipItemPopupUI_hpp */
