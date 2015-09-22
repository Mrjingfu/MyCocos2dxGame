//
//  BagPopUpUi.cpp
//  Tone_Skipper
//
//  Created by 创李 on 15/9/21.
//
//

#include "BagPopUpUi.h"

USING_NS_CC;
using namespace ui;
BagPopUpUi::BagPopUpUi()
{
    
}
BagPopUpUi::~BagPopUpUi()
{
    
}
void BagPopUpUi::addEvents()
{
    cocos2d::ui::Layout* testLayout = cocos2d::ui::Layout::create();
    testLayout->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    testLayout->setBackGroundImage("ui_frame_black.png");
    testLayout->setBackGroundImageScale9Enabled(true);
    testLayout->setContentSize(cocos2d::Size(200,250));
    testLayout->setLayoutType(Layout::Type::RELATIVE);
    testLayout->setScale(SCREEN_SCALE);
    testLayout->setPosition(WINDOW_CENTER);
    getRootPopupLayer()->addChild(testLayout);
    CCLOG("width:%f heigth:%f",testLayout->getContentSize().width,testLayout->getContentSize().height);
    
    Text* titleLabe = Text::create("道具", DEFAULT_FONT, 20);
    titleLabe->setScale(SCREEN_SCALE);
    testLayout->addChild(titleLabe);
    RelativeLayoutParameter* topCenter = RelativeLayoutParameter::create();
    topCenter->setRelativeName("title_rn");
    topCenter->setMargin(Margin(0, 10*SCREEN_SCALE, 0, 0));
    topCenter->setAlign(RelativeLayoutParameter::RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
    titleLabe->setLayoutParameter(topCenter);
    
    ui::ScrollView* scrollView = ui::ScrollView::create();
    scrollView->setContentSize(testLayout->getContentSize());
    scrollView->setPosition(Vec2(testLayout->getContentSize().width/2,testLayout->getContentSize().height/2));
    scrollView->setTouchEnabled(true);
    scrollView->setBounceEnabled(true);
    scrollView->setInnerContainerSize(Size(100,150));
    scrollView->setCameraMask((unsigned short)cocos2d::CameraFlag::DEFAULT);
    
    Layout* scrollLayout = scrollView->getInnerContainer();
    scrollLayout->setCameraMask((unsigned short)cocos2d::CameraFlag::DEFAULT);
    scrollLayout->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
    scrollLayout->setBackGroundColor(Color3B::RED);;

    addChild(scrollView,5);

    
    Button* closeBtn = Button::create("ui_supposed.png");
    closeBtn->addTouchEventListener(CC_CALLBACK_2(BagPopUpUi::onClose, this));
    closeBtn->setScale(SCREEN_SCALE);
    testLayout->addChild(closeBtn);
    RelativeLayoutParameter* topRight = RelativeLayoutParameter::create();
    topRight->setAlign(RelativeLayoutParameter::RelativeAlign::PARENT_TOP_RIGHT);
    closeBtn->setLayoutParameter(topRight);

    
    Layout* cellBgLayer = Layout::create();
    cellBgLayer->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
    cellBgLayer->setBackGroundColor(Color3B(128, 128, 128));;
    cellBgLayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    cellBgLayer->setContentSize(Size(32*5, 32*6));
//  cellBgLayer->setScale(SCREEN_SCALE);
//  testLayout->addChild(cellBgLayer);
    cellBgLayer->setPosition(Vec2(100, 100));
    cellBgLayer->setCameraMask((unsigned short)cocos2d::CameraFlag::DEFAULT);
    scrollView->addChild(cellBgLayer);

//    RelativeLayoutParameter* centerParent = RelativeLayoutParameter::create();
////    centerParent->setRelativeToWidgetName("title_rn");
////    centerParent->setAlign(RelativeLayoutParameter::RelativeAlign::LOCATION_BELOW_CENTER);
//    centerParent->setAlign(RelativeLayoutParameter::RelativeAlign::CENTER_IN_PARENT);
//    cellBgLayer->setLayoutParameter(centerParent);
    
    for (int i =0; i<MAX_ROW; i++) {
        for (int j =0; j<MAX_COL; j++) {
            ImageView* cellBg = ImageView::create("ui_frame_yellow.png");
            cellBg->setScale(SCREEN_SCALE);
            cellBgLayer->addChild(cellBg);
           cellBg->setCameraMask((unsigned short)cocos2d::CameraFlag::DEFAULT);
            cellBg->setPosition(CELL_PT(j, i));
        }
    }
    
    int j = 0;
    int k = MAX_COL;
    for (int i =14; i>=0;i-- ) {
        if (j==0) {
            k--;
        }
        CCLOG("j:%d k:%d",j,k);
        
        ImageView* cellBg = ImageView::create("ui_exclamation.png");
        cellBg->setScale(SCREEN_SCALE);
        cellBgLayer->addChild(cellBg);
        cellBg->setPosition(CELL_PT(k, j));
        j = i%5;
    }
    

}




void BagPopUpUi::onClose(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
    CHECK_ACTION(pSender,type);
    closePopup();
}