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
    btn_role->addTouchEventListener(CC_CALLBACK_2(GameUILayer::onTouchRole, this));
    return true;
}
void GameUILayer::onTouchRole(cocos2d::Ref *ref, cocos2d::ui::Widget::TouchEventType type)
{
    CHECK_ACTION_WRAPPER(ref,type);
    PopupUILayerManager::getInstance()->openPopup(ePopupRole);
}