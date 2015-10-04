//
//  MainUi.cpp
//  Tone_Skipper
//
//  Created by 创李 on 15/9/19.
//
//

#include "MainUi.h"
#include "PopupUILayerManager.h"
#include "RegionSlider.h"
#include "MapMgrs.h"
USING_NS_CC;
using namespace ui;
MainUi::MainUi()
{
    m_pTime             = 0.0f;
    m_pTipsLabel        = nullptr;
    m_pEnergyBar        = nullptr;
    m_pTimeLabel        = nullptr;
    m_pScoreLabel       = nullptr;
    m_pBombLabel        = nullptr;
    m_pDiamondLabel     = nullptr;
    m_pBulletLabel      = nullptr;
    m_pKeyCopperLabel   = nullptr;
    m_pKeyGoldLabel     = nullptr;
    m_pKeySilverLabel   = nullptr;
    
    for (int i =0 ; i<sizeof(m_pHeart)/sizeof(m_pHeart[0]); i++) {
        m_pHeart[i] = nullptr;
    }
}
MainUi::~MainUi()
{
    
}

void MainUi::onEnter()
{
    WrapperUILayer::onEnter();
    cocos2d::Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_MAIN_TIPS, CC_CALLBACK_1(MainUi::onEventTips, this));
}
void MainUi::onExit()
{
    cocos2d::Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_MAIN_TIPS);
    WrapperUILayer::onExit();
}
void MainUi::addEvents()
{
   
    m_pTipsLabel = cocos2d::Label::createWithSystemFont("", DEFAULT_FONT, 13);
    m_pTipsLabel->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
    m_pTipsLabel->setCameraMask((unsigned short)cocos2d::CameraFlag::USER1);
    m_pTipsLabel->setScale(SCREEN_SCALE);
    addChild(m_pTipsLabel);
    
    
    RegionSlider* regionSlider = RegionSlider::create();
    regionSlider->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    regionSlider->setCapInsets(Rect(0, 0, 0, 0));
    regionSlider->setScale(SCREEN_SCALE);
    regionSlider->loadBarTexture("ui_frame_black.png");
    regionSlider->loadSlidBallTextureNormal("ui_frame_black.png");
    regionSlider->loadSlidBallTexturePressed("ui_frame_black.png");
    regionSlider->loadProgressBarTexture("ui_active_green.png");
    regionSlider->setScale9Enabled(true);
    regionSlider->setContentSize(cocos2d::Size(80,16));
    regionSlider->setRotation(-90);
    regionSlider->addEventListener(CC_CALLBACK_2(MainUi::sliderPercentChanged, this));
    regionSlider->setPosition(Vec2(SCREEN_WIDTH*0.8, SCREEN_HEIGHT*0.65));
    m_pRootLayer->addChild(regionSlider);
    
    
    ImageView* frameNiloImg = ImageView::create("ui_frame_yellow.png");
    frameNiloImg->setScale9Enabled(true);
    frameNiloImg->setScale(SCREEN_SCALE);
    frameNiloImg->setPosition(Vec2(SCREEN_WIDTH* 0.05, SCREEN_HEIGHT*0.935));
    m_pRootLayer->addChild(frameNiloImg);
    
    ImageView* niloImg = ImageView::create("ui_red.png");
    niloImg->setPosition(Vec2(SCREEN_WIDTH* 0.05, SCREEN_HEIGHT*0.955));
    niloImg->setScale(SCREEN_SCALE);
    m_pRootLayer->addChild(niloImg);
    
    ImageView* framePudgeImg = ImageView::create("ui_frame_yellow.png");
    framePudgeImg->setScale9Enabled(true);
    framePudgeImg->setScale(SCREEN_SCALE);
    framePudgeImg->setPosition(Vec2(SCREEN_WIDTH* 0.05, SCREEN_HEIGHT*0.935-framePudgeImg->getContentSize().height*SCREEN_SCALE-5*SCREEN_SCALE));
    m_pRootLayer->addChild(framePudgeImg);
    
    ImageView* pudgeImg = ImageView::create("ui_dog.png");
    pudgeImg->setPosition(Vec2(SCREEN_WIDTH* 0.05, SCREEN_HEIGHT*0.935-framePudgeImg->getContentSize().height*SCREEN_SCALE+5*SCREEN_SCALE));
    pudgeImg->setScale(SCREEN_SCALE);
    m_pRootLayer->addChild(pudgeImg);
    
    
    for (int i=0; i< sizeof(m_pHeart)/sizeof(m_pHeart[0]);i++) {
        ImageView* heartImg = ImageView::create("ui_heart.png");
        heartImg->setPosition(Vec2(SCREEN_WIDTH* 0.12+heartImg->getContentSize().width*SCREEN_SCALE*0.6*i, SCREEN_HEIGHT*0.94));
        heartImg->setScale(SCREEN_SCALE);
        m_pRootLayer->addChild(heartImg);
        
        ImageView* hearthollowImg = ImageView::create("ui_heart_hollow.png");
        hearthollowImg->setPosition(Vec2(SCREEN_WIDTH* 0.12+hearthollowImg->getContentSize().width*SCREEN_SCALE*0.6*i, SCREEN_HEIGHT*0.94));
        hearthollowImg->setScale(SCREEN_SCALE);
        m_pRootLayer->addChild(hearthollowImg);
        m_pHeart[i] = heartImg;
    }
    
    ImageView* shadingBar = ImageView::create("ui_active_gray.png");
    shadingBar->setScale9Enabled(true);
    shadingBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    shadingBar->setContentSize(cocos2d::Size(cocos2d::Size(80,15)));
    shadingBar->setPosition(Vec2(SCREEN_WIDTH* 0.1, SCREEN_HEIGHT*0.86));
    shadingBar->setScale(SCREEN_SCALE);
    m_pRootLayer->addChild(shadingBar);
    
    m_pEnergyBar = LoadingBar::create("ui_active_green.png");
    m_pEnergyBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    m_pEnergyBar->setScale9Enabled(true);
    m_pEnergyBar->setContentSize(cocos2d::Size(80,15));
    m_pEnergyBar->setPercent(50);
    m_pEnergyBar->setScale(SCREEN_SCALE);
    m_pEnergyBar->setDirection(cocos2d::ui::LoadingBar::Direction::LEFT);
    m_pEnergyBar->setPosition(Vec2(SCREEN_WIDTH* 0.1, SCREEN_HEIGHT*0.86));
    m_pRootLayer->addChild(m_pEnergyBar);
    
    m_pTimeLabel = Label::createWithSystemFont(StringUtils::format("时间: %02d : %02d",(int)m_pTime/60,(int)m_pTime%60), DEFAULT_FONT, 15);
    m_pTimeLabel->setScale(SCREEN_SCALE);
    m_pTimeLabel->setPosition(Vec2(SCREEN_WIDTH* 0.43, SCREEN_HEIGHT*0.95));
    m_pRootLayer->addChild(m_pTimeLabel);
    
    m_pScoreLabel = Label::createWithSystemFont(StringUtils::format("分数: %d",0), DEFAULT_FONT, 15);
    m_pScoreLabel->setScale(SCREEN_SCALE);
    m_pScoreLabel->setPosition(Vec2(SCREEN_WIDTH* 0.6, SCREEN_HEIGHT*0.95));
    m_pRootLayer->addChild(m_pScoreLabel);
    
    ImageView* bombImg = ImageView::create("ui_bomb.png");
    bombImg->setScale(SCREEN_SCALE);
    bombImg->setPosition(Vec2(SCREEN_WIDTH* 0.37, SCREEN_HEIGHT*0.87));
    m_pRootLayer->addChild(bombImg);
    
    m_pBombLabel = Label::createWithSystemFont(StringUtils::format("x%d",0), DEFAULT_FONT, 12);
    m_pBombLabel->setScale(SCREEN_SCALE);
    m_pBombLabel->setPosition(Vec2(SCREEN_WIDTH* 0.37+bombImg->getContentSize().width*SCREEN_SCALE*0.5+2*SCREEN_SCALE, SCREEN_HEIGHT*0.87));
    m_pRootLayer->addChild(m_pBombLabel);
    
    
    
    ImageView* bulletImg = ImageView::create("ui_bullet.png");
    bulletImg->setScale(SCREEN_SCALE);
    bulletImg->setPosition(Vec2(SCREEN_WIDTH* 0.46, SCREEN_HEIGHT*0.87));
    m_pRootLayer->addChild(bulletImg);
    
    m_pBulletLabel = Label::createWithSystemFont(StringUtils::format("x%d",0), DEFAULT_FONT, 12);
    m_pBulletLabel->setScale(SCREEN_SCALE);
    m_pBulletLabel->setPosition(Vec2(SCREEN_WIDTH* 0.46+bulletImg->getContentSize().width*SCREEN_SCALE*0.5, SCREEN_HEIGHT*0.87));
    m_pRootLayer->addChild(m_pBulletLabel);
    
    
    ImageView* diamondImg = ImageView::create("ui_diamond.png");
    diamondImg->setScale(SCREEN_SCALE);
    diamondImg->setPosition(Vec2(SCREEN_WIDTH* 0.56, SCREEN_HEIGHT*0.865));
    m_pRootLayer->addChild(diamondImg);
    
    m_pDiamondLabel = Label::createWithSystemFont(StringUtils::format("x%d",0), DEFAULT_FONT, 12);
    m_pDiamondLabel->setScale(SCREEN_SCALE);
    m_pDiamondLabel->setPosition(Vec2(SCREEN_WIDTH* 0.56+diamondImg->getContentSize().width*SCREEN_SCALE*0.3+8*SCREEN_SCALE, SCREEN_HEIGHT*0.87));
    m_pRootLayer->addChild(m_pDiamondLabel);

    
    ImageView* keyCopperImg = ImageView::create("ui_key_copper.png");
    keyCopperImg->setScale(SCREEN_SCALE);
    keyCopperImg->setPosition(Vec2(SCREEN_WIDTH* 0.7, SCREEN_HEIGHT*0.95));
    m_pRootLayer->addChild(keyCopperImg);
    
    m_pKeyCopperLabel = Label::createWithSystemFont(StringUtils::format("x%d",0), DEFAULT_FONT, 12);
    m_pKeyCopperLabel->setScale(SCREEN_SCALE);
    m_pKeyCopperLabel->setPosition(Vec2(SCREEN_WIDTH* 0.7+keyCopperImg->getContentSize().width*SCREEN_SCALE*0.3+5*SCREEN_SCALE, SCREEN_HEIGHT*0.95));
    m_pRootLayer->addChild(m_pKeyCopperLabel);
    
    
    ImageView* keyGoldImg = ImageView::create("ui_key_gold..png");
    keyGoldImg->setScale(SCREEN_SCALE);
    keyGoldImg->setPosition(Vec2(SCREEN_WIDTH* 0.77, SCREEN_HEIGHT*0.95));
    m_pRootLayer->addChild(keyGoldImg);
    
    m_pKeyGoldLabel = Label::createWithSystemFont(StringUtils::format("x%d",0), DEFAULT_FONT, 12);
    m_pKeyGoldLabel->setScale(SCREEN_SCALE);
    m_pKeyGoldLabel->setPosition(Vec2(SCREEN_WIDTH* 0.77+keyGoldImg->getContentSize().width*SCREEN_SCALE*0.3+5*SCREEN_SCALE, SCREEN_HEIGHT*0.95));
    m_pRootLayer->addChild(m_pKeyGoldLabel);
    
    
    ImageView* keySilverImg = ImageView::create("ui_key_silver.png");
    keySilverImg->setScale(SCREEN_SCALE);
    keySilverImg->setPosition(Vec2(SCREEN_WIDTH* 0.84, SCREEN_HEIGHT*0.95));
    m_pRootLayer->addChild(keySilverImg);
    
    m_pKeySilverLabel = Label::createWithSystemFont(StringUtils::format("x%d",0), DEFAULT_FONT, 12);
    m_pKeySilverLabel->setScale(SCREEN_SCALE);
    m_pKeySilverLabel->setPosition(Vec2(SCREEN_WIDTH* 0.84+keySilverImg->getContentSize().width*SCREEN_SCALE*0.3+5*SCREEN_SCALE, SCREEN_HEIGHT*0.95));
    m_pRootLayer->addChild(m_pKeySilverLabel);
    
    
    
}
void MainUi::update(float dt)
{
    m_pTime+=dt;
    m_pTimeLabel->setString(StringUtils::format("时间: %02d : %02d",(int)m_pTime/60,(int)m_pTime%60));
}
void MainUi::onEventTips(cocos2d::EventCustom *sender)
{
    if (m_pTipsLabel && m_pTipsLabel->getString().empty()) {
        TipData* tipData = (TipData*)sender->getUserData();
        CCLOG("pos : %f, %f; tips: %s", tipData->m_pPt.x, tipData->m_pPt.y, tipData->m_pDes.c_str());
        m_pTipsLabel->setPosition(tipData->m_pPt);
        m_pTipsLabel->setString(tipData->m_pDes);
        cocos2d::CallFunc* fun1 = cocos2d::CallFunc::create([this](){
            m_pTipsLabel->setString("");
        });
        m_pTipsLabel->runAction(cocos2d::Sequence::createWithTwoActions(cocos2d::DelayTime::create(1.5f), fun1));
    }
    
}
void MainUi::sliderPercentChanged(cocos2d::Ref *sender, cocos2d::ui::Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        RegionSlider* slider = dynamic_cast<RegionSlider*>(sender);
        if (slider) {
            int percent = slider->getPercent();
            float hue = percent/100.0f;
            if (MapMgrs::getInstance()->getNilo()->getHue() !=hue) {
                CCLOG("hue:%f",hue);
                MapMgrs::getInstance()->getNilo()->setHue(hue);
            }
            
        }
        
       
    }
}