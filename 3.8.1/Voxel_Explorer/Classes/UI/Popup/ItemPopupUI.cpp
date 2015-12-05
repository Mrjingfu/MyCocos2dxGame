//
//  ItemPopupUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/26.
//
//

#include "ItemPopupUI.h"
#include "UtilityHelper.h"
#include "PlayerProperty.hpp"
#include "WeaponProperty.hpp"
#include "ArmorProperty.hpp"
#include "MagicOrnamentProperty.hpp"
#include "SecondWeaponProperty.hpp"
#include "EventConst.h"
#include "NoteUi.h"
#include "GameFormula.hpp"
#include "PopupUILayerManager.h"
#include "ItemMoneyLayer.hpp"
USING_NS_CC;
ItemPopupUI::ItemPopupUI()
{
    
    m_cActionType = eNone;
    m_pItemIcon    =nullptr;
    m_pItemName    =nullptr;
    m_pItemlv      =nullptr;
    m_pItemDesc    =nullptr;
    m_pItemType = nullptr;
    m_pItemIdentifyDesc= nullptr;;
    
    m_pAttrFrame    =nullptr;
    m_pItemPropFrame = nullptr;
    m_pBtnDiscard    =nullptr;
    m_pBtnEquip    =nullptr;
    m_pBackGround    =nullptr;
    m_pItemMoneyLayer =nullptr;
    m_pBottomFrame = nullptr;
    m_nItemId = -2;
    
}
ItemPopupUI::~ItemPopupUI()
{
    
}
bool ItemPopupUI::initUi()
{
     if(!load("itemPopupLayer.csb",false))
        return false;
    if (!initBottom())
        return false;
    return true;
}
bool ItemPopupUI::initBottom()
{
    cocos2d::Node*     m_pBottomNode = cocos2d::CSLoader::createNode("itemBottomLayer.csb");
    if (!m_pBottomNode)
        return false;
    
    m_pBottomFrame = dynamic_cast<ui::Layout*>(UtilityHelper::seekNodeByName(m_pBottomNode, "item_bottom_Layer"));
    if (!m_pBottomFrame)
        return false;
    
    m_pBtnDiscard = dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(m_pBottomNode, "item_btn_discard"));
    if (!m_pBtnDiscard)
        return false;
    
    m_pBtnEquip = dynamic_cast<ui::Button*>(UtilityHelper::seekNodeByName(m_pBottomNode, "item_btn_equip"));
    if (!m_pBtnEquip)
        return false;
    
    m_pBtnDiscard->addClickEventListener(CC_CALLBACK_1(ItemPopupUI::onClickDiscard, this));

    m_pBottomFrame->removeFromParentAndCleanup(false);
    
    return true;
}
bool ItemPopupUI::addEvents()
{
    
    m_pAttrFrame = dynamic_cast<ui::Layout*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_attr_layer"));
    if (!m_pAttrFrame)
        return false;

    m_pItemPropFrame= dynamic_cast<ui::Layout*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_prop_layer"));
    if (!m_pItemPropFrame)
        return false;
    
    m_pBackGround =   dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_background"));
    if (!m_pBackGround)
        return false;

    m_pItemIcon =   dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_icon"));
    if (!m_pItemIcon)
        return false;

 
    m_pItemName = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_name_text"));
    if (!m_pItemName)
        return false;
    m_pItemlv = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_lv_num_text"));
    if (!m_pItemlv)
        return false;
   
    m_pItemType = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_prop_type"));
    if (!m_pItemType)
        return false;
    m_pItemEquipDist = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_equip_dist"));
    if (!m_pItemEquipDist)
        return false;
    
    m_pItemNotIden = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "item_prop_not_idn"));
    if (!m_pItemNotIden)
        return false;
    
    m_pItemDesc = NoteUi::create();
    if (!m_pItemDesc)
        return false;
    
    m_pItemMoneyLayer = ItemMoneyLayer::create();
    m_pItemMoneyLayer->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
    
    m_pAttrFrame->setLayoutType(ui::Layout::Type::VERTICAL);
    m_pItemDesc->setFontScale(0.25);
    m_pItemDesc->setContentSize(cocos2d::Size(m_pAttrFrame->getContentSize().width,20));

    
    m_pItemName->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pItemlv->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pItemType->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pItemlv->setVisible(false);
    m_pItemEquipDist->setVisible(false);
    m_pItemNotIden->setVisible(false);
    m_pItemEquipDist->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pItemNotIden->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    m_pItemNotIden->setString(UtilityHelper::getLocalStringForUi("ITEM_NOT_IDENTIFY"));
    
    return true;
}

void ItemPopupUI::useItemFrame()
{
    PickableItemProperty* itemprop = getItemIdProperty();
    std::string str = itemprop->getDesc();
    ui::LinearLayoutParameter* linerParmter = ui::LinearLayoutParameter::create();
    linerParmter->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
    linerParmter->setMargin(ui::Margin(10,5,0,0));
    
    m_pItemDesc->setItemText(str);
    m_pItemDesc->setLayoutParameter(linerParmter);
    m_pAttrFrame->addChild(m_pItemDesc);

}

void ItemPopupUI::IdentifyEquiipFrame()
{
    PickableItemProperty* itemprop = getItemIdProperty();
    std::string str;
    if (itemprop->isIdentified()) {
        str = itemprop->getDesc();
    }else
    {
        str= itemprop->getBeforeIndentifyDesc();
    }
    
    int addAttrCount = 0;
    bool isdescAdd = false;
    std::vector<ADDED_EFFECT> effectList = itemprop->getAddedEffectList();
    int effectSize = effectList.size();

    std::sort(effectList.begin(),effectList.end(),std::less<ADDED_EFFECT>());
    Color3B effectColor = PopupUILayerManager::getInstance()->getTipsColor(TIP_EFFECT);
    
    ui::LinearLayoutParameter* linerParmter = ui::LinearLayoutParameter::create();
    linerParmter->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
    linerParmter->setMargin(ui::Margin(10,-7,0,0));
    
    if (itemprop->getPickableItemPropertyType() == PickableItemProperty::PIPT_WEAPON)
    {
        WeaponProperty* itemproperty = static_cast<WeaponProperty*>(itemprop);
        
        ui::LinearLayoutParameter* onelinerParmter = ui::LinearLayoutParameter::create();
        onelinerParmter->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
        onelinerParmter->setMargin(ui::Margin(10,0,0,0));
        
        addItemProp(StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_ATTACK").c_str(),int(itemproperty->getMinAttack()),int(itemproperty->getMaxAttack())),Color3B::WHITE,onelinerParmter);
        ++addAttrCount;
         std::string itemPropStr;
        for (int i = 0 ; i<effectSize; i++) {
            ADDED_EFFECT effect = effectList.at(i);
            if(effect ==AE_LIGHT_DISTANCE)
            {
                itemPropStr =  StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_LIGHT").c_str(),int(itemproperty->getAddedLightDistance()));
                
            }else if(effect ==AE_MAX_HP)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_HP").c_str(),int(itemproperty->getAddedMaxHp()));
             }else if(effect ==AE_MAX_MP)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MP").c_str(),int(itemproperty->getAddedMaxMp()));
                
            }else if(effect ==AE_MIN_ATTACK)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MIN_HURT").c_str(),int(itemproperty->getMinAttack()));
                
            }else if(effect ==AE_MAX_ATTACK)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MAX_HURT").c_str(),int(itemproperty->getAddedMaxAttack()));
                
            }else if(effect ==AE_MAGICITEM_FIND_RATE){
                
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MAGIC").c_str(),int(itemproperty->getAddedMagicItemFindRate().GetFloatValue()*100.0));
            }else if (effect == AE_CRITICALSTRICK_RATE)
            {
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_CRITICAL_STRIKE").c_str(),int(itemproperty->getAddedCriticalStrikeRate().GetFloatValue()*100.0));
            }else if (effect == AE_SEARCH_DISTANCE)
            {
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_SEQRCH").c_str(),int(itemproperty->getAddedSearchDistance()));
            }
            if (!itemPropStr.empty())
            {
                 addItemProp(itemPropStr,effectColor,linerParmter);
                ++addAttrCount;
            }
            
        }

        
    }else if (itemprop->getPickableItemPropertyType() == PickableItemProperty::PIPT_ARMOR)
    {
        ArmorProperty* itemproperty = static_cast<ArmorProperty*>(itemprop);
        
        ui::LinearLayoutParameter* onelinerParmter = ui::LinearLayoutParameter::create();
        onelinerParmter->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
        onelinerParmter->setMargin(ui::Margin(10,0,0,0));
        
        addItemProp(StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_DEFENSE").c_str(),int(itemproperty->getAddedDefense())), Color3B::WHITE,onelinerParmter);
        
        std::string itemPropStr;
        for (int i = 0 ; i<effectSize; i++) {
            ADDED_EFFECT effect = effectList.at(i);
            if(effect ==AE_LIGHT_DISTANCE)
            {
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_LIGHT").c_str(),int(itemproperty->getAddedLightDistance()));
              
                
            }else if(effect ==AE_MAX_HP)
            {
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_HP").c_str(),int(itemproperty->getAddedMaxHp()));

             }else if(effect ==AE_MAX_MP)
            {
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MP").c_str(),int(itemproperty->getAddedMaxMp()));
 
            }else if(effect ==AE_MAGICITEM_FIND_RATE){
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MAGIC").c_str(),int(itemproperty->getAddedMagicItemFindRate().GetFloatValue()*100.0));
                
            }else if (effect ==AE_SEARCH_DISTANCE)
            {
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_SEQRCH").c_str(),int(itemproperty->getAddedSearchDistance()));
            }
            else if (effect == AE_DODGE_RATE)
            {
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_DODGE").c_str(),int(itemproperty->getAddedDodgeRate().GetFloatValue()*100.0));
                
            }
        }
        if (!itemPropStr.empty())
        {
             ++addAttrCount;
             addItemProp(itemPropStr,effectColor,linerParmter);
        }
        

        
    }else if (itemprop->getPickableItemPropertyType() == PickableItemProperty::PIPT_MAGIC_ORNAMENT)
    {
        MagicOrnamentProperty* itemproperty = static_cast<MagicOrnamentProperty*>(itemprop);

        
        std::string itemPropStr;
        for (int i = 0 ; i<effectSize; i++) {
            ADDED_EFFECT effect = effectList.at(i);
            if(effect ==AE_LIGHT_DISTANCE)
            {
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_LIGHT").c_str(),int(itemproperty->getAddedLightDistance()));
 
            }else if(effect ==AE_MAX_HP)
            {
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_HP").c_str(),int(itemproperty->getAddedMaxHp()));
                
            }else if(effect ==AE_MAX_MP)
            {
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MP").c_str(),int(itemproperty->getAddedMaxMp()));
               
            }else if(effect ==AE_MIN_ATTACK)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MIN_HURT").c_str(),int(itemproperty->getAddedMinAttack()));
            }else if(effect ==AE_MAX_ATTACK)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MAX_HURT").c_str(),int(itemproperty->getAddedMaxAttack()));
                
            }else if(effect ==AE_MAGICITEM_FIND_RATE){
                
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MAGIC").c_str(),int(itemproperty->getAddedMagicItemFindRate().GetFloatValue()*100.0));
               
            }else if (effect ==AE_SEARCH_DISTANCE)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_SEQRCH").c_str(),int(itemproperty->getAddedSearchDistance()));
                
            }else if (effect == AE_DODGE_RATE)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_DODGE").c_str(),int(itemproperty->getAddedDodgeRate().GetFloatValue()*100.0));
            }else if (effect == AE_BLOCK_RATE)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_BLOCK").c_str(),int(itemproperty->getAddedBlockRate().GetFloatValue()*100.0));
                
            }else if (effect == AE_CRITICALSTRICK_RATE)
            {
                
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_CRITICAL_STRIKE").c_str(),int(itemproperty->getAddedCriticalStrikeRate().GetFloatValue()*100.0));
            }
            if (itemPropStr.empty())
                continue;
            if (i!=0)
            {
                addItemProp(itemPropStr,effectColor,linerParmter);
                ++addAttrCount;
            }
            
            else
            {
                ui::LinearLayoutParameter* onelinerParmter = ui::LinearLayoutParameter::create();
                onelinerParmter->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
                onelinerParmter->setMargin(ui::Margin(10,0,0,0));
                addItemProp(itemPropStr,effectColor,onelinerParmter);
                ++addAttrCount;
            }
        }
        
        
    }else if (itemprop->getPickableItemPropertyType() == PickableItemProperty::PIPT_SECOND_WEAPON)
    {
        SecondWeaponProperty* itemproperty = static_cast<SecondWeaponProperty*>(itemprop);
        
        std::string itemPropStr;
        for (int i = 0 ; i<effectSize; i++) {
            ADDED_EFFECT effect = effectList.at(i);
            if(effect ==AE_LIGHT_DISTANCE)
            {
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_LIGHT").c_str(),int(itemproperty->getAddedLightDistance()));
                
            }else if(effect ==AE_MAX_HP)
            {
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_HP").c_str(),int(itemproperty->getAddedMaxHp()));
                
            }else if(effect ==AE_MAX_MP)
            {
                itemPropStr = StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MP").c_str(),int(itemproperty->getAddedMaxMp()));
                
            }else if(effect ==AE_MIN_ATTACK)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MIN_HURT").c_str(),int(itemproperty->getAddedMinAttack()));
            }else if(effect ==AE_MAX_ATTACK)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MAX_HURT").c_str(),int(itemproperty->getAddedMaxAttack()));
                
            }else if(effect ==AE_MAGICITEM_FIND_RATE){
                
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_MAGIC").c_str(),int(itemproperty->getAddedMagicItemFindRate().GetFloatValue()*100.0));
                
            }else if (effect ==AE_SEARCH_DISTANCE)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_SEQRCH").c_str(),int(itemproperty->getAddedSearchDistance()));
                
            }else if (effect == AE_DODGE_RATE)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_DODGE").c_str(),int(itemproperty->getAddedDodgeRate().GetFloatValue()*100.0));
            }else if (effect == AE_BLOCK_RATE)
            {
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_BLOCK").c_str(),int(itemproperty->getAddedBlockRate().GetFloatValue()*100.0));
                
            }else if (effect == AE_CRITICALSTRICK_RATE)
            {
                
                itemPropStr =StringUtils::format(UtilityHelper::getLocalStringForUi("EQUIP_PROP_CRITICAL_STRIKE").c_str(),int(itemproperty->getAddedCriticalStrikeRate().GetFloatValue()*100.0));
            }
            if (itemPropStr.empty())
            {
                itemPropStr.clear();
                continue;
            }
            
            if (i!=0)
            {
                addItemProp(itemPropStr,effectColor,linerParmter);
                ++addAttrCount;
            }
            else
            {
                ui::LinearLayoutParameter* onelinerParmter = ui::LinearLayoutParameter::create();
                onelinerParmter->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
                onelinerParmter->setMargin(ui::Margin(10,0,0,0));
                addItemProp(itemPropStr,effectColor,onelinerParmter);
                ++addAttrCount;
            }
             itemPropStr.clear();
    
        }
    }
    
    if (!str.empty()) {
        m_pItemDesc->setItemText(str);
        m_pItemDesc->setLayoutParameter(linerParmter);
        m_pItemDesc->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        m_pAttrFrame->addChild(m_pItemDesc);
        isdescAdd = true;
    }

    
    cocos2d::Size addSize =cocos2d::Size::ZERO;
    
    if (addAttrCount>=2) {
        addSize = cocos2d::Size(0,11*addAttrCount+addSize.height);
    }

    if (!isdescAdd ) {
        addSize = cocos2d::Size(0,addSize.height-14);
    }
    
    updateItemPopupSize(addSize);
}
void ItemPopupUI::updateItemPopupSize(cocos2d::Size addSize)
{
    m_pAttrFrame->setContentSize(cocos2d::Size(m_pAttrFrame->getContentSize() + addSize));
    m_pRootNode->setContentSize(m_pRootNode->getContentSize()+addSize);
    m_pBackGround->setContentSize(m_pRootNode->getContentSize());
    m_pBackGround->setPosition(m_pRootNode->getContentSize()*0.5);
    m_pItemPropFrame->setPosition(Vec2(m_pItemPropFrame->getPositionX(), m_pRootNode->getContentSize().height));

}
void ItemPopupUI::addMoneyUI()
{
    
    cocos2d::Size addSize = cocos2d::Size::ZERO;
    
    if (m_pItemMoneyLayer) {

        ui::LinearLayoutParameter* lastlinerParmter = ui::LinearLayoutParameter::create();
        lastlinerParmter->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
        if (m_pAttrFrame->getChildrenCount() <=0) {
            lastlinerParmter->setMargin(ui::Margin(0,5,0,0));
        }else
        {
            lastlinerParmter->setMargin(ui::Margin(0,-7,0,0));
        }
        addSize = addSize +cocos2d::Size(0,m_pItemMoneyLayer->getContentSize().height);
        m_pItemMoneyLayer->setLayoutParameter(lastlinerParmter);
        m_pItemMoneyLayer->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        m_pAttrFrame->addChild(m_pItemMoneyLayer);
    }

    updateItemPopupSize(addSize);
}
void ItemPopupUI::addBottomUI()
{

    cocos2d::Size addSize = cocos2d::Size::ZERO;
    if (m_pBottomFrame) {

        ui::LinearLayoutParameter* lastlinerParmter = ui::LinearLayoutParameter::create();
        lastlinerParmter->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
        lastlinerParmter->setMargin(ui::Margin(0,2,0,0));
        
        addSize = cocos2d::Size(0,m_pBottomFrame->getContentSize().height);
        m_pBottomFrame->setLayoutParameter(lastlinerParmter);
        m_pBottomFrame->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        m_pAttrFrame->addChild(m_pBottomFrame);
    }
    
    
    updateItemPopupSize(addSize);
}
PickableItemProperty* ItemPopupUI::getItemIdProperty() const
{
    if (m_nItemId!=-2) {
        return PlayerProperty::getInstance()->getItemFromBag(CChaosNumber(m_nItemId));
    }
    return nullptr;
}
void ItemPopupUI::refreshUIView()
{
    updateItemBaseProp();
    
    updateItemAttrUI();
}
void ItemPopupUI::setItemId(int itemId)
{
    m_nItemId = itemId;
    CCLOG("m_nItemId:%d",m_nItemId);
    
    refreshUIView();
}
void ItemPopupUI::updateItemBaseProp()
{
    PickableItemProperty* itemprop = getItemIdProperty();
    CCASSERT(itemprop!=nullptr, "itemprop is null!");
    m_pItemIcon->loadTexture(itemprop->getIconRes(),cocos2d::ui::Widget::TextureResType::PLIST);
    m_pItemIcon->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    
    m_pItemName->setString(itemprop->getName());
    //设置品质
    switch (itemprop->getQuality()) {
        case PIQ_GENERAL:
            m_pItemName->setTextColor(Color4B(Color3B::WHITE));
            break;
        case PIQ_RARE:
            m_pItemName->setTextColor(Color4B(Color3B::BLUE));
            break;
        case PIQ_EPIC:
            m_pItemName->setTextColor(Color4B(Color3B(255,0,255)));
            break;
        case PIQ_LEGEND:
            m_pItemName->setTextColor(Color4B(Color3B(250,128,10)));
            break;
    }
    
    PickableItemProperty::PickableItemPropertyType itemtype =itemprop->getPickableItemPropertyType();
    std::string str;
    if (itemtype == ArmorProperty::PIPT_KEY) {
        str = UtilityHelper::getLocalStringForUi("ITEM_PROP_TYPE_KEY");
    }else if (itemtype == ArmorProperty::PIPT_WEAPON)
    {
        str = UtilityHelper::getLocalStringForUi("ITEM_PROP_TYPE_WEAPON");
    }else if (itemtype == ArmorProperty::PIPT_SECOND_WEAPON)
    {
        str = UtilityHelper::getLocalStringForUi("ITEM_PROP_TYPE_SECOND_WEAPON");
    }else if (itemtype == ArmorProperty::PIPT_MAGIC_ORNAMENT)
    {
        str = UtilityHelper::getLocalStringForUi("ITEM_PROP_TYPE_MAGIC_ORNAMENT");
    }else if (itemtype == ArmorProperty::PIPT_SCROLL)
    {
        str = UtilityHelper::getLocalStringForUi("ITEM_PROP_TYPE_SCROLL");
    }else if (itemtype == ArmorProperty::PIPT_POTIONS)
    {
        str = UtilityHelper::getLocalStringForUi("ITEM_PROP_TYPE_POTIONS");
    }else if (itemtype == ArmorProperty::PIPT_MATERIAL)
    {
        str = UtilityHelper::getLocalStringForUi("ITEM_PROP_TYPE_MATERIAL");
    }else if (itemtype == ArmorProperty::PIPT_QUEST)
    {
        str = UtilityHelper::getLocalStringForUi("ITEM_PROP_TYPE_QUEST");
    }else if (itemtype == ArmorProperty::PIPT_SUNDRIES)
    {
        str = UtilityHelper::getLocalStringForUi("ITEM_PROP_TYPE_SUNDRIES");
    }
    
    m_pItemType->setString(str);
    if (itemprop->isStackable() && itemprop->getCount()>1 ) {
         m_pItemMoneyLayer->updateItemMoney(itemprop->getValueCopper()*itemprop->getCount().GetLongValue());
    }else
         m_pItemMoneyLayer->updateItemMoney(itemprop->getValueCopper());
   
}
void ItemPopupUI::updateEquipItem()
{
    PickableItemProperty* itemprop = getItemIdProperty();
    CCASSERT(itemprop!=nullptr, "itemprop is null!");
    if (m_pBtnEquip) 
        m_pBtnEquip->addClickEventListener(CC_CALLBACK_1(ItemPopupUI::onClickEquip, this));
    bool isNotEquip = false;
    m_pItemlv->setVisible(true);
    m_pItemlv->setString(StringUtils::format("LV.%ld",itemprop->getLevel().GetLongValue()));
    //添加装备属性
    IdentifyEquiipFrame();

    
    //装备等级>人物等级不可装备
    if ( itemprop->getLevel().GetLongValue() > PlayerProperty::getInstance()->getLevel().GetLongValue()) {
        m_pItemlv->setTextColor(Color4B(PopupUILayerManager::getInstance()->getTipsColor(TIP_NEGATIVE)));
        std::string str = UtilityHelper::getLocalStringForUi("NOT_EQUIP_LEVEL_ENOUGH");
        
        ui::LinearLayoutParameter* linerParmter = ui::LinearLayoutParameter::create();
        linerParmter->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::CENTER_VERTICAL);
        if (m_pAttrFrame->getChildrenCount() <=0) {
            linerParmter->setMargin(ui::Margin(10,5,0,0));
        }else
        {
            linerParmter->setMargin(ui::Margin(10,-7,0,0));
        }
        
        
        addItemProp(str,PopupUILayerManager::getInstance()->getTipsColor(TIP_NEGATIVE),linerParmter);
        updateItemPopupSize(cocos2d::Size(0,11));
        
        isNotEquip = true;
    }
    
    addMoneyUI();

    if (itemprop->isEquipable() ) {
        //如果当前道具就是装备道具不添加底部UI
        if (PlayerProperty::getInstance()->getEquipedWeaponID() == m_nItemId ||
            PlayerProperty::getInstance()->getEquipedArmorID() == m_nItemId ||
            PlayerProperty::getInstance()->getEquipedOrnamentsID() == m_nItemId||
            PlayerProperty::getInstance()->getEquipedSecondWeaponID() == m_nItemId){
            
            m_pItemEquipDist->setVisible(true);
            m_pItemEquipDist->setString(UtilityHelper::getLocalStringForUi("ITEM_ALREDY_EQUIP"));
        }else
            addBottomUI();
    }else
    {
         addBottomUI();
        isNotEquip = true;
    }
    //未鉴定道具也不可以装备
    if (!itemprop->isIdentified())
    {
        isNotEquip = true;
        m_pItemNotIden->setVisible(true);
    }
    
    //不可装备的隐藏装备按钮,显示不可装备文本,改变删除按钮位置
    if (isNotEquip) {
        m_pItemEquipDist->setVisible(true);
        m_pItemEquipDist->setString(UtilityHelper::getLocalStringForUi("ITEM_NOT_EQUIP"));
        m_pItemEquipDist->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        m_pItemEquipDist->setColor(PopupUILayerManager::getInstance()->getTipsColor(TIP_NEGATIVE));
        if (m_pBtnDiscard) {
            m_pBtnDiscard->setVisible(false);
        }
        if (m_pBtnEquip) {
            m_pBtnEquip->setPosition(m_pBottomFrame->getContentSize()*0.5);
            m_pBtnEquip->setTitleText("Discard");
            m_pBtnEquip->addClickEventListener(CC_CALLBACK_1(ItemPopupUI::onClickDiscard, this));
        }
    }
    
}
void ItemPopupUI::updateUseItem()
{
    if (m_pBtnEquip)
        m_pBtnEquip->addClickEventListener(CC_CALLBACK_1(ItemPopupUI::onClickUser, this));
    
    PickableItemProperty* itemprop = getItemIdProperty();
    CCASSERT(itemprop!=nullptr, "itemprop is null!");
    if (itemprop->isStackable() && itemprop->getCount()>1) {
        m_pItemEquipDist->setVisible(true);
        m_pItemEquipDist->setString(StringUtils::format("X%d",int(itemprop->getCount())));

    }
    
    useItemFrame();
    addMoneyUI();
    addBottomUI();
    if (m_pBtnEquip) {
        m_pBtnEquip->setTitleFontName(UtilityHelper::getLocalString("FONT_NAME"));
        m_pBtnEquip->setTitleText("USE");
    }
    
}
void ItemPopupUI::updateItemAttrUI()
{
    
    PickableItemProperty* itemprop = getItemIdProperty();
    CCASSERT(itemprop!=nullptr, "itemprop is null!");
    
    PickableItemProperty::PickableItemPropertyType itemtype =itemprop->getPickableItemPropertyType();
    
    if (itemtype ==PickableItemProperty::PIPT_WEAPON ||itemtype ==PickableItemProperty::PIPT_SECOND_WEAPON||
        itemtype ==PickableItemProperty::PIPT_ARMOR ||itemtype ==PickableItemProperty::PIPT_MAGIC_ORNAMENT ) {
        //更新装备道具UI
        updateEquipItem();
        
    }else{
        //更新使用道具UI
        updateUseItem();
    }
    
    
}
void ItemPopupUI::onClickDiscard(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    CCLOG("onClickDiscard");
    PickableItemProperty* itemprop = getItemIdProperty();
    CCASSERT(itemprop!=nullptr, "itemprop is null!");
    bool isSuccess = false;
    if (itemprop->isStackable()) {
        isSuccess = PlayerProperty::getInstance()->removeStackableItemFromBag(itemprop->getPickableItemType(), 1);
    }else{
        isSuccess = PlayerProperty::getInstance()->removeItemFromBag(CChaosNumber(m_nItemId));
    }
    
    if(isSuccess)
        closePopup();
    
}
void ItemPopupUI::onClickUser(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    CCLOG("onClickUser");
    PickableItemProperty* itemprop = getItemIdProperty();
    CCASSERT(itemprop!=nullptr, "itemprop is null!");
    PickableItemProperty::PickableItemPropertyType itemtype =itemprop->getPickableItemPropertyType();
     bool isItemUse = false;
    if (itemtype == PickableItemProperty::PIPT_POTIONS)
    {
        isItemUse = PlayerProperty::getInstance()->usePotion(CChaosNumber(m_nItemId));
    }else if (itemtype == PickableItemProperty::PIPT_SCROLL)
    {
        isItemUse = PlayerProperty::getInstance()->useScroll(CChaosNumber(m_nItemId));
    }else if (itemtype == PickableItemProperty::PIPT_KEY)
    {
        isItemUse = PlayerProperty::getInstance()->useKey(itemprop->getPickableItemType());
    }
    if (!isItemUse) {
      
        CCLOG("使用道具失败");
    }

}
void ItemPopupUI::onClickEquip(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    CCLOG("onClickEquip");
    PickableItemProperty* itemprop = getItemIdProperty();
    CCASSERT(itemprop!=nullptr, "itemprop is null!");
    bool isEquipSuccess = false;
    if (itemprop->getPickableItemPropertyType() == PickableItemProperty::PIPT_WEAPON) {
        
        isEquipSuccess = PlayerProperty::getInstance()->equipWeapon(CChaosNumber(m_nItemId));
        
    }else if (itemprop->getPickableItemPropertyType() == PickableItemProperty::PIPT_ARMOR){
        
        isEquipSuccess = PlayerProperty::getInstance()->equipArmor(CChaosNumber(m_nItemId));
        
    }else if (itemprop->getPickableItemPropertyType() == PickableItemProperty::PIPT_MAGIC_ORNAMENT)
    {
        isEquipSuccess = PlayerProperty::getInstance()->equipOrnaments(CChaosNumber(m_nItemId));
        
    }else if (itemprop->getPickableItemPropertyType() == PickableItemProperty::PIPT_SECOND_WEAPON)
    {
        isEquipSuccess = PlayerProperty::getInstance()->equipSecondWeapon(CChaosNumber(m_nItemId));
    }
    if (isEquipSuccess) {
        closePopup();
    }else{
        //装备失败 或者提前给出提示
        CCLOG("装备失败 ");
    }
}
void ItemPopupUI::addItemProp(std::string propStr,cocos2d::Color3B fontColor,cocos2d::ui::LinearLayoutParameter* paramLayout)
{
    NoteUi* itemNote = NoteUi::create();
    itemNote->setFontScale(0.25);
    itemNote->setContentSize(cocos2d::Size(m_pAttrFrame->getContentSize().width,20));
    itemNote->setItemText(propStr,fontColor);
    if (paramLayout)
        itemNote->setLayoutParameter(paramLayout);
    itemNote->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    m_pAttrFrame->addChild(itemNote);
}

void ItemPopupUI::closePopup()
{
    
    if(m_pPopupType == ePopupItem)
    {
        PopupUILayer* pLayer = nullptr;
        if (PopupUILayerManager::getInstance()->isOpenPopup(ePopupEquipItem,pLayer)) {
            ItemPopupUI* itemPopupUi = static_cast<ItemPopupUI*>(pLayer);
            if (itemPopupUi) {
                itemPopupUi->closePopup();
            }
        }
        
    }
    outAction();
   
    
}
