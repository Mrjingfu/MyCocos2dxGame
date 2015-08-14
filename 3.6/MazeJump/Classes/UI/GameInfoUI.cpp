//
//  GameUI.cpp
//
//
//
//

#include "GameInfoUI.h"
#include "UtilityHelper.h"
#include "GameConst.h"
#include "MainScene.h"
#include "UIManager.h"
#include "GameConst.h"
#include "storage/local-storage/LocalStorage.h"
USING_NS_CC;

GameInfoUI* GameInfoUI::create()
{
    GameInfoUI *pRet = new(std::nothrow) GameInfoUI();
    if (pRet&& pRet->init() )
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

GameInfoUI::GameInfoUI()
{

}
GameInfoUI::~GameInfoUI()
{
}

bool GameInfoUI::init()
{

    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.width /640.0f;
    
    ui::ImageView* glodView = ui::ImageView::create("ui_gold.png");
    glodView->setPosition(Vec2(70*scale, size.height*0.95));
    glodView->setScale(scale);
    addChild(glodView);
    
    goldTv = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),Value(Value(localStorageGetItem(USER_GOLD_NUM)).asInt()).asString());
    goldTv->setAnchorPoint(Vec2(0, 0.5));
    goldTv->setPosition(Vec2(100*scale,size.height*0.95 ));
    goldTv->setScale(scale*0.5);
    addChild(goldTv);
    
    
    
    
    ui::ImageView* heartView = ui::ImageView::create("ui_heart.png");
    heartView->setPosition(Vec2(70*scale, size.height*0.95-glodView->getContentSize().height*scale - 5*scale));
    heartView->setScale(scale);
    addChild(heartView);
    
    heartTv = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),Value(Value(localStorageGetItem(USER_HEART_NUM)).asInt()).asString());
    heartTv->setAnchorPoint(Vec2(0, 0.5));
    heartTv->setPosition(Vec2(100*scale, size.height*0.95-glodView->getContentSize().height*scale - 5*scale));
    heartTv->setScale(scale*0.5);
    addChild(heartTv);

    return true;
}

 void GameInfoUI::onEnter()
{
    Layer::onEnter();
    

    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_GOLD_CHANGE, std::bind(&GameInfoUI::onGoldChange, this, std::placeholders::_1));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_HEART_CHANGE, std::bind(&GameInfoUI::onHeartChange, this, std::placeholders::_1));


}
 void GameInfoUI::onExit()
{
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_GOLD_CHANGE);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_HEART_CHANGE);


    
}

void GameInfoUI::onhideEndPopup()
{
    
}
void GameInfoUI::onGoldChange(cocos2d::EventCustom* sender)
{
    if(goldTv)
        goldTv->setString(localStorageGetItem(USER_GOLD_NUM));
}
void GameInfoUI::onHeartChange(cocos2d::EventCustom* sender)
{
    if (heartTv)
        heartTv->setString(localStorageGetItem(USER_HEART_NUM));
}





