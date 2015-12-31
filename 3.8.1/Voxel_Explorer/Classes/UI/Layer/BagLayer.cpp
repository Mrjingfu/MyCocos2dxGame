//
//  BagLayer.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/24.
//
//

#include "BagLayer.h"
#include "BagMangerLayerUI.h"
#include "PlayerProperty.hpp"
#include "PickableItemProperty.hpp"
#include "ItemPopupUI.h"
#include "PopupUILayerManager.h"
#include "AlertPopupUI.hpp"
#include "UtilityHelper.h"
#include "StatisticsManager.hpp"
SellItem* SellItem::create(int itemId,int count /*=1*/)
{
    SellItem* sellItem = new (std::nothrow) SellItem();
    if (sellItem )
    {
        sellItem->m_nItemId = itemId;
        sellItem->m_nItemCount = count;
        sellItem->autorelease();
        return sellItem;
    }
    CC_SAFE_DELETE(sellItem);
    return nullptr;
}

BagLayer::BagLayer()
{
    m_bIsIndetify = false;
    m_pGridView = nullptr;
    m_BagMsgLayer = nullptr;
    m_pBtnAllBag= nullptr;
    m_pBtnWeaponBag= nullptr;
    m_pBtnPotionBag= nullptr;
    
}
BagLayer::~BagLayer()
{
    
}

bool BagLayer::init()
{
    if (!WrapperUILayer::init()) {
        return false;
    }
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    setContentSize(cocos2d::Size(250,155));
    setBackGroundImageScale9Enabled(true);
    setBackGroundImage("ui_frame_3.png",TextureResType::PLIST);
    
    m_pBtnAllBag = Button::create("btn_bag_all_press.png","btn_bag_all_normal.png","btn_bag_all_normal.png",TextureResType::PLIST);
    m_pBtnAllBag->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
    m_pBtnAllBag->setPosition(cocos2d::Vec2(getContentSize().width*0.07,getContentSize().height*0.04));
    m_pBtnAllBag->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    m_pBtnAllBag->setEnabled(false);
    addChild(m_pBtnAllBag);
    
    m_pBtnWeaponBag = Button::create("btn_bag_wepon_press.png","btn_bag_wepon_normal.png","btn_bag_wepon_normal.png",TextureResType::PLIST);
    m_pBtnWeaponBag->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
    m_pBtnWeaponBag->setPosition(cocos2d::Vec2(m_pBtnAllBag->getPositionX()+m_pBtnAllBag->getContentSize().width+10,getContentSize().height*0.02));
    m_pBtnWeaponBag->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    m_pBtnWeaponBag->setEnabled(true);
    addChild(m_pBtnWeaponBag);

    
    m_pBtnPotionBag = Button::create("btn_bag_poition_press.png","btn_bag_poition_normal.png","btn_bag_poition_normal.png",TextureResType::PLIST);
    m_pBtnPotionBag->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
    m_pBtnPotionBag->setPosition(cocos2d::Vec2(m_pBtnWeaponBag->getPositionX()+m_pBtnWeaponBag->getContentSize().width+10,getContentSize().height*0.0271));
    m_pBtnPotionBag->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    m_pBtnPotionBag->setEnabled(true);
    addChild(m_pBtnPotionBag);

    
    m_pBtnWeaponBag->addTouchEventListener(CC_CALLBACK_2(BagLayer::onClickSortEquip, this));
    m_pBtnPotionBag->addTouchEventListener(CC_CALLBACK_2(BagLayer::onClickSortPotion, this));
    m_pBtnAllBag->addTouchEventListener(CC_CALLBACK_2(BagLayer::onClickSortAll, this));

    
    m_pGridView = TGridView::create();
    m_pGridView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    m_pGridView->setContentSize(cocos2d::Size(getContentSize().width-10,getContentSize().height-7));
    m_pGridView->setCol(5);
    m_pGridView->setPosition(getContentSize()*0.5);
    m_pGridView->setScrollBarWidth(5);
    m_pGridView->setScrollBarColor(Color3B::WHITE);
    m_pGridView->setScrollBarPositionFromCornerForVertical(cocos2d::Vec2(0,0));
    m_pGridView->setItemsMargin(cocos2d::Size(1,3.5));
    m_pGridView->setFrameMargin(cocos2d::Size(7,4));
    m_pGridView->addEventListener(CC_CALLBACK_2(BagLayer::selectItemEvent, this));
    m_pGridView->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    addChild(m_pGridView);

    m_BagMsgLayer = BagMangerLayerUI::create(m_pGridView->getContentSize());
    m_BagMsgLayer->setPosition(m_pGridView->getContentSize()*0.5);
    m_BagMsgLayer->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    m_pGridView->addChildLayer(m_BagMsgLayer,60);
    
    for (int j =0; j<int(PlayerProperty::getInstance()->getBagMaxSpace()); j++) {
        
        ImageView* itemui = ImageView::create();
        itemui->setTouchEnabled(true);
        itemui->setScale9Enabled(true);
        itemui->setContentSize(cocos2d::Size(45,45));
        itemui->loadTexture("ui_frame_5.png",TextureResType::PLIST);
        itemui->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        m_pGridView->pushBackCustomItem(itemui);
    }
    m_pGridView->forceDoLayout();
    
    refreshUIView();
    
    return true;
}
void BagLayer::refreshUIView()
{
    
    m_BagMsgLayer->setLayerContentSize(cocos2d::Size(m_pGridView->getInnerContainerSize()));
    m_BagMsgLayer->setPosition(m_pGridView->getInnerContainerSize()*0.5);
    //清除背包信息
    if (m_BagMsgLayer)
        m_BagMsgLayer->removeItems();

    //重置边框颜色
    BlendFunc tmp_oBlendFunc = {GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA};
    for(int i=0; i<m_pGridView->getItems().size(); i++)
    {
        ImageView* itemImg = static_cast<ImageView*>(m_pGridView->getItem(i));
        if (itemImg) {
            itemImg->loadTexture("ui_frame_5.png",TextureResType::PLIST);
            itemImg->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        }
    }
    int weaponId = int(PlayerProperty::getInstance()->getEquipedWeaponID());
    int armorId = int(PlayerProperty::getInstance()->getEquipedArmorID());
    int OrnamentId = int(PlayerProperty::getInstance()->getEquipedOrnamentsID());
    int secondWeaponId = int(PlayerProperty::getInstance()->getEquipedSecondWeaponID());
    
    if (m_bIsIndetify) {
//        setSortBtnEnable(true, false, true);
    }
    
    std::vector<PickableItemProperty*> items = getItems();
    int playerLevel = PlayerProperty::getInstance()->getLevel();
    //放置道具
    CCLOG("bagSize:%d",(int)items.size());
    
    for (int i =0; i<items.size(); i++)
    {
        PickableItemProperty* itemProp =items[i];
        ui::ImageView* itemUi = static_cast<ui::ImageView*>( m_pGridView->getItem(i));
        
        if (itemProp && itemUi) {
            // 更新装备UI
            
            m_BagMsgLayer->addItem(i, itemProp->getInstanceID(), itemUi->getPosition(), itemProp->getIconRes());
            
            //设置品质
            switch (itemProp->getQuality()) {
                case PIQ_RARE:
                    itemUi->loadTexture("ui_rape.png",TextureResType::PLIST);
                break;
                case PIQ_EPIC:
                    itemUi->loadTexture("ui_epic.png",TextureResType::PLIST);
                    break;
                case PIQ_LEGEND:
                    itemUi->loadTexture("ui_legend.png",TextureResType::PLIST);
                    break;
                default:
                    break;
            }
            itemUi->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
//            Scale9Sprite* spriteItem = static_cast<Scale9Sprite*>(itemUi->getVirtualRenderer());
//            if (spriteItem) {
//                spriteItem->setBlendFunc(tmp_oBlendFunc);
//                spriteItem->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
////                itemUi->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
//            }

            PickableItemProperty::PickableItemPropertyType itemtype =itemProp->getPickableItemPropertyType();
            if (!m_bIsIndetify && (itemtype ==PickableItemProperty::PIPT_WEAPON ||itemtype ==PickableItemProperty::PIPT_SECOND_WEAPON||
                itemtype ==PickableItemProperty::PIPT_ARMOR ||itemtype ==PickableItemProperty::PIPT_MAGIC_ORNAMENT) )
            {
                if (!itemProp->isIdentified() || itemProp->getLevel() >playerLevel) {
                    m_BagMsgLayer->setItemNoUse(itemProp->getInstanceID(), itemUi->getPosition());
                }
            }

            
            //查看是否可以合并
            if(itemProp->isStackable())
            {
                int count = itemProp->getCount();
                if (count>1)
                    m_BagMsgLayer->setItemCount(itemProp->getInstanceID(),itemUi->getPosition(), count);

            }
            if (itemProp->getInstanceID() == weaponId) {
                m_BagMsgLayer->setItemEquipMark(itemProp->getInstanceID(),itemUi->getPosition());
                
            }
            if ( itemProp->getInstanceID() == armorId) {
                m_BagMsgLayer->setItemEquipMark(itemProp->getInstanceID(),itemUi->getPosition());
                
            }
            if (itemProp->getInstanceID() == OrnamentId) {
                m_BagMsgLayer->setItemEquipMark(itemProp->getInstanceID(),itemUi->getPosition());
                
            }
            if (itemProp->getInstanceID() == secondWeaponId) {
                m_BagMsgLayer->setItemEquipMark(itemProp->getInstanceID(),itemUi->getPosition());
                
            }
            //是否是鉴定
            if (m_bIsIndetify)
            {
                if (itemProp->isIdentified())
                    m_BagMsgLayer->setItemNoUse(itemProp->getInstanceID(), itemUi->getPosition());
                else
                    m_BagMsgLayer->setItemNormalIndentify(itemProp->getInstanceID(),itemUi->getPosition());
                
            }
           
        }
    }
    
}


std::vector<PickableItemProperty*> BagLayer::getItems()
{
    
    eSortBagType sortType = SBT_ALL;
    if (!m_pBtnWeaponBag->isEnabled())
    {
        sortType = BagLayer::SBT_EQUIP;
        
    }else if (!m_pBtnPotionBag->isEnabled())
    {
        sortType = BagLayer::SBT_POTION;
    }
    
    //对道具进行排序， 武器 0  副手武器 1 护甲 2 饰品 3   装备位置
    //
    int weaponId = int(PlayerProperty::getInstance()->getEquipedWeaponID());
    int armorId = int(PlayerProperty::getInstance()->getEquipedArmorID());
    int OrnamentId = int(PlayerProperty::getInstance()->getEquipedOrnamentsID());
    int secondWeaponId = int(PlayerProperty::getInstance()->getEquipedSecondWeaponID());
    int weaponIndex = -1;
    int armorIndex = -1;
    int OrnamentIndex = -1;
    int secondWeaponIndex = -1;
    std::vector<PickableItemProperty*> items;
    
    std::vector<PickableItemProperty*> equipItems;
    std::vector<PickableItemProperty*> otherItems;
    std::vector<PickableItemProperty*> bagItems = PlayerProperty::getInstance()->getPlayerBag();
    for (int i =0 ; i<bagItems.size(); i++)
    {
        PickableItemProperty* itemProp =bagItems[i];
        if (!itemProp) {
            continue;
        }
        
               
        items.push_back(itemProp);
        PickableItemProperty::PickableItemPropertyType itemtype =itemProp->getPickableItemPropertyType();
        if (itemtype ==PickableItemProperty::PIPT_WEAPON ||itemtype ==PickableItemProperty::PIPT_SECOND_WEAPON||
            itemtype ==PickableItemProperty::PIPT_ARMOR ||itemtype ==PickableItemProperty::PIPT_MAGIC_ORNAMENT )
        {
            equipItems.push_back(itemProp);
        }else
        {
            otherItems.push_back(itemProp);
        }
    }
    
    if (sortType == eSortBagType::SBT_EQUIP)
    {
        items.clear();
        items = equipItems;
        
    }else if (sortType == eSortBagType::SBT_POTION)
    {
        items.clear();
        items = otherItems;
    }
    equipItems.clear();
    otherItems.clear();
    
    for (int i =0; i<items.size(); i++) {
        PickableItemProperty* itemProp =items[i];
        if (!itemProp) {
            continue;
        }
        if (weaponId ==  itemProp->getInstanceID()) {
            weaponIndex= i;
        }
        if (armorId ==  itemProp->getInstanceID()) {
            armorIndex = i;
        }
        if (OrnamentId ==  itemProp->getInstanceID()) {
            OrnamentIndex = i;
        }
        if (secondWeaponId ==  itemProp->getInstanceID()) {
            secondWeaponIndex = i;
        }
    }
    
    
    if (sortType == eSortBagType::SBT_ALL || sortType == eSortBagType::SBT_EQUIP) {
        //武器不在首位
        if (weaponIndex>0)
        {
            std::swap( items[0], items[weaponIndex] );
            weaponIndex = 0;
        }
        //护甲不在首位且武器不存在 放在首位
        if (secondWeaponIndex>0 && weaponIndex<0){
            std::swap( items[0], items[secondWeaponIndex] );
            secondWeaponIndex = 0;
        }else if (secondWeaponIndex >1 && weaponIndex==0) {
            //护甲不在第2位且武器存在 放在第2位
            std::swap( items[1], items[secondWeaponIndex] );
            secondWeaponIndex = 1;
        }
        //饰品不在在首位且护甲不存在 武器不存在
        if (armorIndex>0 && weaponIndex<0 && secondWeaponIndex<0)
        {
            std::swap( items[0], items[armorIndex] );
            armorIndex =0 ;
        }else if (armorIndex>1 && weaponIndex==0 && secondWeaponIndex<0)
        {
            std::swap( items[1], items[armorIndex] );
            armorIndex = 1;
        }else if (armorIndex>2 && weaponIndex==0 && secondWeaponIndex==1)
        {
            std::swap( items[2], items[armorIndex] );
            armorIndex = 2;
            
        }
        
        if (OrnamentIndex>0 && weaponIndex<0 && secondWeaponIndex<0 && armorIndex<0)
        {
            std::swap( items[0], items[OrnamentIndex] );
            OrnamentIndex =0 ;
        }else if (OrnamentIndex>1 && weaponIndex==0 && secondWeaponIndex<0 && armorIndex<0)
        {
            std::swap( items[1], items[OrnamentIndex] );
            OrnamentIndex = 1;
        }else if (OrnamentIndex>2 && weaponIndex==0 && secondWeaponIndex==1 && armorIndex<0)
        {
            std::swap( items[2], items[OrnamentIndex] );
            OrnamentIndex = 2;
            
        }else if (OrnamentIndex>3 && weaponIndex==0 && secondWeaponIndex==1 && armorIndex==2)
        {
            std::swap( items[3], items[OrnamentIndex] );
            OrnamentIndex = 3;
        }
    }
    return items;
}

void BagLayer::extendBag()
{
    CCLOG("onEventBagExtend");
    for (int j =0; j<15; j++) {
        ImageView* itemui = ImageView::create();
        itemui->setTouchEnabled(true);
        itemui->setScale9Enabled(true);
        itemui->setContentSize(cocos2d::Size(45,45));
        itemui->loadTexture("ui_frame_5.png",TextureResType::PLIST);
        itemui->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        m_pGridView->pushBackCustomItem(itemui);
    }
    m_pGridView->forceDoLayout();
    m_BagMsgLayer->setLayerContentSize(m_pGridView->getInnerContainerSize());
    m_BagMsgLayer->setPosition(m_pGridView->getInnerContainerSize()*0.5);
    m_pGridView->resume();
    m_pGridView->scrollToBottom(0.8,false);
}
void BagLayer::selectItemEvent(cocos2d::Ref *pSender, TGridView::EventType type)
{
    if (type==TGridView::EventType::ON_SELECTED_ITEM_END) {
        TGridView* gridView = static_cast<TGridView*>(pSender);
        int currentItemId = m_BagMsgLayer->getItemId(gridView->getCurSelectedIndex());
        bagItemOpe(currentItemId);
    }
}




void BagLayer::bagItemOpe(int currentItemId)
{
    if (currentItemId==-1)
        return;
    CCLOG("select itemid = %d", currentItemId);
    PickableItemProperty* itemProp = PlayerProperty::getInstance()->getItemFromBag(CChaosNumber(currentItemId));
    if (!itemProp)
    {
        CCLOG("itemProp is empty");
        return;
    }
    
    //判断点击的武器 是否已经有装备过
    int weaponId = int(PlayerProperty::getInstance()->getEquipedWeaponID());
    int armorId = int(PlayerProperty::getInstance()->getEquipedArmorID());
    int OrnamentId = int(PlayerProperty::getInstance()->getEquipedOrnamentsID());
    int secondWeaponId = int(PlayerProperty::getInstance()->getEquipedSecondWeaponID());
    int equipId = -1;
    ItemPopupUI* Equippopupui = nullptr;
    if (itemProp->getPickableItemPropertyType() == PickableItemProperty::PIPT_WEAPON && currentItemId !=weaponId )
    {
        equipId = weaponId;
    }else if (itemProp->getPickableItemPropertyType() == PickableItemProperty::PIPT_ARMOR && currentItemId !=armorId )
    {
        equipId = armorId;
    }else if (itemProp->getPickableItemPropertyType() == PickableItemProperty::PIPT_MAGIC_ORNAMENT && currentItemId !=OrnamentId )
    {
        equipId = OrnamentId;
    }else if (itemProp->getPickableItemPropertyType() == PickableItemProperty::PIPT_SECOND_WEAPON && currentItemId !=secondWeaponId )
    {
        equipId = secondWeaponId;
    }
    //如果有装备过 打开装备过的武器
    if (equipId!=-1)
    {
        Equippopupui = static_cast<ItemPopupUI*>(PopupUILayerManager::getInstance()->openPopup(ePopupType::ePopupEquipItem));
        if (Equippopupui)
        {
            Equippopupui->setItemId(equipId);
            Equippopupui->getRootNode()->setPosition(cocos2d::Vec2(Equippopupui->getRootNode()->getPositionX(),SCREEN_HEIGHT*0.7));
        }
    }

    bool isSucces = false;
    if (m_bIsIndetify )
    {
        isSucces = PlayerProperty::getInstance()->indentifyItem(CChaosNumber(currentItemId));
        m_bIsIndetify =false;
        
        if (!isSucces)
        {
            AlertPopupUI* alertPopup = static_cast<AlertPopupUI*>(PopupUILayerManager::getInstance()->openPopup(ePopupAlert));
            if (alertPopup) {
                alertPopup->setMessage(UtilityHelper::getLocalStringForUi("BAG_INDENTIFY_FAIL"));
                alertPopup->setPositiveListerner([](Ref* ref){});
                alertPopup->registerCloseCallback([this]()
                {
                     refreshUIView();
                });
            }
            return;
        }
        //统计鉴定
        if (isSucces) {
            PickableItemProperty* itemprop =  PlayerProperty::getInstance()->getItemFromBag(currentItemId);
            if (isSucces && itemprop) {
                StatisticsManager::getInstance()->addIdentifyNum();
                if (itemprop->getAddedEffectList().size() >2) {
                    StatisticsManager::getInstance()->addIdentifyAttrNum();
                }
                if (itemprop->getQuality()>=PIQ_LEGEND) {
                    StatisticsManager::getInstance()->addIdentifyLegendNum();
                }
            }
        }
    }
    
    ItemPopupUI* popupui = static_cast<ItemPopupUI*>(PopupUILayerManager::getInstance()->openPopup(ePopupType::ePopupItem));
    if (popupui)
    {
        //用来回调某些道具直接鉴定
        popupui->registerCloseCallbackD([this](void* data){
            
            if (data) {
                int* id = static_cast<int*>(data);
                bagItemOpe(*id);
            }
            refreshUIView();
        });
        popupui->setItemId(currentItemId);
        
        if (equipId !=-1 && Equippopupui)
        {
            popupui->setDarkLayerVisble(false);
            popupui->getRootNode()->setPosition(cocos2d::Vec2(popupui->getRootNode()->getPositionX(),Equippopupui->getRootNode()->getPositionY()-Equippopupui->getRootNode()->getContentSize().height*0.5 -2- popupui->getRootNode()->getContentSize().height*0.5));
            
        }
    }
}
void BagLayer::onClickSortAll(cocos2d::Ref * ref, cocos2d::ui::Widget::TouchEventType type)
{
    if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
        setSortBtnEnable(false,true,true);
        refreshUIView();
    }
    
}
void BagLayer::onClickSortEquip(cocos2d::Ref * ref, cocos2d::ui::Widget::TouchEventType type)
{
    if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
        setSortBtnEnable(true,false,true);
        refreshUIView();
    }
   
}
void BagLayer::onClickSortPotion(cocos2d::Ref * ref, cocos2d::ui::Widget::TouchEventType type)
{
    if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
  
        setSortBtnEnable(true,true,false);
         refreshUIView();
    }
   
}

void BagLayer::setSortBtnEnable(bool allEnable, bool equipEnable, bool potionEnable)
{
    if (m_pBtnAllBag) {
        m_pBtnAllBag->setEnabled(allEnable);
    }
    if (m_pBtnWeaponBag) {
        m_pBtnWeaponBag->setEnabled(equipEnable);
    }
    if (m_pBtnPotionBag) {
        m_pBtnPotionBag->setEnabled(potionEnable);
    }

}
