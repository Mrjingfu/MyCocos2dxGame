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


BagLayer::BagLayer()
{
    m_bIsIndetify = false;
    m_pGridView = nullptr;
    m_BagMsgLayer = nullptr;
    m_pBtnAllBag= nullptr;
    m_pBtnWeaponBag= nullptr;
    m_pBtnPotionBag= nullptr;
    m_pBtnBagExtend = nullptr;
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

    m_pBtnBagExtend =  Button::create("ui_bag_extend_normal.png","ui_bag_extend_press.png","ui_bag_extend_press.png",TextureResType::PLIST);
    m_pBtnBagExtend->setAnchorPoint(cocos2d::Vec2::ONE);
    m_pBtnBagExtend->setPosition(cocos2d::Vec2(getContentSize().width*0.95,getContentSize().height*0.0271 ));
    m_pBtnBagExtend->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    addChild(m_pBtnBagExtend);
    
    m_pBtnBagExtend->addClickEventListener(CC_CALLBACK_1(BagLayer::onClickBagExtend, this));
    m_pBtnWeaponBag->addTouchEventListener(CC_CALLBACK_2(BagLayer::onClickSortEquip, this));
    m_pBtnPotionBag->addTouchEventListener(CC_CALLBACK_2(BagLayer::onClickSortPotion, this));
    m_pBtnAllBag->addTouchEventListener(CC_CALLBACK_2(BagLayer::onClickSortAll, this));

    
    m_pGridView = TGridView::create();
    m_pGridView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    m_pGridView->setContentSize(cocos2d::Size(getContentSize().width-10,getContentSize().height-7));
    m_pGridView->setCol(5);
    m_pGridView->setPosition(getContentSize()*0.5);
    m_pGridView->setScrollBarWidth(5);
    m_pGridView->setScrollBarAutoHideEnabled(false);
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
    m_pGridView->addChildLayer(m_BagMsgLayer);
    
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
    m_BagMsgLayer->setZOrder(m_pGridView->getItems().size());
    
    return true;
}
void BagLayer::refreshUIView()
{
     //扩展次数超过最大扩展次数,隐藏按钮
    if (PlayerProperty::getInstance()->getBagExtendTimes().GetLongValue() >= PlayerProperty::getInstance()->getBagExtendMaxTimes().GetLongValue()) {
        if (m_pBtnBagExtend)
            m_pBtnBagExtend->setVisible(false);
        }
    
    //清除背包信息
    if (m_BagMsgLayer)
    {
        m_BagMsgLayer->setLayerContentSize(cocos2d::Size(m_pGridView->getInnerContainerSize()));
        m_BagMsgLayer->setPosition(m_pGridView->getInnerContainerSize()*0.5);
        m_BagMsgLayer->removeItems();
    }
    

    //重置边框颜色
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
        
        if (m_BagMsgLayer && itemProp && itemUi) {
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
                    itemUi->loadTexture("ui_frame_5.png",TextureResType::PLIST);
                    itemUi->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
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
  
    sortItem(sortType,items);

    return items;
}
void BagLayer::sortItem(eSortBagType sortType,std::vector<PickableItemProperty*>& items)
{
    
    int weaponId = int(PlayerProperty::getInstance()->getEquipedWeaponID());
    int armorId = int(PlayerProperty::getInstance()->getEquipedArmorID());
    int OrnamentId = int(PlayerProperty::getInstance()->getEquipedOrnamentsID());
    int secondWeaponId = int(PlayerProperty::getInstance()->getEquipedSecondWeaponID());
    
    //对道具进行排序， 武器 0  副手武器 1 护甲 2 饰品 3   装备位置
    if (sortType == eSortBagType::SBT_ALL || sortType == eSortBagType::SBT_EQUIP) {
        
        if (weaponId!=-1)
            std::swap( items[0], items[getItemIndexForVector(items,weaponId)] );
        
        if (secondWeaponId != -1)
            std::swap( items[1], items[getItemIndexForVector(items,secondWeaponId)] );
        
        if (armorId != -1)
            std::swap( items[2], items[getItemIndexForVector(items,armorId)] );
        
        if (OrnamentId != -1) {
            std::swap( items[3], items[getItemIndexForVector(items,OrnamentId)] );
        }
        if (secondWeaponId != -1 && armorId ==-1 && OrnamentId!=-1)
        {
            //副手武器存在 护甲不存在 饰品存在
            std::swap( items[2], items[getItemIndexForVector(items,OrnamentId)] );
        }
        
        if (secondWeaponId == -1 && armorId !=-1 )
        {
            //副手武器不存在 护甲存在
            std::swap( items[1], items[getItemIndexForVector(items,armorId)] );
            //饰品存在
            if (OrnamentId!=-1)
                std::swap( items[2], items[getItemIndexForVector(items,OrnamentId)] );
        }
        
        if (secondWeaponId == -1 && armorId ==-1 && OrnamentId!=-1)
        {
            //副手武器、护甲不存在
            std::swap( items[1], items[getItemIndexForVector(items,OrnamentId)] );
        }
        
        if (items.size() >4) {
            std::sort(items.begin()+4, items.end()-1, [](PickableItemProperty* prop1,PickableItemProperty* prop2){
                return prop1->getPickableItemPropertyType() > prop2->getPickableItemPropertyType();
            });
        }
    }else
    {
        std::sort(items.begin(), items.end(), [](PickableItemProperty* prop1,PickableItemProperty* prop2){
            return prop1->getPickableItemPropertyType() > prop2->getPickableItemPropertyType();
        });
    }
}
int BagLayer::getItemIndexForVector(const std::vector<PickableItemProperty*>& items,int itemId) const
{
    PickableItemProperty* itemProp = PlayerProperty::getInstance()->getItemFromBag(itemId );
    if (itemProp) {
        auto iter = std::find(items.begin(), items.end(), itemProp);
        if (iter != items.end())
            return iter - items.begin();
        
    }
    
    return -1;
}
void BagLayer::extendBag()
{
    CCLOG("onEventBagExtend");
    int extendNum = PlayerProperty::getInstance()->getBagMaxSpace() - m_pGridView->getItems().size();
    for (int j =0; j<extendNum; j++) {
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
    m_pGridView->scrollToBottom(0.8,false);
    m_BagMsgLayer->setZOrder(m_pGridView->getItems().size());
}
void BagLayer::selectItemEvent(cocos2d::Ref *pSender, TGridView::EventType type)
{
    if (type==TGridView::EventType::ON_SELECTED_ITEM_END) {
        TGridView* gridView = static_cast<TGridView*>(pSender);
        if (gridView)
        {
            int currentItemId = m_BagMsgLayer->getItemId((int)gridView->getCurSelectedIndex());
            if (currentItemId!=-1) {
                bagItemOpe(currentItemId);
            }else
            {
                if (m_bIsIndetify) {
                    m_bIsIndetify = false;
                    refreshUIView();
                }
            }
        }
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


    bool isSucces = false;
    if (m_bIsIndetify )
    {
        if (!itemProp->isIdentified())
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
        if (isSucces)
        {
            PickableItemProperty* itemprop =  PlayerProperty::getInstance()->getItemFromBag(currentItemId);
            if (isSucces && itemprop)
            {
                StatisticsManager::getInstance()->addIdentifyNum();
                if (itemprop->getAddedEffectList().size() >2)
                {
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
        
        //如果有装备过 打开装备过的武器
        if (equipId!=-1)
        {
            Equippopupui = static_cast<ItemPopupUI*>(PopupUILayerManager::getInstance()->openPopup(ePopupType::ePopupEquipItem));
            if (Equippopupui)
            {
                Equippopupui->setItemId(equipId);
                //            Equippopupui->getRootNode()->setPosition(cocos2d::Vec2(Equippopupui->getRootNode()->getPositionX(),SCREEN_HEIGHT*0.7));
            }
        }
        
        if (equipId !=-1 && Equippopupui)
        {
            Equippopupui->setDarkLayerVisble(false);
            cocos2d::Size itemRootNode = popupui->getRootNode()->getContentSize();
            cocos2d::Size equipRootNode = Equippopupui->getRootNode()->getContentSize();
            float y = 0.0f;
            if (equipRootNode.height > itemRootNode.height) {
                y = SCREEN_HEIGHT*0.5 + equipRootNode.height*0.5;
            }else
                y = SCREEN_HEIGHT*0.5 + itemRootNode.height*0.5;
            
            Equippopupui->getRootNode()->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_TOP);
            popupui->getRootNode()->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_TOP);
            popupui->getRootNode()->setPosition(cocos2d::Vec2(SCREEN_WIDTH*0.5+5+itemRootNode.width*0.5,y));
            Equippopupui->getRootNode()->setPosition(cocos2d::Vec2(SCREEN_WIDTH*0.5-equipRootNode.width*0.5,y));
//            CCLOG("popupui x:%f,y:%f",popupui->getRootNode()->getPositionX(),popupui->getRootNode()->getPositionY());
//            CCLOG("propupui box x:%f,y:%f width:%f,height:%f",popupui->getRootNode()->getBoundingBox().origin.x,popupui->getRootNode()->getBoundingBox().origin.y,popupui->getRootNode()->getBoundingBox().size.width,popupui->getRootNode()->getBoundingBox().size.height);
//            CCLOG("Equippopupui x:%f,y:%f",Equippopupui->getRootNode()->getPositionX(),Equippopupui->getRootNode()->getPositionY());
//            CCLOG("propupui box x:%f,y:%f width:%f,height:%f",Equippopupui->getRootNode()->getBoundingBox().origin.x,Equippopupui->getRootNode()->getBoundingBox().origin.y,Equippopupui->getRootNode()->getBoundingBox().size.width,Equippopupui->getRootNode()->getBoundingBox().size.height);
            
//            popupui->getRootNode()->setPosition(cocos2d::Vec2(popupui->getRootNode()->getPositionX(),Equippopupui->getRootNode()->getPositionY()-Equippopupui->getRootNode()->getContentSize().height*0.5 -2- popupui->getRootNode()->getContentSize().height*0.5));
            
        }
    }
}
void BagLayer::onClickSortAll(cocos2d::Ref * ref, cocos2d::ui::Widget::TouchEventType type)
{
    if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
        clickEffect();
        setSortBtnEnable(false,true,true);
        refreshUIView();
        m_pGridView->scrollToTop(0.5,false);
    }
    
}
void BagLayer::onClickSortEquip(cocos2d::Ref * ref, cocos2d::ui::Widget::TouchEventType type)
{
    if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
        setSortBtnEnable(true,false,true);
        clickEffect();
        refreshUIView();
        m_pGridView->scrollToTop(0.5,false);
    }
   
}
void BagLayer::onClickSortPotion(cocos2d::Ref * ref, cocos2d::ui::Widget::TouchEventType type)
{
    if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
  
        setSortBtnEnable(true,true,false);
        clickEffect();
        refreshUIView();
        m_pGridView->scrollToTop(0.5,false);
    }
   
}
void BagLayer::onClickBagExtend(cocos2d::Ref* ref)
{
    CHECK_ACTION(ref);
    clickEffect();
    AlertPopupUI* alertPopupUi = static_cast<AlertPopupUI*>(PopupUILayerManager::getInstance()->openPopup(ePopupAlert));
    if (alertPopupUi) {
        
        int copper = PlayerProperty::getInstance()->getValueCopper().GetLongValue();
        int extendCopper = 0;
        if (PlayerProperty::getInstance()->getBagExtendTimes() ==1) {
            extendCopper = 1;
        }else if (PlayerProperty::getInstance()->getBagExtendTimes() ==2)
        {
            extendCopper = 5;
        }else if (PlayerProperty::getInstance()->getBagExtendTimes() ==3)
        {
            extendCopper = 15;
        }else if (PlayerProperty::getInstance()->getBagExtendTimes() ==4)
        {
            extendCopper = 35;
        }
        bool isMoneyEnough = false;
        if (copper >=(extendCopper*10000)) {
            isMoneyEnough = true;
        }
        
        alertPopupUi->setPositiveListerner([](Ref* ref){
        
        },UtilityHelper::getLocalStringForUi("BTN_TEXT_CANCEL"));
        alertPopupUi->setNegativeListerner([isMoneyEnough,alertPopupUi,extendCopper](Ref* ref){
            
            if (isMoneyEnough) {
                if(PlayerProperty::getInstance()->costMoney(extendCopper*10000))
                    PlayerProperty::getInstance()->extendBagSpace();
            }else
                Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYER_MONEY_NOT_ENOUGH);
            
            
        },UtilityHelper::getLocalStringForUi("BAG_TEXT_EXTEND"));
        alertPopupUi->setMessage(cocos2d::StringUtils::format(UtilityHelper::getLocalStringForUi("BAG_TEXT_EXTEND_DESC").c_str(),int(extendCopper)));
        
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
