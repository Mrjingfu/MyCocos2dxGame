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
    m_pActionType = eNone;
    m_pCustomScrollView = nullptr;
    m_pIsScrolling = false;
    m_pRow =2;
    m_pCol = 5;
    m_pCellSize = 34;
}
BagPopUpUi::~BagPopUpUi()
{
    
}
bool BagPopUpUi::initUi()
{
    
    
    cocos2d::ui::Layout* testLayout = cocos2d::ui::Layout::create();
    testLayout->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    testLayout->setBackGroundImage("ui_frame_3.png",TextureResType::PLIST);
    testLayout->setBackGroundImageScale9Enabled(true);
    testLayout->setContentSize(cocos2d::Size(220.0f,100.0f));
    testLayout->setLayoutType(Layout::Type::RELATIVE);

    testLayout->setPosition(WINDOW_CENTER);
    m_pRootLayer->addChild(testLayout);
    CCLOG("width:%f heigth:%f",testLayout->getContentSize().width,testLayout->getContentSize().height);
    
    Text* titleLabe = Text::create("道具", DEFAULT_FONT, 20);
    testLayout->addChild(titleLabe);
    RelativeLayoutParameter* topCenter = RelativeLayoutParameter::create();
    topCenter->setRelativeName("title_rn");
    topCenter->setMargin(Margin(0, 10*SCREEN_SCALE, 0, 0));
    topCenter->setAlign(RelativeLayoutParameter::RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
    titleLabe->setLayoutParameter(topCenter);
    
    

    
    m_pCustomScrollView = cocos2d::ui::ScrollView::create();
    m_pCustomScrollView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    m_pCustomScrollView->jumpToTop();
    m_pCustomScrollView->setContentSize(cocos2d::Size(220.0f, 100.0f));
    m_pCustomScrollView->setPosition(WINDOW_CENTER);
    m_pCustomScrollView->setScrollBarEnabled(false);
//    m_pCustomScrollView->setTouchEnabled(true);
    m_pCustomScrollView->setInnerContainerSize(cocos2d::Size(220.0f,m_pCellSize*m_pRow+(m_pRow-1)*10+16));
//    m_pCustomScrollView->setSwallowTouches(false);
//    m_pCustomScrollView->addEventListener(CC_CALLBACK_2(BagPopUpUi::onScrollEvent, this));
    
//    Layout* scrollLayout = m_pCustomScrollView->getInnerContainer();
//    scrollLayout->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
//    scrollLayout->setBackGroundColor(Color3B::RED);;
    


    
    initItems();
    initBackground();
    testLayout->addChild(m_pCustomScrollView);
    
    Button* closeBtn = Button::create("btn_1.png","","",TextureResType::PLIST);
    closeBtn->addTouchEventListener(CC_CALLBACK_2(BagPopUpUi::onClose, this));
    testLayout->addChild(closeBtn);
    RelativeLayoutParameter* topRight = RelativeLayoutParameter::create();
    topRight->setAlign(RelativeLayoutParameter::RelativeAlign::PARENT_TOP_RIGHT);
    closeBtn->setLayoutParameter(topRight);
    
    
    Button* testBtn = Button::create("btn_1.png","","",TextureResType::PLIST);
    testBtn->addClickEventListener([this](Ref* ref)
                                   {
                                       updateItemRow(1);
                                   });
    testLayout->addChild(testBtn);
    RelativeLayoutParameter* topleft = RelativeLayoutParameter::create();
    topleft->setAlign(RelativeLayoutParameter::RelativeAlign::PARENT_TOP_LEFT);
    testBtn->setLayoutParameter(topleft);
    
//    auto listener = EventListenerTouchOneByOne::create();
//    listener->setSwallowTouches(true);
//    listener->onTouchBegan =  CC_CALLBACK_2(BagPopUpUi::onTouchBegan, this);
//    listener->onTouchEnded = CC_CALLBACK_2(BagPopUpUi::onTouchEnded,this);
//    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
 
    return true;
}
void BagPopUpUi::onScrollEvent(cocos2d::Ref *, cocos2d::ui::ScrollView::EventType eventType)
{
    if (eventType == cocos2d::ui::ScrollView::EventType::SCROLLING)
    {
        m_pIsScrolling = true;
    }
}
bool BagPopUpUi::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    
//   m_pTouch =touch->getLocation();
//    Layout* scrollLayout = m_pCustomScrollView->getInnerContainer();
//    Vec2 toSpt =scrollLayout->convertToNodeSpace(m_pTouch);
//    CCLOG("toSpt x:%f y:%f",toSpt.x,toSpt.y);
//    for (int i=0; i<testImgs.size(); i++) {
//        ImageView* img = testImgs.at(i);
//        Vec2 imgPt = img->getPosition();
//         cocos2d::Rect rect =  cocos2d::Rect(imgPt.x-(m_pCellSize*SCREEN_SCALE)/2, imgPt.y-(m_pCellSize*SCREEN_SCALE)/2, m_pCellSize*SCREEN_SCALE, m_pCellSize*SCREEN_SCALE);
//        if (rect.containsPoint(toSpt)) {
//            CCLOG("npo inde:%d ",i);
//        }
//    }

    return true;
}

void BagPopUpUi::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    
    Vec2 touchEnd = touch->getLocation();
//    if (abs(m_pTouch.x - touchEnd.x) >2 || abs(m_pTouch.y - touchEnd.y) >2) {
//        return;
//    }
    
    
}

Vec2 BagPopUpUi::getItemVec(int col, int row)
{
    
   return  cocos2d::Vec2(row*m_pCellSize+m_pCellSize/2+20+(row-1)*5,m_pCustomScrollView->getInnerContainerSize().height-(col*m_pCellSize+m_pCellSize/2+(col-1)*8+24));
}

void BagPopUpUi::initBackground()
{
    if (m_pCustomScrollView) {
        for (int i =m_pRow-1; i>=0; i--) {
            for (int j =0; j<m_pCol; j++) {
                ImageView* cellBg = ImageView::create("ui_frame_6.png",TextureResType::PLIST);
                cellBg->setScale9Enabled(true);
                cellBg->setContentSize(cocos2d::Size(m_pCellSize,m_pCellSize));
                Vec2 itemVec = getItemVec(i, j);
                cellBg->setPosition(itemVec);
                m_pCustomScrollView->addChild(cellBg);
                testImgs.pushBack(cellBg);
                
                
            }
        }
    }
}
void BagPopUpUi::initItems()
{
    if (m_pCustomScrollView) {
        int col = 0;
        int row = 0;
        for (int i =0; i<col*row;i++ ) {
            col = i%5;
            row = m_pRow-i/5-1;
            CCLOG("col:%d row:%d",col,row);
            Text* tx = Text::create(Value(i).asString(), DEFAULT_FONT, 20);
//            tx->setCameraMask((unsigned short)cocos2d::CameraFlag::USER3);
            tx->setScale(SCREEN_SCALE);
            Vec2 itemVec = getItemVec(row,col);
            m_pCustomScrollView->addChild(tx);
            tx->setPosition(itemVec);
            
        }

    }
}

void BagPopUpUi::updateItemRow(int row)
{
    m_pRow = m_pRow+row;
    if (m_pCustomScrollView) {
        m_pCustomScrollView->setInnerContainerSize( cocos2d::Size(220.0f,m_pCellSize*m_pRow+(m_pRow-1)*10+16));
        for (ImageView* img:testImgs) {
            img->removeFromParentAndCleanup(true);
        }
        testImgs.clear();
        initBackground();
        m_pCustomScrollView->jumpToTop();
//        m_pCustomScrollView->forceDoLayout();

    }
}
void BagPopUpUi::onClose(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
    CHECK_ACTION(pSender,type);
    closePopup();
}