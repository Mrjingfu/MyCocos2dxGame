//
//  GameUILayer.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/16.
//
//

#include "GameUILayer.h"
#include "UtilityHelper.h"
#include "GameConfig.h"
#include "PopupUILayerManager.h"
USING_NS_CC;
GameUILayer::GameUILayer()
{
    
}
GameUILayer::~GameUILayer()
{
    
}
bool GameUILayer::addEvents()
{
      
    ui::ImageView* btn_role = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "btn_role"));
    if (!btn_role)
        return false;
    btn_role->setTouchEnabled(true);
    btn_role->addClickEventListener(CC_CALLBACK_1(GameUILayer::onClickRole, this));
    
    ui::ImageView* progress_blood_bg = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "progress_role_blood_bg"));
    if (!progress_blood_bg)
        return false;

    
    ui::ImageView* progress_margic_bg = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "progress_role_margic_bg"));
    if (!progress_margic_bg)
        return false;
   
    
//    ui::LoadingBar* progress_blood = dynamic_cast<ui::LoadingBar*>(UtilityHelper::seekNodeByName(m_pRootNode, "progress_role_blood"));
//    if (!progress_blood)
//        return false;
//    progress_blood->setScale9Enabled(true);
//    
//    ui::LoadingBar* progress_margic = dynamic_cast<ui::LoadingBar*>(UtilityHelper::seekNodeByName(m_pRootNode, "progress_role_margic"));
//    if (!progress_margic)
//        return false;
//    progress_margic->setScale9Enabled(true);
    

    return true;
}
void GameUILayer::onClickRole(Ref* ref)
{
    CHECK_ACTION(ref);
    PopupUILayerManager::getInstance()->openPopup(ePopupRole);
}