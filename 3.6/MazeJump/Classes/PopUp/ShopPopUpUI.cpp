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
    m_isOnGold = false;
}
ShopPopUpUI::~ShopPopUpUI()
{
}
void ShopPopUpUI::onEnter()
{
    BasePopUpUI::onEnter();
    init();
    if (UIManager::getInstance()->getGameId() == UIManager::UI_MAIN) {
        UIManager::getInstance()->showInfo(true);

    }
    
}
void ShopPopUpUI::onExit()
{
    BasePopUpUI::onExit();
    if (UIManager::getInstance()->getGameId() == UIManager::UI_MAIN) {
        UIManager::getInstance()->showInfo(false);
       
    }
    
}
bool ShopPopUpUI::init()
{

    auto size = Director::getInstance()->getVisibleSize();
   float scale = size.width /640.0f;
    
   
    m_popupBgLayer = ui::ImageView::create(UtilityHelper::getLocalString("UI_SHOP_PANEL"));
    m_popupBgLayer->setPosition(Vec2(size.width*0.5, size.height*0.5));
    m_popupBgLayer->setScale(scale);
    m_dialogLayer->addChild(m_popupBgLayer);
    
    productLayer = Layer::create();
    m_dialogLayer->addChild(productLayer);
    
    goldProductLayer = Layer::create();
    m_dialogLayer->addChild(goldProductLayer);
    
    ui::Button* goldBuyBtn = ui::Button::create("btn_gold_normal.png","btn_gold_pressed.png");
    goldBuyBtn->setPosition(Vec2(size.width*0.4, size.height*0.61));
    goldBuyBtn->setScale(scale*1.2);
    productLayer->addChild(goldBuyBtn);
    
    ui::Button* heartBuyBtn = ui::Button::create("btn_heart_normal.png","btn_heart_pressed.png");
    heartBuyBtn->setPosition(Vec2(size.width*0.4+goldBuyBtn->getContentSize().width*scale+50*scale, size.height*0.61));
    heartBuyBtn->setScale(scale*1.2);
    productLayer->addChild(heartBuyBtn);

    
    cocos2d::Label* heartNumLabel = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),"+15");
    heartNumLabel->setPosition(Vec2(size.width*0.4+goldBuyBtn->getContentSize().width*scale+70*scale, size.height*0.61+20*scale));
    heartNumLabel->setScale(scale*0.4);
    productLayer->addChild(heartNumLabel);
    
    cocos2d::Label* heartGoldNumLabel = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),"-150");
    heartGoldNumLabel->setPosition(Vec2(size.width*0.4+goldBuyBtn->getContentSize().width*scale+70*scale, size.height*0.61-17*scale));
    heartGoldNumLabel->setScale(scale*0.4);
    productLayer->addChild(heartGoldNumLabel);
    
    
    ui::Button* roleBtn = nullptr;
    ui::Button* adsBuyBtn = nullptr;
    ui::Button* restoreBtn = nullptr;
    if (UIManager::getInstance()->getGameId()==UIManager::UI_MAIN) {
        roleBtn = ui::Button::create("btn_character_normal.png","btn_character_pressed.png");
        roleBtn->setPosition(Vec2(size.width*0.4, size.height*0.61-heartBuyBtn->getContentSize().width*scale-30*scale));
        roleBtn->setScale(scale*1.2);
        //禁用设置灰色
//      roleBtn->setBright(false);
//      roleBtn->setTouchEnabled(false);
        productLayer->addChild(roleBtn);
        
        adsBuyBtn = ui::Button::create("btn_removeads_normal.png","btn_removeads_pressed.png");
        adsBuyBtn->setPosition(Vec2(size.width*0.4+roleBtn->getContentSize().width*scale+50*scale, size.height*0.61-heartBuyBtn->getContentSize().width*scale-30*scale ));
        adsBuyBtn->setScale(scale*1.2);
        productLayer->addChild(adsBuyBtn);
        
        restoreBtn = ui::Button::create("btn_restore_normal.png","btn_restore_pressed.png");
        restoreBtn->setPosition(Vec2(size.width*0.4, size.height*0.61-adsBuyBtn->getContentSize().width*2*scale-60*scale ));
        restoreBtn->setScale(scale*1.2);
        productLayer->addChild(restoreBtn);

    }else
    {
        adsBuyBtn = ui::Button::create("btn_removeads_normal.png","btn_removeads_pressed.png");
        adsBuyBtn->setPosition(Vec2(size.width*0.4, size.height*0.61-heartBuyBtn->getContentSize().width*scale-30*scale));
        adsBuyBtn->setScale(scale*1.2);
        productLayer->addChild(adsBuyBtn);
        
        restoreBtn = ui::Button::create("btn_restore_normal.png","btn_restore_pressed.png");
        restoreBtn->setPosition(Vec2(size.width*0.4+adsBuyBtn->getContentSize().width*scale+50*scale, size.height*0.61-heartBuyBtn->getContentSize().width*scale-30*scale ));
        restoreBtn->setScale(scale*1.2);
        productLayer->addChild(restoreBtn);
    }

    ui::Button* coin1_Btn = ui::Button::create("btn_gold1_normal.png","btn_gold1_pressed.png");
    coin1_Btn->setPosition(Vec2(size.width*0.4, size.height*0.61));
    coin1_Btn->setScale(scale*1.2);
    goldProductLayer->addChild(coin1_Btn);
    
    cocos2d::Label* coin1_gold_NumLabel = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),"200");
    coin1_gold_NumLabel->setPosition(Vec2(size.width*0.4+18*scale, size.height*0.61+20*scale));
    coin1_gold_NumLabel->setScale(scale*0.37);
    goldProductLayer->addChild(coin1_gold_NumLabel);
    
    cocos2d::Label* coin1_money_NumLabel = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),"150");
    coin1_money_NumLabel->setPosition(Vec2(size.width*0.4+5*scale, size.height*0.61-20*scale));
    coin1_money_NumLabel->setScale(scale*0.4);
    goldProductLayer->addChild(coin1_money_NumLabel);

    
    ui::Button* coin2_Btn = ui::Button::create("btn_gold2_normal.png","btn_gold2_pressed.png");;
    coin2_Btn->setPosition(Vec2(size.width*0.4+goldBuyBtn->getContentSize().width*scale+50*scale, size.height*0.61));
    coin2_Btn->setScale(scale*1.2);
    goldProductLayer->addChild(coin2_Btn);
    
    
    cocos2d::Label* coin2_gold_NumLabel = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),"500");
    coin2_gold_NumLabel->setPosition(Vec2(size.width*0.4+goldBuyBtn->getContentSize().width*scale+68*scale, size.height*0.61+18*scale));
    coin2_gold_NumLabel->setScale(scale*0.37);
    goldProductLayer->addChild(coin2_gold_NumLabel);
    
    cocos2d::Label* coin2_money_NumLabel = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),"150");
    coin2_money_NumLabel->setPosition(Vec2(size.width*0.4+goldBuyBtn->getContentSize().width*scale+55*scale, size.height*0.61-20*scale));
    coin2_money_NumLabel->setScale(scale*0.4);
    goldProductLayer->addChild(coin2_money_NumLabel);
    
    ui::Button* coin3_Btn = ui::Button::create("btn_gold3_normal.png","btn_gold3_pressed.png");
    coin3_Btn->setPosition(Vec2(size.width*0.4, size.height*0.61-heartBuyBtn->getContentSize().width*scale-30*scale));
    coin3_Btn->setScale(scale*1.2);
    goldProductLayer->addChild(coin3_Btn);
    
    cocos2d::Label* coin3_gold_NumLabel = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),"1000");
    coin3_gold_NumLabel->setPosition(Vec2(size.width*0.4+18*scale, size.height*0.61-heartBuyBtn->getContentSize().width*scale-16*scale));
    coin3_gold_NumLabel->setScale(scale*0.37);
    goldProductLayer->addChild(coin3_gold_NumLabel);
    
    cocos2d::Label* coin3_money_NumLabel = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),"150");
    coin3_money_NumLabel->setPosition(Vec2(size.width*0.4+5*scale, size.height*0.61-heartBuyBtn->getContentSize().width*scale-48*scale));
    coin3_money_NumLabel->setScale(scale*0.4);
    goldProductLayer->addChild(coin3_money_NumLabel);
    
    ui::Button* coin4_Btn = ui::Button::create("btn_gold4_normal.png","btn_gold4_pressed.png");
    coin4_Btn->setPosition(Vec2(size.width*0.4+coin2_Btn->getContentSize().width*scale+50*scale, size.height*0.61-heartBuyBtn->getContentSize().width*scale-30*scale ));
    coin4_Btn->setScale(scale*1.2);
    goldProductLayer->addChild(coin4_Btn);
    
    cocos2d::Label* coin4_gold_NumLabel = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),"5000");
    coin4_gold_NumLabel->setPosition(Vec2(size.width*0.4+goldBuyBtn->getContentSize().width*scale+70*scale, size.height*0.61-heartBuyBtn->getContentSize().width*scale-16*scale));
    coin4_gold_NumLabel->setScale(scale*0.37);
    goldProductLayer->addChild(coin4_gold_NumLabel);
    
    cocos2d::Label* coin4_money_NumLabel = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),"150");
    coin4_money_NumLabel->setPosition(Vec2(size.width*0.4+goldBuyBtn->getContentSize().width*scale+55*scale, size.height*0.61-heartBuyBtn->getContentSize().width*scale-48*scale));
    coin4_money_NumLabel->setScale(scale*0.4);
    goldProductLayer->addChild(coin4_money_NumLabel);
    
    
    ui::Button* coin5_Btn = ui::Button::create("btn_gold5_normal.png","btn_gold5_pressed.png");
    coin5_Btn->setPosition(Vec2(size.width*0.4, size.height*0.61-goldBuyBtn->getContentSize().width*2*scale-60*scale ));
    coin5_Btn->setScale(scale*1.2);
    goldProductLayer->addChild(coin5_Btn);
    
    cocos2d::Label* coin5_gold_NumLabel = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),"8000");
    coin5_gold_NumLabel->setPosition(Vec2(size.width*0.4+26*scale, size.height*0.61-heartBuyBtn->getContentSize().width*2*scale-43*scale));
    coin5_gold_NumLabel->setScale(scale*0.36);
    goldProductLayer->addChild(coin5_gold_NumLabel);
    
    cocos2d::Label* coin5_money_NumLabel = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),"150");
    coin5_money_NumLabel->setPosition(Vec2(size.width*0.4+5*scale, size.height*0.61-heartBuyBtn->getContentSize().width*2*scale-83*scale));
    coin5_money_NumLabel->setScale(scale*0.4);
    goldProductLayer->addChild(coin5_money_NumLabel);
    
    
    ui::Button* backBtn = ui::Button::create("btn_back_normal.png","btn_back_pressed.png");
    backBtn->setPosition(Vec2(size.width*0.4+restoreBtn->getContentSize().width*scale+50*scale, size.height*0.61-heartBuyBtn->getContentSize().width*2*scale-60*scale));
    backBtn->setScale(scale*1.2);
    m_dialogLayer->addChild(backBtn);

    
    goldBuyBtn->addClickEventListener(CC_CALLBACK_1(ShopPopUpUI::onBuyGold, this));
    heartBuyBtn->addClickEventListener(CC_CALLBACK_1(ShopPopUpUI::onBuyHeart, this));
    adsBuyBtn->addClickEventListener(CC_CALLBACK_1(ShopPopUpUI::onBuyRemoveAds, this));
    restoreBtn->addClickEventListener(CC_CALLBACK_1(ShopPopUpUI::onRestore, this));
    if (roleBtn) {
        roleBtn->addClickEventListener(CC_CALLBACK_1(ShopPopUpUI::onRole,this));
    }
    
    coin1_Btn->addClickEventListener(CC_CALLBACK_1(ShopPopUpUI::onProduct, this,"buyCoin1"));
    coin2_Btn->addClickEventListener(CC_CALLBACK_1(ShopPopUpUI::onProduct, this,"buyCoin2"));
    coin3_Btn->addClickEventListener(CC_CALLBACK_1(ShopPopUpUI::onProduct, this,"buyCoin3"));
    coin4_Btn->addClickEventListener(CC_CALLBACK_1(ShopPopUpUI::onProduct, this,"buyCoin4"));
    coin5_Btn->addClickEventListener(CC_CALLBACK_1(ShopPopUpUI::onProduct, this,"buyCoin5"));
    
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
     UIManager::getInstance()->playSound();
    m_isOnGold = true;
    setShopDisplay(SHOP_GOLD);
}
void ShopPopUpUI::onBuyHeart(cocos2d::Ref *ref)
{
    UIManager::getInstance()->playSound();
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
        onBuyGold(this);
        
    }
}
void ShopPopUpUI::onRole(cocos2d::Ref *ref)
{
     UIManager::getInstance()->playSound();
    UIManager::getInstance()->hidePopUp(false);
    UIManager::getInstance()->addPopUp(BasePopUpUI::POPUP_ROLE);
    UIManager::getInstance()->showPopUp(true,BasePopUpUI::POPUP_HORIZONTAL);
    CCLOG("onRole");
}
void ShopPopUpUI::onBuyRemoveAds(cocos2d::Ref *ref)
{
    CCLOG("onBuyRemoveAds");
     UIManager::getInstance()->playSound();
}

void ShopPopUpUI::onRestore(cocos2d::Ref *ref)
{
    CCLOG("onRestore");
     UIManager::getInstance()->playSound();
}

void ShopPopUpUI::onBackShop(cocos2d::Ref *ref)
{
     UIManager::getInstance()->playSound();
    if (m_isOnGold) {
        setShopDisplay(ShopType::SHOP_NORMAL);
        m_isOnGold = false;
    }else
    {
        if (UIManager::getInstance()->getGameId() == UIManager::UI_MAIN) {
            
           
            BasePopUpUI* popup = UIManager::getInstance()->getPopUpUI(BasePopUpUI::POPUP_ROLE);
            if (popup) {
                 UIManager::getInstance()->hidePopUp(false);
                UIManager::getInstance()->showInfo(true);
            }else
            {
                BasePopUpUI* popupstart = UIManager::getInstance()->getPopUpUI(BasePopUpUI::POPUP_START);
                if (popupstart) {
                    UIManager::getInstance()->hidePopUp(false);
                }else
                {
                     UIManager::getInstance()->hidePopUp();
                }
                
            }
        }else
        {
            UIManager::getInstance()->hidePopUp(false);
        }
        
    }
}
void ShopPopUpUI::onProduct(Ref* Ref,const std::string &productId)
{
     UIManager::getInstance()->playSound();
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
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_GOLD_CHANGE);
}

