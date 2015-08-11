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
#include "StarPopUpUI.h"
#include "UIManager.h"
#include "UtilityHelper.h"
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
    m_sound = true;

}
MainUI::~MainUI()
{
}

bool MainUI::init()
{

    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.width /640.0f;
    
    ui::ImageView* titleView = ui::ImageView::create(UtilityHelper::getLocalString("UI_TITLE_TEX"));
    titleView->setPosition(Vec2(size.width*0.5, size.height*0.77));
    titleView->setScale(scale);
    addChild(titleView);
    
    
    soundBtn = ui::Button::create("btn_sounds_on.png");
    soundBtn->setScale(scale);
    soundBtn->setPosition(Vec2(size.width*0.9, size.height*0.93));
    addChild(soundBtn);
    
    ui::Button* shopBtn = ui::Button::create("btn_shop_normal.png","btn_shop_press.png");
    shopBtn->setScale(scale);
    shopBtn->setPosition(Vec2(size.width*0.9,size.height*0.27));
    addChild(shopBtn);
    
    ui::Button* rankBtn = ui::Button::create("btn_rank_normal.png","btn_rank_press.png");
    rankBtn->setScale(scale);
    rankBtn->setPosition(Vec2(size.width*0.9,size.height*0.27-shopBtn->getContentSize().height*scale-20*scale));
    addChild(rankBtn);
    
    ui::Button* commonBtn = ui::Button::create("btn_comment_normal.png","btn_comment_press.png");
    commonBtn->setScale(scale);
    commonBtn->setPosition(Vec2(size.width*0.9,size.height*0.27-rankBtn->getContentSize().height*scale*2-40*scale));
    addChild(commonBtn);

    soundBtn->addClickEventListener(CC_CALLBACK_1(MainUI::onSound, this));
    rankBtn->addClickEventListener(CC_CALLBACK_1(MainUI::onRank, this));
    shopBtn->addClickEventListener(CC_CALLBACK_1(MainUI::onShop, this));
    

    return true;
}


void MainUI::onShop(cocos2d::Ref *ref)
{
    CCLOG("Shop");
    UIManager::getInstance()->addPopUp(BasePopUpUI::POPUP_SHOP);
    UIManager::getInstance()->showPopUp(true,BasePopUpUI::POPUP_HORIZONTAL);
    UIManager::getInstance()->showInfo(true);
}
void MainUI::onRank(cocos2d::Ref *ref)
{
    CCLOG("rank");
}
void MainUI::onSound(cocos2d::Ref *ref)
{
    if(m_sound)
    {
        soundBtn->loadTextureNormal("btn_sounds_off.png");
        m_sound = false;
    }else
    {
        soundBtn->loadTextureNormal("btn_sounds_on.png");
        m_sound = true;
    }
}