//
//  MainUI.cpp
//
//
//
//

#include "MainUI.h"
#include "UtilityHelper.h"
#include "GameConst.h"
#include "MainScene.h"
#include "ShopScene.h"
#include "storage/local-storage/LocalStorage.h"
USING_NS_CC;

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
}
MainUI::~MainUI()
{
}
bool MainUI::init()
{

    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.height /960.0f;
    
    ui::ImageView* bgView = ui::ImageView::create("bg.png");
    bgView->setPosition(Vec2(size.width*0.5, size.height*0.5));
    bgView->setScale(scale);
    addChild(bgView);
    
    ui::ImageView* titleView = ui::ImageView::create("title.png");
    titleView->setPosition(Vec2(size.width*0.5, size.height*0.8));
    titleView->setScale(scale);
    addChild(titleView);
    
    ui::Text* scoreView = ui::Text::create(StringUtils::format(UtilityHelper::getLocalString(LOCAL_BEST_SCORE.c_str()).c_str(),Value(localStorageGetItem(USER_MAX_LEVEL).c_str()).asInt()), FONT_FXZS, 50);
    scoreView->setPosition(Vec2(size.width*0.5, size.height*0.6));
    scoreView->setScale(scale);
    addChild(scoreView);
    
    ui::ImageView* glodView = ui::ImageView::create("uigold.png");
    glodView->setPosition(Vec2(size.width*0.35, size.height*0.5));
    glodView->setScale(scale);
    addChild(glodView);
    
    ui::Text* goldTv = ui::Text::create(StringUtils::format("%d",Value(localStorageGetItem(USER_GOLD_NUM)).asInt()), FONT_FXZS, 40);
    goldTv->setPosition(Vec2(size.width*0.6, size.height*0.5));
    goldTv->setScale(scale);
    addChild(goldTv);
    
    ui::ImageView* heartView = ui::ImageView::create("uiheart.png");
    heartView->setPosition(Vec2(size.width*0.35, size.height*0.5- glodView->getContentSize().height*scale -10*scale));
    heartView->setScale(scale);
    addChild(heartView);
    
    ui::Text* heartTv = ui::Text::create(StringUtils::format("%d",Value(localStorageGetItem(USER_HEART_NUM)).asInt()), FONT_FXZS, 40);
    heartTv->setPosition(Vec2(size.width*0.6, size.height*0.5- glodView->getContentSize().height*scale -10*scale));
    heartTv->setScale(scale);
    addChild(heartTv);
    
    
    ui::Button* playBtn = ui::Button::create("btn_play_normal.png","btn_play_press.png");
    playBtn->setPosition(Vec2(size.width*0.32, heartView->getPositionY()-heartView->getContentSize().height*scale -30*scale));
    playBtn->setScale(scale);
    addChild(playBtn);
    
    ui::Button* resumeBtn = ui::Button::create("btn_resume_normal.png","btn_resume_press.png");
    resumeBtn->setPosition(Vec2(size.width*0.32+playBtn->getContentSize().width*scale+10*scale, heartView->getPositionY()-heartView->getContentSize().height*scale -30*scale));
    resumeBtn->setScale(scale);
    addChild(resumeBtn);
    
    ui::Button* soundBtn = ui::Button::create("btn_sound_normal.png","btn_sound_press.png");
    soundBtn->setScale(scale);
    soundBtn->setPosition(Vec2(size.width*0.3, size.height*0.2));
    addChild(soundBtn);
    
    ui::Button* rankBtn = ui::Button::create("btn_rank_normal.png","btn_rank_press.png");
    rankBtn->setScale(scale);
    rankBtn->setPosition(Vec2(size.width*0.3+soundBtn->getContentSize().width*scale+30*scale, size.height*0.2));
    addChild(rankBtn);
    
    ui::Button* shopBtn = ui::Button::create("btn_shop_normal.png","btn_shop_press.png");
    shopBtn->setScale(scale);
    shopBtn->setPosition(Vec2(rankBtn->getPositionX()+rankBtn->getContentSize().width*scale+30*scale, size.height*0.2));
    addChild(shopBtn);
    
    playBtn->addClickEventListener(CC_CALLBACK_1(MainUI::onPlayGame, this));
    resumeBtn->addClickEventListener(CC_CALLBACK_1(MainUI::onResumeGame, this));
    soundBtn->addClickEventListener(CC_CALLBACK_1(MainUI::onSound, this));
    rankBtn->addClickEventListener(CC_CALLBACK_1(MainUI::onRank, this));
    shopBtn->addClickEventListener(CC_CALLBACK_1(MainUI::onShop, this));
    
    return true;
}
void MainUI::onPlayGame(cocos2d::Ref *ref)
{
    auto scene = MainScene::createScene();
    Director::getInstance()->replaceScene(scene);
}
void MainUI::onResumeGame(cocos2d::Ref *ref)
{
    CCLOG("resumeGame");
}
void MainUI::onShop(cocos2d::Ref *ref)
{
    CCLOG("Shop");
    auto scene = ShopScene::createScene();
    Director::getInstance()->replaceScene(scene);
}
void MainUI::onRank(cocos2d::Ref *ref)
{
    CCLOG("rank");
}
void MainUI::onSound(cocos2d::Ref *ref)
{
    CCLOG("onsound");
}