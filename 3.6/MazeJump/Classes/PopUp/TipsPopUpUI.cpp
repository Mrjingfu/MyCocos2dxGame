//
//  TipsUI.cpp
//
//
//
//

#include "TipsPopUpUI.h"
#include "UtilityHelper.h"
#include "GameConst.h"
#include "UIManager.h"
#include "ShopPopUpUI.h"
#include "storage/local-storage/LocalStorage.h"
USING_NS_CC;

TipsPopUpUI* TipsPopUpUI::create(TipsType type)
{
    TipsPopUpUI *pRet = new(std::nothrow) TipsPopUpUI(type);
    if (pRet )
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

TipsPopUpUI::TipsPopUpUI(TipsType type):m_tipType(type)
{
}
TipsPopUpUI::~TipsPopUpUI()
{
}
void TipsPopUpUI::onEnter()
{
    BasePopUpUI::onEnter();
    init();
}
void TipsPopUpUI::onExit()
{
    BasePopUpUI::onExit();
}

bool TipsPopUpUI::init()
{

    auto size = Director::getInstance()->getVisibleSize();
    float scale = size.width /640.0f;

    ui::ImageView* bgView = ui::ImageView::create("ui_continue_bg.png");
    bgView->setPosition(Vec2(size.width*0.5, size.height*0.45));
    bgView->setScale(scale);
    m_dialogLayer->addChild(bgView);
    if (m_tipType == TIP_GOLD) {
        tipsTv = ui::Text::create(UtilityHelper::getLocalString("GOLD_NOT_ENOUGH"), FONT_FXZS, 30);
    }else if (m_tipType == TIP_HEART)
    {
         tipsTv = ui::Text::create(UtilityHelper::getLocalString("HEART_NOT_ENOUGH"), FONT_FXZS, 30);
    }

    tipsTv->setPosition(Vec2(size.width*0.5, size.height*0.50));
    tipsTv->setScale(scale);
    m_dialogLayer->addChild(tipsTv);
    ui::Button* cancelBtn = ui::Button::create("btn_ok_normal.png","btn_ok_press.png");
    cancelBtn->setPosition(Vec2(size.width*0.38, size.height*0.4));
    
    cancelBtn->setScale(scale);
    cancelBtn->setTitleText(UtilityHelper::getLocalString("CANCEL"));
    cancelBtn->setTitleFontName(FONT_FXZS);
    cancelBtn->setTitleFontSize(18);
    Label* cancelLable = cancelBtn->getTitleRenderer();
    cancelLable->setDimensions(cancelBtn->getContentSize().width*0.3, cancelBtn->getContentSize().height*0.5);
    cancelBtn->addTouchEventListener([=](Ref* sender, cocos2d::ui::Widget::TouchEventType type)
                                     {
                                         if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
                                         {
                                             cancelLable->setScale(1);
                                         }else if(type == cocos2d::ui::Widget::TouchEventType::BEGAN)
                                         {
                                             cancelLable->setScale(0.95);
                                         }
                                     });
    m_dialogLayer->addChild(cancelBtn);
    ui::Button* oKBtn = ui::Button::create("btn_ok_normal.png","btn_ok_press.png");
    oKBtn->setPosition(Vec2(size.width*0.38+cancelBtn->getContentSize().width*scale +5*scale, size.height*0.4));
    
    oKBtn->setScale(scale);
    oKBtn->setTitleText(UtilityHelper::getLocalString("OK"));
    oKBtn->setTitleFontName(FONT_FXZS);
    oKBtn->setTitleFontSize(18);
    Label* okLable = oKBtn->getTitleRenderer();
    okLable->setDimensions(oKBtn->getContentSize().width*0.3, oKBtn->getContentSize().height*0.5);
    oKBtn->addTouchEventListener([=](Ref* sender, cocos2d::ui::Widget::TouchEventType type)
                                   {
                                       if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
                                       {
                                           okLable->setScale(1);
                                       }else if(type == cocos2d::ui::Widget::TouchEventType::BEGAN)
                                       {
                                           okLable->setScale(0.95);
                                       }
                                   });
    m_dialogLayer->addChild(oKBtn);

    oKBtn->addClickEventListener(CC_CALLBACK_1(TipsPopUpUI::onOk, this));
    cancelBtn->addClickEventListener(CC_CALLBACK_1(TipsPopUpUI::onCancel, this));

    return true;
}
void TipsPopUpUI::onOk(Ref* ref)
{
    UIManager::getInstance()->hidePopUp();
    if (m_tipType == TipsType::TIP_HEART) {
        
        UIManager::getInstance()->addPopUp(BasePopUpUI::POPUP_SHOP);
        UIManager::getInstance()->showInfo(true);
        UIManager::getInstance()->showPopUp();
        
    }else if (m_tipType == TipsType::TIP_GOLD)
    {
        
        UIManager::getInstance()->addPopUp(BasePopUpUI::POPUP_SHOP);
        ShopPopUpUI* shopPopUp = static_cast<ShopPopUpUI*>(UIManager::getInstance()->getPopUpUI(BasePopUpUI::POPUP_SHOP));
        if(shopPopUp)
            shopPopUp->setShopDisplay(ShopPopUpUI::SHOP_GOLD);
        UIManager::getInstance()->showPopUp(false);
    }
}
void TipsPopUpUI::onhideEndPopup()
{
    
}
void TipsPopUpUI::onCancel(Ref* ref)
{
    UIManager::getInstance()->hidePopUp();
}
