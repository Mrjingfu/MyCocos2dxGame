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
#include "EquipItemPopupUI.h"
#include "UtilityHelper.h"

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
        case ePopupEquipItem:
            popupLayer = EquipItemPopupUI::create();
        default:
            break;
    }
    return popupLayer;
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
            m_cCurrentPopUpType = m_lTypeList.front();
            m_lTypeList.pop_front();
        }else
        {
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
void PopupUILayerManager::showStatus(TipTypes tipType, cocos2d::Vec2 pos, std::string text)
{
    Label* m_pLabel = cocos2d::Label::createWithSystemFont(text,UtilityHelper::getLocalString("FONT_NAME"),36);
    m_pLabel->setScale(0.4);
    m_pLabel->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    m_pParentLayer->addChild(m_pLabel);
    m_pLabel->setPosition(pos);
    switch (tipType) {
        case TIP_DEFAULT:
            m_pLabel->setTextColor(cocos2d::Color4B(cocos2d::Color3B(255,255,255)));
            break;
        case TIP_POSITIVE:
            m_pLabel->setTextColor(cocos2d::Color4B(cocos2d::Color3B(0,255,0)));
            break;
        case TIP_NEGATIVE:
        case TIP_DODGE:
        case TIP_BOLOCK:
        case TIP_CRITICAL_STRIKE:
            m_pLabel->setTextColor(cocos2d::Color4B(cocos2d::Color3B(255,0,0)));
            break;
        case TIP_WARNING:
            m_pLabel->setTextColor(cocos2d::Color4B(cocos2d::Color3B(255,136,0)));
            break;
        case TIP_NEUTRAL:
            m_pLabel->setTextColor(cocos2d::Color4B(cocos2d::Color3B(255,255,0)));
            break;
        default:
            break;
    }
    if (tipType != TIP_CRITICAL_STRIKE ) {
        cocos2d::ScaleTo* ScaleTo1 = cocos2d::ScaleTo::create(0.8, 0.8);
        cocos2d::MoveBy* moveBy = cocos2d::MoveBy::create(0.8, cocos2d::Vec2(0,30.0f));
        cocos2d::FadeOut* fadeOut = cocos2d::FadeOut::create(0.2);
        cocos2d::CallFunc* delFunc = cocos2d::CallFunc::create(CC_CALLBACK_0(RemoveSelf::create, this));
        m_pLabel->runAction(cocos2d::Sequence::create(cocos2d::Spawn::createWithTwoActions(moveBy, ScaleTo1),fadeOut,delFunc, nil));
    }else
    {
        cocos2d::MoveBy* moveBy = cocos2d::MoveBy::create(0.8, cocos2d::Vec2(0,30.0f));
        cocos2d::FadeOut* fadeOut = cocos2d::FadeOut::create(0.2);
        cocos2d::CallFunc* delFunc = cocos2d::CallFunc::create(CC_CALLBACK_0(RemoveSelf::create, this));
        m_pLabel->runAction(cocos2d::Sequence::create(moveBy,fadeOut,delFunc, nil));
    }

}

