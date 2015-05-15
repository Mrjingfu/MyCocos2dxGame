//
//  MainUI.cpp
//  TinyFlare
//
//  Created by wang haibo on 15/4/20.
//
//

#include "MainUI.h"
#include "EncrytionUtility.h"
#include "UtilityHelper.h"
#include "GameController.h"
#include "SimpleAudioEngine.h"
#include "ActorsManager.h"
USING_NS_CC;
using namespace CocosDenshion;

MainUI* MainUI::create()
{
    MainUI *pRet = new(std::nothrow) MainUI();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

MainUI::MainUI()
{
    m_pPauseGameBtn         = nullptr;
    m_pLevelProgressBg      = nullptr;
    m_pLevelProgress        = nullptr;
    m_pLevelProgressBar     = nullptr;
    m_pLevelProgressComplete= nullptr;
    m_pStageText            = nullptr;
    m_pStageTextBottom      = nullptr;
    m_pBufferContainer      = nullptr;
    m_pStardust             = nullptr;
    m_pStardustX            = nullptr;
    m_pStardustNum          = nullptr;
    
}
MainUI::~MainUI()
{
}
bool MainUI::init()
{
    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.height/480.0f;
    m_pStardust = ui::ImageView::create("diamonditem.png");
    if(!m_pStardust)
        return false;
    m_pStardust->setPosition(Vec2(30*scale, size.height - 30*scale));
    m_pStardust->setScale(0.05f*scale, 0.07f*scale);
    addChild(m_pStardust);
    
    m_pStardustX = ui::Text::create(" x ", "FZXS12.TTF", m_pStardust->getContentSize().height*0.05f*scale);
    if(!m_pStardustX)
        return false;
    m_pStardustX->setPosition(m_pStardust->getPosition() + Vec2(m_pStardust->getContentSize().width*0.05f*scale, 0));
    m_pStardustX->setAnchorPoint(Vec2(0.5, 0.5f));
    m_pStardustX->setColor(Color3B(208,255,208));
    addChild(m_pStardustX);
    
    int stardustNum = EncrytionUtility::getIntegerForKey("CurStardustNum", 0);
    m_pStardustNum = ui::Text::create(Value(stardustNum).asString(), "FZXS12.TTF", m_pStardust->getContentSize().height*0.05f*scale);
    if(!m_pStardustNum)
        return false;
    m_pStardustNum->setColor(Color3B(208,255,208));
    m_pStardustNum->setAnchorPoint(Vec2(0, 0.6f));
    m_pStardustNum->setPosition(m_pStardustX->getPosition() + Vec2(m_pStardustX->getContentSize().width*0.3f*scale, 0));
    addChild(m_pStardustNum);
    
    m_pBufferContainer = BufferContainer::create();
    if(!m_pBufferContainer)
        return false;
    addChild(m_pBufferContainer);
    
    m_pBufferContainer->setPosition(Vec2(size.width*0.2f, m_pStardust->getPosition().y));
    m_pBufferContainer->setScale(0.2f*scale);
    
    m_pPauseGameBtn = ui::Button::create("pause.png");
    if(!m_pPauseGameBtn)
        return false;
    m_pPauseGameBtn->addTouchEventListener(CC_CALLBACK_2(MainUI::pressPauseGameBtn, this));
    m_pPauseGameBtn->setPosition(Vec2(size.width - 30*scale, size.height - 30*scale));
    m_pPauseGameBtn->setScale(0.3f*scale);
    addChild(m_pPauseGameBtn);
    
    m_pLevelProgressBg = ui::ImageView::create("menubg.png");
    if(!m_pLevelProgressBg)
        return false;
    m_pLevelProgressBg->setScale9Enabled(true);
    m_pLevelProgressBg->setCapInsets(cocos2d::Rect(0,2,128,0.5f));
    m_pLevelProgressBg->setContentSize(cocos2d::Size(size.width*0.4f,8.0f*scale));
    m_pLevelProgressBg->setPosition(Vec2(size.width*0.5f, 50.0f*scale));
    m_pLevelProgressBg->setOpacity(128);
    addChild(m_pLevelProgressBg);
    
    m_pLevelProgress = ui::LoadingBar::create("menubg.png");
    if(!m_pLevelProgress)
        return false;
    m_pLevelProgress->setScale9Enabled(true);
    m_pLevelProgress->setCapInsets(cocos2d::Rect(0,1,128,0.5f));
    m_pLevelProgress->setContentSize(cocos2d::Size(size.width*0.4f,8.0f*scale));
    m_pLevelProgress->setPosition(Vec2(size.width*0.5f, 50.0f*scale));
    addChild(m_pLevelProgress);
    
    m_pLevelProgressBar = ui::ImageView::create("playermain.png");
    if(!m_pLevelProgressBar)
        return false;
    m_pLevelProgressBar->setPosition(Vec2(m_pLevelProgressBg->getPosition().x - size.width*0.2f, 50.0f*scale));
    m_pLevelProgressBar->setRotation(90);
    m_pLevelProgressBar->setScale(0.25f*scale);
    addChild(m_pLevelProgressBar);
    
    m_pLevelProgressComplete = ui::ImageView::create("diamonditem.png");
    if(!m_pLevelProgressComplete)
        return false;
    m_pLevelProgressComplete->setPosition(Vec2(m_pLevelProgressBg->getPosition().x + size.width*0.2f + 5.0f*scale, 50.0f*scale));
    m_pLevelProgressComplete->setScale(0.05f*scale, 0.07f*scale);
    addChild(m_pLevelProgressComplete);
    
    std::string strStage = UtilityHelper::getLocalString("STAGE");
    Value stageNum = Value(EncrytionUtility::getIntegerForKey("CurrentStage", 1));
    strStage += stageNum.asString();
    m_pStageText = ui::Text::create(strStage, "FZXS12.TTF", m_pStardust->getContentSize().height*0.08f*scale);
    if(!m_pStageText)
        return false;
    m_pStageText->setPosition(Vec2(size.width*0.75f, size.height*0.7f));
    m_pStageText->setColor(Color3B(208,255,208));
    m_pStageText->setOpacity(0);
    addChild(m_pStageText);
    
    m_pStageTextBottom = ui::Text::create(strStage, "FZXS12.TTF", m_pStardust->getContentSize().height*0.04f*scale);
    if(!m_pStageTextBottom)
        return false;
    m_pStageTextBottom->setPosition(Vec2(size.width*0.5f, 70.0f*scale));
    m_pStageTextBottom->setColor(Color3B(208,255,208));
    m_pStageTextBottom->setOpacity(0);
    addChild(m_pStageTextBottom);
    return true;
}


void MainUI::pressPauseGameBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
        if(GameController::getInstance()->isPaused())
            GameController::getInstance()->resume();
        else
            GameController::getInstance()->pause();
    }
}

void MainUI::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *unused_event)
{
    if(keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
    {
        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
        if(GameController::getInstance()->isPaused())
            GameController::getInstance()->resume();
        else
            GameController::getInstance()->pause();
    }
}
void MainUI::nextStage(int stage)
{
    if(stage > 1)
        setLevelPercent(100);
    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.height/480.0f;
    std::string strStage = UtilityHelper::getLocalString("STAGE");
    Value stageNum = Value(stage);
    strStage += stageNum.asString();
    
    if(m_pStageText)
    {
        m_pStageText->stopAllActions();
        m_pStageText->setString(strStage);
        m_pStageText->setOpacity(0);
        m_pStageText->setScale(1.0f);
        m_pStageText->setPosition(Vec2(size.width*0.75f, size.height*0.7f));
        EaseSineIn* easeIn = EaseSineIn::create(FadeIn::create(0.5f));
        EaseSineOut* easeOut1 = EaseSineOut::create(MoveTo::create(0.5f, Vec2(size.width*0.5f, size.height*0.7f)));
        Spawn* spawn1 = Spawn::createWithTwoActions(easeIn, easeOut1);
        DelayTime* delay = DelayTime::create(1.0f);
        EaseSineOut* easeOut2 = EaseSineOut::create(FadeOut::create(0.2f));
        ScaleTo* scaleTo = ScaleTo::create(0.2f, 2.0f);
        Spawn* spawn2 = Spawn::createWithTwoActions(easeOut2, scaleTo);
        Sequence* sequece = Sequence::create(spawn1, delay, spawn2, NULL);
        m_pStageText->runAction(sequece);
    }
    if(m_pStageTextBottom)
    {
        m_pStageTextBottom->stopAllActions();
        m_pStageTextBottom->setString(strStage);
        m_pStageTextBottom->setOpacity(0);
        m_pStageTextBottom->setPosition(Vec2(size.width*0.5f, 70.0f*scale));
        DelayTime* delay2 = DelayTime::create(1.0f);
        EaseSineIn* easeIn1 = EaseSineIn::create(FadeIn::create(1.0f));
        EaseSineOut* easeOut3 = EaseSineOut::create(MoveTo::create(1.0f, Vec2(m_pLevelProgressBg->getPosition().x - size.width*0.12f, 70.0f*scale)));
        Spawn* spawn3 = Spawn::createWithTwoActions(easeIn1, easeOut3);
        
        Sequence* sequece1 = Sequence::createWithTwoActions(delay2, spawn3);
        m_pStageTextBottom->runAction(sequece1);
    }
    
    setLevelPercent(0);
}
void MainUI::addStardust(ChaosNumber& num)
{
    ChaosNumber curStarDust;
    curStarDust = EncrytionUtility::getIntegerForKey("CurStardustNum", 0);
    curStarDust = curStarDust + num.GetLongValue();
    EncrytionUtility::setIntegerForKey("CurStardustNum", (int)(curStarDust.GetLongValue()));
    if(m_pStardustNum)
    {
        m_pStardustNum->setString(Value((int)(curStarDust.GetLongValue())).asString());
        m_pStardustNum->stopAllActions();
        EaseSineIn* easeIn1 = EaseSineIn::create(ScaleTo::create(0.2f, 1.2f));
        EaseSineIn* easeIn2 = EaseSineIn::create(ScaleTo::create(0.2f, 1.0f));
        Sequence* sequece = Sequence::createWithTwoActions(easeIn1, easeIn2);
        m_pStardustNum->runAction(sequece);
    }
    SimpleAudioEngine::getInstance()->playEffect("Pickup_GemBells11.wav");
}
void MainUI::subStardust(ChaosNumber& num)
{
    ChaosNumber curStarDust;
    curStarDust = EncrytionUtility::getIntegerForKey("CurStardustNum", 0);
    curStarDust = curStarDust - num.GetLongValue();
    EncrytionUtility::setIntegerForKey("CurStardustNum", (int)(curStarDust.GetLongValue()));
    if(m_pStardustNum)
    {
        m_pStardustNum->setString(Value((int)(curStarDust.GetLongValue())).asString());
        m_pStardustNum->stopAllActions();
        EaseSineIn* easeIn1 = EaseSineIn::create(ScaleTo::create(0.2f, 0.8f));
        EaseSineIn* easeIn2 = EaseSineIn::create(ScaleTo::create(0.2f, 1.0f));
        Sequence* sequece = Sequence::createWithTwoActions(easeIn1, easeIn2);
        m_pStardustNum->runAction(sequece);
    }
}
void MainUI::setLevelPercent(float percent)
{
    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.height/480.0f;
    if(m_pLevelProgress)
        m_pLevelProgress->setPercent(percent*100);
    if(m_pLevelProgressBar)
        m_pLevelProgressBar->setPosition(Vec2(m_pLevelProgressBg->getPosition().x - size.width*0.2f + size.width*0.4f*percent, 50.0f*scale));
    if(percent == 100.0f)
    {
        this->stopAllActions();
        ChaosNumber curStage(1);
        curStage = EncrytionUtility::getIntegerForKey("CurrentStage", 1);
        CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(MainUI::spawnLevelStardust,this));
        DelayTime* delay = DelayTime::create(2.0f/curStage.GetLongValue());
        Sequence* sequece = Sequence::createWithTwoActions(callFunc, delay);
        Repeat* repeat = Repeat::create(sequece, (int)(curStage.GetLongValue()));
        this->runAction(repeat);
    }
}
void MainUI::spawnLevelStardust()
{
    ActorsManager::spawnStardust(Stardust::ST_LARGE, GameController::getInstance()->getStardustStartPos());
}
void MainUI::onBeginAccel(float time)
{
    if (m_pBufferContainer) {
        m_pBufferContainer->showAccel(time);
    }
}
void MainUI::onEndAccel()
{
    if (m_pBufferContainer) {
        m_pBufferContainer->hideAccel();
    }
}

void MainUI::onBeginMulti(float time)
{
    if (m_pBufferContainer) {
        m_pBufferContainer->showMulti(time);
    }
}
void MainUI::onEndMulti()
{
    if (m_pBufferContainer) {
        m_pBufferContainer->hideMulti();
    }
}

void MainUI::onBeginProtected(float time)
{
    if (m_pBufferContainer) {
        m_pBufferContainer->showProtected(time);
    }
}
void MainUI::onEndProtected()
{
    if (m_pBufferContainer) {
        m_pBufferContainer->hideProtected();
    }
}

void MainUI::onBeginTime(float time)
{
    if (m_pBufferContainer) {
        m_pBufferContainer->showTime(time);
    }
}
void MainUI::onEndTime()
{
    if (m_pBufferContainer) {
        m_pBufferContainer->hideTime();
    }
}
void MainUI::onPause()
{
    if(m_pLevelProgressBg)
        m_pLevelProgressBg->setVisible(false);
    if(m_pLevelProgress)
        m_pLevelProgress->setVisible(false);
    if(m_pLevelProgressBar)
        m_pLevelProgressBar->setVisible(false);
    if(m_pLevelProgressComplete)
        m_pLevelProgressComplete->setVisible(false);
    if(m_pStageText)
        m_pStageText->setVisible(false);
    if(m_pStageTextBottom)
        m_pStageTextBottom->setVisible(false);
    if(m_pBufferContainer)
        m_pBufferContainer->setVisible(false);
}
void MainUI::onResume()
{
    if(m_pLevelProgressBg)
        m_pLevelProgressBg->setVisible(true);
    if(m_pLevelProgress)
        m_pLevelProgress->setVisible(true);
    if(m_pLevelProgressBar)
        m_pLevelProgressBar->setVisible(true);
    if(m_pLevelProgressComplete)
        m_pLevelProgressComplete->setVisible(true);
    if(m_pStageText)
        m_pStageText->setVisible(true);
    if(m_pStageTextBottom)
        m_pStageTextBottom->setVisible(true);
    if(m_pBufferContainer)
        m_pBufferContainer->setVisible(true);
}