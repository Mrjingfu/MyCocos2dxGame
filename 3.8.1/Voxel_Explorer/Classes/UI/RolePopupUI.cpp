//
//  RolePopUpUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/22.
//
//

#include "RolePopupUI.h"
#include "ItemUI.h"
#include "UtilityHelper.h"
#include "PlayerProperty.hpp"
#include "PopupUILayerManager.h"
#include "ItemPopupUI.h"
#include "EventConst.h"
#include "GameFormula.hpp"
#include "KeyProperty.hpp"
USING_NS_CC;
RolePopupUI::RolePopupUI()
{
    m_cActionType           = eNone;
    m_pGridView             = nullptr;
    m_pBtnClose             = nullptr;
    m_pBtnChangeBag         = nullptr;
    m_pWeaponUi             = nullptr;
    m_pArmorUi              = nullptr;
    m_pOrnamentUi           = nullptr;
    m_pSecondWeaponUi       = nullptr;
    m_pRoleHp               = nullptr;
    m_pRoleMp               = nullptr;
    m_pRoleExp              = nullptr;
    m_pRoleLightDis         = nullptr;
    m_pRoleSearchDis        = nullptr;
    m_pRoleMargicFind       = nullptr;
    m_pRoleCriticalStrike   = nullptr;
    m_pRoleBlock            = nullptr;
    m_pRoleDodge            = nullptr;
    m_pShopBtn              = nullptr;
    
}
RolePopupUI::~RolePopupUI()
{
    
}
void RolePopupUI::onEnter()
{

    EventListenerCustom *listener = EventListenerCustom::create(EVENT_PLAYER_PROPERTY_DIRTY, CC_CALLBACK_1(RolePopupUI::onEventUpdateData,this));
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);

    PopupUILayer::onEnter();
}
void RolePopupUI::onExit()
{
    Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
    PopupUILayer::onExit();
}
bool RolePopupUI::initUi()
{
    
    Node* charNode = cocos2d::CSLoader::createNode("characterLayer.csb");
    if (!charNode)
        return  false;
    charNode->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    charNode->setPosition(WINDOW_CENTER);
    m_pRootLayer->addChild(charNode);
    Layout* equipFrame = dynamic_cast<ui::Layout*>(UtilityHelper::seekNodeByName(charNode, "equip_frame"));
    if (!equipFrame)
        return false;
    Layout* gridFrame = dynamic_cast<ui::Layout*>(UtilityHelper::seekNodeByName(charNode, "grid_frame"));
    if (!gridFrame)
        return false;
    m_pBtnChangeBag = dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(charNode, "prop_btn_change_bag"));
    if (!m_pBtnChangeBag)
        return false;
    
    m_pRoleHp = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(charNode, "role_prop_hp"));
    if (!m_pRoleHp)
        return false;
    m_pRoleMp = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(charNode, "role_prop_mp"));
    if (!m_pRoleMp)
        return false;
    m_pRoleExp = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(charNode, "role_prop_exp"));
    if (!m_pRoleExp)
        return false;
    m_pRoleLightDis = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(charNode, "role_prop_light"));
    if (!m_pRoleLightDis)
        return false;
    m_pRoleSearchDis = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(charNode, "role_prop_search"));
    if (!m_pRoleSearchDis)
        return false;
    m_pRoleMargicFind = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(charNode, "role_prop_magic"));
    if (!m_pRoleMargicFind)
        return false;
    m_pRoleCriticalStrike = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(charNode, "role_prop_critical_strike"));
    if (!m_pRoleCriticalStrike)
        return false;
    m_pRoleBlock = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(charNode, "role_prop_block"));
    if (!m_pRoleBlock)
        return false;
    m_pRoleDodge = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(charNode, "role_prop_dodge"));
    if (!m_pRoleDodge)
        return false;
    m_pRoleHp->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pRoleMp->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pRoleExp->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pRoleLightDis->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pRoleSearchDis->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pRoleCriticalStrike->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pRoleMargicFind->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pRoleBlock->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pRoleDodge->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
 
    
    
    m_pRoleHp->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("ROLE_SHOW_HP").c_str(),int(PlayerProperty::getInstance()->getCurrentHP()),int(PlayerProperty::getInstance()->getMaxHP())));
    m_pRoleMp->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("ROLE_SHOW_MP").c_str(),int(PlayerProperty::getInstance()->getCurrentMP()),int(PlayerProperty::getInstance()->getMaxMP())));
    m_pRoleExp->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("ROLE_SHOW_EXP").c_str(),int(PlayerProperty::getInstance()->getExp()),int(GameFormula::getNextLevelExp(PlayerProperty::getInstance()->getLevel()))));
    m_pRoleLightDis->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_LIGHT_DIS").c_str(),int(PlayerProperty::getInstance()->getLightDistance())));
    m_pRoleSearchDis->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_SEARCH_DIS").c_str(),int(PlayerProperty::getInstance()->getSearchDistance())));
    m_pRoleCriticalStrike ->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_CRITICAL_STRIKE").c_str(),int(PlayerProperty::getInstance()->getCriticalStrikeRate())));
    m_pRoleMargicFind->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_MARGIC_FIND").c_str(),int(PlayerProperty::getInstance()->getMagicItemFindRate())));
    m_pRoleBlock->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_BLOCK").c_str(),int(PlayerProperty::getInstance()->getBlockRate())));
    m_pRoleDodge->setString(StringUtils::format(UtilityHelper::getLocalStringForUi("PROP_SHOW_DODGE").c_str(),int(PlayerProperty::getInstance()->getDodgeRate())));

    m_pBtnChangeBag->addClickEventListener(CC_CALLBACK_1(RolePopupUI::onClickChnageBag, this));
    
    
    m_pWeaponUi = ItemUI::create();
    m_pWeaponUi->setPosition(Vec2(m_pWeaponUi->getContentSize().width*0.5+8, equipFrame->getContentSize().height*0.5));
    equipFrame->addChild(m_pWeaponUi);
    
    
    m_pSecondWeaponUi = ItemUI::create();
    m_pSecondWeaponUi->setPosition(Vec2(m_pWeaponUi->getContentSize().width*0.5+8+m_pWeaponUi->getContentSize().width*1+2, equipFrame->getContentSize().height*0.5));
    equipFrame->addChild(m_pSecondWeaponUi);

    m_pArmorUi = ItemUI::create();
    m_pArmorUi->setPosition(Vec2(m_pWeaponUi->getContentSize().width*0.5+8+m_pWeaponUi->getContentSize().width*2+4, equipFrame->getContentSize().height*0.5));
    equipFrame->addChild(m_pArmorUi);
    
    m_pOrnamentUi = ItemUI::create();
    m_pOrnamentUi->setPosition(Vec2(m_pWeaponUi->getContentSize().width*0.5+8+m_pWeaponUi->getContentSize().width*3+6, equipFrame->getContentSize().height*0.5));
    equipFrame->addChild(m_pOrnamentUi);

    
    m_pShopBtn = ImageView::create("ui_shop_icon.png",TextureResType::PLIST);
    m_pShopBtn->setScale9Enabled(true);
    m_pShopBtn->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    m_pShopBtn->setContentSize(cocos2d::Size(45,45));
    m_pShopBtn->setPosition(Vec2(8+m_pWeaponUi->getContentSize().width*4+8, equipFrame->getContentSize().height*0.5));
    equipFrame->addChild(m_pShopBtn);
    
    m_pGridView = TGridView::create();
    m_pGridView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    m_pGridView->setContentSize(cocos2d::Size(gridFrame->getContentSize().width-10,gridFrame->getContentSize().height-7));
    m_pGridView->setCol(5);
    m_pGridView->setPosition(gridFrame->getContentSize()*0.5);
    m_pGridView->setScrollBarEnabled(false);
    m_pGridView->setItemsMargin(cocos2d::Size(1,3.5));
    m_pGridView->setFrameMargin(cocos2d::Size(3,4));
    m_pGridView->addEventListener(CC_CALLBACK_2(RolePopupUI::selectItemEvent, this));
    gridFrame->addChild(m_pGridView);

    
    
    m_pBtnClose = ui::Button::create("ui_btn_back_1.png","","",TextureResType::PLIST);
    m_pBtnClose->setScale9Enabled(true);
    m_pBtnClose->setPosition(Vec2(SCREEN_WIDTH*0.9, SCREEN_HEIGHT*0.95));
    m_pRootLayer->addChild(m_pBtnClose);
    m_pBtnClose->addClickEventListener(CC_CALLBACK_1(RolePopupUI::onClickColse, this));
    
    for (int j =0; j<int(PlayerProperty::getInstance()->getBagMaxSpace()); j++) {

        ItemUI* itemui = ItemUI::create();
        m_pGridView->addChild(itemui);
    }
    
    updateItems();
    
    return true;
}
void RolePopupUI::onClickChnageBag(Ref* ref)
{
    CHECK_ACTION(ref);
    for (int j =0; j<5*3; j++) {
        
        ItemUI* itemui = ItemUI::create();
        m_pGridView->pushBackCustomItem(itemui);
    }
    m_pGridView->resume();
    m_pGridView->scrollToBottom(0.8,false);
}
void RolePopupUI::onClickColse(Ref* ref)
{
    CHECK_ACTION(ref);
     closePopup();
}

void RolePopupUI::updateItems()
{

    for(int i=0; i<int(PlayerProperty::getInstance()->getBagMaxSpace()); i++)
    {
        ItemUI* itemUi = static_cast<ItemUI*>( m_pGridView->getItem(i));
        if (itemUi) {
            itemUi->removeItem();
        }
    }
    CCLOG("bagSize:%d",(int)PlayerProperty::getInstance()->getPlayerBag().size());
    for (int i =0; i<PlayerProperty::getInstance()->getPlayerBag().size(); i++) {
        PickableItemProperty* itemProp =PlayerProperty::getInstance()->getPlayerBag()[i];
         ItemUI* itemUi = static_cast<ItemUI*>( m_pGridView->getItem(i));
        if (itemProp && itemUi) {
            // 更新装备UI
            int weaponId = int(PlayerProperty::getInstance()->getEquipedWeaponID());
            int armorId = int(PlayerProperty::getInstance()->getEquipedArmorID());
            int OrnamentId = int(PlayerProperty::getInstance()->getEquipedOrnamentsID());
            int secondWeaponId = int(PlayerProperty::getInstance()->getEquipedSecondWeaponID());
            CCLOG("weaponId:%d armorId:%d OrnamentId:%d secondWeaponId:%d itemid:%d",weaponId,armorId,OrnamentId,secondWeaponId,itemProp->getInstanceID());
            if ( m_pWeaponUi && itemProp->getInstanceID() == weaponId) {
                itemUi->setEquipEnable(true);
                m_pWeaponUi->addItem(itemProp->getInstanceID(), itemProp->getIconRes());
            }
            if (m_pArmorUi &&  itemProp->getInstanceID() == armorId) {
                itemUi->setEquipEnable(true);
                m_pArmorUi->addItem(itemProp->getInstanceID(), itemProp->getIconRes());
            }
            if (m_pOrnamentUi &&  itemProp->getInstanceID() == OrnamentId) {
                itemUi->setEquipEnable(true);
                m_pOrnamentUi->addItem(itemProp->getInstanceID(), itemProp->getIconRes());
            }
            if (m_pSecondWeaponUi &&  itemProp->getInstanceID() == secondWeaponId) {
                itemUi->setEquipEnable(true);
                m_pSecondWeaponUi->addItem(itemProp->getInstanceID(), itemProp->getIconRes());
            }
            //查看是否可以合并
            if(itemProp->isStackable())
            {
                PickableItemProperty::PickableItemPropertyType itemtype =itemProp->getPickableItemPropertyType() ;
                int count = 0;
                if ( itemtype == PickableItemProperty::PIPT_KEY) {
                    CCLOG("合并 PIPT_KEY");
                    KeyProperty* stackProp = static_cast<KeyProperty*>(itemProp);
                    count = stackProp->getCount();
                }else if (itemtype == PickableItemProperty::PIPT_MATERIAL){
                    
                    CCLOG("合并 PIPT_MATERIAL");
                    
                }else if(itemtype == PickableItemProperty::PIPT_POTIONS)
                {
                    CCLOG("合并 PIPT_POTIONS");
                }
                itemUi->addItem(itemProp->getInstanceID(), itemProp->getIconRes(),count);
            }else
                itemUi->addItem(itemProp->getInstanceID(), itemProp->getIconRes());
        }

    }
}
void RolePopupUI::selectItemEvent(cocos2d::Ref *pSender, TGridView::EventType type)
{
    
    if (type==TGridView::EventType::ON_SELECTED_ITEM_END) {
        TGridView* gridView = static_cast<TGridView*>(pSender);
        ItemUI* currentItem = static_cast<ItemUI*>(gridView->getItem(gridView->getCurSelectedIndex()));
        if (currentItem && currentItem->isHaveItem()) {
            
                ItemPopupUI* popupui = static_cast<ItemPopupUI*>(PopupUILayerManager::getInstance()->openPopup(ePopupType::ePopupItem));
                if (popupui) {
                    popupui->updateItemPopup(currentItem->getItemId());
                }
             CCLOG("select itemid = %d", currentItem->getItemId());
            
        }
        
    }
}
void RolePopupUI::onEventUpdateData(cocos2d::EventCustom *sender)
{
    updateItems();
}