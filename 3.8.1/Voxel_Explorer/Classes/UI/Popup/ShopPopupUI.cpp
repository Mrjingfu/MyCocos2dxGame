//
//  ShopPopupUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/26.
//
//

#include "ShopPopupUI.h"
#include "BagShopLayer.hpp"
#include "UtilityHelper.h"
#include "PickableItemProperty.hpp"
#include "PlayerProperty.hpp"
#include "BagMangerLayerUI.h"
#include "PopupUILayerManager.h"
#include "PickableItemProperty.hpp"
#include "ItemShopBuyPopupUI.hpp"
#include "EventConst.h"
ShopPopupUI::ShopPopupUI()
{
    m_cActionType       = eNone;
    m_nIsBlankClose     = false;
    m_pBagLayer         = nullptr;
    m_pShopMangerLayer  = nullptr;
    m_pShopGridView     = nullptr;
    m_pShopTitleText      = nullptr;

}
ShopPopupUI::~ShopPopupUI()
{
    
}
bool ShopPopupUI::init()
{
    if (PopupUILayer::init()) {
         return this->load("shopPopupLayer.csb",false);
    }
    
    return false;
    
}
bool ShopPopupUI::addEvents()
{
    cocos2d::ui::ImageView* m_shopFrame = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "shop_bg_frame"));
    if (!m_shopFrame)
        return false;
    m_pBtnClose = dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode, "shop_btn_close"));
    if (!m_pBtnClose)
        return false;
    
    m_pShopTitleText= dynamic_cast<ui::TextBMFont*>(UtilityHelper::seekNodeByName(m_pRootNode, "shop_title_text"));
    if (!m_pShopTitleText)
        return false;
    
    m_pShopTitleText->setFntFile(UtilityHelper::getLocalStringForUi("FONT_NAME"));
    
    m_pBagLayer = BagShopLayer::create();
    m_pBagLayer->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
    m_pBagLayer->setPosition(cocos2d::Size(m_pRootNode->getContentSize().width*0.5,0));
    m_pBagLayer->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    m_pRootNode->addChild(m_pBagLayer);

    
    m_pShopGridView = TGridView::create();
    m_pShopGridView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    m_pShopGridView->setContentSize(cocos2d::Size(m_shopFrame->getContentSize().width-10,m_shopFrame->getContentSize().height-7));
    m_pShopGridView->setCol(5);
    m_pShopGridView->setPosition(m_shopFrame->getContentSize()*0.5);
    m_pShopGridView->setScrollBarWidth(5);
    m_pShopGridView->setScrollBarColor(Color3B::WHITE);
    m_pShopGridView->setScrollBarPositionFromCornerForVertical(cocos2d::Vec2(0,0));
//    m_pShopGridView->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    m_pShopGridView->setItemsMargin(cocos2d::Size(1,5));
    m_pShopGridView->setFrameMargin(cocos2d::Size(7,15));
    m_pShopGridView->addEventListener(CC_CALLBACK_2(ShopPopupUI::selectItemEvent, this));
    m_pShopGridView->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    m_shopFrame->addChild(m_pShopGridView);

    int shopItemSize = getShopItems().size()/15?15:15*((int)getShopItems().size()/15+1);
    
    for (int j =0; j<shopItemSize; j++) {
        
        ImageView* itemui = ImageView::create();
        itemui->setTouchEnabled(true);
        itemui->setScale9Enabled(true);
        itemui->setContentSize(cocos2d::Size(45,45));
        itemui->loadTexture("ui_frame_5.png",TextureResType::PLIST);
        itemui->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        m_pShopGridView->pushBackCustomItem(itemui);
    }
    m_pShopGridView->forceDoLayout();
    
    m_pShopMangerLayer = BagMangerLayerUI::create(m_pShopGridView->getInnerContainerSize());
    m_pShopMangerLayer->setPosition(m_pShopGridView->getContentSize()*0.5);
    m_pShopMangerLayer->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    m_pShopGridView->addChildLayer(m_pShopMangerLayer,60);
    
    m_pBtnClose->addClickEventListener(CC_CALLBACK_1(ShopPopupUI::onClickClose, this));
    refreshUIView();
    
    return true;
}
void ShopPopupUI::onEnter()
{
    PopupUILayer::onEnter();
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_NPC_DATA_DIRTY, CC_CALLBACK_1(ShopPopupUI::onEventUpdateNpcData,this));
//    EventListenerCustom *listener = EventListenerCustom::create(EVENT_PLAYER_PROPERTY_DIRTY, CC_CALLBACK_1(ShopPopupUI::onEventUpdateNpcData,this));
//    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
}
void ShopPopupUI::onExit()
{
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_NPC_DATA_DIRTY);
    Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
    PopupUILayer::onExit();
}
void ShopPopupUI::onEventUpdateNpcData(cocos2d::EventCustom *sender)
{
    refreshUIView();
}
void ShopPopupUI::refreshUIView()
{
    if (m_pBagLayer) {
        m_pBagLayer->refreshUIView();
    }
    updateShopBuyItems();
}
void ShopPopupUI::updateShopBuyItems()
{
    if (!m_pBagLayer || !m_pShopGridView)
        return;
    if (m_pShopMangerLayer) {
        m_pShopMangerLayer->removeItems();
    }

    //重置边框颜色
    for(int i=0; i<m_pShopGridView->getItems().size(); i++)
    {
        ImageView* itemImg = static_cast<ImageView*>(m_pShopGridView->getItem(i));
        if (itemImg) {
            itemImg->loadTexture("ui_frame_5.png",TextureResType::PLIST);
            itemImg->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        }
    }
    updateShopDataItems();

}
void ShopPopupUI::setShopTitle(const std::string &titleKey)
{
    if (m_pShopTitleText) {
        m_pShopTitleText->setString(UtilityHelper::getLocalStringForUi(titleKey));
    }
   refreshUIView();
}

void ShopPopupUI::updateShopDataItems()
{
    std::vector<PickableItemProperty*> itemProps = getShopItems();
    

    int playerLevel = PlayerProperty::getInstance()->getLevel();
    for (int i=0; i<itemProps.size(); i++)
    {
        PickableItemProperty* property = itemProps[i];
        ui::ImageView* img =static_cast<ui::ImageView*>( m_pShopGridView->getItem(i));
        if (property && img)
        {
            
            m_pShopMangerLayer->addItem(i, property->getInstanceID(), img->getPosition(), property->getIconRes());
            if (!property->isIdentified() || property->getLevel() >playerLevel) {
                m_pShopMangerLayer->setItemNoUse(property->getInstanceID(), img->getPosition());
            }else
            {
                //设置品质
                switch (property->getQuality()) {
                    case PIQ_RARE:
                        img->loadTexture("ui_rape.png",TextureResType::PLIST);
                        break;
                    case PIQ_EPIC:
                        img->loadTexture("ui_epic.png",TextureResType::PLIST);
                        break;
                    case PIQ_LEGEND:
                        img->loadTexture("ui_legend.png",TextureResType::PLIST);
                        break;
                    default:
                        break;
                }
                 img->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
            }
            
        }
    }
    
}
void ShopPopupUI::onClickClose(Ref* ref)
{
    CHECK_ACTION(ref);
    clickEffect();
    closePopup();
}
void ShopPopupUI::selectItemEvent(cocos2d::Ref *pSender, TGridView::EventType type)
{
    if (type==TGridView::EventType::ON_SELECTED_ITEM_END) {
        TGridView* gridView = static_cast<TGridView*>(pSender);
        int currentItemId = m_pShopMangerLayer->getItemId(gridView->getCurSelectedIndex());
        if (currentItemId!=-1) {
            
            shopItemOpe(currentItemId);
        }
    }
}
void ShopPopupUI::shopItemOpe(int itemId)
{

    ItemShopBuyPopupUI* shopItem = static_cast<ItemShopBuyPopupUI*>( PopupUILayerManager::getInstance()->openPopup(ePopupItemShopBuy));
    if (shopItem) {
        shopItem->setItemShopProp(m_eShopType,itemId);
        shopItem->registerCloseCallback(CC_CALLBACK_0(ShopPopupUI::refreshUIView, this));
        PickableItemProperty* itemProp = shopItem->getItemIdProperty();
        
        
        //判断点击的武器 是否已经有装备过
        int weaponId = int(PlayerProperty::getInstance()->getEquipedWeaponID());
        int armorId = int(PlayerProperty::getInstance()->getEquipedArmorID());
        int OrnamentId = int(PlayerProperty::getInstance()->getEquipedOrnamentsID());
        int secondWeaponId = int(PlayerProperty::getInstance()->getEquipedSecondWeaponID());
        int equipId = -1;
        if (itemProp->getPickableItemPropertyType() == PickableItemProperty::PIPT_WEAPON && itemId !=weaponId )
        {
            equipId = weaponId;
        }else if (itemProp->getPickableItemPropertyType() == PickableItemProperty::PIPT_ARMOR && itemId !=armorId )
        {
            equipId = armorId;
        }else if (itemProp->getPickableItemPropertyType() == PickableItemProperty::PIPT_MAGIC_ORNAMENT && itemId !=OrnamentId )
        {
            equipId = OrnamentId;
        }else if (itemProp->getPickableItemPropertyType() == PickableItemProperty::PIPT_SECOND_WEAPON && itemId !=secondWeaponId )
        {
            equipId = secondWeaponId;
        }
        
        
        //如果有装备过 打开装备过的武器
        if (equipId!=-1)
        {
            ItemPopupUI* Equippopupui = static_cast<ItemPopupUI*>(PopupUILayerManager::getInstance()->openPopup(ePopupType::ePopupEquipItem));
            if (Equippopupui)
            {
                Equippopupui->setItemId(equipId);
                Equippopupui->setDarkLayerVisble(false);
                cocos2d::Size itemRootNode = shopItem->getRootNode()->getContentSize();
                cocos2d::Size equipRootNode = Equippopupui->getRootNode()->getContentSize();
                float y = 0.0f;
                if (equipRootNode.height > itemRootNode.height) {
                    y = SCREEN_HEIGHT*0.5 + equipRootNode.height*0.5;
                }else
                    y = SCREEN_HEIGHT*0.5 + itemRootNode.height*0.5;
                
                Equippopupui->getRootNode()->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_TOP);
                shopItem->getRootNode()->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_TOP);
                shopItem->getRootNode()->setPosition(cocos2d::Vec2(SCREEN_WIDTH*0.5+5+itemRootNode.width*0.5,y));
                Equippopupui->getRootNode()->setPosition(cocos2d::Vec2(SCREEN_WIDTH*0.5-equipRootNode.width*0.5,y));
                
            }
        }
    }


}
