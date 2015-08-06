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
#include "storage/local-storage/LocalStorage.h"
USING_NS_CC;

ShopPopUpUI* ShopPopUpUI::create()
{
    ShopPopUpUI *pRet = new(std::nothrow) ShopPopUpUI();
    if (pRet )
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

ShopPopUpUI::ShopPopUpUI()
{
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
    float scale = size.height /960.0f;
    
    auto bg = LayerColor::create(Color4B(107, 223, 255,255),size.width,size.height);
    bg->setPosition(Vec2::ZERO);
    m_dialogLayer->addChild(bg);
    
    
     productLayer = Layer::create();
    m_dialogLayer->addChild(productLayer);
    
     goldProductLayer = Layer::create();
    m_dialogLayer->addChild(goldProductLayer);
    
    ui::Button* backBtn = ui::Button::create("btn_back_normal.png","btn_back_press.png");
    backBtn->setPosition(Vec2(size.width*0.2, size.height*0.9));
    backBtn->setScale(scale);
    m_dialogLayer->addChild(backBtn);
    

    
    
    ui::ImageView* shopTv = ui::ImageView::create("ui_shop_icon.png");
    shopTv->setPosition(Vec2(size.width*0.32, size.height*0.75));
    shopTv->setScale(scale);
    m_dialogLayer->addChild(shopTv);

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
    

    
    goldBuyBtn->addClickEventListener(CC_CALLBACK_1(ShopPopUpUI::onBuyGold, this));
    heartBuyBtn->addClickEventListener(CC_CALLBACK_1(ShopPopUpUI::onBuyHeart, this));
    adsBuyBtn->addClickEventListener(CC_CALLBACK_1(ShopPopUpUI::onBuyRemoveAds, this));
    restoreBtn->addClickEventListener(CC_CALLBACK_1(ShopPopUpUI::onRestore, this));
    
    coin1_Btn->addClickEventListener(CC_CALLBACK_1(ShopPopUpUI::onBuyCoin1, this));
    coin2_Btn->addClickEventListener(CC_CALLBACK_1(ShopPopUpUI::onBuyCoin2, this));
    coin3_Btn->addClickEventListener(CC_CALLBACK_1(ShopPopUpUI::onBuyCoin3, this));
    coin4_Btn->addClickEventListener(CC_CALLBACK_1(ShopPopUpUI::onBuyCoin4, this));
    coin5_Btn->addClickEventListener(CC_CALLBACK_1(ShopPopUpUI::onBuyCoin5, this));
    
    productLayer->setVisible(true);
    goldProductLayer->setVisible(false);
    
    return true;
}

void ShopPopUpUI::onBuyGold(cocos2d::Ref *ref)
{
    productLayer->setVisible(false);
    goldProductLayer->setVisible(true);
}
void ShopPopUpUI::onBuyHeart(cocos2d::Ref *ref)
{
    CCLOG("onBuyHeart");
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

