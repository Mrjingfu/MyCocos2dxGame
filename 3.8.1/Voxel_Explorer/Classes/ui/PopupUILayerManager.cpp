//
//  PopupUILayerManager.cpp
//  Tone_Skipper
//
//  Created by 创李 on 15/9/18.
//
//

#include "PopupUILayerManager.h"
#include "BagPopUpUi.h"

PopupUILayerManager::PopupUILayerManager()
{
    m_pParentLayer = nullptr;
    
    for (int i=0; i<ePopupCount; i++) {
        m_pPopupContainer[i] = nullptr;
    }
    m_pCurrentPopUpType = ePopupInvalid;
    m_pLastPopUpType = ePopupInvalid;
    m_pTypeList.clear();
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
    if (m_pCurrentPopUpType == ePopupInvalid)
        return nullptr;
    else
        return m_pPopupContainer[m_pCurrentPopUpType];
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
    m_pCurrentPopUpType = ePopupInvalid;
    m_pLastPopUpType = ePopupInvalid;
    m_pTypeList.clear();
}

PopupUILayer* PopupUILayerManager::openPopup(ePopupType type,int zorder /* = eZorderPopupUILayer */)
{
    m_pLastPopUpType = m_pCurrentPopUpType;
    if(m_pCurrentPopUpType!= ePopupInvalid)
    {
        m_pTypeList.push_front(m_pCurrentPopUpType);
        m_pCurrentPopUpType = type;
    }else
    {
        m_pCurrentPopUpType = type;
    }
    m_pPopupContainer[m_pCurrentPopUpType] = initPopUp(m_pCurrentPopUpType);
    
    PopupUILayer* popupLayer = m_pPopupContainer[m_pCurrentPopUpType];
    popupLayer->setPopupType(m_pCurrentPopUpType);
    
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
        case ePopupBag:
            popupLayer = BagPopUpUi::create();
            break;
        case ePopupTest:
//            popupLayer = TestPopUI::create();
        default:
            break;
    }
    return popupLayer;
}
void PopupUILayerManager::closeCurrentPopup()
{
    if (nullptr !=m_pPopupContainer[m_pCurrentPopUpType] && m_pPopupContainer[m_pCurrentPopUpType]->getParent()) {
        m_pPopupContainer[m_pCurrentPopUpType]->closePopup();
    }
}
void PopupUILayerManager::setParentLayer(cocos2d::Layer *parent)
{
    m_pParentLayer = parent;
}
void PopupUILayerManager::resetPopupType(ePopupType type)
{
    if (!m_pTypeList.empty())
    {
        if (type == m_pCurrentPopUpType)
        {
            m_pCurrentPopUpType = m_pTypeList.front();
            m_pTypeList.pop_front();
        }else
        {
            std::list<ePopupType> typeList;
            typeList.clear();
            for (auto iter = m_pTypeList.begin(); iter != m_pTypeList.end(); iter++) {
                ePopupType tmp = *iter;
                if (type != tmp) {
                    typeList.push_back(tmp);
                }
            }
            m_pTypeList.clear();
            for (auto iter = typeList.begin(); iter!=typeList.end(); iter++) {
                m_pTypeList.push_back(*iter);
            }
        }
    }else
    {
        m_pCurrentPopUpType = ePopupInvalid;
    }
}
bool PopupUILayerManager::isOpenPopup(ePopupType type, PopupUILayer *&pLayer)
{
    for (auto iter = m_pTypeList.begin(); iter!=m_pTypeList.end(); iter++)
    {
        if (type == *iter)
        {
            pLayer = m_pPopupContainer[type];
            return  true;
        }
    }
    if (type==m_pCurrentPopUpType) {
        pLayer = m_pPopupContainer[type];
        return true;
    }
    return false;
}


