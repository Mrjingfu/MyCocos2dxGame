//
//  MenuUI.cpp
//  TinyFlare
//
//  Created by wang haibo on 15/4/15.
//
//

#include "MenuUI.h"
#include "UtilityHelper.h"
#include "GameController.h"
#include "SimpleAudioEngine.h"
#include "EncrytionUtility.h"
#include "HelpScene.h"
#include "NativeBridge.h"
#include "Cocos2dxStore.h"
#include "TinyFlareAssets.h"
USING_NS_CC;
using namespace CocosDenshion;
using namespace soomla;
MenuUI* MenuUI::create()
{
    MenuUI *pRet = new(std::nothrow) MenuUI();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

MenuUI::MenuUI()
{
    m_pPlayGameBtn      = nullptr;
    m_pRemoveADSBtn     = nullptr;
//    m_pRankBtn          = nullptr;
//    m_pShareBtn         = nullptr;
    m_pHelpBtn          = nullptr;
    m_pMenuBg           = nullptr;
    m_pGameTitle        = nullptr;
    m_pPlayText         = nullptr;
    
    goodBalanceChangedHandler = Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_GOOD_BALANCE_CHANGED,
                                                                                                      CC_CALLBACK_1(MenuUI::updateGoodBalance, this));
}
MenuUI::~MenuUI()
{
    Director::getInstance()->getEventDispatcher()->removeEventListener(goodBalanceChangedHandler);
}
bool MenuUI::init()
{
    auto keyboardListener=EventListenerKeyboard::create();
    keyboardListener->onKeyReleased=CC_CALLBACK_2(MenuUI::onKeyReleased,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener,this);
    
    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.height/640.0f;
    m_pMenuBg = ui::ImageView::create("menubg.png", TextureResType::PLIST);
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
    
    m_pGameTitle = ui::TextBMFont::create(UtilityHelper::getLocalString("GAME_NAME"), "v5prophit.fnt");
    if(!m_pGameTitle)
        return false;
    m_pGameTitle->setScale(0.38f*scale, 0.6f*scale);
    m_pGameTitle->setPosition(Vec2(size.width*1.5f, size.height*0.65f));
    addChild(m_pGameTitle);
    
    DelayTime* delay = DelayTime::create(0.2f);
    MoveTo* moveTo = MoveTo::create(0.2f, Vec2(size.width*0.5f, size.height*0.65f));
    Sequence* sequence = Sequence::createWithTwoActions(delay, moveTo);
    m_pGameTitle->runAction(sequence);
    
    m_pPlayGameBtn = ui::Button::create("menubg.png", "", "", TextureResType::PLIST);
    if(!m_pPlayGameBtn)
        return false;
    m_pPlayGameBtn->addTouchEventListener(CC_CALLBACK_2(MenuUI::pressPlayGameBtn, this));
    m_pPlayGameBtn->setScale9Enabled(true);
    m_pPlayGameBtn->setCapInsets(cocos2d::Rect(0,2,128,0.5f));
    m_pPlayGameBtn->setContentSize(cocos2d::Size(size.width,size.height*0.1f));
    m_pPlayGameBtn->setPosition(Vec2(size.width*0.5f, size.height*0.3f));
    m_pPlayGameBtn->setScale(0);
    addChild(m_pPlayGameBtn);
    
    Sequence* sequence2 = Sequence::createWithTwoActions(delay, spawn);
    m_pPlayGameBtn->runAction(sequence2);
    
    m_pPlayText = ui::Text::create(UtilityHelper::getLocalString("PRESS_BEGIN"), "FZXS12.TTF", size.height*0.05f);
    if(!m_pPlayText)
        return false;
    if(EncrytionUtility::getIntegerForKey("CurrentStage", 1) != 1)
        m_pPlayText->setString(UtilityHelper::getLocalString("PRESS_CONTINUE"));
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
        m_pRemoveADSBtn = ui::Button::create("removeads.png", "", "", TextureResType::PLIST);
        if(!m_pRemoveADSBtn)
            return false;
        m_pRemoveADSBtn->addTouchEventListener(CC_CALLBACK_2(MenuUI::pressRemoveADSBtn, this));
        m_pRemoveADSBtn->setPosition(Vec2(size.width - m_pRemoveADSBtn->getContentSize().width*scale*1.4f, size.height*0.1f));
        m_pRemoveADSBtn->setScale(0.4f*scale);
        addChild(m_pRemoveADSBtn);
    }
    
//    m_pRankBtn = ui::Button::create("rank.png");
//    if(!m_pRankBtn)
//        return false;
//    m_pRankBtn->addTouchEventListener(CC_CALLBACK_2(MenuUI::pressRankBtn, this));
//    m_pRankBtn->setPosition(Vec2(size.width - m_pRankBtn->getContentSize().width*scale*0.7f, size.height*0.1f));
//    m_pRankBtn->setScale(0.4f*scale);
//    m_pRankBtn->setVisible(false);
//    addChild(m_pRankBtn);
//    
//    m_pShareBtn = ui::Button::create("share.png");
//    if(!m_pShareBtn)
//        return false;
//    m_pShareBtn->addTouchEventListener(CC_CALLBACK_2(MenuUI::pressShareBtn, this));
//    m_pShareBtn->setPosition(Vec2(size.width - m_pShareBtn->getContentSize().width*scale*0.7f, size.height*0.1f));
//    m_pShareBtn->setScale(0.4f*scale);
//    m_pShareBtn->setVisible(false);
//    addChild(m_pShareBtn);
    
    m_pHelpBtn = ui::Button::create("help.png", "", "", TextureResType::PLIST);
    if(!m_pHelpBtn)
        return false;
    m_pHelpBtn->addTouchEventListener(CC_CALLBACK_2(MenuUI::pressHelpBtn, this));
    m_pHelpBtn->setPosition(Vec2(size.width - m_pHelpBtn->getContentSize().width*scale*0.7f, size.height*0.1f));
    m_pHelpBtn->setScale(0.4f*scale);
    addChild(m_pHelpBtn);
    return true;
}
void MenuUI::pressPlayGameBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
        NativeBridge::getInstance()->hideAdsView();
        GameController::getInstance()->setGameState(GS_GAME);
    }
}
void MenuUI::pressRemoveADSBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
        CCError *soomlaError = NULL;
        CCStoreInventory::sharedStoreInventory()->buyItem(NO_ADS_ITEM_ID, &soomlaError);
        if (soomlaError) {
            CCSoomlaUtils::logException("PauseUI::pressRemoveADSBtn", soomlaError);
            return;
        }

    }
}
//void MenuUI::pressRankBtn(Ref* p,TouchEventType eventType)
//{
//  if(eventType == TouchEventType::ENDED)
//  {
//      SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
//  }
//}
//void MenuUI::pressShareBtn(Ref* p,TouchEventType eventType)
//{
//  if(eventType == TouchEventType::ENDED)
//  {
//      SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
//  }
//}
void MenuUI::pressHelpBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
        Scene* scene = HelpScene::createScene();
        Director::getInstance()->pushScene(scene);
    }
}

void MenuUI::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *unused_event)
{
    if(keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
    {
        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
        //Director::getInstance()->end();
    }
}

void MenuUI::updateGoodBalance(cocos2d::EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    soomla::CCVirtualGood *virtualGood = dynamic_cast<CCVirtualGood *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_GOOD));
    __Integer *balance = dynamic_cast<__Integer *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_BALANCE));

    if (virtualGood->getItemId()->compare(NO_ADS_ITEM_ID) == 0 && balance->getValue() == 1) {
        EncrytionUtility::setBoolForKey("RemoveAds",true);
        NativeBridge::getInstance()->hideAdsView();
        m_pRemoveADSBtn->removeFromParentAndCleanup(true);
        m_pRemoveADSBtn = nullptr;
    }
}