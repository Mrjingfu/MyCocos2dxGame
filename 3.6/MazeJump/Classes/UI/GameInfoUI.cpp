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
    m_popUpUiId = BasePopUpUI::POPUP_UNKOWN;
    isNowHidePopup = false;
}
GameInfoUI::~GameInfoUI()
{
}

bool GameInfoUI::init()
{

    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.height /960.0f;
    
    ui::ImageView* glodView = ui::ImageView::create("ui_gold_bar.png");
    glodView->setPosition(Vec2(size.width*0.15, size.height*0.95));
    glodView->setScale(scale);
    addChild(glodView);
    
     goldTv = ui::Text::create(StringUtils::format("%d",Value(localStorageGetItem(USER_GOLD_NUM)).asInt()), FONT_FXZS, 35);
    goldTv->setPosition(Vec2(glodView->getContentSize().width/2*scale+10*scale,glodView->getContentSize().height/2*scale +8*scale));
    goldTv->setScale(scale);
    glodView->addChild(goldTv);
    
    ui::ImageView* heartView = ui::ImageView::create("ui_heart_bar.png");
    heartView->setPosition(Vec2(size.width*0.13, size.height*0.95-glodView->getContentSize().height*scale - 5*scale));
    heartView->setScale(scale);
    addChild(heartView);
    
     heartTv = ui::Text::create(StringUtils::format("%d",Value(localStorageGetItem(USER_HEART_NUM)).asInt()), FONT_FXZS, 35);
    heartTv->setPosition(Vec2(heartView->getContentSize().width/2*scale+15*scale, heartView->getContentSize().height/2*scale+8*scale));
    heartTv->setScale(scale);
    heartView->addChild(heartTv);
    
    
//    ui::ImageView* disImg = ui::ImageView::create("ui_distance.png");
//    disImg->setPosition(Vec2(size.width*0.53, size.height*0.92));
//    disImg->setScale(scale);
//    addChild(disImg);
//
//    gameScoreTv = ui::Text::create(UtilityHelper::getLocalString("GAME_DISTANCE"), FONT_FXZS, 35);
//    gameScoreTv->setPosition(Vec2(size.width*0.53, size.height*0.96));
//    gameScoreTv->setScale(scale);
//    addChild(gameScoreTv);
    
    pauseImg = ui::Button::create("btn_pause_normal.png","btn_pause_press.png");
    pauseImg->setPosition(Vec2(size.width*0.9, size.height*0.93));
    pauseImg->setScale(scale);
    addChild(pauseImg);
    
    pauseImg->addClickEventListener(CC_CALLBACK_1(GameInfoUI::onPause, this));

    return true;
}
void GameInfoUI::setPopUpId(BasePopUpUI::PopUp_UI popUpId)
{
    m_popUpUiId = popUpId;
    if (m_popUpUiId!=BasePopUpUI::POPUP_UNKOWN) {
        pauseImg->loadTextureNormal("btn_back_normal.png");
        pauseImg->loadTexturePressed("btn_back_press.png");
    }else{
        pauseImg->loadTextureNormal("btn_pause_normal.png");
        pauseImg->loadTexturePressed("btn_pause_press.png");
    }
    
}

void GameInfoUI::onPause(cocos2d::Ref *ref)
{
    if (isNowHidePopup)
        return;
        CCLOG("on pause");
    if (m_popUpUiId!=BasePopUpUI::POPUP_UNKOWN) {
        UIManager::getInstance()->hidePopUp(CC_CALLBACK_0(GameInfoUI::onhidePopup, this));
        isNowHidePopup = true;
    }else{
        UIManager::getInstance()->addPopUp(BasePopUpUI::POPUP_SHOP);
        UIManager::getInstance()->showPopUp(BasePopUpUI::POPUP_HORIZONTAL);
    }
}
void GameInfoUI::onhidePopup()
{
    isNowHidePopup = false;
    if (UIManager::getInstance()->getGameId() == UIManager::UI_MAIN) {
        this->setVisible(false);
    }
}
void GameInfoUI::onAddGold()
{
    goldTv->setString(localStorageGetItem(USER_GOLD_NUM));
}
void GameInfoUI::onAddHeart()
{
    heartTv->setString(localStorageGetItem(USER_HEART_NUM));
}
void GameInfoUI::onAddScore()
{
    
}
void GameInfoUI::onRunLost()
{
    CCLOG("GAME OVER");
}
void GameInfoUI::onGrounLost()
{
    
}
void GameInfoUI::onGroundWin()
{
    
}
void GameInfoUI::onGroundRecordEnd()
{
    
}