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
class NoteUi;

class ItemPopupUI : public PopupUILayer{
    
    ItemPopupUI();
public:
    CREATE_FUNC(ItemPopupUI);
    virtual bool init();
    virtual bool addEvents();
    void updateItemPopup(int itemId);
    virtual ~ItemPopupUI();
private:
    virtual void closePopup();
    void onClickDiscard(Ref* ref);
    void onClickEquip(Ref* ref);
    void onClickUser(Ref* ref);
    void IdentifyEquiipFrame();
    void itemFrame();
    //不可装备对话框 isEquip 是否显示装备按钮
    void noEquipFrame(bool isEquip);
    
private:
    
    cocos2d::ui::ImageView* m_pItemIcon;
    cocos2d::ui::Text*   m_pItemName;
    cocos2d::ui::Text*   m_pItemlv;
    cocos2d::ui::Text*   m_pItemEquipDist;
    cocos2d::ui::Text*   m_pItemNotIden;
    NoteUi*   m_pItemDesc;

    cocos2d::ui::Text*  m_pItemType;               //类型
    cocos2d::ui::Text*  m_pItemGoldNum;            // 金币
    cocos2d::ui::Text*  m_pItemSilverNum;          // 银币
    cocos2d::ui::Text*  m_pItemCopperNum;          // 铜币
    cocos2d::ui::ImageView* m_pItemGoldIcon;
    cocos2d::ui::ImageView* m_pItemSilverIcon;
    cocos2d::ui::ImageView* m_pItemCopperIcon;
    cocos2d::ui::Text*  m_pItemIdentifyDesc;    
    
    NoteUi*  m_pItemBasicAtk;           //基础攻击力
    NoteUi*  m_pItemBasicDef;           //基础防御力
    NoteUi*  m_pItemHp;                 //Hp
    NoteUi*  m_pItemMp;                 //MP
    NoteUi*  m_pItemLightDis;           //光照范围
    NoteUi*  m_pItemSearchDis;          //搜索范围
    NoteUi*  m_pItemMargicFind;         //取魔率
    NoteUi*  m_pItemCriticalStrike;     //暴击率
    NoteUi*  m_pItemBlock;              //格挡率
    NoteUi*  m_pItemDodge;              //闪避率
    NoteUi*  m_pItemMinHurt;            //最小伤害
    NoteUi*  m_pItemMaxHurt;            //最大伤害
    
    cocos2d::ui::Button* m_pBtnDiscard;
    cocos2d::ui::Button* m_pBtnEquip;
    
    cocos2d::ui::Layout* m_pAttrFrame;
    cocos2d::ui::Layout* m_pMoneyFrame;
    cocos2d::ui::Layout* m_pItemPropFrame;
    
    cocos2d::ui::ImageView* m_pBackGround;
    int m_nItemId;
};

#endif /* EquipItemPopupUI_hpp */
