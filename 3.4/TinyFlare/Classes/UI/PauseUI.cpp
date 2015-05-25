//
//  PauseUI.cpp
//  TinyFlare
//
//  Created by wang haibo on 15/4/22.
//
//

#include "PauseUI.h"
#include "GameController.h"
#include "SimpleAudioEngine.h"
#include "UtilityHelper.h"
#include "EncrytionUtility.h"
#include "ChaosNumber.h"
#include "HelpScene.h"
#include "NativeBridge.h"
#include "Cocos2dxStore.h"
#include "TinyFlareAssets.h"
USING_NS_CC;
using namespace CocosDenshion;
using namespace soomla;

PauseUI* PauseUI::create()
{
    PauseUI *pRet = new(std::nothrow) PauseUI();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

PauseUI::PauseUI()
{
    //m_pRankBtn      = nullptr;
    m_pRemoveADSBtn = nullptr;
    m_pBackBtn      = nullptr;
    
    m_pStardust             = nullptr;
    m_pStardustX            = nullptr;
    m_pStardustNum          = nullptr;
    
    m_pPurchaseBtn          = nullptr;
    
    m_pStardustDropLevelText    = nullptr;
    m_pStardustDropLevel1       = nullptr;
    m_pStardustDropLevel2       = nullptr;
    m_pStardustDropLevel3       = nullptr;
    m_pStardustDropLevel4       = nullptr;
    m_pStardustDropLevel5       = nullptr;
    m_pStardustDropLevelAdd     = nullptr;
    
    m_pItemDropLevelText        = nullptr;
    m_pItemDropLevel1           = nullptr;
    m_pItemDropLevel2           = nullptr;
    m_pItemDropLevel3           = nullptr;
    m_pItemDropLevel4           = nullptr;
    m_pItemDropLevel5           = nullptr;
    m_pItemDropLevelAdd         = nullptr;
    
    m_pItemEffectLevelText      = nullptr;
    m_pItemEffectLevel1         = nullptr;
    m_pItemEffectLevel2         = nullptr;
    m_pItemEffectLevel3         = nullptr;
    m_pItemEffectLevel4         = nullptr;
    m_pItemEffectLevel5         = nullptr;
    m_pItemEffectLevelAdd       = nullptr;
    
    m_pPanelBg  = nullptr;
    m_pPlayText = nullptr;
    
    currencyBalanceChangedHandler = Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_CURRENCY_BALANCE_CHANGED,
                                                                                                          CC_CALLBACK_1(PauseUI::updateCurrencyBalance, this));
    goodBalanceChangedHandler = Director::getInstance()->getEventDispatcher()->addCustomEventListener(CCStoreConsts::EVENT_GOOD_BALANCE_CHANGED,
                                                                                                      CC_CALLBACK_1(PauseUI::updateGoodBalance, this));
}
PauseUI::~PauseUI()
{
    Director::getInstance()->getEventDispatcher()->removeEventListener(currencyBalanceChangedHandler);
    Director::getInstance()->getEventDispatcher()->removeEventListener(goodBalanceChangedHandler);
}
bool PauseUI::init()
{
    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.height/640.0f;
    m_pPanelBg = ui::ImageView::create("menubg.png");
    if(!m_pPanelBg)
        return false;
    m_pPanelBg->setScale9Enabled(true);
    m_pPanelBg->setCapInsets(cocos2d::Rect(0,2,128,0.5f));
    m_pPanelBg->setContentSize(cocos2d::Size(size.width,size.height*0.7f));
    m_pPanelBg->setPosition(Vec2(size.width*0.5f, size.height*0.5f));
    m_pPanelBg->setScale(0);
    addChild(m_pPanelBg);
    
//    m_pRankBtn = ui::Button::create("rank.png");
//    if(!m_pRemoveADSBtn)
//        return false;
//    m_pRankBtn->addTouchEventListener(CC_CALLBACK_2(PauseUI::pressRankBtn, this));
//    m_pRankBtn->setPosition(Vec2(size.width - m_pRankBtn->getContentSize().width*scale*2.1f, size.height*0.8f));
//    m_pRankBtn->setScale(0.4f*scale);
//    m_pRankBtn->setVisible(false);
//    addChild(m_pRankBtn);
    
    if(!EncrytionUtility::getBoolForKey("RemoveAds",false))
    {
        m_pRemoveADSBtn = ui::Button::create("removeads.png");
        if(!m_pRemoveADSBtn)
            return false;
        m_pRemoveADSBtn->addTouchEventListener(CC_CALLBACK_2(PauseUI::pressRemoveADSBtn, this));
        m_pRemoveADSBtn->setPosition(Vec2(size.width - m_pRemoveADSBtn->getContentSize().width*scale*1.4f, size.height*0.08f));
        m_pRemoveADSBtn->setScale(0.4f*scale);
        m_pPanelBg->addChild(m_pRemoveADSBtn);
    }
    
    m_pBackBtn = ui::Button::create("exit.png");
    if(!m_pBackBtn)
        return false;
    m_pBackBtn->addTouchEventListener(CC_CALLBACK_2(PauseUI::pressBackBtn, this));
    m_pBackBtn->setPosition(Vec2(size.width - m_pBackBtn->getContentSize().width*scale*0.7f, size.height*0.08f));
    m_pBackBtn->setScale(0.4f*scale);
    m_pPanelBg->addChild(m_pBackBtn);
    
    m_pStardust = ui::ImageView::create("diamonditem.png");
    if(!m_pStardust)
        return false;
    m_pStardust->setPosition(Vec2(size.width*0.78f, size.height*0.5f));
    m_pStardust->setScale(0.1f*scale, 0.14f*scale);
    m_pPanelBg->addChild(m_pStardust);
    
    m_pStardustX = ui::Text::create(" + ", "FZXS12.TTF", m_pStardust->getContentSize().height*0.1f*scale);
    if(!m_pStardustX)
        return false;
    m_pStardustX->setPosition(m_pStardust->getPosition() + Vec2(m_pStardust->getContentSize().width*0.1f*scale, 0));
    m_pStardustX->setAnchorPoint(Vec2(0.5, 0.5f));
    m_pStardustX->setColor(Color3B(208,255,208));
    m_pPanelBg->addChild(m_pStardustX);
    
    m_pStardustNum = ui::Text::create(Value(1000).asString(), "FZXS12.TTF", m_pStardust->getContentSize().height*0.1f*scale);
    if(!m_pStardustNum)
        return false;
    m_pStardustNum->setColor(Color3B(208,255,208));
    m_pStardustNum->setAnchorPoint(Vec2(0, 0.5f));
    m_pStardustNum->setPosition(m_pStardustX->getPosition() + Vec2(m_pStardustX->getContentSize().width*0.3f*scale, 0));
    m_pPanelBg->addChild(m_pStardustNum);
    
    m_pPurchaseBtn = ui::Button::create("purchase.png");
    if(!m_pPurchaseBtn)
        return false;
    m_pPurchaseBtn->addTouchEventListener(CC_CALLBACK_2(PauseUI::pressPurchaseBtn, this));
    m_pPurchaseBtn->setPosition(Vec2(size.width*0.85f, size.height*0.35f));
    m_pPurchaseBtn->setScale(0.8f*scale);
    m_pPanelBg->addChild(m_pPurchaseBtn);
    
    m_pStardustDropLevelText = ui::Text::create(UtilityHelper::getLocalString("STARDUST_DROP"), "FZXS12.TTF", size.height*0.04f);
    if(!m_pStardustDropLevelText)
        return false;
    m_pStardustDropLevelText->setAnchorPoint(Vec2(0, 0.5f));
    m_pStardustDropLevelText->setPosition(Vec2(size.width*0.1f, size.height*0.6f));
    m_pStardustDropLevelText->setColor(Color3B(208,255,208));
    m_pPanelBg->addChild(m_pStardustDropLevelText);
    
    m_pStardustDropLevel1 = ui::ImageView::create("level_empty.png");
    if(!m_pStardustDropLevel1)
        return false;
    m_pStardustDropLevel1->setAnchorPoint(Vec2(0, 0.5f));
    m_pStardustDropLevel1->setScale9Enabled(true);
    m_pStardustDropLevel1->setCapInsets(cocos2d::Rect(20,20,88,88));
    m_pStardustDropLevel1->setContentSize(cocos2d::Size(size.height*0.3f,size.height*0.1f));
    m_pStardustDropLevel1->setPosition(Vec2(m_pStardustDropLevelText->getPosition().x, m_pStardustDropLevelText->getPosition().y -50*scale));
    m_pStardustDropLevel1->setScale(0.5f);
    m_pPanelBg->addChild(m_pStardustDropLevel1);
    
    m_pStardustDropLevel2 = ui::ImageView::create("level_empty.png");
    if(!m_pStardustDropLevel2)
        return false;
    m_pStardustDropLevel2->setAnchorPoint(Vec2(0, 0.5f));
    m_pStardustDropLevel2->setScale9Enabled(true);
    m_pStardustDropLevel2->setCapInsets(cocos2d::Rect(20,20,88,88));
    m_pStardustDropLevel2->setContentSize(cocos2d::Size(size.height*0.3f,size.height*0.1f));
    m_pStardustDropLevel2->setPosition(Vec2(m_pStardustDropLevel1->getPosition().x + size.height*0.15f + 10*scale, m_pStardustDropLevelText->getPosition().y -50*scale));
    m_pStardustDropLevel2->setScale(0.5f);
    m_pPanelBg->addChild(m_pStardustDropLevel2);
    
    m_pStardustDropLevel3 = ui::ImageView::create("level_empty.png");
    if(!m_pStardustDropLevel3)
        return false;
    m_pStardustDropLevel3->setAnchorPoint(Vec2(0, 0.5f));
    m_pStardustDropLevel3->setScale9Enabled(true);
    m_pStardustDropLevel3->setCapInsets(cocos2d::Rect(20,20,88,88));
    m_pStardustDropLevel3->setContentSize(cocos2d::Size(size.height*0.3f,size.height*0.1f));
    m_pStardustDropLevel3->setPosition(Vec2(m_pStardustDropLevel2->getPosition().x + size.height*0.15f + 10*scale, m_pStardustDropLevelText->getPosition().y -50*scale));
    m_pStardustDropLevel3->setScale(0.5f);
    m_pPanelBg->addChild(m_pStardustDropLevel3);
    
    m_pStardustDropLevel4 = ui::ImageView::create("level_empty.png");
    if(!m_pStardustDropLevel4)
        return false;
    m_pStardustDropLevel4->setAnchorPoint(Vec2(0, 0.5f));
    m_pStardustDropLevel4->setScale9Enabled(true);
    m_pStardustDropLevel4->setCapInsets(cocos2d::Rect(20,20,88,88));
    m_pStardustDropLevel4->setContentSize(cocos2d::Size(size.height*0.3f,size.height*0.1f));
    m_pStardustDropLevel4->setPosition(Vec2(m_pStardustDropLevel3->getPosition().x + size.height*0.15f + 10*scale, m_pStardustDropLevelText->getPosition().y -50*scale));
    m_pStardustDropLevel4->setScale(0.5f);
    m_pPanelBg->addChild(m_pStardustDropLevel4);
    
    m_pStardustDropLevel5 = ui::ImageView::create("level_empty.png");
    if(!m_pStardustDropLevel5)
        return false;
    m_pStardustDropLevel5->setAnchorPoint(Vec2(0, 0.5f));
    m_pStardustDropLevel5->setScale9Enabled(true);
    m_pStardustDropLevel5->setCapInsets(cocos2d::Rect(20,20,88,88));
    m_pStardustDropLevel5->setContentSize(cocos2d::Size(size.height*0.3f,size.height*0.1f));
    m_pStardustDropLevel5->setPosition(Vec2(m_pStardustDropLevel4->getPosition().x + size.height*0.15f + 10*scale, m_pStardustDropLevelText->getPosition().y -50*scale));
    m_pStardustDropLevel5->setScale(0.5f);
    m_pPanelBg->addChild(m_pStardustDropLevel5);
    
    m_pStardustDropLevelAdd = ui::Button::create("plus.png");
    if(!m_pStardustDropLevelAdd)
        return false;
    m_pStardustDropLevelAdd->setAnchorPoint(Vec2(0, 0.5f));
    m_pStardustDropLevelAdd->setPosition(Vec2(m_pStardustDropLevel5->getPosition().x + size.height*0.15f + 50*scale, m_pStardustDropLevelText->getPosition().y -50*scale));
    m_pStardustDropLevelAdd->setScale(0.25f);
    m_pStardustDropLevelAdd->addTouchEventListener(CC_CALLBACK_2(PauseUI::pressStardustDropLevelAddBtn, this));
    m_pPanelBg->addChild(m_pStardustDropLevelAdd);
    
    
    m_pItemDropLevelText = ui::Text::create(UtilityHelper::getLocalString("ITEM_DROP"), "FZXS12.TTF", size.height*0.04f);
    if(!m_pItemDropLevelText)
        return false;
    m_pItemDropLevelText->setAnchorPoint(Vec2(0, 0.5f));
    m_pItemDropLevelText->setPosition(Vec2(size.width*0.1f, size.height*0.4f));
    m_pItemDropLevelText->setColor(Color3B(208,255,208));
    m_pPanelBg->addChild(m_pItemDropLevelText);
    
    m_pItemDropLevel1 = ui::ImageView::create("level_empty.png");
    if(!m_pItemDropLevel1)
        return false;
    m_pItemDropLevel1->setAnchorPoint(Vec2(0, 0.5f));
    m_pItemDropLevel1->setScale9Enabled(true);
    m_pItemDropLevel1->setCapInsets(cocos2d::Rect(20,20,88,88));
    m_pItemDropLevel1->setContentSize(cocos2d::Size(size.height*0.3f,size.height*0.1f));
    m_pItemDropLevel1->setPosition(Vec2(m_pItemDropLevelText->getPosition().x, m_pItemDropLevelText->getPosition().y -50*scale));
    m_pItemDropLevel1->setScale(0.5f);
    m_pPanelBg->addChild(m_pItemDropLevel1);
    

    m_pItemDropLevel2 = ui::ImageView::create("level_empty.png");
    if(!m_pItemDropLevel2)
        return false;
    m_pItemDropLevel2->setAnchorPoint(Vec2(0, 0.5f));
    m_pItemDropLevel2->setScale9Enabled(true);
    m_pItemDropLevel2->setCapInsets(cocos2d::Rect(20,20,88,88));
    m_pItemDropLevel2->setContentSize(cocos2d::Size(size.height*0.3f,size.height*0.1f));
    m_pItemDropLevel2->setPosition(Vec2(m_pItemDropLevel1->getPosition().x + size.height*0.15f + 10*scale, m_pItemDropLevelText->getPosition().y -50*scale));
    m_pItemDropLevel2->setScale(0.5f);
    m_pPanelBg->addChild(m_pItemDropLevel2);
    
    m_pItemDropLevel3 = ui::ImageView::create("level_empty.png");
    if(!m_pItemDropLevel3)
        return false;
    m_pItemDropLevel3->setAnchorPoint(Vec2(0, 0.5f));
    m_pItemDropLevel3->setScale9Enabled(true);
    m_pItemDropLevel3->setCapInsets(cocos2d::Rect(20,20,88,88));
    m_pItemDropLevel3->setContentSize(cocos2d::Size(size.height*0.3f,size.height*0.1f));
    m_pItemDropLevel3->setPosition(Vec2(m_pItemDropLevel2->getPosition().x + size.height*0.15f + 10*scale, m_pItemDropLevelText->getPosition().y -50*scale));
    m_pItemDropLevel3->setScale(0.5f);
    m_pPanelBg->addChild(m_pItemDropLevel3);

    m_pItemDropLevel4 = ui::ImageView::create("level_empty.png");
    if(!m_pItemDropLevel4)
        return false;
    m_pItemDropLevel4->setAnchorPoint(Vec2(0, 0.5f));
    m_pItemDropLevel4->setScale9Enabled(true);
    m_pItemDropLevel4->setCapInsets(cocos2d::Rect(20,20,88,88));
    m_pItemDropLevel4->setContentSize(cocos2d::Size(size.height*0.3f,size.height*0.1f));
    m_pItemDropLevel4->setPosition(Vec2(m_pItemDropLevel3->getPosition().x + size.height*0.15f + 10*scale, m_pItemDropLevelText->getPosition().y -50*scale));
    m_pItemDropLevel4->setScale(0.5f);
    m_pPanelBg->addChild(m_pItemDropLevel4);
    
    m_pItemDropLevel5 = ui::ImageView::create("level_empty.png");
    if(!m_pItemDropLevel5)
        return false;
    m_pItemDropLevel5->setAnchorPoint(Vec2(0, 0.5f));
    m_pItemDropLevel5->setScale9Enabled(true);
    m_pItemDropLevel5->setCapInsets(cocos2d::Rect(15,15,98,98));
    m_pItemDropLevel5->setContentSize(cocos2d::Size(size.height*0.3f,size.height*0.1f));
    m_pItemDropLevel5->setPosition(Vec2(m_pItemDropLevel4->getPosition().x + size.height*0.15f + 10*scale, m_pItemDropLevelText->getPosition().y -50*scale));
    m_pItemDropLevel5->setScale(0.5f);
    m_pPanelBg->addChild(m_pItemDropLevel5);

    m_pItemDropLevelAdd = ui::Button::create("plus.png");
    if(!m_pItemDropLevelAdd)
        return false;
    m_pItemDropLevelAdd->setAnchorPoint(Vec2(0, 0.5f));
    m_pItemDropLevelAdd->setPosition(Vec2(m_pStardustDropLevel5->getPosition().x + size.height*0.15f + 50*scale, m_pItemDropLevelText->getPosition().y -50*scale));
    m_pItemDropLevelAdd->setScale(0.25f);
    m_pItemDropLevelAdd->addTouchEventListener(CC_CALLBACK_2(PauseUI::pressItemDropLevelAddBtn, this));
    m_pPanelBg->addChild(m_pItemDropLevelAdd);
    
    m_pItemEffectLevelText = ui::Text::create(UtilityHelper::getLocalString("ITEM_EFFECT"), "FZXS12.TTF", size.height*0.04f);
    if(!m_pItemEffectLevelText)
        return false;
    m_pItemEffectLevelText->setAnchorPoint(Vec2(0, 0.5f));
    m_pItemEffectLevelText->setPosition(Vec2(size.width*0.1f, size.height*0.2f));
    m_pItemEffectLevelText->setColor(Color3B(208,255,208));
    m_pPanelBg->addChild(m_pItemEffectLevelText);

    m_pItemEffectLevel1 = ui::ImageView::create("level_empty.png");
    if(!m_pItemEffectLevel1)
        return false;
    m_pItemEffectLevel1->setAnchorPoint(Vec2(0, 0.5f));
    m_pItemEffectLevel1->setScale9Enabled(true);
    m_pItemEffectLevel1->setCapInsets(cocos2d::Rect(20,20,88,88));
    m_pItemEffectLevel1->setContentSize(cocos2d::Size(size.height*0.3f,size.height*0.1f));
    m_pItemEffectLevel1->setPosition(Vec2(m_pItemEffectLevelText->getPosition().x, m_pItemEffectLevelText->getPosition().y -50*scale));
    m_pItemEffectLevel1->setScale(0.5f);
    m_pPanelBg->addChild(m_pItemEffectLevel1);
    
    m_pItemEffectLevel2 = ui::ImageView::create("level_empty.png");
    if(!m_pItemEffectLevel2)
        return false;
    m_pItemEffectLevel2->setAnchorPoint(Vec2(0, 0.5f));
    m_pItemEffectLevel2->setScale9Enabled(true);
    m_pItemEffectLevel2->setCapInsets(cocos2d::Rect(20,20,88,88));
    m_pItemEffectLevel2->setContentSize(cocos2d::Size(size.height*0.3f,size.height*0.1f));
    m_pItemEffectLevel2->setPosition(Vec2(m_pItemEffectLevel1->getPosition().x + size.height*0.15f + 10*scale, m_pItemEffectLevelText->getPosition().y -50*scale));
    m_pItemEffectLevel2->setScale(0.5f);
    m_pPanelBg->addChild(m_pItemEffectLevel2);
    
    m_pItemEffectLevel3 = ui::ImageView::create("level_empty.png");
    if(!m_pItemEffectLevel3)
        return false;
    m_pItemEffectLevel3->setAnchorPoint(Vec2(0, 0.5f));
    m_pItemEffectLevel3->setScale9Enabled(true);
    m_pItemEffectLevel3->setCapInsets(cocos2d::Rect(20,20,88,88));
    m_pItemEffectLevel3->setContentSize(cocos2d::Size(size.height*0.3f,size.height*0.1f));
    m_pItemEffectLevel3->setPosition(Vec2(m_pItemEffectLevel2->getPosition().x + size.height*0.15f + 10*scale, m_pItemEffectLevelText->getPosition().y -50*scale));
    m_pItemEffectLevel3->setScale(0.5f);
    m_pPanelBg->addChild(m_pItemEffectLevel3);
    
    m_pItemEffectLevel4 = ui::ImageView::create("level_empty.png");
    if(!m_pItemEffectLevel4)
        return false;
    m_pItemEffectLevel4->setAnchorPoint(Vec2(0, 0.5f));
    m_pItemEffectLevel4->setScale9Enabled(true);
    m_pItemEffectLevel4->setCapInsets(cocos2d::Rect(20,20,88,88));
    m_pItemEffectLevel4->setContentSize(cocos2d::Size(size.height*0.3f,size.height*0.1f));
    m_pItemEffectLevel4->setPosition(Vec2(m_pItemEffectLevel3->getPosition().x + size.height*0.15f + 10*scale, m_pItemEffectLevelText->getPosition().y -50*scale));
    m_pItemEffectLevel4->setScale(0.5f);
    m_pPanelBg->addChild(m_pItemEffectLevel4);
    
    m_pItemEffectLevel5 = ui::ImageView::create("level_empty.png");
    if(!m_pItemEffectLevel5)
        return false;
    m_pItemEffectLevel5->setAnchorPoint(Vec2(0, 0.5f));
    m_pItemEffectLevel5->setScale9Enabled(true);
    m_pItemEffectLevel5->setCapInsets(cocos2d::Rect(20,20,88,88));
    m_pItemEffectLevel5->setContentSize(cocos2d::Size(size.height*0.3f,size.height*0.1f));
    m_pItemEffectLevel5->setPosition(Vec2(m_pItemEffectLevel4->getPosition().x + size.height*0.15f + 10*scale, m_pItemEffectLevelText->getPosition().y -50*scale));
    m_pItemEffectLevel5->setScale(0.5f);
    m_pPanelBg->addChild(m_pItemEffectLevel5);
    
    m_pItemEffectLevelAdd = ui::Button::create("plus.png");
    if(!m_pItemEffectLevelAdd)
        return false;
    m_pItemEffectLevelAdd->setAnchorPoint(Vec2(0, 0.5f));
    m_pItemEffectLevelAdd->setPosition(Vec2(m_pItemEffectLevel5->getPosition().x + size.height*0.15f + 50*scale, m_pItemEffectLevelText->getPosition().y -50*scale));
    m_pItemEffectLevelAdd->setScale(0.25f);
    m_pItemEffectLevelAdd->addTouchEventListener(CC_CALLBACK_2(PauseUI::pressItemEffectLevelAddBtn, this));
    m_pPanelBg->addChild(m_pItemEffectLevelAdd);
    
    updateUI();

    return true;
}
void PauseUI::beginToPause()
{
    if(m_pPanelBg)
    {
        ScaleTo* scaleTo1 = ScaleTo::create(0.2f, 0, 1.0f);
        ScaleTo* scaleTo2 = ScaleTo::create(0.2f, 1.0f, 1.0f);
        Spawn* spawn = Spawn::createWithTwoActions(scaleTo1, scaleTo2);
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(GameController::pauseStart, GameController::getInstance()));
        Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
        m_pPanelBg->runAction(sequnce);
    }
}
void PauseUI::endToPause()
{
    if(m_pPanelBg)
    {
        m_pPanelBg->stopAllActions();
        ScaleTo* scaleTo1 = ScaleTo::create(0.2f, 1.0f, 0.0f);
        ScaleTo* scaleTo2 = ScaleTo::create(0.2f, 0.0f, 0.0f);
        Spawn* spawn = Spawn::createWithTwoActions(scaleTo1, scaleTo2);
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(GameController::pauseEnd, GameController::getInstance()));
        Sequence* sequnce = Sequence::createWithTwoActions(spawn, callFunc);
        m_pPanelBg->runAction(sequnce);
    }
}
void PauseUI::pressStardustDropLevelAddBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
        ChaosNumber stardustDropLevel;
        stardustDropLevel = EncrytionUtility::getIntegerForKey("StardustDropLevel", 1);
        if(stardustDropLevel.GetLongValue() < 5)
        {
            ChaosNumber curStardustNum;
            curStardustNum = EncrytionUtility::getIntegerForKey("CurStardustNum", 0);
            if(stardustDropLevel == 4)
            {
                ChaosNumber needStardust(600);
                if(curStardustNum >= needStardust)
                {
                    stardustDropLevel = stardustDropLevel + 1;
                    EncrytionUtility::setIntegerForKey("StardustDropLevel", (int)(stardustDropLevel.GetLongValue()));
                    GameController::getInstance()->subStardust(needStardust);
                }
            }
            else if (stardustDropLevel == 3)
            {
                ChaosNumber needStardust(270);
                if(curStardustNum >= needStardust)
                {
                    stardustDropLevel = stardustDropLevel + 1;
                    EncrytionUtility::setIntegerForKey("StardustDropLevel", (int)(stardustDropLevel.GetLongValue()));
                    GameController::getInstance()->subStardust(needStardust);
                }

            }
            else if (stardustDropLevel == 2)
            {
                ChaosNumber needStardust(100);
                if(curStardustNum >= needStardust)
                {
                    stardustDropLevel = stardustDropLevel + 1;
                    EncrytionUtility::setIntegerForKey("StardustDropLevel", (int)(stardustDropLevel.GetLongValue()));
                    GameController::getInstance()->subStardust(needStardust);
                }

            }
            else if (stardustDropLevel == 1)
            {
                ChaosNumber needStardust(30);
                if(curStardustNum >= needStardust)
                {
                    stardustDropLevel = stardustDropLevel + 1;
                    EncrytionUtility::setIntegerForKey("StardustDropLevel", (int)(stardustDropLevel.GetLongValue()));
                    GameController::getInstance()->subStardust(needStardust);
                }

            }
        }
        updateUI();
    }
}
void PauseUI::pressItemDropLevelAddBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
        ChaosNumber itemDropLevel;
        itemDropLevel = EncrytionUtility::getIntegerForKey("ItemDropLevel", 1);
        if(itemDropLevel.GetLongValue() < 5)
        {
            ChaosNumber curStardustNum;
            curStardustNum = EncrytionUtility::getIntegerForKey("CurStardustNum", 0);
            if(itemDropLevel == 4)
            {
                ChaosNumber needStardust(700);
                if(curStardustNum >= needStardust)
                {
                    itemDropLevel = itemDropLevel + 1;
                    EncrytionUtility::setIntegerForKey("ItemDropLevel", (int)(itemDropLevel.GetLongValue()));
                    GameController::getInstance()->subStardust(needStardust);
                }
            }
            else if (itemDropLevel == 3)
            {
                ChaosNumber needStardust(320);
                if(curStardustNum >= needStardust)
                {
                    itemDropLevel = itemDropLevel + 1;
                    EncrytionUtility::setIntegerForKey("ItemDropLevel", (int)(itemDropLevel.GetLongValue()));
                    GameController::getInstance()->subStardust(needStardust);
                }
                
            }
            else if (itemDropLevel == 2)
            {
                ChaosNumber needStardust(140);
                if(curStardustNum >= needStardust)
                {
                    itemDropLevel = itemDropLevel + 1;
                    EncrytionUtility::setIntegerForKey("ItemDropLevel", (int)(itemDropLevel.GetLongValue()));
                    GameController::getInstance()->subStardust(needStardust);
                }
                
            }
            else if (itemDropLevel == 1)
            {
                ChaosNumber needStardust(40);
                if(curStardustNum >= needStardust)
                {
                    itemDropLevel = itemDropLevel + 1;
                    EncrytionUtility::setIntegerForKey("ItemDropLevel", (int)(itemDropLevel.GetLongValue()));
                    GameController::getInstance()->subStardust(needStardust);
                }
                
            }
        }
        updateUI();
    }
}
void PauseUI::pressItemEffectLevelAddBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
        ChaosNumber itemEffectLevel;
        itemEffectLevel = EncrytionUtility::getIntegerForKey("ItemEffectLevel", 1);
        if(itemEffectLevel.GetLongValue() < 5)
        {
            ChaosNumber curStardustNum;
            curStardustNum = EncrytionUtility::getIntegerForKey("CurStardustNum", 0);
            if(itemEffectLevel == 4)
            {
                ChaosNumber needStardust(800);
                if(curStardustNum >= needStardust)
                {
                    itemEffectLevel = itemEffectLevel + 1;
                    EncrytionUtility::setIntegerForKey("ItemEffectLevel", (int)(itemEffectLevel.GetLongValue()));
                    GameController::getInstance()->subStardust(needStardust);
                }
            }
            else if (itemEffectLevel == 3)
            {
                ChaosNumber needStardust(390);
                if(curStardustNum >= needStardust)
                {
                    itemEffectLevel = itemEffectLevel + 1;
                    EncrytionUtility::setIntegerForKey("ItemEffectLevel", (int)(itemEffectLevel.GetLongValue()));
                    GameController::getInstance()->subStardust(needStardust);
                }
                
            }
            else if (itemEffectLevel == 2)
            {
                ChaosNumber needStardust(160);
                if(curStardustNum >= needStardust)
                {
                    itemEffectLevel = itemEffectLevel + 1;
                    EncrytionUtility::setIntegerForKey("ItemEffectLevel", (int)(itemEffectLevel.GetLongValue()));
                    GameController::getInstance()->subStardust(needStardust);
                }
                
            }
            else if (itemEffectLevel == 1)
            {
                ChaosNumber needStardust(50);
                if(curStardustNum >= needStardust)
                {
                    itemEffectLevel = itemEffectLevel + 1;
                    EncrytionUtility::setIntegerForKey("ItemEffectLevel", (int)(itemEffectLevel.GetLongValue()));
                    GameController::getInstance()->subStardust(needStardust);
                }
                
            }
        }
        updateUI();
    }
}
//void PauseUI::pressRankBtn(Ref* p,TouchEventType eventType)
//{
//        if(eventType == TouchEventType::ENDED)
//        {
//            SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
//        }
//}
void PauseUI::pressRemoveADSBtn(Ref* p,TouchEventType eventType)
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
void PauseUI::pressBackBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        GameController::getInstance()->resume();
        GameController::getInstance()->pauseEnd();
        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
        GameController::getInstance()->setGameState(GS_MENU);
        NativeBridge::getInstance()->showAdsView();
    }
}
void PauseUI::pressPurchaseBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
        CCError *soomlaError = NULL;
        CCStoreInventory::sharedStoreInventory()->buyItem(THOUSAND_STARDUST_ITEM_ID, &soomlaError);
        if (soomlaError) {
            CCSoomlaUtils::logException("PauseUI::pressPurchaseBtn", soomlaError);
            return;
        }
    }
}
void PauseUI::updateUI()
{
    ChaosNumber curStardustNum;
    curStardustNum = EncrytionUtility::getIntegerForKey("CurStardustNum", 0);
    ChaosNumber stardustDropLevel;
    stardustDropLevel = EncrytionUtility::getIntegerForKey("StardustDropLevel", 1);
    ChaosNumber itemDropLevel;
    itemDropLevel = EncrytionUtility::getIntegerForKey("ItemDropLevel", 1);
    ChaosNumber itemEffectLevel;
    itemEffectLevel = EncrytionUtility::getIntegerForKey("ItemEffectLevel", 1);
    
    if(stardustDropLevel >= 5)
    {
        if(m_pStardustDropLevelText)
        {
            m_pStardustDropLevelText->setColor(Color3B(208,255,208));
            m_pStardustDropLevelText->setString(UtilityHelper::getLocalString("STARDUST_DROP_MAX"));
        }
        if (m_pStardustDropLevelAdd)
            m_pStardustDropLevelAdd->setVisible(false);
        if (m_pStardustDropLevel1)
            m_pStardustDropLevel1->loadTexture("level_full.png");
        if (m_pStardustDropLevel2)
            m_pStardustDropLevel2->loadTexture("level_full.png");
        if (m_pStardustDropLevel3)
            m_pStardustDropLevel3->loadTexture("level_full.png");
        if (m_pStardustDropLevel4)
            m_pStardustDropLevel4->loadTexture("level_full.png");
        if (m_pStardustDropLevel5)
            m_pStardustDropLevel5->loadTexture("level_full.png");
    }
    else if(stardustDropLevel == 4)
    {
        if(m_pStardustDropLevelText && m_pStardustDropLevelAdd)
        {
            ChaosNumber needStardust(600);
            if(curStardustNum >= needStardust)
            {
                std::string strStardustDropLevel = String::createWithFormat(UtilityHelper::getLocalString("STARDUST_DROP").c_str(), (int)(needStardust.GetLongValue()), 5)->getCString();
                m_pStardustDropLevelText->setColor(Color3B(208,255,208));
                m_pStardustDropLevelText->setString(strStardustDropLevel);
                m_pStardustDropLevelAdd->setVisible(true);
            }
            else
            {
                std::string strStardustDropLevel = String::createWithFormat(UtilityHelper::getLocalString("LEVEL_FAILED").c_str(), (int)(needStardust.GetLongValue()))->getCString();
                m_pStardustDropLevelText->setColor(Color3B(255,100,220));
                m_pStardustDropLevelText->setString(strStardustDropLevel);
                m_pStardustDropLevelAdd->setVisible(false);
            }
        }
        if (m_pStardustDropLevel1)
            m_pStardustDropLevel1->loadTexture("level_full.png");
        if (m_pStardustDropLevel2)
            m_pStardustDropLevel2->loadTexture("level_full.png");
        if (m_pStardustDropLevel3)
            m_pStardustDropLevel3->loadTexture("level_full.png");
        if (m_pStardustDropLevel4)
            m_pStardustDropLevel4->loadTexture("level_full.png");
    }
    else if(stardustDropLevel == 3)
    {
        if(m_pStardustDropLevelText && m_pStardustDropLevelAdd)
        {
            ChaosNumber needStardust(270);
            if(curStardustNum >= needStardust)
            {
                std::string strStardustDropLevel = String::createWithFormat(UtilityHelper::getLocalString("STARDUST_DROP").c_str(), (int)(needStardust.GetLongValue()), 4)->getCString();
                m_pStardustDropLevelText->setColor(Color3B(208,255,208));
                m_pStardustDropLevelText->setString(strStardustDropLevel);
                m_pStardustDropLevelAdd->setVisible(true);
            }
            else
            {
                std::string strStardustDropLevel = String::createWithFormat(UtilityHelper::getLocalString("LEVEL_FAILED").c_str(), (int)(needStardust.GetLongValue()))->getCString();
                m_pStardustDropLevelText->setColor(Color3B(255,100,220));
                m_pStardustDropLevelText->setString(strStardustDropLevel);
                m_pStardustDropLevelAdd->setVisible(false);
            }
        }
        if (m_pStardustDropLevel1)
            m_pStardustDropLevel1->loadTexture("level_full.png");
        if (m_pStardustDropLevel2)
            m_pStardustDropLevel2->loadTexture("level_full.png");
        if (m_pStardustDropLevel3)
            m_pStardustDropLevel3->loadTexture("level_full.png");
    }
    else if(stardustDropLevel == 2)
    {
        if(m_pStardustDropLevelText && m_pStardustDropLevelAdd)
        {
            ChaosNumber needStardust(100);
            if(curStardustNum >= needStardust)
            {
                std::string strStardustDropLevel = String::createWithFormat(UtilityHelper::getLocalString("STARDUST_DROP").c_str(), (int)(needStardust.GetLongValue()), 3)->getCString();
                m_pStardustDropLevelText->setColor(Color3B(208,255,208));
                m_pStardustDropLevelText->setString(strStardustDropLevel);
                m_pStardustDropLevelAdd->setVisible(true);
            }
            else
            {
                std::string strStardustDropLevel = String::createWithFormat(UtilityHelper::getLocalString("LEVEL_FAILED").c_str(), (int)(needStardust.GetLongValue()))->getCString();
                m_pStardustDropLevelText->setColor(Color3B(255,100,220));
                m_pStardustDropLevelText->setString(strStardustDropLevel);
                m_pStardustDropLevelAdd->setVisible(false);
            }
        }
        if (m_pStardustDropLevel1)
            m_pStardustDropLevel1->loadTexture("level_full.png");
        if (m_pStardustDropLevel2)
            m_pStardustDropLevel2->loadTexture("level_full.png");
    }
    else if(stardustDropLevel == 1)
    {
        if(m_pStardustDropLevelText && m_pStardustDropLevelAdd)
        {
            ChaosNumber needStardust(30);
            if(curStardustNum >= needStardust)
            {
                std::string strStardustDropLevel = String::createWithFormat(UtilityHelper::getLocalString("STARDUST_DROP").c_str(), (int)(needStardust.GetLongValue()), 2)->getCString();
                m_pStardustDropLevelText->setColor(Color3B(208,255,208));
                m_pStardustDropLevelText->setString(strStardustDropLevel);
                m_pStardustDropLevelAdd->setVisible(true);
            }
            else
            {
                std::string strStardustDropLevel = String::createWithFormat(UtilityHelper::getLocalString("LEVEL_FAILED").c_str(), (int)(needStardust.GetLongValue()))->getCString();
                m_pStardustDropLevelText->setColor(Color3B(255,100,220));
                m_pStardustDropLevelText->setString(strStardustDropLevel);
                m_pStardustDropLevelAdd->setVisible(false);
            }
        }
        if (m_pStardustDropLevel1)
            m_pStardustDropLevel1->loadTexture("level_full.png");
    }
    
    
    if(itemDropLevel >= 5)
    {
        if(m_pItemDropLevelText)
        {
            m_pItemDropLevelText->setColor(Color3B(208,255,208));
            m_pItemDropLevelText->setString(UtilityHelper::getLocalString("ITEM_DROP_MAX"));
        }
        if (m_pItemDropLevelAdd)
            m_pItemDropLevelAdd->setVisible(false);
        if (m_pItemDropLevel1)
            m_pItemDropLevel1->loadTexture("level_full.png");
        if (m_pItemDropLevel2)
            m_pItemDropLevel2->loadTexture("level_full.png");
        if (m_pItemDropLevel3)
            m_pItemDropLevel3->loadTexture("level_full.png");
        if (m_pItemDropLevel4)
            m_pItemDropLevel4->loadTexture("level_full.png");
        if (m_pItemDropLevel5)
            m_pItemDropLevel5->loadTexture("level_full.png");
    }
    else if(itemDropLevel == 4)
    {
        if(m_pItemDropLevelText && m_pItemDropLevelAdd)
        {
            ChaosNumber needStardust(700);
            if(curStardustNum >= needStardust)
            {
                std::string strItemDropLevel = String::createWithFormat(UtilityHelper::getLocalString("ITEM_DROP").c_str(), (int)(needStardust.GetLongValue()), 5)->getCString();
                m_pItemDropLevelText->setColor(Color3B(208,255,208));
                m_pItemDropLevelText->setString(strItemDropLevel);
                m_pItemDropLevelAdd->setVisible(true);
            }
            else
            {
                std::string strItemDropLevel = String::createWithFormat(UtilityHelper::getLocalString("LEVEL_FAILED").c_str(), (int)(needStardust.GetLongValue()))->getCString();
                m_pItemDropLevelText->setColor(Color3B(255,100,220));
                m_pItemDropLevelText->setString(strItemDropLevel);
                m_pItemDropLevelAdd->setVisible(false);
            }
        }
        if (m_pItemDropLevel1)
            m_pItemDropLevel1->loadTexture("level_full.png");
        if (m_pItemDropLevel2)
            m_pItemDropLevel2->loadTexture("level_full.png");
        if (m_pItemDropLevel3)
            m_pItemDropLevel3->loadTexture("level_full.png");
        if (m_pItemDropLevel4)
            m_pItemDropLevel4->loadTexture("level_full.png");
    }
    else if(itemDropLevel == 3)
    {
        if(m_pItemDropLevelText && m_pItemDropLevelAdd)
        {
            ChaosNumber needStardust(320);
            if(curStardustNum >= needStardust)
            {
                std::string strItemDropLevel = String::createWithFormat(UtilityHelper::getLocalString("ITEM_DROP").c_str(), (int)(needStardust.GetLongValue()), 4)->getCString();
                m_pItemDropLevelText->setColor(Color3B(208,255,208));
                m_pItemDropLevelText->setString(strItemDropLevel);
                m_pItemDropLevelAdd->setVisible(true);
            }
            else
            {
                std::string strItemDropLevel = String::createWithFormat(UtilityHelper::getLocalString("LEVEL_FAILED").c_str(), (int)(needStardust.GetLongValue()))->getCString();
                m_pItemDropLevelText->setColor(Color3B(255,100,220));
                m_pItemDropLevelText->setString(strItemDropLevel);
                m_pItemDropLevelAdd->setVisible(false);
            }
        }
        if (m_pItemDropLevel1)
            m_pItemDropLevel1->loadTexture("level_full.png");
        if (m_pItemDropLevel2)
            m_pItemDropLevel2->loadTexture("level_full.png");
        if (m_pItemDropLevel3)
            m_pItemDropLevel3->loadTexture("level_full.png");
    }
    else if(itemDropLevel == 2)
    {
        if(m_pItemDropLevelText && m_pItemDropLevelAdd)
        {
            ChaosNumber needStardust(140);
            if(curStardustNum >= needStardust)
            {
                std::string strItemDropLevel = String::createWithFormat(UtilityHelper::getLocalString("ITEM_DROP").c_str(), (int)(needStardust.GetLongValue()), 3)->getCString();
                m_pItemDropLevelText->setColor(Color3B(208,255,208));
                m_pItemDropLevelText->setString(strItemDropLevel);
                m_pItemDropLevelAdd->setVisible(true);
            }
            else
            {
                std::string strItemDropLevel = String::createWithFormat(UtilityHelper::getLocalString("LEVEL_FAILED").c_str(), (int)(needStardust.GetLongValue()))->getCString();
                m_pItemDropLevelText->setColor(Color3B(255,100,220));
                m_pItemDropLevelText->setString(strItemDropLevel);
                m_pItemDropLevelAdd->setVisible(false);
            }
        }
        if (m_pItemDropLevel1)
            m_pItemDropLevel1->loadTexture("level_full.png");
        if (m_pItemDropLevel2)
            m_pItemDropLevel2->loadTexture("level_full.png");
    }
    else if(itemDropLevel == 1)
    {
        if(m_pItemDropLevelText && m_pItemDropLevelAdd)
        {
            ChaosNumber needStardust(40);
            if(curStardustNum >= needStardust)
            {
                std::string strItemDropLevel = String::createWithFormat(UtilityHelper::getLocalString("ITEM_DROP").c_str(), (int)(needStardust.GetLongValue()), 2)->getCString();
                m_pItemDropLevelText->setColor(Color3B(208,255,208));
                m_pItemDropLevelText->setString(strItemDropLevel);
                m_pItemDropLevelAdd->setVisible(true);
            }
            else
            {
                std::string strItemDropLevel = String::createWithFormat(UtilityHelper::getLocalString("LEVEL_FAILED").c_str(), (int)(needStardust.GetLongValue()))->getCString();
                m_pItemDropLevelText->setColor(Color3B(255,100,220));
                m_pItemDropLevelText->setString(strItemDropLevel);
                m_pItemDropLevelAdd->setVisible(false);
            }
        }
        if (m_pItemDropLevel1)
            m_pItemDropLevel1->loadTexture("level_full.png");
    }

    if(itemEffectLevel >= 5)
    {
        if(m_pItemEffectLevelText)
        {
            m_pItemEffectLevelText->setColor(Color3B(208,255,208));
            m_pItemEffectLevelText->setString(UtilityHelper::getLocalString("ITEM_EFFECT_MAX"));
        }
        if (m_pItemEffectLevelAdd)
            m_pItemEffectLevelAdd->setVisible(false);
        if (m_pItemEffectLevel1)
            m_pItemEffectLevel1->loadTexture("level_full.png");
        if (m_pItemEffectLevel2)
            m_pItemEffectLevel2->loadTexture("level_full.png");
        if (m_pItemEffectLevel3)
            m_pItemEffectLevel3->loadTexture("level_full.png");
        if (m_pItemEffectLevel4)
            m_pItemEffectLevel4->loadTexture("level_full.png");
        if (m_pItemEffectLevel5)
            m_pItemEffectLevel5->loadTexture("level_full.png");
    }
    else if(itemEffectLevel == 4)
    {
        if(m_pItemEffectLevelText && m_pItemEffectLevelAdd)
        {
            ChaosNumber needStardust(800);
            if(curStardustNum >= needStardust)
            {
                std::string strItemEffectLevel = String::createWithFormat(UtilityHelper::getLocalString("ITEM_EFFECT").c_str(), (int)(needStardust.GetLongValue()), 5)->getCString();
                m_pItemEffectLevelText->setColor(Color3B(208,255,208));
                m_pItemEffectLevelText->setString(strItemEffectLevel);
                m_pItemEffectLevelAdd->setVisible(true);
            }
            else
            {
                std::string strItemEffectLevel = String::createWithFormat(UtilityHelper::getLocalString("LEVEL_FAILED").c_str(), (int)(needStardust.GetLongValue()))->getCString();
                m_pItemEffectLevelText->setColor(Color3B(255,100,220));
                m_pItemEffectLevelText->setString(strItemEffectLevel);
                m_pItemEffectLevelAdd->setVisible(false);
            }
        }
        if (m_pItemEffectLevel1)
            m_pItemEffectLevel1->loadTexture("level_full.png");
        if (m_pItemEffectLevel2)
            m_pItemEffectLevel2->loadTexture("level_full.png");
        if (m_pItemEffectLevel3)
            m_pItemEffectLevel3->loadTexture("level_full.png");
        if (m_pItemEffectLevel4)
            m_pItemEffectLevel4->loadTexture("level_full.png");
    }
    else if(itemEffectLevel == 3)
    {
        if(m_pItemEffectLevelText && m_pItemEffectLevelAdd)
        {
            ChaosNumber needStardust(390);
            if(curStardustNum >= needStardust)
            {
                std::string strItemEffectLevel = String::createWithFormat(UtilityHelper::getLocalString("ITEM_EFFECT").c_str(), (int)(needStardust.GetLongValue()), 4)->getCString();
                m_pItemEffectLevelText->setColor(Color3B(208,255,208));
                m_pItemEffectLevelText->setString(strItemEffectLevel);
                m_pItemEffectLevelAdd->setVisible(true);
            }
            else
            {
                std::string strItemEffectLevel = String::createWithFormat(UtilityHelper::getLocalString("LEVEL_FAILED").c_str(), (int)(needStardust.GetLongValue()))->getCString();
                m_pItemEffectLevelText->setColor(Color3B(255,100,220));
                m_pItemEffectLevelText->setString(strItemEffectLevel);
                m_pItemEffectLevelAdd->setVisible(false);
            }
        }
        if (m_pItemEffectLevel1)
            m_pItemEffectLevel1->loadTexture("level_full.png");
        if (m_pItemEffectLevel2)
            m_pItemEffectLevel2->loadTexture("level_full.png");
        if (m_pItemEffectLevel3)
            m_pItemEffectLevel3->loadTexture("level_full.png");
    }
    else if(itemEffectLevel == 2)
    {
        if(m_pItemEffectLevelText && m_pItemEffectLevelAdd)
        {
            ChaosNumber needStardust(160);
            if(curStardustNum >= needStardust)
            {
                std::string strItemEffectLevel = String::createWithFormat(UtilityHelper::getLocalString("ITEM_EFFECT").c_str(), (int)(needStardust.GetLongValue()), 3)->getCString();
                m_pItemEffectLevelText->setColor(Color3B(208,255,208));
                m_pItemEffectLevelText->setString(strItemEffectLevel);
                m_pItemEffectLevelAdd->setVisible(true);
            }
            else
            {
                std::string strItemEffectLevel = String::createWithFormat(UtilityHelper::getLocalString("LEVEL_FAILED").c_str(), (int)(needStardust.GetLongValue()))->getCString();
                m_pItemEffectLevelText->setColor(Color3B(255,100,220));
                m_pItemEffectLevelText->setString(strItemEffectLevel);
                m_pItemEffectLevelAdd->setVisible(false);
            }
        }
        if (m_pItemEffectLevel1)
            m_pItemEffectLevel1->loadTexture("level_full.png");
        if (m_pItemEffectLevel2)
            m_pItemEffectLevel2->loadTexture("level_full.png");
    }
    else if(itemEffectLevel == 1)
    {
        if(m_pItemEffectLevelText && m_pItemEffectLevelAdd)
        {
            ChaosNumber needStardust(50);
            if(curStardustNum >= needStardust)
            {
                std::string strItemEffectLevel = String::createWithFormat(UtilityHelper::getLocalString("ITEM_EFFECT").c_str(), (int)(needStardust.GetLongValue()), 2)->getCString();
                m_pItemEffectLevelText->setColor(Color3B(208,255,208));
                m_pItemEffectLevelText->setString(strItemEffectLevel);
                m_pItemEffectLevelAdd->setVisible(true);
            }
            else
            {
                std::string strItemEffectLevel = String::createWithFormat(UtilityHelper::getLocalString("LEVEL_FAILED").c_str(), (int)(needStardust.GetLongValue()))->getCString();
                m_pItemEffectLevelText->setColor(Color3B(255,100,220));
                m_pItemEffectLevelText->setString(strItemEffectLevel);
                m_pItemEffectLevelAdd->setVisible(false);
            }
        }
        if (m_pItemEffectLevel1)
            m_pItemEffectLevel1->loadTexture("level_full.png");
    }

}
void PauseUI::updateGoodBalance(cocos2d::EventCustom *event) {
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
void PauseUI::updateCurrencyBalance(cocos2d::EventCustom *event) {
    __Dictionary *eventData = (__Dictionary *)event->getUserData();
    __Integer *amountAdded = dynamic_cast<__Integer *>(eventData->objectForKey(CCStoreConsts::DICT_ELEMENT_AMOUNT_ADDED));
    ChaosNumber add(amountAdded->getValue());
    GameController::getInstance()->addStardust(add);
}
