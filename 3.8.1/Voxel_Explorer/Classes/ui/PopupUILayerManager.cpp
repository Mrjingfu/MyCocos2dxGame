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


