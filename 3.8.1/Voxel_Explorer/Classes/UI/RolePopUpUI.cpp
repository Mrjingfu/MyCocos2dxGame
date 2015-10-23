//
//  RolePopUpUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/22.
//
//

#include "RolePopUpUI.h"
#include "ItemUI.h"
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
    charNode->setPosition(Vec2(WND_CENTER_X, SCREEN_HEIGHT*0.6+ORIGIN_Y));
    m_pRootLayer->addChild(charNode);
    
    
    m_pWeaponUi = ItemUI::create();
    m_pWeaponUi->setPosition(Vec2(charNode->getContentSize().width*0.15+ORIGIN_X, charNode->getContentSize().height*0.4+ORIGIN_Y));
    charNode->addChild(m_pWeaponUi);
    
    m_pArmorUi = ItemUI::create();
    m_pArmorUi->setPosition(Vec2(charNode->getContentSize().width*0.15+ORIGIN_X+m_pWeaponUi->getContentSize().width+10, charNode->getContentSize().height*0.4+ORIGIN_Y));
    charNode->addChild(m_pArmorUi);
    
    m_pOrnament = ItemUI::create();
    m_pOrnament->setPosition(Vec2(charNode->getContentSize().width*0.15+ORIGIN_X+m_pWeaponUi->getContentSize().width*2+20, charNode->getContentSize().height*0.4+ORIGIN_Y));
    charNode->addChild(m_pOrnament);
    
    cocos2d::ui::ImageView* gridImage = ui::ImageView::create("ui_frame_3.png",TextureResType::PLIST);
    gridImage->setScale9Enabled(true);
    gridImage->setPosition(Vec2(WND_CENTER_X, SCREEN_HEIGHT*0.35));
    gridImage->setContentSize(cocos2d::Size(charNode->getContentSize().width,140));
    m_pRootLayer->addChild(gridImage);

    
    gridView = TGridView::create();
    gridView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    gridView->setContentSize(cocos2d::Size(charNode->getContentSize().width-10,132));
    gridView->setCol(5);
    gridView->setPosition(gridImage->getContentSize()*0.5);
    gridView->setScrollBarEnabled(false);
    gridView->setItemsMargin(cocos2d::Size(1,3.5));
    gridView->setFrameMargin(cocos2d::Size(4,4));
    gridView->addEventListener(CC_CALLBACK_2(RolePopUpUI::selectItemEvent, this));
    gridImage->addChild(gridView);

    for (int j =0; j<5*3; j++) {

        ItemUI* itemui = ItemUI::create();
        gridView->addChild(itemui);
    }
    
    Button* closeBtn = Button::create("ui_frame_2.png","","",TextureResType::PLIST);
    closeBtn->setScale9Enabled(true);
    closeBtn->setContentSize(cocos2d::Size(30,30));
    closeBtn->setPosition(Vec2(SCREEN_WIDTH*0.9+ORIGIN_X, SCREEN_HEIGHT*0.93+ORIGIN_Y));
    closeBtn->addTouchEventListener(CC_CALLBACK_2(RolePopUpUI::onTouchColse, this));
    m_pRootLayer->addChild(closeBtn);
    
    Button* changeBagBtn = Button::create("ui_frame_2.png","","",TextureResType::PLIST);
    changeBagBtn->setScale9Enabled(true);
    changeBagBtn->setContentSize(cocos2d::Size(60,35));
    changeBagBtn->setPosition(Vec2(SCREEN_WIDTH*0.6+ORIGIN_X, SCREEN_HEIGHT*0.35-gridImage->getContentSize().height/2-changeBagBtn->getContentSize().height/2-ORIGIN_Y/2));
    changeBagBtn->addTouchEventListener(CC_CALLBACK_2(RolePopUpUI::onTouchChnageBag, this));
    changeBagBtn->setTitleText("changeBag");
    changeBagBtn->setTitleFontName(DEFAULT_FONT);
    changeBagBtn->setTitleFontSize(10);
    m_pRootLayer->addChild(changeBagBtn);
    
    
    for (int i =0 ; i<15; i++) {
        ItemUI* ss = static_cast<ItemUI*>(gridView->getItem(i));
        ss->addItem("W_Sword001.png");
        m_pItemUis.push_back(Value("W_Sword001.png"));
    }
    
   
    return true;
}
void RolePopUpUI::onTouchChnageBag(Ref* ref,cocos2d::ui::Widget::TouchEventType type)
{
    CHECK_ACTION_WRAPPER(ref,type);
    for (int j =0; j<5*3; j++) {
        
        ItemUI* itemui = ItemUI::create();
        itemui->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        gridView->pushBackCustomItem(itemui);
    }
    MessageBox("更新背包成功", "提示");
}
void RolePopUpUI::onTouchColse(Ref* ref,cocos2d::ui::Widget::TouchEventType type)
{
     CHECK_ACTION_WRAPPER(ref,type);
     closePopup();
}

void RolePopUpUI::updateItems()
{
    int size =gridView->getItems().size();
    for (int i =0 ; i<size; i++) {
        ItemUI* curitemui =static_cast<ItemUI*>(gridView->getItem(i));
        if (curitemui) {
            curitemui->removeItem();
        }
    }
    for (int i =0; i<m_pItemUis.size(); i++) {
        std::string curitemui = m_pItemUis.at(i).asString();
        ItemUI* ss = static_cast<ItemUI*>(gridView->getItem(i));
        if (ss) {
            ss->addItem(curitemui);
        }
        
    }
}
void RolePopUpUI::selectItemEvent(cocos2d::Ref *pSender, TGridView::EventType type)
{
    
    if (type==TGridView::EventType::ON_SELECTED_ITEM_END) {
        TGridView* gridView = static_cast<TGridView*>(pSender);
        CC_UNUSED_PARAM(gridView);
        ItemUI* currentItem = static_cast<ItemUI*>(gridView->getItem(gridView->getCurSelectedIndex()));
        if (currentItem && currentItem->isHaveItem()) {
            currentItem->removeItem();
            auto it = std::next( m_pItemUis.begin(), gridView->getCurSelectedIndex() );
            m_pItemUis.erase(it);
            updateItems();
            CCLOG("select child end index = %ld", gridView->getCurSelectedIndex());
        }
        
    }
    

}