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

    btn_achieve->addTouchEventListener(CC_CALLBACK_2(MenuUILayer::onTouchAchieve, this));
    btn_setting->addTouchEventListener(CC_CALLBACK_2(MenuUILayer::onTouchSetting, this));
    btn_rank->addTouchEventListener(CC_CALLBACK_2(MenuUILayer::onTouchRank, this));
    btn_start->addTouchEventListener(CC_CALLBACK_2(MenuUILayer::onTouchStart, this));
    btn_rate->addTouchEventListener(CC_CALLBACK_2(MenuUILayer::onTouchRate, this));
    return true;
}

void MenuUILayer::onTouchAchieve(cocos2d::Ref *ref, cocos2d::ui::Widget::TouchEventType type)
{
    CHECK_ACTION_WRAPPER(ref,type);
    CCLOG("onTouchAchieve");
}
void MenuUILayer::onTouchSetting(cocos2d::Ref *ref, cocos2d::ui::Widget::TouchEventType type)
{
    CHECK_ACTION_WRAPPER(ref,type);
    CCLOG("onTouchSetting");
}
void MenuUILayer::onTouchRank(cocos2d::Ref *ref, cocos2d::ui::Widget::TouchEventType type)
{
    CHECK_ACTION_WRAPPER(ref,type);
    CCLOG("onTouchRank");
}
void MenuUILayer::onTouchStart(cocos2d::Ref *ref, cocos2d::ui::Widget::TouchEventType type)
{
    CHECK_ACTION_WRAPPER(ref,type);

    CCLOG("onTouchStart");
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(scene);
    
}
void MenuUILayer::onTouchRate(cocos2d::Ref *ref, cocos2d::ui::Widget::TouchEventType type)
{
    CHECK_ACTION_WRAPPER(ref,type);
    CCLOG("onTouchRate");
    
}