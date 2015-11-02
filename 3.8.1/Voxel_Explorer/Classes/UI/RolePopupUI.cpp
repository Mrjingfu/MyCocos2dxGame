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
USING_NS_CC;
RolePopupUI::RolePopupUI()
{
    m_cActionType  = eNone;
    m_pGridView = nullptr;
}
RolePopupUI::~RolePopupUI()
{
    
}
void RolePopupUI::onEnter()
{
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_UI_UPDATE_ROLE_DATA, CC_CALLBACK_1(RolePopupUI::onEventUpdateData, this));
    PopupUILayer::onEnter();
}
void RolePopupUI::onExit()
{
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_UI_UPDATE_ROLE_DATA);
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
        itemui->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        m_pGridView->pushBackCustomItem(itemui);
    }
    MessageBox("更新背包成功", "提示");
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
                if ( itemtype == PickableItemProperty::PIPT_KEY) {
                    
                    CCLOG("合并 PIPT_KEY");
                    
                }else if (itemtype == PickableItemProperty::PIPT_MATERIAL){
                    
                    CCLOG("合并 PIPT_MATERIAL");
                    
                }else if(itemtype == PickableItemProperty::PIPT_POTIONS)
                {
                    CCLOG("合并 PIPT_POTIONS");
                }
                itemUi->addItem(itemProp->getInstanceID(), itemProp->getIconRes());
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
            ItemPopupUI* itemPopupui = static_cast<ItemPopupUI*>(PopupUILayerManager::getInstance()->openPopup(ePopupType::ePopupItem));
            if (itemPopupui) {
                itemPopupui->updateItemPopup(currentItem->getItemId());
                CCLOG("select itemid = %d", currentItem->getItemId());
            }
            
        }
        
    }
}
void RolePopupUI::onEventUpdateData(cocos2d::EventCustom *sender)
{
    updateItems();
}