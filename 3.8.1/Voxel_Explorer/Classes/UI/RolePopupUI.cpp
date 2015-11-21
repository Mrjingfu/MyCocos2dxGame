//
//  RolePopUpUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/22.
//
//

#include "RolePopupUI.h"
#include "UtilityHelper.h"
#include "PlayerProperty.hpp"
#include "PopupUILayerManager.h"
#include "ItemPopupUI.h"
#include "EventConst.h"
#include "GameFormula.hpp"
#include "KeyProperty.hpp"
#include "BagLayerUI.h"
USING_NS_CC;
RolePopupUI::RolePopupUI()
{
    m_cActionType           = eNone;
    m_pGridView             = nullptr;
    m_pBtnClose             = nullptr;
    m_pBtnChangeBag         = nullptr;
    m_pBtnWeaponBag         = nullptr;
    m_pBtnPotionBag         = nullptr;
    m_pBtnAllBag         = nullptr;
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
    m_BagLayer              = nullptr;
    m_pGridFrame            = nullptr;
    _isOpenIdentify = false;
}
RolePopupUI::~RolePopupUI()
{
    
}
void RolePopupUI::onEnter()
{

//    EventListenerCustom *listener = EventListenerCustom::create(EVENT_PLAYER_PROPERTY_DIRTY, CC_CALLBACK_1(RolePopupUI::onEventUpdateData,this));
//    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);

    PopupUILayer::onEnter();
}
void RolePopupUI::onExit()
{
//    Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
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
     m_pGridFrame = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(charNode, "grid_frame"));
    if (!m_pGridFrame)
        return false;
    m_pBtnChangeBag = dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(charNode, "prop_btn_change_bag"));
    if (!m_pBtnChangeBag)
        return false;
    m_pBtnWeaponBag= dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(charNode, "prop_btn_bag_wepon"));
    if (!m_pBtnWeaponBag)
        return false;
    m_pBtnPotionBag = dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(charNode, "prop_btn_bag_poition"));
    if (!m_pBtnPotionBag)
        return false;
    m_pBtnAllBag= dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(charNode, "prop_btn_bag_all"));
    if (!m_pBtnAllBag)
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
    m_pBtnWeaponBag->addTouchEventListener(CC_CALLBACK_2(RolePopupUI::onClickSortEquip, this));
    m_pBtnPotionBag->addTouchEventListener(CC_CALLBACK_2(RolePopupUI::onClickSortPotion, this));
    m_pBtnAllBag->addTouchEventListener(CC_CALLBACK_2(RolePopupUI::onClickSortAll, this));
    
    m_pWeaponUi = cocos2d::ui::ImageView::create();
    m_pWeaponUi->setScale9Enabled(true);
    m_pWeaponUi->setContentSize(cocos2d::Size(45,45));
    m_pWeaponUi->loadTexture("ui_weapon_icon.png",TextureResType::PLIST);
    m_pWeaponUi->setPosition(Vec2(m_pWeaponUi->getContentSize().width*0.5+8, equipFrame->getContentSize().height*0.5));
    equipFrame->addChild(m_pWeaponUi);
    
    
    m_pSecondWeaponUi = cocos2d::ui::ImageView::create();
    m_pSecondWeaponUi->setScale9Enabled(true);
    m_pSecondWeaponUi->setContentSize(cocos2d::Size(45,45));
    m_pSecondWeaponUi->loadTexture("ui_secondweapon_icon.png",TextureResType::PLIST);
    m_pSecondWeaponUi->setPosition(Vec2(m_pWeaponUi->getContentSize().width*0.5+8+m_pWeaponUi->getContentSize().width*1+2, equipFrame->getContentSize().height*0.5));
    equipFrame->addChild(m_pSecondWeaponUi);

    m_pArmorUi = cocos2d::ui::ImageView::create();
    m_pArmorUi->setScale9Enabled(true);
    m_pArmorUi->setContentSize(cocos2d::Size(45,45));
    m_pArmorUi->loadTexture("ui_armor_icon.png",TextureResType::PLIST);
    m_pArmorUi->setPosition(Vec2(m_pWeaponUi->getContentSize().width*0.5+8+m_pWeaponUi->getContentSize().width*2+4, equipFrame->getContentSize().height*0.5));
    equipFrame->addChild(m_pArmorUi);
    
    m_pOrnamentUi = cocos2d::ui::ImageView::create();
    m_pOrnamentUi->setScale9Enabled(true);
    m_pOrnamentUi->setContentSize(cocos2d::Size(45,45));
    m_pOrnamentUi->loadTexture("ui_ornament_icon.png",TextureResType::PLIST);
    m_pOrnamentUi->setPosition(Vec2(m_pWeaponUi->getContentSize().width*0.5+8+m_pWeaponUi->getContentSize().width*3+6, equipFrame->getContentSize().height*0.5));
    equipFrame->addChild(m_pOrnamentUi);

    
    m_pShopBtn = ImageView::create("ui_shop_icon.png",TextureResType::PLIST);
    m_pShopBtn->setScale9Enabled(true);
    m_pShopBtn->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    m_pShopBtn->setContentSize(cocos2d::Size(45,45));
    m_pShopBtn->setPosition(Vec2(8+m_pWeaponUi->getContentSize().width*4+8, equipFrame->getContentSize().height*0.5));
    equipFrame->addChild(m_pShopBtn);
    
    
    m_pEquipFrame = Layout::create();
    m_pEquipFrame->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
    m_pEquipFrame->setContentSize(equipFrame->getContentSize());
    m_pEquipFrame->setPosition(equipFrame->getContentSize()*0.5);
    equipFrame->addChild(m_pEquipFrame);
    
    m_pGridView = TGridView::create();
    m_pGridView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    m_pGridView->setContentSize(cocos2d::Size(m_pGridFrame->getContentSize().width-10,m_pGridFrame->getContentSize().height-7));
    m_pGridView->setCol(5);
    m_pGridView->setPosition(m_pGridFrame->getContentSize()*0.5);
//    m_pGridView->setScrollBarEnabled(false);
    m_pGridView->setScrollBarWidth(5);
    m_pGridView->setScrollBarColor(Color3B::WHITE);
    m_pGridView->setScrollBarPositionFromCornerForVertical(cocos2d::Vec2(0,0));
    m_pGridView->setItemsMargin(cocos2d::Size(1,3.5));
    m_pGridView->setFrameMargin(cocos2d::Size(7,4));
    m_pGridView->addEventListener(CC_CALLBACK_2(RolePopupUI::selectItemEvent, this));
    m_pGridFrame->addChild(m_pGridView);

    m_BagLayer = BagLayerUI::create(m_pGridView->getContentSize());
    m_BagLayer->setPosition(m_pGridView->getContentSize()*0.5);
    m_pGridView->addChildLayer(m_BagLayer,40);
    
    m_pBtnClose = ui::Button::create("ui_btn_back_1.png","","",TextureResType::PLIST);
    m_pBtnClose->setScale9Enabled(true);
    m_pBtnClose->setPosition(Vec2(SCREEN_WIDTH*0.9, SCREEN_HEIGHT*0.95));
    m_pRootLayer->addChild(m_pBtnClose);
    m_pBtnClose->addClickEventListener(CC_CALLBACK_1(RolePopupUI::onClickColse, this));
    
    for (int j =0; j<int(PlayerProperty::getInstance()->getBagMaxSpace()); j++) {

        ImageView* itemui = ImageView::create();
        itemui->setTouchEnabled(true);
        itemui->setScale9Enabled(true);
        itemui->setContentSize(cocos2d::Size(45,45));
        itemui->loadTexture("ui_frame_5.png",TextureResType::PLIST);
        m_pGridView->pushBackCustomItem(itemui);
    }
    m_pGridView->forceDoLayout();
    
    updateItems();
    
    return true;
}
void RolePopupUI::onClickChnageBag(Ref* ref)
{
    PlayerProperty::getInstance()->extendBagSpace();
    
    CHECK_ACTION(ref);
    for (int j =0; j<5*3; j++) {
        ImageView* itemui = ImageView::create();
        itemui->setTouchEnabled(true);
        itemui->setScale9Enabled(true);
        itemui->setContentSize(cocos2d::Size(45,45));
        itemui->loadTexture("ui_frame_5.png",TextureResType::PLIST);
        itemui->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        m_pGridView->pushBackCustomItem(itemui);
    }
    m_pGridView->forceDoLayout();
    m_BagLayer->setLayerContentSize(m_pGridView->getInnerContainerSize());
    m_BagLayer->setPosition(m_pGridView->getInnerContainerSize()*0.5);
    m_pGridView->resume();
    updateItems();
    m_pGridView->scrollToBottom(0.8,false);
}
void RolePopupUI::onClickColse(Ref* ref)
{
    CHECK_ACTION(ref);
    if (_isOpenIdentify) {
        _isOpenIdentify = false;
        updateItems();
    }else
    {
        closePopup();
    }
}

void RolePopupUI::updateItems()
{
    //清除背包信息
    if (m_BagLayer)
        m_BagLayer->removeItems();
    //清除装备栏信息
    if (m_pEquipFrame)
        m_pEquipFrame->removeAllChildren();
    //重置边框颜色
    for(int i=0; i<m_pGridView->getItems().size(); i++)
    {
        ImageView* itemImg = static_cast<ImageView*>(m_pGridView->getItem(i));
        if (itemImg) {
            itemImg->setColor(Color3B::WHITE);
        }
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

    if (!m_pBtnWeaponBag->isEnabled())
    {
        items.clear();
        items = equipItems;

    }else if (!m_pBtnPotionBag->isEnabled())
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
    
   
    if (!m_pBtnAllBag->isEnabled() || !m_pBtnWeaponBag->isEnabled()) {
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
  
    //放置道具
    CCLOG("bagSize:%d",(int)items.size());
    for (int i =0; i<items.size(); i++)
    {
        PickableItemProperty* itemProp =items[i];
        ui::ImageView* itemUi = static_cast<ui::ImageView*>( m_pGridView->getItem(i));
        
        if (itemProp && itemUi && itemProp) {
            // 更新装备UI
            
            CCLOG("weaponId:%d armorId:%d OrnamentId:%d secondWeaponId:%d itemid:%d",weaponId,armorId,OrnamentId,secondWeaponId,itemProp->getInstanceID());
            m_BagLayer->addItem(i, itemProp->getInstanceID(), itemUi->getPosition(), itemProp->getIconRes());
            
            //设置品质
            switch (itemProp->getQuality()) {
                case PIQ_GENERAL:
                    itemUi->setColor(Color3B::WHITE);
                    break;
                case PIQ_RARE:
                    itemUi->setColor(Color3B::BLUE);
                    break;
                case PIQ_EPIC:
                    itemUi->setColor(Color3B(255,0,255));
                    break;
                case PIQ_LEGEND:
                    itemUi->setColor(Color3B(250,128,10));
                    break;
            }
            
            //查看是否可以合并
            if(itemProp->isStackable())
            {
                int count = itemProp->getCount();
                m_BagLayer->setItemCount(itemUi->getPosition(), count);
            }
            
            if ( m_pWeaponUi && itemProp->getInstanceID() == weaponId) {
                m_BagLayer->setItemEquipMark(itemUi->getPosition());
                setEquipItem(m_pWeaponUi->getPosition(),itemProp->getIconRes());
            }
            if (m_pArmorUi &&  itemProp->getInstanceID() == armorId) {
                m_BagLayer->setItemEquipMark(itemUi->getPosition());
               setEquipItem(m_pArmorUi->getPosition(),itemProp->getIconRes());
            }
            if (m_pOrnamentUi &&  itemProp->getInstanceID() == OrnamentId) {
                m_BagLayer->setItemEquipMark(itemUi->getPosition());
                setEquipItem(m_pOrnamentUi->getPosition(),itemProp->getIconRes());
            }
            if (m_pSecondWeaponUi &&  itemProp->getInstanceID() == secondWeaponId) {
                m_BagLayer->setItemEquipMark(itemUi->getPosition());
                setEquipItem(m_pSecondWeaponUi->getPosition(),itemProp->getIconRes());
            }
            
            //如果使用鉴定卷轴 更新itemUi
            if (_isOpenIdentify && !itemProp->isIdentified()) {
//                itemUi->setIndentify();
            }
            
            
        }

    }
   
}
void RolePopupUI::selectItemEvent(cocos2d::Ref *pSender, TGridView::EventType type)
{
    
    if (type==TGridView::EventType::ON_SELECTED_ITEM_END) {
        TGridView* gridView = static_cast<TGridView*>(pSender);
        int currentItemId = m_BagLayer->getItemId(gridView->getCurSelectedIndex());
        if (currentItemId!=-1 ) {
            
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
            if (equipId!=-1) {
                
                Equippopupui = static_cast<ItemPopupUI*>(PopupUILayerManager::getInstance()->openPopup(ePopupType::ePopupEquipItem));
                if (Equippopupui) {
                    Equippopupui->updateItemPopup(equipId);
                    CCLOG("Equippopupui Y:%f",Equippopupui->getRootNode()->getPositionY());
                    Equippopupui->getRootNode()->setPosition(cocos2d::Vec2(Equippopupui->getRootNode()->getPositionX(),SCREEN_HEIGHT*0.7));
//                    Equippopupui->getRootNode()->setPosition(cocos2d::Vec2(SCREEN_WIDTH*0.27,Equippopupui->getRootNode()->getPositionY()));
                    
                    CCLOG("select itemid = %d", currentItemId);
                }
            }
            
            //使用鉴定卷轴 只能点击未鉴定的物品
            if (_isOpenIdentify ) {
                if (!itemProp->isIdentified()) {
                    CCLOG("select itemid:%d",currentItemId);
                    bool isSuccess = PlayerProperty::getInstance()->indentifyItem(CChaosNumber(currentItemId));
                    _isOpenIdentify =false;
                    if (isSuccess) {
                        CCLOG("鉴定成功");
                        ItemPopupUI* popupui = static_cast<ItemPopupUI*>(PopupUILayerManager::getInstance()->openPopup(ePopupType::ePopupItem));
                        if (popupui) {
                            popupui->registerCloseCallback(CC_CALLBACK_0(RolePopupUI::updateItems, this));
                            popupui->updateItemPopup(currentItemId);
                            if (equipId !=-1) {
                                popupui->setDarkLayerVisble(false);
                                CCLOG("Equippopupui Y:%f",Equippopupui->getRootNode()->getPositionY());
                               popupui->getRootNode()->setPosition(cocos2d::Vec2(popupui->getRootNode()->getPositionX(),Equippopupui->getRootNode()->getPositionY()-Equippopupui->getRootNode()->getContentSize().height*0.5 - popupui->getRootNode()->getContentSize().height*0.5));
                            }
                            CCLOG("select itemid = %d", currentItemId);
                        }
                    }else{
                        CCLOG("鉴定失败");
                        PopupUILayerManager::getInstance()->closeCurrentPopup();
                        //弹出鉴定失败窗口
                    }
                }
               
            }else
            {

                //未使用鉴定卷轴 正常打开
                ItemPopupUI* popupui = static_cast<ItemPopupUI*>(PopupUILayerManager::getInstance()->openPopup(ePopupType::ePopupItem));
                if (popupui) {
                    popupui->registerCloseCallback(CC_CALLBACK_0(RolePopupUI::updateItems, this));
                    popupui->updateItemPopup(currentItemId);
                    
                    if (equipId !=-1) {
                        popupui->setDarkLayerVisble(false);
                       
                        if (Equippopupui) {
                            
//                            popupui->getRootNode()->setPosition(cocos2d::Vec2(Equippopupui->getRootNode()->getPositionX()+Equippopupui->getRootNode()->getContentSize().width,Equippopupui->getRootNode()->getPositionY()));
                            popupui->getRootNode()->setPosition(cocos2d::Vec2(popupui->getRootNode()->getPositionX(),Equippopupui->getRootNode()->getPositionY()-Equippopupui->getRootNode()->getContentSize().height*0.5 - popupui->getRootNode()->getContentSize().height*0.5));
                        }
                        
                    }
                    CCLOG("select itemid = %d", currentItemId);
                }
            }
            
        }
    }
}
void RolePopupUI::onEventUpdateData(cocos2d::EventCustom *sender)
{
    updateItems();
}
void RolePopupUI::onClickSortAll(cocos2d::Ref * ref, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::BEGAN) {
            m_pBtnAllBag->setEnabled(false);
            m_pBtnPotionBag->setEnabled(true);
            m_pBtnWeaponBag->setEnabled(true);
    }
    updateItems();
}
void RolePopupUI::onClickSortEquip(cocos2d::Ref * ref, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::BEGAN) {
            m_pBtnAllBag->setEnabled(true);
            m_pBtnPotionBag->setEnabled(true);
            m_pBtnWeaponBag->setEnabled(false);
    }
    updateItems();
}
void RolePopupUI::onClickSortPotion(cocos2d::Ref * ref, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::BEGAN) {
            m_pBtnAllBag->setEnabled(true);
            m_pBtnPotionBag->setEnabled(false);
            m_pBtnWeaponBag->setEnabled(true);
        
    }
    updateItems();
}

void RolePopupUI::setEquipItem(cocos2d::Vec2 pt, std::string itemIcon)
{
    if (m_pEquipFrame) {
        ui::ImageView* img = ui::ImageView::create(itemIcon,ui::TextureResType::PLIST);
        img->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        img->setPosition(pt);
        img->setScale(0.9);
        img->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        m_pEquipFrame->addChild(img);
    }
}

