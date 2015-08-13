//
//  ShopUI.cpp
//
//
//
//

#include "ShopPopUpUI.h"
#include "UtilityHelper.h"
#include "GameConst.h"
#include "MainScene.h"
#include "UIManager.h"
#include "storage/local-storage/LocalStorage.h"
USING_NS_CC;

ShopPopUpUI* ShopPopUpUI::create()
{
    ShopPopUpUI *pRet = new(std::nothrow) ShopPopUpUI();
    if (pRet)
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

ShopPopUpUI::ShopPopUpUI()
{
    m_shopType = SHOP_NORMAL;
}
ShopPopUpUI::~ShopPopUpUI()
{
}
void ShopPopUpUI::onEnter()
{
    BasePopUpUI::onEnter();
    init();
}
void ShopPopUpUI::onExit()
{
    BasePopUpUI::onExit();
    
}
bool ShopPopUpUI::init()
{

    auto size = Director::getInstance()->getVisibleSize();
   float scale = size.width /640.0f;
    
   
    
    ui::ImageView* bgView = ui::ImageView::create("ui_shop_bg.png");
    bgView->setPosition(Vec2(size.width*0.5, size.height*0.4));
    bgView->setScale(scale);
    m_dialogLayer->addChild(bgView);
    
    productLayer = Layer::create();
    m_dialogLayer->addChild(productLayer);
    
    goldProductLayer = Layer::create();
    m_dialogLayer->addChild(goldProductLayer);
    
   
    
    ui::ImageView* shopTv = ui::ImageView::create("ui_shop_icon.png");
    shopTv->setPosition(Vec2(size.width*0.4, size.height*0.7));
    shopTv->setScale(scale);
    m_dialogLayer->addChild(shopTv);

    ui::Button* goldBuyBtn = ui::Button::create("btn_glodmore_normal.png","btn_glodmore_press.png");
    goldBuyBtn->setPosition(Vec2(size.width*0.4, size.height*0.48));
    goldBuyBtn->setScale(scale);
    productLayer->addChild(goldBuyBtn);
    
    ui::Button* heartBuyBtn = ui::Button::create("btn_heartbuy_normal.png","btn_heartbuy_press.png");
    heartBuyBtn->setPosition(Vec2(size.width*0.4+goldBuyBtn->getContentSize().width*scale+50*scale, size.height*0.48));
    heartBuyBtn->setScale(scale);
    productLayer->addChild(heartBuyBtn);

    ui::Button* adsBuyBtn = ui::Button::create("btn_removeadd_noraml.png","btn_removeadd_press.png");
    adsBuyBtn->setPosition(Vec2(size.width*0.4, size.height*0.44-goldBuyBtn->getContentSize().height*scale ));
    adsBuyBtn->setScale(scale);
    productLayer->addChild(adsBuyBtn);
    
    ui::Button* restoreBtn = ui::Button::create("btn_restore_normal.png","btn_restore_press.png");
    restoreBtn->setPosition(Vec2(size.width*0.4+adsBuyBtn->getContentSize().width*scale+50*scale, size.height*0.44-goldBuyBtn->getContentSize().height*scale));
    restoreBtn->setScale(scale);
    productLayer->addChild(restoreBtn);
    
    

    ui::Button* coin1_Btn = ui::Button::create("btn_coins01_normal.png","btn_coins01_press.png");
    coin1_Btn->setPosition(Vec2(size.width*0.4, size.height*0.52));
    coin1_Btn->setScale(scale);
    goldProductLayer->addChild(coin1_Btn);
    
    
    ui::Button* coin2_Btn = ui::Button::create("btn_coins02_normal.png","btn_coins02_press.png");
    coin2_Btn->setPosition(Vec2(size.width*0.4+coin1_Btn->getContentSize().width*scale+50*scale, size.height*0.52));
    coin2_Btn->setScale(scale);
    goldProductLayer->addChild(coin2_Btn);
    
    ui::Button* coin3_Btn = ui::Button::create("btn_coins03_normal.png","btn_coins03_press.png");
    coin3_Btn->setPosition(Vec2(size.width*0.4, size.height*0.52-coin2_Btn->getContentSize().width*scale - 20*scale));
    coin3_Btn->setScale(scale);
    goldProductLayer->addChild(coin3_Btn);
    
    ui::Button* coin4_Btn = ui::Button::create("btn_coins04_normal.png","btn_coins04_press.png");
    coin4_Btn->setPosition(Vec2(size.width*0.4+coin1_Btn->getContentSize().width*scale+50*scale, size.height*0.52-coin2_Btn->getContentSize().width*scale - 20*scale));
    coin4_Btn->setScale(scale);
    goldProductLayer->addChild(coin4_Btn);
    
    ui::Button* coin5_Btn = ui::Button::create("btn_coins05_normal.png","btn_coins05_press.png");
    coin5_Btn->setPosition(Vec2(size.width*0.4, size.height*0.52-coin2_Btn->getContentSize().width*2*scale - 40*scale));
    coin5_Btn->setScale(scale);
    goldProductLayer->addChild(coin5_Btn);
    
    ui::Button* backBtn = ui::Button::create("btn_shopback_normal.png","btn_shopback_press.png");
    backBtn->setPosition(Vec2(size.width*0.4+coin1_Btn->getContentSize().width*scale+50*scale, size.height*0.52-coin2_Btn->getContentSize().width*2*scale - 40*scale));
    backBtn->setScale(scale);
    goldProductLayer->addChild(backBtn);

    
    goldBuyBtn->addClickEventListener(CC_CALLBACK_1(ShopPopUpUI::onBuyGold, this));
    heartBuyBtn->addClickEventListener(CC_CALLBACK_1(ShopPopUpUI::onBuyHeart, this));
    adsBuyBtn->addClickEventListener(CC_CALLBACK_1(ShopPopUpUI::onBuyRemoveAds, this));
    restoreBtn->addClickEventListener(CC_CALLBACK_1(ShopPopUpUI::onRestore, this));
    
    coin1_Btn->addClickEventListener(CC_CALLBACK_1(ShopPopUpUI::onBuyCoin1, this));
    coin2_Btn->addClickEventListener(CC_CALLBACK_1(ShopPopUpUI::onBuyCoin2, this));
    coin3_Btn->addClickEventListener(CC_CALLBACK_1(ShopPopUpUI::onBuyCoin3, this));
    coin4_Btn->addClickEventListener(CC_CALLBACK_1(ShopPopUpUI::onBuyCoin4, this));
    coin5_Btn->addClickEventListener(CC_CALLBACK_1(ShopPopUpUI::onBuyCoin5, this));
    
    backBtn->addClickEventListener(CC_CALLBACK_1(ShopPopUpUI::onBackShop, this));
    
    setShopDisplay(m_shopType);
    
    
    return true;
}
void ShopPopUpUI::setShopDisplay(ShopType type)
{
    m_shopType = type;
    if (m_shopType == ShopType::SHOP_GOLD) {
        productLayer->setVisible(false);
        goldProductLayer->setVisible(true);
    }else if (m_shopType == SHOP_NORMAL)
    {
        productLayer->setVisible(true);
        goldProductLayer->setVisible(false);
    }
}
void ShopPopUpUI::onBuyGold(cocos2d::Ref *ref)
{
    productLayer->setVisible(false);
    goldProductLayer->setVisible(true);
}
void ShopPopUpUI::onBuyHeart(cocos2d::Ref *ref)
{

    CCLOG("onBuyHeart");
    int goldNum = Value(localStorageGetItem(USER_GOLD_NUM)).asInt();
    if (goldNum>=150) {
        localStorageSetItem(USER_GOLD_NUM, Value(goldNum-150).asString());
        localStorageSetItem(USER_HEART_NUM, Value(Value(localStorageGetItem(USER_HEART_NUM)).asInt()+15).asString());
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_START_HEART_CHANGE);
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_START_GOLD_CHANGE);
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_HEART_CHANGE);
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_GOLD_CHANGE);
    }else
    {
        CCLOG("Shop");
        UIManager::getInstance()->addPopUp(BasePopUpUI::POPUP_GLOD_NOT_ENOUGT);
        UIManager::getInstance()->showPopUp(false);
        
    }
}

void ShopPopUpUI::onBuyRemoveAds(cocos2d::Ref *ref)
{
    CCLOG("onBuyRemoveAds");
}

void ShopPopUpUI::onRestore(cocos2d::Ref *ref)
{
    CCLOG("onRestore");
}
void ShopPopUpUI::onBuyCoin1(cocos2d::Ref *ref)
{
    CCLOG("onBuyCoin1");
    onProduct("buyCoin1");
}
void ShopPopUpUI::onBuyCoin2(cocos2d::Ref *ref)
{
    CCLOG("onBuyCoin2");
    onProduct("buyCoin2");
}
void ShopPopUpUI::onBuyCoin3(cocos2d::Ref *ref)
{
    CCLOG("onBuyCoin3");
    onProduct("buyCoin3");
}
void ShopPopUpUI::onBuyCoin4(cocos2d::Ref *ref)
{
    CCLOG("onBuyCoin4");
    onProduct("buyCoin4");
}
void ShopPopUpUI::onBuyCoin5(cocos2d::Ref *ref)
{
    CCLOG("onBuyCoin5");
    onProduct("buyCoin5");
    
}
void ShopPopUpUI::onBackShop(cocos2d::Ref *ref)
{
    productLayer->setVisible(true);
    goldProductLayer->setVisible(false);
}
void ShopPopUpUI::onProduct(const std::string &productId)
{
    int num = 0;
    CCLOG("product:%s",productId.c_str());
    if (!strcmp(productId.c_str(), "buyCoin1"))
    {
        num = 200;
    }
    else if (!strcmp(productId.c_str(), "buyCoin2"))
    {
        num = 500;
    }
    else if (!strcmp(productId.c_str(), "buyCoin3"))
    {
        num = 1000;
    }
    else if (!strcmp(productId.c_str(), "buyCoin4"))
    {
        num = 2500;
    }
    else if (!strcmp(productId.c_str(), "buyCoin5"))
    {
        num = 10000;
    }
    localStorageSetItem(USER_GOLD_NUM, Value(Value(localStorageGetItem(USER_GOLD_NUM)).asInt()+num).asString());
    
}

