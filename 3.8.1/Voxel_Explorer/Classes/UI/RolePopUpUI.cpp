//
//  RolePopUpUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/22.
//
//

#include "RolePopUpUI.h"
#include "UtilityHelper.h"

USING_NS_CC;
RolePopUpUI::RolePopUpUI()
{
    m_pActionType  = eNone;
    gridView = nullptr;
}
RolePopUpUI::~RolePopUpUI()
{
    
}
bool RolePopUpUI::initUi()
{
    
    Node* charNode = cocos2d::CSLoader::createNode("characterLayer.csb");
    if (!charNode)
        return  false;

    charNode->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    CCLOG("X:%f,Y:%f",charNode->getPositionX(),charNode->getPositionY());
    CCLOG("ORIGIN_X:%f,ORIGIN_Y:%f",ORIGIN_X,ORIGIN_Y);
    charNode->setPosition(Vec2(WND_CENTER_X, SCREEN_HEIGHT*0.7));
    m_pRootLayer->addChild(charNode);
        
    gridView = TGridView::create();
    gridView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    gridView->setContentSize(cocos2d::Size(250,156));
    gridView->setCol(5);
    gridView->setBackGroundImageScale9Enabled(true);
    gridView->setBackGroundImage("ui_frame_3.png",TextureResType::PLIST);
    gridView->setPosition(Vec2(WND_CENTER_X, SCREEN_HEIGHT*0.35));
    gridView->setScrollBarEnabled(false);
    gridView->setItemsMargin(cocos2d::Size(8,11));
    gridView->addEventListener(CC_CALLBACK_2(RolePopUpUI::selectItemEvent, this));
    m_pRootLayer->addChild(gridView);
    
    for (int j =0; j<5*3; j++) {

        ImageView* cellBg = ImageView::create("ui_frame_6.png",TextureResType::PLIST);
        cellBg->setTouchEnabled(true);
        cellBg->setScale9Enabled(true);
        cellBg->setContentSize(cocos2d::Size(40,40));
        gridView->addChild(cellBg);
    }
    
    Button* closeBtn = Button::create("btn_1.png","","",TextureResType::PLIST);
    closeBtn->setScale9Enabled(true);
    closeBtn->setPosition(Vec2(SCREEN_WIDTH*0.93+ORIGIN_X, SCREEN_HEIGHT*0.93+ORIGIN_Y));
    closeBtn->addTouchEventListener(CC_CALLBACK_2(RolePopUpUI::onTouchColse, this));
    m_pRootLayer->addChild(closeBtn);
    
    Button* changeBagBtn = Button::create("btn_1.png","","",TextureResType::PLIST);
    changeBagBtn->setScale9Enabled(true);
    changeBagBtn->setContentSize(cocos2d::Size(60,35));
    changeBagBtn->setPosition(Vec2(SCREEN_WIDTH*0.6+ORIGIN_X, SCREEN_HEIGHT*0.35-gridView->getContentSize().height/2-changeBagBtn->getContentSize().height/2));
    changeBagBtn->addTouchEventListener(CC_CALLBACK_2(RolePopUpUI::onTouchChnageBag, this));
    changeBagBtn->setTitleText("changeBag");
    changeBagBtn->setTitleFontName(DEFAULT_FONT);
    changeBagBtn->setTitleFontSize(10);
    m_pRootLayer->addChild(changeBagBtn);
    return true;
}
void RolePopUpUI::onTouchChnageBag(Ref* ref,cocos2d::ui::Widget::TouchEventType type)
{
    CHECK_ACTION_WRAPPER(ref,type);
    for (int j =0; j<5*3; j++) {
        
        ImageView* cellBg = ImageView::create("ui_frame_6.png",TextureResType::PLIST);
        cellBg->setTouchEnabled(true);
        cellBg->setScale9Enabled(true);
        cellBg->setContentSize(cocos2d::Size(40,40));
        cellBg->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        gridView->pushBackCustomItem(cellBg);
    }
    MessageBox("更新背包成功", "提示");
}
void RolePopUpUI::onTouchColse(Ref* ref,cocos2d::ui::Widget::TouchEventType type)
{
     CHECK_ACTION_WRAPPER(ref,type);
     closePopup();
}
void RolePopUpUI::selectItemEvent(cocos2d::Ref *pSender, TGridView::EventType type)
{
    
    if (type==TGridView::EventType::ON_SELECTED_ITEM_END) {
        TGridView* gridView = static_cast<TGridView*>(pSender);
        CC_UNUSED_PARAM(gridView);
        CCLOG("select child end index = %ld", gridView->getCurSelectedIndex());
    }
    

}