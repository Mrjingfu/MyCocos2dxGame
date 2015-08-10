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
    if (pRet&& pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

StarPopUpUI::StarPopUpUI()
{
   
}
StarPopUpUI::~StarPopUpUI()
{
}

bool StarPopUpUI::init()
{
    
    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.height /960.0f;
    ui::ImageView* bgView = ui::ImageView::create("ui_start_bg.png");
    bgView->setPosition(Vec2(size.width*0.5,size.height*0.5));
    bgView->setScale(scale);
    addChild(bgView);
    
    ui::Text* titleView = ui::Text::create(UtilityHelper::getLocalString("START_GAME"), FONT_FXZS, 35);
    titleView->setPosition(Vec2(size.width*0.5, size.height*0.5+bgView->getContentSize().height*0.5*scale -40*scale));
    titleView->setScale(scale);
    addChild(titleView);
    
    ui::ImageView* goldView = ui::ImageView::create("ui_gold.png");
    goldView->setPosition(Vec2(size.width*0.6, size.height*0.55));
    goldView->setScale(scale);
   addChild(goldView);

     goldTv = ui::Text::create(StringUtils::format("%d",Value(localStorageGetItem(USER_GOLD_NUM)).asInt()), FONT_FXZS, 30);
    goldTv->setPosition(Vec2(size.width*0.6+goldView->getContentSize().width*scale+20*scale, size.height*0.55));
    goldTv->setScale(scale);
    addChild(goldTv);

    ui::ImageView* heartView = ui::ImageView::create("ui_heart.png");
    heartView->setPosition(Vec2(size.width*0.33, size.height*0.55));
    heartView->setScale(scale);
    addChild(heartView);

     heartTv = ui::Text::create(StringUtils::format("%d",Value(localStorageGetItem(USER_HEART_NUM)).asInt()), FONT_FXZS, 40);
    heartTv->setPosition(Vec2(size.width*0.33+heartView->getContentSize().width*scale+20*scale, size.height*0.55));
    heartTv->setScale(scale);
    addChild(heartTv);
    
     lastScoreView = ui::Text::create(StringUtils::format(UtilityHelper::getLocalString("BEST_DISTANCE").c_str(),Value(localStorageGetItem(USER_MAX_LEVEL).c_str()).asInt()), FONT_FXZS, 35);
    lastScoreView->setPosition(Vec2(size.width*0.45, size.height*0.48));
    lastScoreView->setScale(scale);
    addChild(lastScoreView);
    


    ui::Button* playBtn = ui::Button::create("btn_ok_normal.png","btn_ok_press.png");
    playBtn->setPosition(Vec2(size.width*0.38, size.height*0.4));
    
    playBtn->setScale(scale);
    playBtn->setTitleText(UtilityHelper::getLocalString("RESTART_GAME"));
    playBtn->setTitleFontName(FONT_FXZS);
    playBtn->setTitleFontSize(18);
    Label* playLable = playBtn->getTitleRenderer();
    playLable->setDimensions(playBtn->getContentSize().width*0.5, playBtn->getContentSize().height*0.5);
    playBtn->addTouchEventListener([=](Ref* sender, cocos2d::ui::Widget::TouchEventType type)
                                    {
                                        if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
                                        {
                                            playLable->setScale(1);
                                        }else if(type == cocos2d::ui::Widget::TouchEventType::BEGAN)
                                        {
                                            playLable->setScale(0.95);
                                        }
                                    });
    playBtn->addClickEventListener(CC_CALLBACK_1(StarPopUpUI::onPlayGame, this));
    addChild(playBtn);

    ui::Button* resumeBtn = ui::Button::create("btn_heart5_normal.png","btn_heart5_press.png");
    resumeBtn->setPosition(Vec2(size.width*0.38+playBtn->getContentSize().width*scale+10*scale,size.height*0.4));
    resumeBtn->setScale(scale);
    resumeBtn->addClickEventListener(CC_CALLBACK_1(StarPopUpUI::onResumeGame, this));

    addChild(resumeBtn);
    
    
    
    return true;
}
void StarPopUpUI::onPlayGame(cocos2d::Ref *ref)
{
    
    UIManager::getInstance()->hidePopUp(CC_CALLBACK_0(StarPopUpUI::onHidePop, this));
}
void StarPopUpUI::onHidePop()
{
    localStorageSetItem(USER_LAST_LEVEL, Value(0).asString());
    auto scene = MainScene::createScene();
    Director::getInstance()->replaceScene(scene);
}
void StarPopUpUI::onResumeGame(cocos2d::Ref *ref)
{
    CCLOG("onResumeGame");
    this->hidePopUp();
    
    int heartNum = Value(localStorageGetItem(USER_HEART_NUM)).asInt();
    if (heartNum>=5) {
        localStorageSetItem(USER_HEART_NUM, Value(heartNum-5).asString());
        localStorageSetItem(USER_LAST_LEVEL, localStorageGetItem(USER_MAX_LEVEL));
        auto scene = MainScene::createScene();
        Director::getInstance()->replaceScene(scene);
    }else
    {
        CCLOG("Shop");
//        auto scene = ShopScene::createScene(SHOP_HEART_NOT_ENOUGH);
//        Director::getInstance()->pushScene(scene);
    }
    
}

