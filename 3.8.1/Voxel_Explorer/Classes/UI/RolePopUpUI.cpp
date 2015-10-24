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
    m_pActionType  = eRightCenter;
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
    charNode->setPosition(WINDOW_CENTER);
    m_pRootLayer->addChild(charNode);
    Layout* equipFrame = dynamic_cast<ui::Layout*>(UtilityHelper::seekNodeByName(charNode, "equip_frame"));
    if (!equipFrame)
        return false;
    Layout* gridFrame = dynamic_cast<ui::Layout*>(UtilityHelper::seekNodeByName(charNode, "grid_frame"));
    if (!gridFrame)
        return false;
    
    
    
    m_pWeaponUi = ItemUI::create();
    m_pWeaponUi->setPosition(Vec2(equipFrame->getContentSize().width*0.2, equipFrame->getContentSize().height*0.5));
    equipFrame->addChild(m_pWeaponUi);
    
    m_pArmorUi = ItemUI::create();
    m_pArmorUi->setPosition(Vec2(charNode->getContentSize().width*0.2+m_pWeaponUi->getContentSize().width+10, equipFrame->getContentSize().height*0.5));
    equipFrame->addChild(m_pArmorUi);
    
    m_pOrnament = ItemUI::create();
    m_pOrnament->setPosition(Vec2(charNode->getContentSize().width*0.2+m_pWeaponUi->getContentSize().width*2+20, equipFrame->getContentSize().height*0.5));
    equipFrame->addChild(m_pOrnament);
    
    
    gridView = TGridView::create();
    gridView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    gridView->setContentSize(cocos2d::Size(gridFrame->getContentSize().width-10,132));
    gridView->setCol(5);
    gridView->setPosition(gridFrame->getContentSize()*0.5);
    gridView->setScrollBarEnabled(false);
    gridView->setItemsMargin(cocos2d::Size(1,3.5));
    gridView->setFrameMargin(cocos2d::Size(4,4));
    gridView->addEventListener(CC_CALLBACK_2(RolePopUpUI::selectItemEvent, this));
    gridFrame->addChild(gridView);

    for (int j =0; j<5*3; j++) {

        ItemUI* itemui = ItemUI::create();
        gridView->addChild(itemui);
    }
    
    Button* closeBtn = Button::create("ui_frame_2.png","","",TextureResType::PLIST);
    closeBtn->setScale9Enabled(true);
    closeBtn->setContentSize(cocos2d::Size(30,30));
    closeBtn->setPosition(Vec2(SCREEN_WIDTH*0.9, SCREEN_HEIGHT*0.93));
    closeBtn->addClickEventListener(CC_CALLBACK_1(RolePopUpUI::onClickColse, this));
    m_pRootLayer->addChild(closeBtn);
    
    Button* changeBagBtn = Button::create("ui_frame_2.png","","",TextureResType::PLIST);
    changeBagBtn->setScale9Enabled(true);
    changeBagBtn->setContentSize(cocos2d::Size(60,35));
    changeBagBtn->setPosition(Vec2(charNode->getPositionX(), charNode->getPositionY()- charNode->getContentSize().height/2-changeBagBtn->getContentSize().height/2));
    changeBagBtn->addClickEventListener(CC_CALLBACK_1(RolePopUpUI::onClickChnageBag, this));
    changeBagBtn->setTitleText("changeBag");
    changeBagBtn->setTitleFontName(DEFAULT_FONT);
    changeBagBtn->setTitleFontSize(10);
    m_pRootLayer->addChild(changeBagBtn);
    
    registerCloseCallback([](){
        CCLOG("SDSDSDSD");
    });
    for (int i =0 ; i<15; i++) {
        ItemUI* ss = static_cast<ItemUI*>(gridView->getItem(i));
        ss->addItem("W_Sword001.png");
        m_pItemUis.push_back(Value("W_Sword001.png"));
    }
    
   
    return true;
}
void RolePopUpUI::onClickChnageBag(Ref* ref)
{
    CHECK_ACTION(ref);
    for (int j =0; j<5*3; j++) {
        
        ItemUI* itemui = ItemUI::create();
        itemui->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        gridView->pushBackCustomItem(itemui);
    }
    MessageBox("更新背包成功", "提示");
}
void RolePopUpUI::onClickColse(Ref* ref)
{
    CHECK_ACTION(ref);
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