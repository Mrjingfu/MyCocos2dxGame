//
//  DeathUI.cpp
//  TinyFlare
//
//  Created by wang haibo on 15/4/27.
//
//

#include "DeathUI.h"
#include "UtilityHelper.h"
#include "GameController.h"
#include "SimpleAudioEngine.h"
#include "HelpScene.h"
#include "NativeBridge.h"
#include "Cocos2dxStore.h"
#include "TinyFlareAssets.h"
#include "EncrytionUtility.h"
USING_NS_CC;
using namespace CocosDenshion;
using namespace soomla;

DeathUI* DeathUI::create()
{
    DeathUI *pRet = new(std::nothrow) DeathUI();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

DeathUI::DeathUI()
{
    m_pPlayGameBtn      = nullptr;
    m_pRemoveADSBtn     = nullptr;
//    m_pRankBtn          = nullptr;
//    m_pShareBtn         = nullptr;
    m_pBackBtn          = nullptr;
    m_pMenuBg           = nullptr;
    m_pGameTitle        = nullptr;
    m_pPlayText         = nullptr;
    
    goodBalanceChangedHandler = Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_GOOD_BALANCE_CHANGED,
                                                                                                      CC_CALLBACK_1(DeathUI::updateGoodBalance, this));
}
DeathUI::~DeathUI()
{
    Director::getInstance()->getEventDispatcher()->removeEventListener(goodBalanceChangedHandler);
}
bool DeathUI::init()
{
    auto keyboardListener=EventListenerKeyboard::create();
    keyboardListener->onKeyReleased=CC_CALLBACK_2(DeathUI::onKeyReleased,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener,this);
    
    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.height/640.0f;
    
    m_pMenuBg = ui::ImageView::create("menubg.png");
    if(!m_pMenuBg)
        return false;
    m_pMenuBg->setScale9Enabled(true);
    m_pMenuBg->setCapInsets(cocos2d::Rect(0,1,128,2));
    m_pMenuBg->setContentSize(cocos2d::Size(size.width,size.height*0.3f));
    m_pMenuBg->setPosition(Vec2(size.width*0.5f, size.height*0.65f));
    m_pMenuBg->setScale(0);
    addChild(m_pMenuBg);
    
    ScaleTo* scaleTo1 = ScaleTo::create(0.2f, 0, 1.0f);
    ScaleTo* scaleTo2 = ScaleTo::create(0.2f, 1.0f, 1.0f);
    Spawn* spawn = Spawn::createWithTwoActions(scaleTo1, scaleTo2);
    m_pMenuBg->runAction(spawn);
    
    m_pGameTitle = ui::Text::create(UtilityHelper::getLocalString("DEAD"), "FZXS12.TTF", size.height*0.1f);
    if(!m_pGameTitle)
        return false;
    m_pGameTitle->setPosition(Vec2(size.width*1.5f, size.height*0.65f));
    m_pGameTitle->setColor(Color3B(208,255,208));
    addChild(m_pGameTitle);
    
    DelayTime* delay = DelayTime::create(0.2f);
    MoveTo* moveTo = MoveTo::create(0.2f, Vec2(size.width*0.5f, size.height*0.65f));
    Sequence* sequence = Sequence::createWithTwoActions(delay, moveTo);
    m_pGameTitle->runAction(sequence);
    
    m_pPlayGameBtn = ui::Button::create("menubg.png");
    if(!m_pPlayGameBtn)
        return false;
    m_pPlayGameBtn->addTouchEventListener(CC_CALLBACK_2(DeathUI::pressContinueGameBtn, this));
    m_pPlayGameBtn->setScale9Enabled(true);
    m_pPlayGameBtn->setCapInsets(cocos2d::Rect(0,2,128,0.5f));
    m_pPlayGameBtn->setContentSize(cocos2d::Size(size.width,size.height*0.1f));
    m_pPlayGameBtn->setPosition(Vec2(size.width*0.5f, size.height*0.3f));
    m_pPlayGameBtn->setScale(0);
    addChild(m_pPlayGameBtn);
    
    Sequence* sequence2 = Sequence::createWithTwoActions(delay, spawn);
    m_pPlayGameBtn->runAction(sequence2);
    
    m_pPlayText = ui::Text::create(UtilityHelper::getLocalString("PRESS_CONTINUE"), "FZXS12.TTF", size.height*0.05f);
    if(!m_pPlayText)
        return false;
    m_pPlayText->setPosition(cocos2d::Size(size.width*0.5f,size.height*0.3f));
    m_pPlayText->setOpacity(0);
    m_pPlayText->setColor(Color3B(208,255,208));
    addChild(m_pPlayText);
    
    EaseSineOut* easeOut1 = EaseSineOut::create(FadeIn::create(0.5f));
    EaseSineOut* easeOut2 = EaseSineOut::create(FadeOut::create(0.5f));
    Sequence* sequence3 = Sequence::create(easeOut1, delay, easeOut2, NULL);
    RepeatForever* repeat = RepeatForever::create(sequence3);
    m_pPlayText->runAction(repeat);
    
    if(!EncrytionUtility::getBoolForKey("RemoveAds",false))
    {
        m_pRemoveADSBtn = ui::Button::create("removeads.png");
        if(!m_pRemoveADSBtn)
            return false;
        m_pRemoveADSBtn->addTouchEventListener(CC_CALLBACK_2(DeathUI::pressRemoveADSBtn, this));
        m_pRemoveADSBtn->setPosition(Vec2(size.width - m_pRemoveADSBtn->getContentSize().width*scale*1.4f, size.height*0.1f));
        m_pRemoveADSBtn->setScale(0.4f*scale);
        addChild(m_pRemoveADSBtn);
    }
    
//    m_pRankBtn = ui::Button::create("rank.png");
//    if(!m_pRankBtn)
//        return false;
//    m_pRankBtn->addTouchEventListener(CC_CALLBACK_2(DeathUI::pressRankBtn, this));
//    m_pRankBtn->setPosition(Vec2(size.width - m_pRankBtn->getContentSize().width*scale*0.7f, size.height*0.1f));
//    m_pRankBtn->setScale(0.4f*scale);
//    addChild(m_pRankBtn);
//    
//    m_pShareBtn = ui::Button::create("share.png");
//    if(!m_pShareBtn)
//        return false;
//    m_pShareBtn->addTouchEventListener(CC_CALLBACK_2(DeathUI::pressShareBtn, this));
//    m_pShareBtn->setPosition(Vec2(size.width - m_pShareBtn->getContentSize().width*scale*0.7f, size.height*0.1f));
//    m_pShareBtn->setScale(0.4f*scale);
//    addChild(m_pShareBtn);
    
    m_pBackBtn = ui::Button::create("exit.png");
    if(!m_pBackBtn)
        return false;
    m_pBackBtn->addTouchEventListener(CC_CALLBACK_2(DeathUI::pressBackBtn, this));
    m_pBackBtn->setPosition(Vec2(size.width - m_pBackBtn->getContentSize().width*scale*0.7f, size.height*0.1f));
    m_pBackBtn->setScale(0.4f*scale);
    addChild(m_pBackBtn);
    NativeBridge::getInstance()->playInterstitialAds();
    return true;
}
void DeathUI::pressContinueGameBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
        GameController::getInstance()->setGameState(GS_GAME);
    }
}
void DeathUI::pressRemoveADSBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
        CCError *soomlaError = NULL;
        CCStoreInventory::sharedStoreInventory()->buyItem(NO_ADS_ITEM_ID, &soomlaError);
        if (soomlaError) {
            CCSoomlaUtils::logException("DeathUI::pressRemoveADSBtn", soomlaError);
            return;
        }
    }
}
//void DeathUI::pressRankBtn(Ref* p,TouchEventType eventType)
//{
//    if(eventType == TouchEventType::ENDED)
//    {
//        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
//    }
//}
//void DeathUI::pressShareBtn(Ref* p,TouchEventType eventType)
//{
//    if(eventType == TouchEventType::ENDED)
//    {
//        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
//    }
//}
void DeathUI::pressBackBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
        GameController::getInstance()->setGameState(GS_MENU);
        NativeBridge::getInstance()->showAdsView();
    }
}
void DeathUI::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *unused_event)
{
    if(keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
    {
        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
        GameController::getInstance()->setGameState(GS_MENU);
    }
}
void DeathUI::updateGoodBalance(cocos2d::EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    soomla::CCVirtualGood *virtualGood = dynamic_cast<CCVirtualGood *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_GOOD));
    __Integer *balance = dynamic_cast<__Integer *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_BALANCE));
    CCLOG("----sssss = %d", balance->getValue());
    if (virtualGood->getItemId()->compare(NO_ADS_ITEM_ID) == 0 && balance->getValue() == 1) {
        EncrytionUtility::setBoolForKey("RemoveAds",true);
        NativeBridge::getInstance()->hideAdsView();
        m_pRemoveADSBtn->removeFromParentAndCleanup(true);
        m_pRemoveADSBtn = nullptr;
    }
}