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
    m_popupBgLayer = ui::ImageView::create(UtilityHelper::getLocalString("UI_START_PANEL"));
    m_popupBgLayer->setPosition(Vec2(size.width*0.5,size.height*0.5));
    m_popupBgLayer->setScale(scale);
    
    m_dialogLayer->addChild(m_popupBgLayer);

   
    m_goldTv = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),Value(Value(localStorageGetItem(USER_GOLD_NUM)).asInt()).asString());
    m_goldTv->setAnchorPoint(Vec2(1, 0.5));
    m_goldTv->setPosition(Vec2(size.width*0.7, size.height*0.6));
    m_goldTv->setScale(scale*0.5);
    m_goldTv->setHorizontalAlignment(TextHAlignment::RIGHT);
    m_dialogLayer->addChild(m_goldTv);


    m_heartTv = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),Value(Value(localStorageGetItem(USER_HEART_NUM)).asInt()).asString());
    m_heartTv->setAnchorPoint(Vec2(1, 0.5));
    m_heartTv->setPosition(Vec2(size.width*0.7, size.height*0.53));
    m_heartTv->setScale(scale*0.5);
    m_heartTv->setHorizontalAlignment(TextHAlignment::RIGHT);
    m_dialogLayer->addChild(m_heartTv);
    
     m_maxLevelTv = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),Value(Value(localStorageGetItem(USER_MAX_LEVEL)).asInt()).asString());
    m_maxLevelTv->setPosition(Vec2(size.width*0.7, size.height*0.45));
    m_maxLevelTv->setScale(scale*0.5);
    m_maxLevelTv->setAnchorPoint(Vec2(1, 0.5));
    m_maxLevelTv->setHorizontalAlignment(TextHAlignment::RIGHT);
    m_dialogLayer->addChild(m_maxLevelTv);
    


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
    if (m_goldTv) {
        m_goldTv->setString(localStorageGetItem(USER_GOLD_NUM));
    }
}
void StarPopUpUI::onHeartChange(cocos2d::EventCustom *sender)
{
    CCLOG("StarPopUpUI::onHeartChange");
    if (m_heartTv) {
        m_heartTv->setString(localStorageGetItem(USER_HEART_NUM));
    }
}

void StarPopUpUI::onPlayGame(cocos2d::Ref *ref)
{
    isContinue = false;
    UIManager::getInstance()->hidePopUp(true,CC_CALLBACK_0(StarPopUpUI::onHidePop, this));
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
        UIManager::getInstance()->hidePopUp(true,CC_CALLBACK_0(StarPopUpUI::onHidePop, this));
    }else
    {
        CCLOG("Shop");
        UIManager::getInstance()->addPopUp(BasePopUpUI::POPUP_SHOP);
        UIManager::getInstance()->showPopUp(false);
    }
    
}

