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
    isNowHidePopup = false;
}
GameInfoUI::~GameInfoUI()
{
}

bool GameInfoUI::init()
{

    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.width /640.0f;
    
    disLayer = cocos2d::Layer::create();
    addChild(disLayer);
    
    ui::ImageView* glodView = ui::ImageView::create("ui_gold_bar.png");
    glodView->setPosition(Vec2(size.width*0.15, size.height*0.95));
    glodView->setScale(scale);
    addChild(glodView);
    
    goldTv = ui::Text::create(StringUtils::format("%d",Value(localStorageGetItem(USER_GOLD_NUM)).asInt()), FONT_FXZS, 25);
    goldTv->setPosition(Vec2(size.width*0.15+25*scale,size.height*0.95 ));
    goldTv->setScale(scale);
    addChild(goldTv);
    
    ui::ImageView* heartView = ui::ImageView::create("ui_heart_bar.png");
    heartView->setPosition(Vec2(size.width*0.13, size.height*0.95-glodView->getContentSize().height*scale - 5*scale));
    heartView->setScale(scale);
    addChild(heartView);
    
    heartTv = ui::Text::create(StringUtils::format("%d",Value(localStorageGetItem(USER_HEART_NUM)).asInt()), FONT_FXZS, 25);
    heartTv->setPosition(Vec2(size.width*0.13+22*scale, size.height*0.95-glodView->getContentSize().height*scale - 5*scale));
    heartTv->setScale(scale);
    addChild(heartTv);
    
    
    ui::ImageView* disImg = ui::ImageView::create("ui_distance.png");
    disImg->setPosition(Vec2(size.width*0.53, size.height*0.95));
    disImg->setScale(scale);
    disLayer->addChild(disImg);

    gameScoreTv = ui::Text::create(StringUtils::format(UtilityHelper::getLocalString("GAME_DISTANCE").c_str(),Value(localStorageGetItem(USER_LAST_LEVEL)).asInt()), FONT_FXZS, 25);
    gameScoreTv->setPosition(Vec2(size.width*0.48, size.height*0.95));
    gameScoreTv->setScale(scale);
    disLayer->addChild(gameScoreTv);
    
    pauseImg = ui::Button::create("btn_pause_normal.png","btn_pause_press.png");
    pauseImg->setPosition(Vec2(size.width*0.9, size.height*0.93));
    pauseImg->setScale(scale);
    disLayer->addChild(pauseImg);
    
    pauseImg->addClickEventListener(CC_CALLBACK_1(GameInfoUI::onPause, this));



    return true;
}
void GameInfoUI::setPopUpId(BasePopUpUI::PopUp_UI popUpId)
{
     m_popUpIds.push_back(popUpId);
}
void GameInfoUI::removePopUpId()
{
    auto it = std::next( m_popUpIds.begin(), m_popUpIds.size()-1 );
    m_popUpIds.erase(it);
}
 void GameInfoUI::onEnter()
{
    Layer::onEnter();
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_GOLD_CHANGE, std::bind(&GameInfoUI::onGoldChange, this, std::placeholders::_1));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_HEART_CHANGE, std::bind(&GameInfoUI::onHeartChange, this, std::placeholders::_1));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_MAX_DISTANCE_CHANGE, std::bind(&GameInfoUI::onMaxDistanceChange, this, std::placeholders::_1));

}
 void GameInfoUI::onExit()
{
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_GOLD_CHANGE);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_HEART_CHANGE);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_MAX_DISTANCE_CHANGE);

    
}
void GameInfoUI::onPause(cocos2d::Ref *ref)
{

    if (isNowHidePopup)
        return;
    
    
    if ( m_popUpIds.size()>0) {
        
        if (UIManager::getInstance()->getGameId() == UIManager::UI_GAME && m_popUpIds.size() ==1)
        {
            Director::getInstance()->resume();
        }
        isNowHidePopup = true;
        UIManager::getInstance()->hidePopUp(CC_CALLBACK_0(GameInfoUI::onhideEndPopup, this));
        UIManager::getInstance()->setCancel(true);
    }else{
        UIManager::getInstance()->addPopUp(BasePopUpUI::POPUP_SHOP);
        UIManager::getInstance()->showPopUp(true,BasePopUpUI::POPUP_HORIZONTAL,CC_CALLBACK_0(GameInfoUI::onshowStartEnd, this));
    }
    
    if (m_popUpIds.size() > 0) {
        pauseImg->loadTextureNormal("btn_back_normal.png");
        pauseImg->loadTexturePressed("btn_back_press.png");
    }
    
    
}
void GameInfoUI::onshowStartEnd()
{
    if (UIManager::getInstance()->getGameId() == UIManager::UI_GAME && m_popUpIds.size()>0) {
        Director::getInstance()->pause();
    }
}

void GameInfoUI::onhideEndPopup()
{
    isNowHidePopup = false;
    BasePopUpUI::PopUp_UI lpopUpId = m_popUpIds.back();
    if (UIManager::getInstance()->getGameId() == UIManager::UI_MAIN && lpopUpId==BasePopUpUI::POPUP_SHOP) {
        this->setVisible(false);
    }else{
        removePopUpId();
    }
    if (m_popUpIds.size() == 0) {
        
        pauseImg->loadTextureNormal("btn_pause_normal.png");
        pauseImg->loadTexturePressed("btn_pause_press.png");
    }
    
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
void GameInfoUI::onMaxDistanceChange(cocos2d::EventCustom* sender)
{
    if (gameScoreTv)
        gameScoreTv->setString(StringUtils::format(UtilityHelper::getLocalString("GAME_DISTANCE").c_str(),Value(localStorageGetItem(USER_LAST_LEVEL)).asInt()));
}




