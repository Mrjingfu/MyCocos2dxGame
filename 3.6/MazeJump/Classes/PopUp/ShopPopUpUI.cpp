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
#include "SdkBoxManager.h"
#include "NativeBridge.h"
#include "storage/local-storage/LocalStorage.h"
#include "AudioEngine.h"
USING_NS_CC;
using namespace experimental;

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
    m_shopType          = SHOP_NORMAL;
    m_isOnGold          = false;
    m_isOnHeart         = false;
    adsBuyBtn           = nullptr;
    productLayer        = nullptr;
    goldProductLayer    = nullptr;
    tipTv               = nullptr;
    heartTv             = nullptr;
    goldTv              = nullptr;
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
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_PURCHASE_GOLD_OK, std::bind(&ShopPopUpUI::onProuuctSucessEvent, this, std::placeholders::_1));
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_PURCHASE_REMOVEADS_OK, std::bind(&ShopPopUpUI::onRemoveAdaSucessEvent, this, std::placeholders::_1));
    
    NativeBridge::getInstance()->showAdsView();
}
void ShopPopUpUI::onExit()
{
    NativeBridge::getInstance()->hideAdsView();
    if (UIManager::getInstance()->getGameId() == UIManager::UI_MAIN) {
        UIManager::getInstance()->showInfo(false);
       
    }
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_PURCHASE_GOLD_OK);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_PURCHASE_REMOVEADS_OK);
    BasePopUpUI::onExit();
}
bool ShopPopUpUI::init()
{

    auto size = Director::getInstance()->getVisibleSize();
   float scale = size.width /640.0f;
    
   
    m_popupBgLayer = cocos2d::ui::ImageView::create(UtilityHelper::getLocalString("UI_SHOP_PANEL"),cocos2d::ui::TextureResType::PLIST);
    m_popupBgLayer->setPosition(Vec2(size.width*0.5, size.height*0.5));
    m_popupBgLayer->setScale(scale);
    m_dialogLayer->addChild(m_popupBgLayer);
    
    productLayer = Layer::create();
    m_dialogLayer->addChild(productLayer);
    
    goldProductLayer = Layer::create();
    m_dialogLayer->addChild(goldProductLayer);
    
    heartProductLayer = Layer::create();
    m_dialogLayer->addChild(heartProductLayer);
    
    cocos2d::ui::Button* goldBuyBtn = cocos2d::ui::Button::create("btn_gold_normal.png","btn_gold_pressed.png","",cocos2d::ui::TextureResType::PLIST);
    goldBuyBtn->setPosition(Vec2(size.width*0.4, size.height*0.61));
    goldBuyBtn->setScale(scale*1.2);
    productLayer->addChild(goldBuyBtn);
    
    cocos2d::ui::Button* heartBuyBtn = cocos2d::ui::Button::create("btn_heart_normal.png","btn_heart_pressed.png","",cocos2d::ui::TextureResType::PLIST);
    heartBuyBtn->setPosition(Vec2(size.width*0.4+goldBuyBtn->getContentSize().width*scale+50*scale, size.height*0.61));
    heartBuyBtn->setScale(scale*1.2);
    productLayer->addChild(heartBuyBtn);
    

    
    cocos2d::ui::Button* roleBtn = nullptr;
    cocos2d::ui::Button* restoreBtn = nullptr;
    if (UIManager::getInstance()->getGameId()==UIManager::UI_MAIN) {
        roleBtn = cocos2d::ui::Button::create("btn_character_normal.png","btn_character_pressed.png","",cocos2d::ui::TextureResType::PLIST);
        roleBtn->setPosition(Vec2(size.width*0.4, size.height*0.61-heartBuyBtn->getContentSize().width*scale-30*scale));
        roleBtn->setScale(scale*1.2);
        //禁用设置灰色
//      roleBtn->setBright(false);
//      roleBtn->setTouchEnabled(false);
        productLayer->addChild(roleBtn);
        
        adsBuyBtn = cocos2d::ui::Button::create("btn_removeads_normal.png","btn_removeads_pressed.png","",cocos2d::ui::TextureResType::PLIST);
        adsBuyBtn->setPosition(Vec2(size.width*0.4+roleBtn->getContentSize().width*scale+50*scale, size.height*0.61-heartBuyBtn->getContentSize().width*scale-30*scale ));
        adsBuyBtn->setScale(scale*1.2);
        productLayer->addChild(adsBuyBtn);
        
        restoreBtn = cocos2d::ui::Button::create("btn_restore_normal.png","btn_restore_pressed.png","",cocos2d::ui::TextureResType::PLIST);
        restoreBtn->setPosition(Vec2(size.width*0.4, size.height*0.61-adsBuyBtn->getContentSize().width*2*scale-60*scale ));
        restoreBtn->setScale(scale*1.2);
        productLayer->addChild(restoreBtn);

    }else
    {
        adsBuyBtn = cocos2d::ui::Button::create("btn_removeads_normal.png","btn_removeads_pressed.png","",cocos2d::ui::TextureResType::PLIST);
        adsBuyBtn->setPosition(Vec2(size.width*0.4, size.height*0.61-heartBuyBtn->getContentSize().width*scale-30*scale));
        adsBuyBtn->setScale(scale*1.2);
        productLayer->addChild(adsBuyBtn);
        
        restoreBtn = cocos2d::ui::Button::create("btn_restore_normal.png","btn_restore_pressed.png","",cocos2d::ui::TextureResType::PLIST);
        restoreBtn->setPosition(Vec2(size.width*0.4+adsBuyBtn->getContentSize().width*scale+50*scale, size.height*0.61-heartBuyBtn->getContentSize().width*scale-30*scale ));
        restoreBtn->setScale(scale*1.2);
        productLayer->addChild(restoreBtn);
    }
    
    bool removeAds = Value(localStorageGetItem("RemoveAds")).asBool();
    if(removeAds)
    {
        if (adsBuyBtn) {
            adsBuyBtn->setBright(false);
            adsBuyBtn->setTouchEnabled(false);
        }
    }
    
    
    
    std::string conin1 ;
    std::string conin2 ;
    std::string conin3 ;
    std::string conin4 ;
    std::string conin5;
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
    if (SdkBoxManager::getInstance()->getProducts().size()>=5) {
        conin1=SdkBoxManager::getInstance()->getProducts().at(0).price;
        conin2=SdkBoxManager::getInstance()->getProducts().at(1).price;
        conin3=SdkBoxManager::getInstance()->getProducts().at(2).price;
        conin4=SdkBoxManager::getInstance()->getProducts().at(3).price;
        conin5=SdkBoxManager::getInstance()->getProducts().at(4).price;
    }
    
#endif

    cocos2d::ui::Button* coin1_Btn = cocos2d::ui::Button::create("btn_gold1_normal.png","btn_gold1_pressed.png","",cocos2d::ui::TextureResType::PLIST);
    coin1_Btn->setPosition(Vec2(size.width*0.4, size.height*0.61));
    coin1_Btn->setScale(scale*1.2);
    goldProductLayer->addChild(coin1_Btn);
    
    cocos2d::Label* coin1_gold_NumLabel = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),"450");
    coin1_gold_NumLabel->setPosition(Vec2(size.width*0.4+18*scale, size.height*0.61+23*scale));
    coin1_gold_NumLabel->setScale(scale*0.7);
    goldProductLayer->addChild(coin1_gold_NumLabel);

    cocos2d::Label* coin1_money_NumLabel = Label::createWithSystemFont(conin1, FONT_FXZS, 30);
    coin1_money_NumLabel->setPosition(Vec2(size.width*0.4+5*scale, size.height*0.61-18*scale));
    coin1_money_NumLabel->setScale(scale*0.72);
    goldProductLayer->addChild(coin1_money_NumLabel);

    
    cocos2d::ui::Button* coin2_Btn = cocos2d::ui::Button::create("btn_gold2_normal.png","btn_gold2_pressed.png","",cocos2d::ui::TextureResType::PLIST);
    coin2_Btn->setPosition(Vec2(size.width*0.4+goldBuyBtn->getContentSize().width*scale+50*scale, size.height*0.61));
    coin2_Btn->setScale(scale*1.2);
    goldProductLayer->addChild(coin2_Btn);
    
    
    cocos2d::Label* coin2_gold_NumLabel = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),"1500");
    coin2_gold_NumLabel->setPosition(Vec2(size.width*0.4+goldBuyBtn->getContentSize().width*scale+68*scale, size.height*0.61+20*scale));
    coin2_gold_NumLabel->setScale(scale*0.7);
    goldProductLayer->addChild(coin2_gold_NumLabel);
    
    cocos2d::Label* coin2_money_NumLabel = Label::createWithSystemFont(conin2, FONT_FXZS, 30);
    coin2_money_NumLabel->setPosition(Vec2(size.width*0.4+goldBuyBtn->getContentSize().width*scale+55*scale, size.height*0.61-18*scale));
    coin2_money_NumLabel->setScale(scale*0.72);
    goldProductLayer->addChild(coin2_money_NumLabel);
    
    cocos2d::ui::Button* coin3_Btn = cocos2d::ui::Button::create("btn_gold3_normal.png","btn_gold3_pressed.png","",cocos2d::ui::TextureResType::PLIST);
    coin3_Btn->setPosition(Vec2(size.width*0.4, size.height*0.61-heartBuyBtn->getContentSize().width*scale-30*scale));
    coin3_Btn->setScale(scale*1.2);
    goldProductLayer->addChild(coin3_Btn);
    
    cocos2d::Label* coin3_gold_NumLabel = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),"2500");
    coin3_gold_NumLabel->setPosition(Vec2(size.width*0.4+20*scale, size.height*0.61-heartBuyBtn->getContentSize().width*scale-14*scale));
    coin3_gold_NumLabel->setScale(scale*0.7);
    goldProductLayer->addChild(coin3_gold_NumLabel);
    
    cocos2d::Label* coin3_money_NumLabel = Label::createWithSystemFont(conin3, FONT_FXZS, 30);
    coin3_money_NumLabel->setPosition(Vec2(size.width*0.4+5*scale, size.height*0.61-heartBuyBtn->getContentSize().width*scale-46*scale));
    coin3_money_NumLabel->setScale(scale*0.72);
    goldProductLayer->addChild(coin3_money_NumLabel);
    
    cocos2d::ui::Button* coin4_Btn = cocos2d::ui::Button::create("btn_gold4_normal.png","btn_gold4_pressed.png","",cocos2d::ui::TextureResType::PLIST);
    coin4_Btn->setPosition(Vec2(size.width*0.4+coin2_Btn->getContentSize().width*scale+50*scale, size.height*0.61-heartBuyBtn->getContentSize().width*scale-30*scale ));
    coin4_Btn->setScale(scale*1.2);
    goldProductLayer->addChild(coin4_Btn);
    
    cocos2d::Label* coin4_gold_NumLabel = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),"6000");
    coin4_gold_NumLabel->setPosition(Vec2(size.width*0.4+goldBuyBtn->getContentSize().width*scale+75*scale, size.height*0.61-heartBuyBtn->getContentSize().width*scale-12*scale));
    coin4_gold_NumLabel->setScale(scale*0.7);
    goldProductLayer->addChild(coin4_gold_NumLabel);
    
    cocos2d::Label* coin4_money_NumLabel = Label::createWithSystemFont(conin4, FONT_FXZS, 30);
    coin4_money_NumLabel->setPosition(Vec2(size.width*0.4+goldBuyBtn->getContentSize().width*scale+55*scale, size.height*0.61-heartBuyBtn->getContentSize().width*scale-46*scale));
    coin4_money_NumLabel->setScale(scale*0.72);
    goldProductLayer->addChild(coin4_money_NumLabel);
    
    
    cocos2d::ui::Button* coin5_Btn = cocos2d::ui::Button::create("btn_gold5_normal.png","btn_gold5_pressed.png","",cocos2d::ui::TextureResType::PLIST);
    coin5_Btn->setPosition(Vec2(size.width*0.4, size.height*0.61-goldBuyBtn->getContentSize().width*2*scale-60*scale ));
    coin5_Btn->setScale(scale*1.2);
    goldProductLayer->addChild(coin5_Btn);
    
    cocos2d::Label* coin5_gold_NumLabel = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),"12500");
    coin5_gold_NumLabel->setPosition(Vec2(size.width*0.4+26*scale, size.height*0.61-heartBuyBtn->getContentSize().width*2*scale-48*scale));
    coin5_gold_NumLabel->setScale(scale*0.65);
    goldProductLayer->addChild(coin5_gold_NumLabel);
    
    cocos2d::Label* coin5_money_NumLabel = Label::createWithSystemFont(conin5, FONT_FXZS, 30);
    coin5_money_NumLabel->setPosition(Vec2(size.width*0.4, size.height*0.61-heartBuyBtn->getContentSize().width*2*scale-83*scale));
    coin5_money_NumLabel->setScale(scale*0.72);
    goldProductLayer->addChild(coin5_money_NumLabel);
    
    
    
    
    
    cocos2d::ui::Button* heart1_Btn = cocos2d::ui::Button::create("btn_buyHeart_normal.png","btn_buyHeart_pressed.png","",cocos2d::ui::TextureResType::PLIST);
    heart1_Btn->setPosition(Vec2(size.width*0.4, size.height*0.61));
    heart1_Btn->setScale(scale*1.2);
    heartProductLayer->addChild(heart1_Btn);
    
    
    cocos2d::Label* heart1_NumLabel = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),"+1");
    heart1_NumLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    heart1_NumLabel->setPosition(Vec2(size.width*0.4+15*scale, size.height*0.61+20*scale));
    heart1_NumLabel->setScale(scale*0.6);
    heartProductLayer->addChild(heart1_NumLabel);
    
    cocos2d::Label* heartGold1_NumLabel = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),"-100");
    heartGold1_NumLabel->setPosition(Vec2(size.width*0.4+25*scale, size.height*0.61-18*scale));
    heartGold1_NumLabel->setScale(scale*0.6);
    heart1_NumLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    heartProductLayer->addChild(heartGold1_NumLabel);
    
    
    
    cocos2d::ui::Button* heart2_Btn = cocos2d::ui::Button::create("btn_buyHeart_normal.png","btn_buyHeart_pressed.png","",cocos2d::ui::TextureResType::PLIST);
    heart2_Btn->setPosition(Vec2(size.width*0.4+goldBuyBtn->getContentSize().width*scale+50*scale, size.height*0.61));
    heart2_Btn->setScale(scale*1.2);
    heartProductLayer->addChild(heart2_Btn);
    
    
    cocos2d::Label* heart2_NumLabel = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),"+5");
    heart2_NumLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    heart2_NumLabel->setPosition(Vec2(size.width*0.4+goldBuyBtn->getContentSize().width*scale+60*scale, size.height*0.61+20*scale));
    heart2_NumLabel->setScale(scale*0.6);
    heartProductLayer->addChild(heart2_NumLabel);
    
    cocos2d::Label* heartGold2_NumLabel = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),"-480");
    heartGold2_NumLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    heartGold2_NumLabel->setPosition(Vec2(size.width*0.4+goldBuyBtn->getContentSize().width*scale+45*scale, size.height*0.61-18*scale));
    heartGold2_NumLabel->setScale(scale*0.6);
    heartProductLayer->addChild(heartGold2_NumLabel);
  
    
    cocos2d::ui::Button* heart3_Btn = cocos2d::ui::Button::create("btn_buyHeart_normal.png","btn_buyHeart_pressed.png","",cocos2d::ui::TextureResType::PLIST);
    heart3_Btn->setPosition(Vec2(size.width*0.4, size.height*0.61-heartBuyBtn->getContentSize().width*scale-30*scale));
    heart3_Btn->setScale(scale*1.2);
    heartProductLayer->addChild(heart3_Btn);
    
    cocos2d::Label* heart3_NumLabel = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),"+10");
    heart3_NumLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    heart3_NumLabel->setPosition(Vec2(size.width*0.4+15*scale, size.height*0.61-heartBuyBtn->getContentSize().width*scale-5*scale));
    heart3_NumLabel->setScale(scale*0.6);
    heartProductLayer->addChild(heart3_NumLabel);
    
    cocos2d::Label* heartGold3_NumLabel = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),"-900");
    heartGold3_NumLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    heartGold3_NumLabel->setPosition(Vec2(size.width*0.4-6*scale, size.height*0.61-heartBuyBtn->getContentSize().width*scale-48*scale));
    heartGold3_NumLabel->setScale(scale*0.6);
    heartProductLayer->addChild(heartGold3_NumLabel);
    

    
    cocos2d::ui::Button* heart4_Btn = cocos2d::ui::Button::create("btn_buyHeart_normal.png","btn_buyHeart_pressed.png","",cocos2d::ui::TextureResType::PLIST);
    heart4_Btn->setPosition(Vec2(size.width*0.4+coin2_Btn->getContentSize().width*scale+50*scale, size.height*0.61-heartBuyBtn->getContentSize().width*scale-30*scale ));
    heart4_Btn->setScale(scale*1.2);
    heartProductLayer->addChild(heart4_Btn);

    
    cocos2d::Label* heart4_NumLabel = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),"+25");
    heart4_NumLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    heart4_NumLabel->setPosition(Vec2(size.width*0.4+coin2_Btn->getContentSize().width*scale+62*scale, size.height*0.61-heartBuyBtn->getContentSize().width*scale-10*scale ));
    heart4_NumLabel->setScale(scale*0.6);
    heartProductLayer->addChild(heart4_NumLabel);
    
    cocos2d::Label* heartGold4_NumLabel = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),"-2200");
    heartGold4_NumLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    heartGold4_NumLabel->setPosition(Vec2(size.width*0.4+coin2_Btn->getContentSize().width*scale+45*scale, size.height*0.61-heartBuyBtn->getContentSize().width*scale-48*scale ));
    heartGold4_NumLabel->setScale(scale*0.6);
    heartProductLayer->addChild(heartGold4_NumLabel);
    
    
    cocos2d::ui::Button* heart5_Btn = cocos2d::ui::Button::create("btn_buyHeart_normal.png","btn_buyHeart_pressed.png","",cocos2d::ui::TextureResType::PLIST);
    heart5_Btn->setPosition(Vec2(size.width*0.4, size.height*0.61-goldBuyBtn->getContentSize().width*2*scale-60*scale ));
    heart5_Btn->setScale(scale*1.2);
    heartProductLayer->addChild(heart5_Btn);
    
    
    cocos2d::Label* heart5_NumLabel = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),"+50");
    heart5_NumLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    heart5_NumLabel->setPosition(Vec2(size.width*0.4+15*scale, size.height*0.61-goldBuyBtn->getContentSize().width*2*scale-40*scale ));
    heart5_NumLabel->setScale(scale*0.6);
    heartProductLayer->addChild(heart5_NumLabel);
    
    cocos2d::Label* heartGold5_NumLabel = Label::createWithBMFont(UtilityHelper::getLocalString("FONT_NUMBER"),"-4500");
    heartGold5_NumLabel->setPosition(Vec2(size.width*0.4+20*scale, size.height*0.61-goldBuyBtn->getContentSize().width*2*scale-78*scale ));
    heartGold5_NumLabel->setScale(scale*0.6);
    heartProductLayer->addChild(heartGold5_NumLabel);
    

    
    cocos2d::ui::Button* backBtn = cocos2d::ui::Button::create("btn_back_pressed.png","","",cocos2d::ui::TextureResType::PLIST);
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
    
    coin1_Btn->addClickEventListener(CC_CALLBACK_1(ShopPopUpUI::onProduct, this,PURCHASE_ID1));
    coin2_Btn->addClickEventListener(CC_CALLBACK_1(ShopPopUpUI::onProduct, this,PURCHASE_ID2));
    coin3_Btn->addClickEventListener(CC_CALLBACK_1(ShopPopUpUI::onProduct, this,PURCHASE_ID3));
    coin4_Btn->addClickEventListener(CC_CALLBACK_1(ShopPopUpUI::onProduct, this,PURCHASE_ID4));
    coin5_Btn->addClickEventListener(CC_CALLBACK_1(ShopPopUpUI::onProduct, this,PURCHASE_ID5));
    
    heart1_Btn->addClickEventListener(CC_CALLBACK_1(ShopPopUpUI::onProductHeart, this,1,100));
    heart2_Btn->addClickEventListener(CC_CALLBACK_1(ShopPopUpUI::onProductHeart, this,5,480));
    heart3_Btn->addClickEventListener(CC_CALLBACK_1(ShopPopUpUI::onProductHeart, this,10,900));
    heart4_Btn->addClickEventListener(CC_CALLBACK_1(ShopPopUpUI::onProductHeart, this,25,2200));
    heart5_Btn->addClickEventListener(CC_CALLBACK_1(ShopPopUpUI::onProductHeart, this,50,4500));
    
    
    backBtn->addClickEventListener(CC_CALLBACK_1(ShopPopUpUI::onBackShop, this));
    
    setShopDisplay(m_shopType);
    
    return true;
}


void ShopPopUpUI::setShopDisplay(ShopType type)
{
    m_shopType = type;
    if (m_shopType == ShopType::SHOP_GOLD) {
        productLayer->setVisible(false);
        heartProductLayer->setVisible(false);
        goldProductLayer->setVisible(true);
    }else if (m_shopType == SHOP_NORMAL)
    {
        productLayer->setVisible(true);
        goldProductLayer->setVisible(false);
        heartProductLayer->setVisible(false);
    }else if (m_shopType == SHOP_HEART)
    {
        productLayer->setVisible(false);
        goldProductLayer->setVisible(false);
        heartProductLayer->setVisible(true);
    }
}
void ShopPopUpUI::onBuyGold(cocos2d::Ref *ref)
{
     UIManager::getInstance()->playBtnSound();
    m_isOnGold = true;
    setShopDisplay(SHOP_GOLD);
}
void ShopPopUpUI::onBuyHeart(cocos2d::Ref *ref)
{
    UIManager::getInstance()->playBtnSound();
    CCLOG("onBuyHeart");
    m_isOnHeart = true;
    setShopDisplay(SHOP_HEART);

}
void ShopPopUpUI::onRole(cocos2d::Ref *ref)
{
     UIManager::getInstance()->playBtnSound();
    UIManager::getInstance()->hidePopUp(false);
    UIManager::getInstance()->addPopUp(BasePopUpUI::POPUP_ROLE);
    UIManager::getInstance()->showPopUp(true,BasePopUpUI::POPUP_HORIZONTAL);
    CCLOG("onRole");
}
void ShopPopUpUI::onBuyRemoveAds(cocos2d::Ref *ref)
{
    CCLOG("onBuyRemoveAds");
     UIManager::getInstance()->playBtnSound();
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
    SdkBoxManager::getInstance()->purchase(PURCHASE_ID6);
#endif
}

void ShopPopUpUI::onRestore(cocos2d::Ref *ref)
{
    CCLOG("onRestore");
    UIManager::getInstance()->playBtnSound();
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
    SdkBoxManager::getInstance()->restore();
#endif
}

void ShopPopUpUI::onBackShop(cocos2d::Ref *ref)
{
     UIManager::getInstance()->playBtnSound();
    if (m_isOnGold) {
        setShopDisplay(ShopType::SHOP_NORMAL);
        m_isOnGold = false;
    }else if (m_isOnHeart)
    {
        setShopDisplay(ShopType::SHOP_NORMAL);
        m_isOnHeart = false;
    }
    else
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
                Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_START_HEART_CHANGE);
                Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_START_GOLD_CHANGE);
                
            }
        }else
        {
            UIManager::getInstance()->hidePopUp(false);
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_RUNNER_ADD_PRODUCT);
        }
        
    }
}
void ShopPopUpUI::onProduct(Ref* Ref,const std::string &productId)
{
     UIManager::getInstance()->playBtnSound();
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
    SdkBoxManager::getInstance()->purchase(productId);
#else
    int num = 0;
    CCLOG("product:%s",productId.c_str());
    if (productId == PURCHASE_ID1)
    {
        num = 450;
    }
    else if (productId == PURCHASE_ID2)
    {
        num = 1500;
    }
    else if (productId == PURCHASE_ID3)
    {
        num = 2500;
    }
    else if (productId == PURCHASE_ID4)
    {
        num = 6000;
    }
    else if (productId == PURCHASE_ID5)
    {
        num = 12500;
    }
    localStorageSetItem(USER_GOLD_NUM, Value(Value(localStorageGetItem(USER_GOLD_NUM)).asInt()+num).asString());
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_GOLD_CHANGE);
#endif

}
void ShopPopUpUI::onProductHeart(cocos2d::Ref *Ref, int addHeartNum, int reduceGoldNum)
{
    CCLOG("addHeartNum:%d,reduceGoldNum:%d",addHeartNum,reduceGoldNum);
    int goldNum = Value(localStorageGetItem(USER_GOLD_NUM)).asInt();
    if (goldNum>=reduceGoldNum) {
        localStorageSetItem(USER_GOLD_NUM, Value(goldNum-reduceGoldNum).asString());
        localStorageSetItem(USER_HEART_NUM, Value(Value(localStorageGetItem(USER_HEART_NUM)).asInt()+addHeartNum).asString());
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_HEART_CHANGE);
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_GOLD_CHANGE);
        AudioEngine::play2d("pickupheart.wav");
        
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
        SdkBoxManager::getInstance()->logEvent("Purchase", "Purchase Heart", "Heart", addHeartNum);
#endif
    }else
    {
        CCLOG("Shop");
        onBuyGold(this);
        
    }
}
void ShopPopUpUI::onProuuctSucessEvent(cocos2d::EventCustom *sender)
{
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_GOLD_CHANGE);
}
void ShopPopUpUI::onRemoveAdaSucessEvent(cocos2d::EventCustom *sender)
{
    if (adsBuyBtn) {
        adsBuyBtn->setBright(false);
        adsBuyBtn->setTouchEnabled(false);
    }
    NativeBridge::getInstance()->hideAdsView();
    
}

