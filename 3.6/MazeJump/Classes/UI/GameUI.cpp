//
//  GameUI.cpp
//
//
//
//

#include "GameUI.h"
#include "UtilityHelper.h"
#include "GameConst.h"
#include "MainScene.h"
#include "storage/local-storage/LocalStorage.h"
USING_NS_CC;

GameUI* GameUI::create()
{
    GameUI *pRet = new(std::nothrow) GameUI();
    if (pRet )
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

GameUI::GameUI()
{
    m_message= GU_UNKNOWN;
}
GameUI::~GameUI()
{
}
void GameUI::onEnter()
{
    BaseUI::onEnter();
    init();
}
void GameUI::onExit()
{
    BaseUI::onExit();
}
bool GameUI::init()
{

    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.height /960.0f;
    
    ui::ImageView* glodView = ui::ImageView::create("ui_gold.png");
    glodView->setPosition(Vec2(size.width*0.1, size.height*0.92));
    glodView->setScale(scale);
    m_uiLayer->addChild(glodView);
    
     goldTv = ui::Text::create(StringUtils::format("%d",Value(localStorageGetItem(USER_GOLD_NUM)).asInt()), FONT_FXZS, 35);
    goldTv->setPosition(Vec2(size.width*0.1+glodView->getContentSize().width*scale+8*scale, size.height*0.92));
    goldTv->setScale(scale);
    m_uiLayer->addChild(goldTv);
    
    ui::ImageView* heartView = ui::ImageView::create("ui_heart.png");
    heartView->setPosition(Vec2(size.width*0.8, size.height*0.92));
    heartView->setScale(scale);
    m_uiLayer->addChild(heartView);
    
     heartTv = ui::Text::create(StringUtils::format("%d",Value(localStorageGetItem(USER_HEART_NUM)).asInt()), FONT_FXZS, 35);
    heartTv->setPosition(Vec2(size.width*0.8+heartView->getContentSize().width*scale+8*scale, size.height*0.92));
    heartTv->setScale(scale);
    m_uiLayer->addChild(heartTv);
    
    
     gameScoreTv = ui::Text::create(StringUtils::format(UtilityHelper::getLocalString("GAME_SCORE").c_str(),Value(localStorageGetItem(USER_LAST_LEVEL)).asInt()), FONT_FXZS, 35);
    gameScoreTv->setPosition(Vec2(size.width*0.5, size.height*0.92));
    gameScoreTv->setScale(scale);
    m_uiLayer->addChild(gameScoreTv);

    return true;
}
void GameUI::setGameMessage( UIMessage state)
{

    m_message = state;
    switch (m_message) {
        case GU_ADD_GOLD:
            onAddGold();
            break;
        case GU_ADD_HEART:
            onAddHeart();
            break;
        case GU_ADD_SCORE:
            onAddScore();
            break;
        case GU_RUN_LOSE:
            onRunLost();
            break;
        case  GU_GROUND_LOST:
            onGrounLost();
            break;
        case GU_GROUND_WIN:
            onGroundWin();
            break;
        case GU_GROUND_RECORD_END:
            break;
        default:
            break;
    }
    m_message = GU_UNKNOWN;
}
void GameUI::onAddGold()
{
    goldTv->setString(localStorageGetItem(USER_GOLD_NUM));
}
void GameUI::onAddHeart()
{
    heartTv->setString(localStorageGetItem(USER_HEART_NUM));
}
void GameUI::onAddScore()
{
    gameScoreTv->setString(StringUtils::format(UtilityHelper::getLocalString("GAME_SCORE").c_str(),Value(localStorageGetItem(USER_LAST_LEVEL)).asInt()));
}
void GameUI::onRunLost()
{
    CCLOG("GAME OVER");
}
void GameUI::onGrounLost()
{
    
}
void GameUI::onGroundWin()
{
    
}
void GameUI::onGroundRecordEnd()
{
    
}