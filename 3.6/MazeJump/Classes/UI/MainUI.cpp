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
#include "StartUI.h"
#include "storage/local-storage/LocalStorage.h"
USING_NS_CC;

MainUI* MainUI::create()
{
    MainUI *pRet = new(std::nothrow) MainUI();
    if (pRet )
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
void MainUI::onEnter()
{
    BaseUI::onEnter();
    init();
}
void MainUI::onExit()
{
    BaseUI::onExit();
}
bool MainUI::init()
{

    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.height /960.0f;
    
    
    ui::ImageView* bgView = ui::ImageView::create("ui_bg.png");
    bgView->setPosition(Vec2(size.width*0.5, size.height*0.5));
    bgView->setScale(scale);
    m_uiLayer->addChild(bgView);
    
    ui::ImageView* titleView = ui::ImageView::create("ui_title.png");
    titleView->setPosition(Vec2(size.width*0.5, size.height*0.8));
    titleView->setScale(scale);
    m_uiLayer->addChild(titleView);
    
    
    ui::Button* playBtn = ui::Button::create("btn_play_normal.png","btn_play_press.png");
    playBtn->setScale(scale);
    playBtn->setPosition(Vec2(size.width*0.5,size.height*0.5));
    m_uiLayer->addChild(playBtn);

    
    ui::Button* soundBtn = ui::Button::create("btn_sound_normal.png","btn_sound_press.png");
    soundBtn->setScale(scale);
    soundBtn->setPosition(Vec2(size.width*0.3, size.height*0.2));
    m_uiLayer->addChild(soundBtn);
    
    ui::Button* rankBtn = ui::Button::create("btn_rank_normal.png","btn_rank_press.png");
    rankBtn->setScale(scale);
    rankBtn->setPosition(Vec2(size.width*0.3+soundBtn->getContentSize().width*scale+30*scale, size.height*0.2));
    m_uiLayer->addChild(rankBtn);
    
    ui::Button* shopBtn = ui::Button::create("btn_shop_normal.png","btn_shop_press.png");
    shopBtn->setScale(scale);
    shopBtn->setPosition(Vec2(rankBtn->getPositionX()+rankBtn->getContentSize().width*scale+30*scale, size.height*0.2));
    m_uiLayer->addChild(shopBtn);

    
    
    playBtn->addClickEventListener(CC_CALLBACK_1(MainUI::onPlayGame, this));
    soundBtn->addClickEventListener(CC_CALLBACK_1(MainUI::onSound, this));
    rankBtn->addClickEventListener(CC_CALLBACK_1(MainUI::onRank, this));
    shopBtn->addClickEventListener(CC_CALLBACK_1(MainUI::onShop, this));
    
    startui = StartUI::create(this);
    startui->setPosition(Vec2(0, size.height));
    m_dialogLayer->addChild(startui);
    m_dialogLayer->setVisible(false);
    return true;
}
void MainUI::onPlayGame(cocos2d::Ref *ref)
{

    m_maskLayer->setVisible(true);
    m_isShowDialog = true;
    m_dialogLayer->setVisible(true);
    cocos2d::MoveTo* moveTo = cocos2d::MoveTo::create(0.2,Vec2::ZERO);
    cocos2d::JumpBy* jumpBy =cocos2d::JumpBy::create(0.2,Point::ZERO, 50, 1);
    startui->runAction(Sequence::createWithTwoActions(moveTo, jumpBy));

}

void MainUI::onShop(cocos2d::Ref *ref)
{
    CCLOG("Shop");
    auto scene = ShopScene::createScene();
    Director::getInstance()->pushScene(scene);
}
void MainUI::onRank(cocos2d::Ref *ref)
{
    CCLOG("rank");
}
void MainUI::onSound(cocos2d::Ref *ref)
{
    CCLOG("onsound");
}