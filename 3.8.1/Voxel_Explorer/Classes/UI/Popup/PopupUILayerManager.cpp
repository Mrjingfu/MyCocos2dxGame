//
//  PopupUILayerManager.cpp
//  Tone_Skipper
//
//  Created by 创李 on 15/9/18.
//
//

#include "PopupUILayerManager.h"
#include "RolePopUpUI.h"
#include "ItemPopupUI.h"
#include "UtilityHelper.h"
#include "InfoPopupUI.h"
#include "ShopPopupUI.h"
#include "PausePopupUI.h"
#include "ItemShopBuyPopupUI.hpp"
#include "ItemShopSellPopupUI.hpp"
#include "WeaponShopPopupUI.h"
#include "MagicShopPopupUI.h"
#include "TaskPopupUI.hpp"
#include "AlchemyShopPopupUI.hpp"
#include "GambleShopPopupUI.hpp"
#include "OldManPopupUI.hpp"
#include "LittleWitchPopupUI.hpp"
#include "NursePopupUI.hpp"
#include "DialoguePopupUI.hpp"
PopupUILayerManager::PopupUILayerManager()
{
    m_pParentLayer = nullptr;
    
    for (int i=0; i<ePopupCount; i++) {
        m_pPopupContainer[i] = nullptr;
    }
    m_cCurrentPopUpType = ePopupInvalid;
    m_pLastPopUpType = ePopupInvalid;
    m_lTypeList.clear();
}
PopupUILayerManager::~PopupUILayerManager()
{
    
}
PopupUILayerManager* PopupUILayerManager::getInstance()
{
    static PopupUILayerManager s_instance;
    return &s_instance;
}

PopupUILayer* PopupUILayerManager::getCurrentPopUpLayer()
{
    if (m_cCurrentPopUpType == ePopupInvalid)
        return nullptr;
    else
        return m_pPopupContainer[m_cCurrentPopUpType];
}
PopupUILayer* PopupUILayerManager::getPopUpLayerByType(ePopupType type)
{
    if (type <=ePopupInvalid || type>=ePopupCount)
        return nullptr;
    else
        return m_pPopupContainer[type];
}

void PopupUILayerManager::onExitScene()
{
    m_cCurrentPopUpType = ePopupInvalid;
    m_pLastPopUpType = ePopupInvalid;
    m_lTypeList.clear();
}

PopupUILayer* PopupUILayerManager::openPopup(ePopupType type,int zorder /* = eZorderPopupUILayer */)
{
    m_pLastPopUpType = m_cCurrentPopUpType;
    if(m_cCurrentPopUpType!= ePopupInvalid)
    {
        m_lTypeList.push_front(m_cCurrentPopUpType);
        m_cCurrentPopUpType = type;
    }else
    {
        m_cCurrentPopUpType = type;
    }
    m_pPopupContainer[m_cCurrentPopUpType] = initPopUp(m_cCurrentPopUpType);
    
    PopupUILayer* popupLayer = m_pPopupContainer[m_cCurrentPopUpType];
    popupLayer->setPopupType(m_cCurrentPopUpType);
    
    if(popupLayer->getParent())
        return popupLayer;
    //有摄像机的情况需要设置对应的CameraMask
//    popupLayer->setCameraMask((unsigned short)cocos2d::CameraFlag::USER3);
    popupLayer->setZOrder(zorder);
    m_pParentLayer->addChild(popupLayer);
    popupLayer->openPopup();
    
    return popupLayer;
}

PopupUILayer* PopupUILayerManager::initPopUp(ePopupType type)
{
    PopupUILayer* popupLayer = nullptr;
    switch (type) {
        case ePopupRole:
            popupLayer = RolePopupUI::create();
            break;
        case ePopupItem:
            popupLayer = ItemPopupUI::create();
            break;
        case ePopupInfo:
            popupLayer = InfoPopupUI::create();
            break;
        case ePopupEquipItem:
            popupLayer = ItemPopupUI::create();
            break;
        case ePopupPause:
            popupLayer = PausePopupUI::create();
            break;
        case ePopupItemShopBuy:
            popupLayer = ItemShopBuyPopupUI::create();
            break;
        case ePopupItemShopSell:
            popupLayer = ItemShopSellPopupUI::create();
            break;
        case ePopupWeaponShop:
            popupLayer = WeaponShopPopupUI::create();
            break;
        case ePopupMagicShop:
            popupLayer = MagicShopPopupUI::create();
            break;
        case ePopupGambleShop:
            popupLayer = GambleShopPopupUI::create();
            break;
        case ePopupAlchemyShop:
            popupLayer = AlchemyShopPopupUI::create();
            break;
        case ePopupNurse:
            popupLayer = NursePopupUI::create();
            break;
        case ePopupLittleWitch:
            popupLayer = LittleWitchPopupUI::create();
             break;
        case ePopupOldMan:
            popupLayer = OldManPopupUI::create();
            break;
        case ePopupTask:
            popupLayer = TaskPopupUI::create();
            break;
        case ePopupDialogue:
            popupLayer = DialoguePopupUI::create();
            break;
        default:
            break;
    }
    return popupLayer;
}

void PopupUILayerManager::closeAllPopup()
{
    for (int i= 0 ;i<ePopupCount;i++)
    {
        PopupUILayer* popup =  m_pPopupContainer[i];
        if (popup) {
            popup->closePopup();
        }
    }
}
void PopupUILayerManager::closeCurrentPopup()
{
    if (nullptr !=m_pPopupContainer[m_cCurrentPopUpType] && m_pPopupContainer[m_cCurrentPopUpType]->getParent()) {
        m_pPopupContainer[m_cCurrentPopUpType]->closePopup();
    }
}
void PopupUILayerManager::setParentLayer(cocos2d::Layer *parent)
{
    m_pParentLayer = parent;
}
void PopupUILayerManager::resetPopupType(ePopupType type)
{
    if (!m_lTypeList.empty())
    {
        if (type == m_cCurrentPopUpType)
        {
            //关闭的是m_currentPopUpType
            m_cCurrentPopUpType = m_lTypeList.front();
            m_lTypeList.pop_front();
        }else
        {
            //关闭的不是m_currentPopUpType而是list里的，此时m_currentPopUpType不变
            std::list<ePopupType> typeList;
            typeList.clear();
            for (auto iter = m_lTypeList.begin(); iter != m_lTypeList.end(); iter++) {
                ePopupType tmp = *iter;
                if (type != tmp) {
                    typeList.push_back(tmp);
                }
            }
            m_lTypeList.clear();
            for (auto iter = typeList.begin(); iter!=typeList.end(); iter++) {
                m_lTypeList.push_back(*iter);
            }
        }
    }else
    {
        m_cCurrentPopUpType = ePopupInvalid;
    }
}
bool PopupUILayerManager::isOpenPopup(ePopupType type, PopupUILayer *&pLayer)
{
    for (auto iter = m_lTypeList.begin(); iter!=m_lTypeList.end(); iter++)
    {
        if (type == *iter)
        {
            pLayer = m_pPopupContainer[type];
            return  true;
        }
    }
    if (type==m_cCurrentPopUpType) {
        pLayer = m_pPopupContainer[type];
        return true;
    }
    return false;
}

cocos2d::Color3B PopupUILayerManager::getTipsColor(TipTypes tipType)
{
    switch (tipType) {
        case TIP_DEFAULT:
            return cocos2d::Color3B(255,255,255);  //白色
        case TIP_POSITIVE:
            return cocos2d::Color3B(0,255,0);     //绿色
        case TIP_NEGATIVE:
            return cocos2d::Color3B(255,0,0);     //红色
        case TIP_QUESTION:
        case TIP_WARNING:
            return cocos2d::Color3B(255,136,0);   //橘色
        case TIP_NEUTRAL:
            return cocos2d::Color3B(255,255,0);   //黄色
        case TIP_DODGE:
            return cocos2d::Color3B(0,255,0);     //闪避
        case TIP_BOLOCK:
            return cocos2d::Color3B(255,135,255); //格挡
        case TIP_CRITICAL_STRIKE:
            return cocos2d::Color3B(255,255,0);   //暴击
        case TIP_EFFECT:
            return cocos2d::Color3B(107, 216, 176);
        case TIP_BLUE:
            return cocos2d::Color3B(0, 127, 224);
        default:
            break;
    }
    return cocos2d::Color3B(255,255,255);
}
void PopupUILayerManager::showStatusImport(TipTypes tipType, std::string text)
{
//    int charCount = 0;
//    if(cocos2d::Application::getInstance()->getCurrentLanguage() ==cocos2d::LanguageType::CHINESE)
//    {
//        charCount =10;
//    }else{
//        charCount = 40;
//    }
//    UtilityHelper::getLineStr(text, charCount);
    Label* m_pLabel = cocos2d::Label::createWithTTF(text,UtilityHelper::getLocalString("FONT_NAME"),36);
    m_pLabel->setScale(0.8);
    m_pLabel->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    m_pParentLayer->addChild(m_pLabel,eZOrderPopupLayer);
    m_pLabel->setPosition(Vec2(WND_CENTER_X,SCREEN_HEIGHT*0.65));
    m_pLabel->setTextColor(cocos2d::Color4B(getTipsColor(tipType)));
//    m_pLabel->enableOutline(cocos2d::Color4B::BLUE,1);
    cocos2d::MoveTo*  moveTo = cocos2d::MoveTo::create(0.5,Vec2(WND_CENTER_X,SCREEN_HEIGHT*0.73));
    cocos2d::DelayTime* delay = cocos2d::DelayTime::create(1.0f);
    cocos2d::FadeOut* fadeOut = cocos2d::FadeOut::create(0.2);
    m_pLabel->resume();
    m_pLabel->runAction(cocos2d::Sequence::create(moveTo,delay,fadeOut,RemoveSelf::create(), nil));

    
}
void PopupUILayerManager::showStatus(TipTypes tipType,  std::string text,cocos2d::Vec2 pos)
{
    Label* m_pLabel = cocos2d::Label::createWithTTF(text,UtilityHelper::getLocalString("FONT_NAME"),36);
    m_pLabel->setScale(0.5);
    m_pLabel->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    m_pParentLayer->addChild(m_pLabel);
    m_pLabel->setPosition(pos);
    m_pLabel->setTextColor(cocos2d::Color4B(getTipsColor(tipType)));
    if (tipType == TIP_CRITICAL_STRIKE) {
        cocos2d::ScaleTo* ScaleTo1 = cocos2d::ScaleTo::create(0.3, 0.8);
        cocos2d::MoveBy* moveBy = cocos2d::MoveBy::create(0.3, Vec2(0, 30.0f));
        cocos2d::DelayTime* delay = cocos2d::DelayTime::create(0.2);
        cocos2d::FadeOut* fadeOut = cocos2d::FadeOut::create(0.2);
        m_pLabel->runAction(cocos2d::Sequence::create(cocos2d::Spawn::createWithTwoActions(moveBy, ScaleTo1),delay,fadeOut,RemoveSelf::create(), nil));
    }
    else
    {
        cocos2d::MoveBy* moveBy = cocos2d::MoveBy::create(0.5, cocos2d::Vec2(0,20.0f));
        cocos2d::DelayTime* delay = cocos2d::DelayTime::create(0.2);
        cocos2d::FadeOut* fadeOut = cocos2d::FadeOut::create(0.2);
        m_pLabel->runAction(cocos2d::Sequence::create(moveBy,delay,fadeOut,RemoveSelf::create(), nil));
    }

}

