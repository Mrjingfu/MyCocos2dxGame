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
#include "AlertPopupUI.hpp"
#include "InformationPopupUI.h"
#include "GlobalPromptLayer.hpp"
#include "AchievePopupUI.h"
#include "AchieveItemPopupUI.hpp"
#include "DeadPopupUI.h"
PopupUILayerManager::PopupUILayerManager()
{
    m_pParentLayer = nullptr;
    m_pGlobalPromptlayer = nullptr;
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
    if (m_pParentLayer)
        m_pParentLayer = nullptr;
    if (m_pGlobalPromptlayer)
        m_pGlobalPromptlayer = nullptr;
    m_cCurrentPopUpType = ePopupInvalid;
    m_pLastPopUpType = ePopupInvalid;
    m_lTypeList.clear();
    for (int i=0; i<ePopupCount; i++) {
        if (m_pPopupContainer[i])
            m_pPopupContainer[i]->schedulerResume();
            m_pPopupContainer[i] = nullptr;
    }
}

PopupUILayer* PopupUILayerManager::openPopup(ePopupType type,int zorder /* = eZorderPopupUILayer */)
{
    //针对Prompt调用 因为首次打开popup 会暂停界面 得清除所有的
    if(m_pGlobalPromptlayer)
        m_pGlobalPromptlayer->clearGlobalPrompt();
    //end
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
        case ePopupAlert:
            popupLayer = AlertPopupUI::create();
            break;
        case ePopupInformation:
            popupLayer = InformationPopupUI::create();
            break;
        case ePopupAchieve:
            popupLayer = AchievePopupUI::create();
            break;
        case ePopupAchieveItem:
            popupLayer = AchieveItemPopupUI::create();
            break;
        case ePopupDead:
            popupLayer = DeadPopupUI::create();
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
        case TIP_WARNING:
            return cocos2d::Color3B(255,136,0);   //橘色
        case TIP_NEUTRAL:
            return cocos2d::Color3B(255,255,0);   //黄色
        case TIP_DODGE:
            return cocos2d::Color3B(0,255,0);     //闪避
        case TIP_BOLOCK:
            return cocos2d::Color3B(255,135,255); //格挡
        case TIP_ROLE_CRITICAL_STRIKE:
            return cocos2d::Color3B(255,0,0);     //红色
        case TIP_MONSTER_CRITICAL_STRIKE:
            return cocos2d::Color3B(255,255,0);   //暴击
        case TIP_EFFECT:
            return cocos2d::Color3B(107, 216, 176);
        default:
            break;
    }
    return cocos2d::Color3B(255,255,255);
}
void PopupUILayerManager::showStatusImport(TipTypes tipType, std::string text)
{
    
    if (nullptr == m_pGlobalPromptlayer) {
        m_pGlobalPromptlayer = GlobalPromptLayer::create();
        m_pParentLayer->addChild(m_pGlobalPromptlayer,eZOrderPopupLayer);
    }
    m_pGlobalPromptlayer->shwoGlobalPrompt(tipType, text);
  
}


