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
    virtual bool initBottom();
    virtual void refreshUIView() override;
    virtual void setItemId(int itemId);
    virtual void updateItemAttrUI();//更新道具属性UI
    virtual void updateEquipItem();//更新武器道具UI
    virtual void updateUseItem();//更新使用道具UI
    virtual ~ItemPopupUI();
protected:
    virtual void closePopup() override;
    virtual void addBottomUI();//添加底部UI,如按钮等
    virtual void addMoneyUI();//添加价格UI
    virtual void updateItemBaseProp();//更新道具基础属性UI
    void updateItemPopupSize(cocos2d::Size addSize);
    virtual PickableItemProperty* getItemIdProperty()const;
    void addItemProp(std::string propStr,cocos2d::Color3B fontColor=cocos2d::Color3B::WHITE,cocos2d::ui::LinearLayoutParameter* parmLayout = nullptr);
    virtual void onClickDiscard(Ref* ref);
    virtual void onClickEquip(Ref* ref);
    virtual void onClickUser(Ref* ref);
    virtual void onClickIdentified(Ref* ref);
    virtual void IdentifyEquiipFrame();//添加装备鉴定属性UI
    virtual void useItemFrame();//添加使用道具UI
    std::string  getBossName() const;
    void testUI();
    
protected:
    
    cocos2d::ui::ImageView* m_pItemIcon;
    cocos2d::ui::Text*   m_pItemName;
    cocos2d::ui::Text*   m_pItemlv;
    cocos2d::ui::Text*   m_pItemEquipDist;
    cocos2d::ui::Text*   m_pItemNotIden;
    NoteUi*   m_pItemDesc;

    cocos2d::ui::Text*  m_pItemType;               //类型
    cocos2d::ui::Text*  m_pItemIdentifyDesc;
    cocos2d::ui::Layout* m_pAttrFrame;
    cocos2d::ui::Layout* m_pItemPropFrame;
    cocos2d::ui::ImageView* m_pBackGround;

    ItemMoneyLayer* m_pItemMoneyLayer;
    
    cocos2d::ui::Layout* m_pBottomFrame;
    cocos2d::ui::Button* m_pBtnDiscard;
    cocos2d::ui::Button* m_pBtnEquip;
    int m_nItemId;
};

#endif /* EquipItemPopupUI_hpp */
