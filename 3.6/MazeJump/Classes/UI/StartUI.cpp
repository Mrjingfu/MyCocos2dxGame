//
//  StartUI.cpp
//
//
//
//

#include "StartUI.h"
#include "UtilityHelper.h"
#include "GameConst.h"
#include "MainScene.h"
#include "ShopScene.h"
#include "storage/local-storage/LocalStorage.h"
USING_NS_CC;

StartUI* StartUI::create(BaseUI* baseUi)
{
    StartUI *pRet = new(std::nothrow) StartUI();
    if (pRet&& pRet->init(baseUi))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

StartUI::StartUI()
{
    m_baseUi = nullptr;
}
StartUI::~StartUI()
{
}

bool StartUI::init(BaseUI* baseUi)
{
    m_baseUi = baseUi;
    
    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.height /960.0f;
    ui::ImageView* bgView = ui::ImageView::create("ui_start_bg.png");
    bgView->setPosition(Vec2(size.width*0.5,size.height*0.5));
    bgView->setScale(scale);
    addChild(bgView);
    
    ui::Text* titleView = ui::Text::create(UtilityHelper::getLocalString("START_GAME"), FONT_FXZS, 50);
    titleView->setPosition(Vec2(size.width*0.5, size.height*0.5+bgView->getContentSize().height*0.5*scale -50*scale));
    titleView->setScale(scale);
    addChild(titleView);
    
    ui::ImageView* goldView = ui::ImageView::create("ui_gold.png");
    goldView->setPosition(Vec2(size.width*0.6, size.height*0.58));
    goldView->setScale(scale);
    addChild(goldView);

     goldTv = ui::Text::create(StringUtils::format("%d",Value(localStorageGetItem(USER_GOLD_NUM)).asInt()), FONT_FXZS, 40);
    goldTv->setPosition(Vec2(size.width*0.6+goldView->getContentSize().width*scale+20*scale, size.height*0.58));
    goldTv->setScale(scale);
    addChild(goldTv);

    ui::ImageView* heartView = ui::ImageView::create("ui_heart.png");
    heartView->setPosition(Vec2(size.width*0.25, size.height*0.58));
    heartView->setScale(scale);
    addChild(heartView);

     heartTv = ui::Text::create(StringUtils::format("%d",Value(localStorageGetItem(USER_HEART_NUM)).asInt()), FONT_FXZS, 40);
    heartTv->setPosition(Vec2(size.width*0.25+heartView->getContentSize().width*scale+20*scale, size.height*0.58));
    heartTv->setScale(scale);
    addChild(heartTv);
    
     lastScoreView = ui::Text::create(StringUtils::format(UtilityHelper::getLocalString("LAST_SCORE").c_str(),Value(localStorageGetItem(USER_LAST_LEVEL).c_str()).asInt()), FONT_FXZS, 40);
    lastScoreView->setPosition(Vec2(size.width*0.42, size.height*0.51));
    lastScoreView->setScale(scale);
    addChild(lastScoreView);
    
     bestscoreView = ui::Text::create(StringUtils::format(UtilityHelper::getLocalString("BEST_SCORE").c_str(),Value(localStorageGetItem(USER_MAX_LEVEL).c_str()).asInt()), FONT_FXZS, 40);
    bestscoreView->setPosition(Vec2(size.width*0.42, size.height*0.51-lastScoreView->getContentSize().height*scale-30*scale));
    bestscoreView->setScale(scale);
    addChild(bestscoreView);

    ui::Button* playBtn = ui::Button::create("btn_ok_normal.png","btn_ok_press.png");
    playBtn->setPosition(Vec2(size.width*0.35, size.height*0.35));
    
    playBtn->setScale(scale);
    playBtn->setTitleText(UtilityHelper::getLocalString("RESTART_GAME"));
    playBtn->setTitleFontName(FONT_FXZS);
    playBtn->setTitleFontSize(22);
    Label* playLable = playBtn->getTitleRenderer();
    playLable->setDimensions(playBtn->getContentSize().width*0.5, playBtn->getContentSize().height*0.5);
    playBtn->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type)
                                    {
                                        if (type == Widget::TouchEventType::ENDED)
                                        {
                                            playLable->setScale(1);
                                        }else if(type == Widget::TouchEventType::BEGAN)
                                        {
                                            playLable->setScale(0.95);
                                        }
                                    });
    playBtn->addClickEventListener(CC_CALLBACK_1(StartUI::onPlayGame, this));
    addChild(playBtn);

    ui::Button* resumeBtn = ui::Button::create("btn_ok_normal.png","btn_ok_press.png");
    resumeBtn->setPosition(Vec2(size.width*0.35+playBtn->getContentSize().width*scale+10*scale,size.height*0.35));
    resumeBtn->setScale(scale);
    resumeBtn->setTitleFontName(FONT_FXZS);
    resumeBtn->setTitleText(UtilityHelper::getLocalString("RESUME_GAME"));
    resumeBtn->setTitleFontSize(22);
    Label* resumeLable = resumeBtn->getTitleRenderer();
    resumeLable->setDimensions(resumeBtn->getContentSize().width*0.5, resumeBtn->getContentSize().height*0.5);
    resumeBtn->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type)
                                   {
                                       if (type == Widget::TouchEventType::ENDED)
                                       {
                                           resumeLable->setScale(1);
                                       }else if(type == Widget::TouchEventType::BEGAN)
                                       {
                                           resumeLable->setScale(0.95);
                                       }
                                   });
    resumeBtn->addClickEventListener(CC_CALLBACK_1(StartUI::onResumeGame, this));

    addChild(resumeBtn);
    
    
    
    return true;
}
void StartUI::onPlayGame(cocos2d::Ref *ref)
{
    localStorageSetItem(USER_LAST_LEVEL, Value(0).asString());
    m_baseUi->setShowDilog(false);
    auto scene = MainScene::createScene();
    Director::getInstance()->replaceScene(scene);
}
void StartUI::onResumeGame(cocos2d::Ref *ref)
{
    CCLOG("onResumeGame");
    
    int heartNum = Value(localStorageGetItem(USER_HEART_NUM)).asInt();
    if (heartNum>0) {
        localStorageSetItem(USER_HEART_NUM, Value(heartNum-1).asString());
        m_baseUi->setShowDilog(false);
        auto scene = MainScene::createScene();
        Director::getInstance()->replaceScene(scene);
    }else
    {
        CCLOG("Shop");
        auto scene = ShopScene::createScene(SHOP_HEART_NOT_ENOUGH);
        Director::getInstance()->pushScene(scene);
    }
    
}
void StartUI::onEnter()
{
    Layout::onEnter();
    if (heartTv) {
        heartTv->setString(StringUtils::format("%d",Value(localStorageGetItem(USER_HEART_NUM)).asInt()));
    }
    if (goldTv) {
        goldTv->setString(StringUtils::format("%d",Value(localStorageGetItem(USER_GOLD_NUM)).asInt()));
    }
    if (lastScoreView) {
        lastScoreView->setString(StringUtils::format(UtilityHelper::getLocalString("LAST_SCORE").c_str(),Value(localStorageGetItem(USER_LAST_LEVEL).c_str()).asInt()));
    }
    if (bestscoreView) {
        bestscoreView->setString(StringUtils::format(UtilityHelper::getLocalString("BEST_SCORE").c_str(),Value(localStorageGetItem(USER_MAX_LEVEL).c_str()).asInt()));
    }
}
void StartUI::onExit()
{
     Layout::onExit();
}
