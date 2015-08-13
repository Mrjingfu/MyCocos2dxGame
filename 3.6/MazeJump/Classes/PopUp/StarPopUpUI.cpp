//
//  StartUI.cpp
//
//
//
//

#include "StarPopUpUI.h"
#include "UtilityHelper.h"
#include "GameConst.h"
#include "MainScene.h"
#include "UIManager.h"
#include "storage/local-storage/LocalStorage.h"
USING_NS_CC;

StarPopUpUI* StarPopUpUI::create()
{
    StarPopUpUI *pRet = new(std::nothrow) StarPopUpUI();
    if (pRet)
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

StarPopUpUI::StarPopUpUI()
{
    isContinue = false;
}
StarPopUpUI::~StarPopUpUI()
{
}

bool StarPopUpUI::init()
{
    
    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.width /640.0f;
    ui::ImageView* bgView = ui::ImageView::create(UtilityHelper::getLocalString("UI_START_PANEL"));
    bgView->setPosition(Vec2(size.width*0.5,size.height*0.5));
    bgView->setScale(scale);
    
    m_dialogLayer->addChild(bgView);


    goldTv =Label::createWithTTF(StringUtils::format("%d",Value(localStorageGetItem(USER_GOLD_NUM)).asInt()), FONT_FXZS, 30);
    goldTv->setAnchorPoint(Vec2(1, 0.5));
    goldTv->setPosition(Vec2(size.width*0.7, size.height*0.6));
    goldTv->setScale(scale);
    goldTv->setHorizontalAlignment(TextHAlignment::RIGHT);
    m_dialogLayer->addChild(goldTv);

   

    heartTv = Label::createWithTTF(StringUtils::format("%d",Value(localStorageGetItem(USER_HEART_NUM)).asInt()), FONT_FXZS, 30);
    heartTv->setAnchorPoint(Vec2(1, 0.5));
    heartTv->setPosition(Vec2(size.width*0.7, size.height*0.53));
    heartTv->setScale(scale);
heartTv->setHorizontalAlignment(TextHAlignment::RIGHT);
    m_dialogLayer->addChild(heartTv);
    
     lastScoreView = Label::createWithTTF(localStorageGetItem(USER_MAX_LEVEL), FONT_FXZS, 30);
    lastScoreView->setPosition(Vec2(size.width*0.7, size.height*0.45));
    lastScoreView->setScale(scale);
    lastScoreView->setAnchorPoint(Vec2(1, 0.5));
    lastScoreView->setHorizontalAlignment(TextHAlignment::RIGHT);
    m_dialogLayer->addChild(lastScoreView);
    


    ui::Button* playBtn = ui::Button::create(UtilityHelper::getLocalString("UI_START_BTN_NEW"));
    playBtn->setPosition(Vec2(size.width*0.38, size.height*0.37));
    
    playBtn->setScale(scale);
    playBtn->addClickEventListener(CC_CALLBACK_1(StarPopUpUI::onPlayGame, this));
    m_dialogLayer->addChild(playBtn);

    ui::Button* resumeBtn = ui::Button::create(UtilityHelper::getLocalString("UI_START_BTN_CONTINUE"));
    resumeBtn->setPosition(Vec2(size.width*0.38+playBtn->getContentSize().width*scale+25*scale,size.height*0.37));
    resumeBtn->setScale(scale);
    resumeBtn->addClickEventListener(CC_CALLBACK_1(StarPopUpUI::onResumeGame, this));

    m_dialogLayer->addChild(resumeBtn);
    
    
    
    return true;
}
void StarPopUpUI::onEnter()
{
    BasePopUpUI::onEnter();
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_START_GOLD_CHANGE, std::bind(&StarPopUpUI::onGoldChange, this, std::placeholders::_1));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_START_HEART_CHANGE, std::bind(&StarPopUpUI::onHeartChange, this, std::placeholders::_1));
    init();
}
void StarPopUpUI::onExit()
{
    BasePopUpUI::onExit();
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_START_GOLD_CHANGE);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_START_HEART_CHANGE);

}
void StarPopUpUI::onGoldChange(cocos2d::EventCustom *sender)
{
    CCLOG("StarPopUpUI::onGoldChange");
    if (goldTv) {
        goldTv->setString(localStorageGetItem(USER_GOLD_NUM));
    }
}
void StarPopUpUI::onHeartChange(cocos2d::EventCustom *sender)
{
    CCLOG("StarPopUpUI::onHeartChange");
    if (heartTv) {
        heartTv->setString(localStorageGetItem(USER_HEART_NUM));
    }
}

void StarPopUpUI::onPlayGame(cocos2d::Ref *ref)
{
    isContinue = false;
    UIManager::getInstance()->hidePopUp(CC_CALLBACK_0(StarPopUpUI::onHidePop, this));
}
void StarPopUpUI::onHidePop()
{
    if (isContinue) {
        localStorageSetItem(USER_HEART_NUM, Value(Value(localStorageGetItem(USER_HEART_NUM)).asInt()-5).asString());
        localStorageSetItem(USER_LAST_LEVEL, localStorageGetItem(USER_MAX_LEVEL));
        auto scene = MainScene::createScene();
        Director::getInstance()->replaceScene(scene);
        isContinue = false;
    }else
    {
        localStorageSetItem(USER_LAST_LEVEL, Value(0).asString());
        auto scene = MainScene::createScene();
        Director::getInstance()->replaceScene(scene);
    }

}
void StarPopUpUI::onResumeGame(cocos2d::Ref *ref)
{
    CCLOG("onResumeGame");
    
    int heartNum = Value(localStorageGetItem(USER_HEART_NUM)).asInt();
    if (heartNum>=5) {
        isContinue = true;
        UIManager::getInstance()->hidePopUp(CC_CALLBACK_0(StarPopUpUI::onHidePop, this));
    }else
    {
        CCLOG("Shop");
        UIManager::getInstance()->addPopUp(BasePopUpUI::POPUP_HEART_NOT_ENOUGT);
        UIManager::getInstance()->showPopUp(false);
    }
    
}

