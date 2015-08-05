//
//  ShopUI.cpp
//
//
//
//

#include "ShopUI.h"
#include "UtilityHelper.h"
#include "GameConst.h"
#include "MainScene.h"
#include "storage/local-storage/LocalStorage.h"
USING_NS_CC;

ShopUI* ShopUI::create(const std::string& tip)
{
    ShopUI *pRet = new(std::nothrow) ShopUI(tip);
    if (pRet )
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

ShopUI::ShopUI(const std::string& tip):m_tip(tip)
{
}
ShopUI::~ShopUI()
{
}
void ShopUI::onEnter()
{
    BaseUI::onEnter();
    init();
}
void ShopUI::onExit()
{
    BaseUI::onExit();
}
bool ShopUI::init()
{

    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.height /960.0f;
    
    auto bg = LayerColor::create(Color4B(107, 223, 255,255),size.width,size.height);
    bg->setPosition(Vec2::ZERO);
    m_uiLayer->addChild(bg);
    
    
     productLayer = Layer::create();
    m_uiLayer->addChild(productLayer);
    
     goldProductLayer = Layer::create();
    m_uiLayer->addChild(goldProductLayer);
    
    ui::Button* backBtn = ui::Button::create("btn_back_normal.png","btn_back_press.png");
    backBtn->setPosition(Vec2(size.width*0.2, size.height*0.9));
    backBtn->setScale(scale);
    m_uiLayer->addChild(backBtn);
    
    ui::ImageView* glodView = ui::ImageView::create("ui_gold.png");
    glodView->setPosition(Vec2(size.width*0.85, size.height*0.92));
    glodView->setScale(scale);
    m_uiLayer->addChild(glodView);
    
     goldTv = ui::Text::create(StringUtils::format("%d",Value(localStorageGetItem(USER_GOLD_NUM)).asInt()), FONT_FXZS, 40);
    goldTv->setPosition(Vec2(size.width*0.7, size.height*0.92));
    goldTv->setScale(scale);
    m_uiLayer->addChild(goldTv);
    
    ui::ImageView* heartView = ui::ImageView::create("ui_heart.png");
    heartView->setPosition(Vec2(size.width*0.85, size.height*0.92- glodView->getContentSize().height*scale -10*scale));
    heartView->setScale(scale);
    m_uiLayer->addChild(heartView);
    
     heartTv = ui::Text::create(StringUtils::format("%d",Value(localStorageGetItem(USER_HEART_NUM)).asInt()), FONT_FXZS, 40);
    heartTv->setPosition(Vec2(size.width*0.7, size.height*0.92- glodView->getContentSize().height*scale -10*scale));
    heartTv->setScale(scale);
    m_uiLayer->addChild(heartTv);
    
    
    ui::ImageView* shopTv = ui::ImageView::create("ui_shop_icon.png");
    shopTv->setPosition(Vec2(size.width*0.32, size.height*0.75));
    shopTv->setScale(scale);
    m_uiLayer->addChild(shopTv);
    
    tipTv = ui::Text::create(UtilityHelper::getLocalString(m_tip.c_str()), FONT_FXZS, 40);
    tipTv->setPosition(Vec2(size.width*0.34+shopTv->getContentSize().width*scale +70*scale,  size.height*0.75));
    tipTv->setScale(scale);
    addChild(tipTv);
    
    
    ui::Button* goldBuyBtn = ui::Button::create("btn_glodmore_normal.png","btn_glodmore_press.png");
    goldBuyBtn->setPosition(Vec2(size.width*0.35, size.height*0.6));
    goldBuyBtn->setScale(scale);
    productLayer->addChild(goldBuyBtn);
    
    ui::Button* heartBuyBtn = ui::Button::create("btn_heartbuy_normal.png","btn_heartbuy_press.png");
    heartBuyBtn->setPosition(Vec2(size.width*0.35+goldBuyBtn->getContentSize().width*scale+50*scale, size.height*0.6));
    heartBuyBtn->setScale(scale);
    productLayer->addChild(heartBuyBtn);
    
    ui::Button* adsBuyBtn = ui::Button::create("btn_removeads_noraml.png","btn_removeads_press.png");
    adsBuyBtn->setPosition(Vec2(size.width*0.35, size.height*0.6-goldBuyBtn->getContentSize().height*scale -35*scale));
    adsBuyBtn->setScale(scale);
    productLayer->addChild(adsBuyBtn);
    
    ui::Button* restoreBtn = ui::Button::create("btn_restore_normal.png","btn_restore_press.png");
    restoreBtn->setPosition(Vec2(size.width*0.35+adsBuyBtn->getContentSize().width*scale+50*scale, size.height*0.6-goldBuyBtn->getContentSize().height*scale -35*scale));
    restoreBtn->setScale(scale);
    productLayer->addChild(restoreBtn);
    
    

    
    ui::Button* coin1_Btn = ui::Button::create("btn_coins01_normal.png","btn_coins01_press.png");
    coin1_Btn->setPosition(Vec2(size.width*0.35, size.height*0.6));
    coin1_Btn->setScale(scale);
    goldProductLayer->addChild(coin1_Btn);
    
    
    ui::Button* coin2_Btn = ui::Button::create("btn_coins02_normal.png","btn_coins02_press.png");
    coin2_Btn->setPosition(Vec2(size.width*0.35+coin1_Btn->getContentSize().width*scale+50*scale, size.height*0.6));
    coin2_Btn->setScale(scale);
    goldProductLayer->addChild(coin2_Btn);
    
    ui::Button* coin3_Btn = ui::Button::create("btn_coins03_normal.png","btn_coins03_press.png");
    coin3_Btn->setPosition(Vec2(size.width*0.35, coin2_Btn->getPositionY()-coin2_Btn->getContentSize().width*scale - 35*scale));
    coin3_Btn->setScale(scale);
    goldProductLayer->addChild(coin3_Btn);
    
    ui::Button* coin4_Btn = ui::Button::create("btn_coins04_normal.png","btn_coins04_press.png");
    coin4_Btn->setPosition(Vec2(size.width*0.35+coin1_Btn->getContentSize().width*scale+50*scale, coin2_Btn->getPositionY() -coin2_Btn->getContentSize().width*scale-35*scale));
    coin4_Btn->setScale(scale);
    goldProductLayer->addChild(coin4_Btn);
    
    ui::Button* coin5_Btn = ui::Button::create("btn_coins05_normal.png","btn_coins05_press.png");
    coin5_Btn->setPosition(Vec2(size.width*0.35, coin4_Btn->getPositionY()-coin4_Btn->getContentSize().width*scale -35*scale));
    coin5_Btn->setScale(scale);
    goldProductLayer->addChild(coin5_Btn);
    
    backBtn->addClickEventListener(CC_CALLBACK_1(ShopUI::onBack, this));
    
    goldBuyBtn->addClickEventListener(CC_CALLBACK_1(ShopUI::onBuyGold, this));
    heartBuyBtn->addClickEventListener(CC_CALLBACK_1(ShopUI::onBuyHeart, this));
    adsBuyBtn->addClickEventListener(CC_CALLBACK_1(ShopUI::onBuyRemoveAds, this));
    restoreBtn->addClickEventListener(CC_CALLBACK_1(ShopUI::onRestore, this));
    
    coin1_Btn->addClickEventListener(CC_CALLBACK_1(ShopUI::onBuyCoin1, this));
    coin2_Btn->addClickEventListener(CC_CALLBACK_1(ShopUI::onBuyCoin2, this));
    coin3_Btn->addClickEventListener(CC_CALLBACK_1(ShopUI::onBuyCoin3, this));
    coin4_Btn->addClickEventListener(CC_CALLBACK_1(ShopUI::onBuyCoin4, this));
    coin5_Btn->addClickEventListener(CC_CALLBACK_1(ShopUI::onBuyCoin5, this));
    
    productLayer->setVisible(true);
    goldProductLayer->setVisible(false);
    
    return true;
}

void ShopUI::onBack(cocos2d::Ref *ref)
{
    if (goldProductLayer->isVisible()) {
        if (std::strcmp(m_tip.c_str(), SHOP_BUY.c_str())) {
            setTips(SHOP_BUY);
        }
        goldProductLayer->setVisible(false);
        productLayer->setVisible(true);
    }else{
        Director::getInstance()->popScene();
    }
}
void ShopUI::onBuyGold(cocos2d::Ref *ref)
{
    productLayer->setVisible(false);
    goldProductLayer->setVisible(true);
}
void ShopUI::onBuyHeart(cocos2d::Ref *ref)
{
    CCLOG("onBuyHeart");
    int goldNum = Value(localStorageGetItem(USER_GOLD_NUM)).asInt();
    if (goldNum >= 150) {
        localStorageSetItem(USER_HEART_NUM, Value(Value(localStorageGetItem(USER_HEART_NUM)).asInt()+15).asString());
        localStorageSetItem(USER_GOLD_NUM, Value(Value(localStorageGetItem(USER_GOLD_NUM)).asInt()-150).asString());
        updateUserData();
    }else
    {
        setTips(SHOP_GOLD_NOT_ENOUGH);
        productLayer->setVisible(false);
        goldProductLayer->setVisible(true);
    }
    
    
}
void ShopUI::setTips(const std::string &tipkey)
{
    m_tip = tipkey;
    tipTv->setString(UtilityHelper::getLocalString(m_tip.c_str()));
}
void ShopUI::onBuyRemoveAds(cocos2d::Ref *ref)
{
    CCLOG("onBuyRemoveAds");
}

void ShopUI::onRestore(cocos2d::Ref *ref)
{
    CCLOG("onRestore");
}
void ShopUI::onBuyCoin1(cocos2d::Ref *ref)
{
    CCLOG("onBuyCoin1");
    onProduct("buyCoin1");
}
void ShopUI::onBuyCoin2(cocos2d::Ref *ref)
{
    CCLOG("onBuyCoin2");
    onProduct("buyCoin2");
}
void ShopUI::onBuyCoin3(cocos2d::Ref *ref)
{
    CCLOG("onBuyCoin3");
    onProduct("buyCoin3");
}
void ShopUI::onBuyCoin4(cocos2d::Ref *ref)
{
    CCLOG("onBuyCoin4");
    onProduct("buyCoin4");
}
void ShopUI::onBuyCoin5(cocos2d::Ref *ref)
{
    CCLOG("onBuyCoin5");
    onProduct("buyCoin5");
    
}
void ShopUI::onProduct(const std::string &productId)
{
    int num = 0;
    CCLOG("product:%s",productId.c_str());
    if (!std::strcmp(productId.c_str(), "buyCoin1"))
    {
        num = 200;
    }
    else if (!std::strcmp(productId.c_str(), "buyCoin2"))
    {
        num = 500;
    }
    else if (!std::strcmp(productId.c_str(), "buyCoin3"))
    {
        num = 1000;
    }
    else if (!std::strcmp(productId.c_str(), "buyCoin4"))
    {
        num = 2500;
    }
    else if (!std::strcmp(productId.c_str(), "buyCoin5"))
    {
        num = 10000;
    }
    localStorageSetItem(USER_GOLD_NUM, Value(Value(localStorageGetItem(USER_GOLD_NUM)).asInt()+num).asString());
    updateUserData();
}
void ShopUI::updateUserData()
{
    if (heartTv) {
        heartTv->setString(StringUtils::format("%d",Value(localStorageGetItem(USER_HEART_NUM)).asInt()));
    }
    if (goldTv) {
        goldTv->setString(StringUtils::format("%d",Value(localStorageGetItem(USER_GOLD_NUM)).asInt()));
    }
}
