//
//  PromptLayer.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/24.
//
//

#include "PromptLayer.hpp"
#include "VoxelExplorer.h"
PromptLayer::PromptLayer()
{
    m_pActor = nullptr;
    m_bIsAction = false;
}
PromptLayer::~PromptLayer()
{
    
}
PromptLayer* PromptLayer::create(PromptLayer::ePromptType type)
{
    PromptLayer* promptLayer = new (std::nothrow) PromptLayer();
    if (promptLayer && promptLayer->init(type))
    {
        promptLayer->autorelease();
        return promptLayer;
    }
    CC_SAFE_DELETE(promptLayer);
    return nullptr;
}
bool PromptLayer::init(PromptLayer::ePromptType type)
{
    if (!ImageView::init()) {
        return false;
    }
    setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
    switch (type) {
        case PT_CONFUSING:
            loadTexture("ui_question_icon.png",TextureResType::PLIST);
            break;
        case PT_AWAKE:
            loadTexture("ui_excalmatory_icon.png",TextureResType::PLIST);
            break;
    }
    setVisible(false);
    setCameraMask((unsigned int)cocos2d::CameraFlag::USER2);
    return true;
}

void PromptLayer::update(float delta)
{
    if (!m_pActor)
        return;
    float tempTime = 0.0f;
    tempTime+=delta;
    
    cocos2d::Vec3 displayPt = m_pActor->getPosition3D();
    cocos2d::Vec2 pt = VoxelExplorer::getInstance()->getMainCamera()->projectGL(displayPt);
    pt =  cocos2d::Vec2(pt.x, pt.y+m_pActor->getBoundingBox().size.height*3.5);
    setPosition(pt);
    if (!m_bIsAction && tempTime >=0.013) {
        tempTime = 0.0f;
        m_bIsAction = true;
        setVisible(true);
        cocos2d::ScaleTo* scaleToStart = cocos2d::ScaleTo::create(0.35, 1.3);
        cocos2d::ScaleTo* scaleToEnd = cocos2d::ScaleTo::create(0.35, 0.6);
        this->runAction(cocos2d::Sequence::create(scaleToStart,scaleToEnd,scaleToStart,scaleToEnd,cocos2d::RemoveSelf::create(), nil));
    }
    
}
void PromptLayer::onEnter()
{
    ImageView::onEnter();
    scheduleUpdate();
}
void PromptLayer::onExit()
{
    unscheduleUpdate();
    ImageView::onExit();
}
