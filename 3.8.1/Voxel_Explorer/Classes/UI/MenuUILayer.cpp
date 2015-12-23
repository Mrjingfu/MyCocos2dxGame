//
//  MenuUILayer.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/20.
//
//

#include "MenuUILayer.h"
#include "UtilityHelper.h"
#include "GameConfig.h"
#include "GameScene.h"
#include "PopupUILayerManager.h"

USING_NS_CC;
MenuUILayer::MenuUILayer()
{
    
}
MenuUILayer::~MenuUILayer()
{
    
}
bool MenuUILayer::addEvents()
{
    
    
    cocos2d::ui::Button* btn_achieve = dynamic_cast<cocos2d::ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode,"btn_achieve"));
    if (!btn_achieve)
        return false;
    cocos2d::ui::Button* btn_setting = dynamic_cast<cocos2d::ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode,"btn_setting"));
    if (!btn_setting)
        return false;
    cocos2d::ui::Button* btn_rank = dynamic_cast<cocos2d::ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode,"btn_rank"));
    if (!btn_rank)
        return false;
    cocos2d::ui::Button* btn_rate = dynamic_cast<cocos2d::ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode,"btn_rate"));
    if (!btn_rate)
        return false;
    cocos2d::ui::Button* btn_start = dynamic_cast<cocos2d::ui::Button*>(UtilityHelper::seekNodeByName(m_pRootNode,"btn_start"));
    if (!btn_start)
        return false;

    btn_achieve->addClickEventListener(CC_CALLBACK_1(MenuUILayer::onClickAchieve, this));
    btn_setting->addClickEventListener(CC_CALLBACK_1(MenuUILayer::onClickSetting, this));
    btn_rank->addClickEventListener(CC_CALLBACK_1(MenuUILayer::onClickRank, this));
    btn_start->addClickEventListener(CC_CALLBACK_1(MenuUILayer::onClickStart, this));
    btn_rate->addClickEventListener(CC_CALLBACK_1(MenuUILayer::onClickRate, this));
    return true;
}

void MenuUILayer::onClickAchieve(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    clickEffect();
    CCLOG("onTouchAchieve");
    PopupUILayerManager::getInstance()->openPopup(ePopupAchieve);
}
void MenuUILayer::onClickSetting(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    clickEffect();
    CCLOG("onTouchSetting");
}
void MenuUILayer::onClickRank(cocos2d::Ref *ref)
{
    
    CHECK_ACTION(ref);
    clickEffect();
    CCLOG("onTouchRank");
//    PopupUILayerManager::getInstance()->openPopup(ePopupInfo);
}
void MenuUILayer::onClickStart(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    clickEffect();
    CCLOG("onTouchStart");
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(scene);
    
}

void MenuUILayer::onClickRate(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    clickEffect();
    CCLOG("onTouchRate");
}