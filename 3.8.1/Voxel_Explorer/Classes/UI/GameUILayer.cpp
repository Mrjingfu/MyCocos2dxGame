//
//  GameUILayer.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/16.
//
//

#include "GameUILayer.h"
#include "UtilityHelper.h"
#include "GameConfig.h"
USING_NS_CC;
GameUILayer::GameUILayer()
{
    
}
GameUILayer::~GameUILayer()
{
    
}
bool GameUILayer::addEvents()
{
    Node* node1 = dynamic_cast<Node*>(UtilityHelper::seekNodeByName(m_pRootNode, "ProjectNode_1"));
    if (!node1)
        return false;
    node1->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    CCLOG("X:%f,Y:%f",node1->getPositionX(),node1->getPositionY());
    CCLOG("ORIGIN_X:%f,ORIGIN_Y:%f",ORIGIN_X,ORIGIN_Y);
    node1->setPosition(Vec2(SCREEN_WIDTH/2, SCREEN_HEIGHT*0.75));
    
    Node* node2 = dynamic_cast<Node*>(UtilityHelper::seekNodeByName(m_pRootNode, "ProjectNode_2"));
    if (!node2)
        return false;
    node2->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    CCLOG("X:%f,Y:%f",node2->getPositionX(),node2->getPositionY());
    CCLOG("ORIGIN_X:%f,ORIGIN_Y:%f",ORIGIN_X,ORIGIN_Y);
    node2->setPosition(Vec2(SCREEN_WIDTH/2, SCREEN_HEIGHT*0.3));
    
    ui::ScrollView* scrollView = ui::ScrollView::create();
    scrollView->setContentSize(cocos2d::Size(280.0f, 100.0f));
    scrollView->setClippingEnabled(true);
    ui::ScrollView* ss = dynamic_cast<ui::ScrollView*>(UtilityHelper::seekNodeByName(node2, "package_scroll"));
    if (!ss) {
        return false;
    }
    ss->setClippingType(ui::ScrollView::ClippingType::SCISSOR);
    ss->setClippingEnabled(true);
    return true;
}