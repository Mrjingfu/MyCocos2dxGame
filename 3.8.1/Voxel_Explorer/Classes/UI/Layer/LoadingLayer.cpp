//
//  Archivelayer.cpp
//  lichuang
//
//  Created by lichuang on 2016/01/11.
//
//

#include "LoadingLayer.hpp"
#include "UtilityHelper.h"
#include "VoxelExplorer.h"
USING_NS_CC;
LoadingLayer::LoadingLayer()
{
    m_nCamerFlag = cocos2d::CameraFlag::DEFAULT;
}

LoadingLayer::~LoadingLayer()
{
    
}

bool LoadingLayer::initUi()
{
    if (!WrapperUILayer::initUi())
            return false;
    return load("loadingLayer.csb",false);
}
bool LoadingLayer::addEvents()
{
    m_LoadingIcon = dynamic_cast<cocos2d::ui::ImageView*>(UtilityHelper::seekNodeByName(m_pRootNode, "loading_bar"));
    if (!m_LoadingIcon)
        return false;

    loadingGameAction();
    
    return true;
}
void LoadingLayer::loadingGameAction()
{
    EaseSineOut* fadeIn = EaseSineOut::create(FadeIn::create(0.5f));
    
    EaseSineIn* moveUp = EaseSineIn::create(MoveBy::create(0.5,cocos2d::Vec2(0,12)));
    EaseSineIn* moveLeft = EaseSineIn::create(MoveBy::create(0.3,cocos2d::Vec2(-12,0)));
    EaseSineIn* moveRight = EaseSineIn::create(MoveBy::create(0.6,cocos2d::Vec2(15,0)));
    m_LoadingIcon->runAction(RepeatForever::create(Spawn::create(fadeIn, moveUp,moveLeft,moveRight,nullptr)));
}

