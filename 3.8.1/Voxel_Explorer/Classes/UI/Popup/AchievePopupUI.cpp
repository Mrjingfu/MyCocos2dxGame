//
//  ShopPopupUI.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/26.
//
//

#include "AchievePopupUI.h"
#include "UtilityHelper.h"
#include "AchieveMangerLayerUI.h"
#include "AchievementManager.h"
#include "EventConst.h"
AchievePopupUI::AchievePopupUI()
{
    m_cActionType       = eNone;
    m_pAchieveGridView         = nullptr;
    m_pAchieveMangerLayer = nullptr;

}
AchievePopupUI::~AchievePopupUI()
{
    
}
bool AchievePopupUI::initUi()
{
    if (!PopupUILayer::initUi())
        return false;
     return this->load("achievementLayer.csb",false);
   
}
bool AchievePopupUI::addEvents()
{
    cocos2d::ui::ImageView* m_achieveFrame = dynamic_cast<ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "achieve_layer_bg"));
    if (!m_achieveFrame)
        return false;
  
    cocos2d::ui::Text* title = dynamic_cast<ui::Text*>(UtilityHelper::seekNodeByName(m_pRootNode, "achieve_layer_title"));
    if (!title)
        return false;
    title->setFontName(UtilityHelper::getLocalString("FONT_NAME"));
    title->setString(UtilityHelper::getLocalStringForUi("TITLE_ACHIEVE"));

    
    m_pAchieveGridView = TGridView::create();
    m_pAchieveGridView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    m_pAchieveGridView->setContentSize(cocos2d::Size(m_achieveFrame->getContentSize().width,m_achieveFrame->getContentSize().height-25));
    m_pAchieveGridView->setCol(2);
    m_pAchieveGridView->setPosition(cocos2d::Vec2(m_achieveFrame->getContentSize().width*0.5,m_achieveFrame->getContentSize().width*0.44));
    m_pAchieveGridView->setScrollBarWidth(2);
    m_pAchieveGridView->setScrollBarColor(Color3B::WHITE);
    m_pAchieveGridView->setScrollBarPositionFromCorner(cocos2d::Vec2(5,0));
//    m_pShopGridView->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    m_pAchieveGridView->setItemsMargin(cocos2d::Size(3,6));
    m_pAchieveGridView->setFrameMargin(cocos2d::Size(9,2));
//    m_pAchieveGridView->addEventListener(CC_CALLBACK_2(ShopPopupUI::selectItemEvent, this));
    m_pAchieveGridView->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    m_achieveFrame->addChild(m_pAchieveGridView);

    int ItemSize = AchievementManager::getInstance()->getAllAchieves().size();
    
    for (int j =0; j<ItemSize; j++) {
        
        ImageView* itemui = ImageView::create();
        itemui->setTouchEnabled(true);
        itemui->setScale9Enabled(true);
        itemui->setContentSize(cocos2d::Size(130,50));
        itemui->loadTexture("ui_frame_3.png",TextureResType::PLIST);
        itemui->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        m_pAchieveGridView->pushBackCustomItem(itemui);
    }
    m_pAchieveGridView->forceDoLayout();
    
    m_pAchieveMangerLayer = AchieveMangerLayerUI::create(m_pAchieveGridView->getInnerContainerSize());
    m_pAchieveMangerLayer->setPosition(m_pAchieveGridView->getContentSize()*0.5);
    m_pAchieveMangerLayer->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
    m_pAchieveGridView->addChildLayer(m_pAchieveMangerLayer,ItemSize);
    
    
    refreshUIView();
    
    return true;
}
void AchievePopupUI::onEnter()
{
    PopupUILayer::onEnter();
//    Director::getInstance()->getEventDispatcher()->addCustomEventListener(EVENT_NPC_DATA_DIRTY, CC_CALLBACK_1(ShopPopupUI::onEventUpdateNpcData,this));
//    EventListenerCustom *listener = EventListenerCustom::create(EVENT_PLAYER_PROPERTY_DIRTY, CC_CALLBACK_1(ShopPopupUI::onEventUpdateNpcData,this));
//    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
}
void AchievePopupUI::onExit()
{
//    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(EVENT_NPC_DATA_DIRTY);
//    Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
    PopupUILayer::onExit();
}

void AchievePopupUI::refreshUIView()
{
    updateAllAchieves();
 }

void AchievePopupUI::updateAllAchieves()
{
    if (m_pAchieveMangerLayer) {
        m_pAchieveMangerLayer->removeItems();
    }
    
    
    cocos2d::Vector<AchieveProperty*> allAchieves = AchievementManager::getInstance()->getAllAchieves();
    std::sort(allAchieves.begin(), allAchieves.end(), std::less<AchieveProperty*>());
    for (int i=0; i<allAchieves.size(); i++) {
        AchieveProperty* achieveProp = allAchieves.at(i);
        ui::ImageView* itemView = static_cast<ui::ImageView*>(m_pAchieveGridView->getItem(i));
        if (achieveProp && itemView)
        {
            eAchievementDetailType type = achieveProp->getAchieveDetailType();
            std::string icon = achieveProp->getAchieveIcon();
            std::string name = achieveProp->getAchieveName();
            std::string targetDesc = achieveProp->getTargetDesc();
            bool isCommple = achieveProp->isCommple();
            bool isHide = achieveProp->isHideAchieve();
            m_pAchieveMangerLayer->addItemAchieve(type, itemView->getPosition(),icon,name,targetDesc,isHide,isCommple);
        }
    }
}
void AchievePopupUI::updateCommpleAchieves()
{
    
}

