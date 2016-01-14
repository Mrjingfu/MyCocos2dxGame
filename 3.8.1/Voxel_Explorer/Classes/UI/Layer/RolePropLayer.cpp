//
//  RolePropLayer.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/27.
//
//

#include "RolePropLayer.hpp"
#include "PlayerProperty.hpp"
#include "TGridView.h"
#include "GameFormula.hpp"
#include "PopupUILayerManager.h"
USING_NS_CC;
RolePropLayer::RolePropLayer()
{
    
}
RolePropLayer::~RolePropLayer()
{
    
}
bool RolePropLayer::addEvents()
{
    if (!CharacterPropLayer::addEvents())
        return false;
    
    m_pCharacterIcon->loadTexture("chr_sword.png",TextureResType::PLIST);
    m_pCharacterIconFrame->setTouchEnabled(true);
    m_pCharacterIconFrame->addClickEventListener(CC_CALLBACK_1(RolePropLayer::onClickRole, this));
    return true;
}
void RolePropLayer::onClickRole(cocos2d::Ref *ref)
{
    CHECK_ACTION(ref);
    clickEffect();
    PopupUILayerManager::getInstance()->openPopup(ePopupRole);
}
void RolePropLayer::updateCharacterBuff()
{
    if (!m_pCharacterBufferList->getItems().empty()) {
        m_pCharacterBufferList->removeAllChildren();
    }
    
    int flag = PlayerProperty::getInstance()->getPlayerBuffer();
    if ((flag&PB_SPEEDUP) == PB_SPEEDUP) {
        ui::ImageView* buffim = ui::ImageView::create("ui_buffer_speedup.png",TextureResType::PLIST);
        buffim->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        m_pCharacterBufferList->pushBackCustomItem(buffim);
    }
    if ((flag&PB_STEALTH) == PB_STEALTH)
    {
        ui::ImageView* buffim = ui::ImageView::create("ui_buffer_stealth.png",TextureResType::PLIST);
        buffim->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        m_pCharacterBufferList->pushBackCustomItem(buffim);
    }
    if ((flag&PB_STRONGER) == PB_STRONGER)
    {
        ui::ImageView* buffim = ui::ImageView::create("ui_buffer_stronger.png",TextureResType::PLIST);
        buffim->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        m_pCharacterBufferList->pushBackCustomItem(buffim);
    }
    if ((flag&PB_POISONING) == PB_POISONING)
    {
        ui::ImageView* buffim = ui::ImageView::create("ui_buffer_poisoning.png",TextureResType::PLIST);
        buffim->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        m_pCharacterBufferList->pushBackCustomItem(buffim);
    }
    if ((flag&PB_FROZEN) == PB_FROZEN)
    {
        ui::ImageView* buffim = ui::ImageView::create("ui_buffer_frozen.png",TextureResType::PLIST);
        buffim->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        m_pCharacterBufferList->pushBackCustomItem(buffim);
    }
    if ((flag&PB_PARALYTIC) == PB_PARALYTIC)
    {
        ui::ImageView* buffim = ui::ImageView::create("ui_buffer_paralytic.png",TextureResType::PLIST);
        buffim->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        m_pCharacterBufferList->pushBackCustomItem(buffim);
    }
    if ((flag&PB_WEAK) == PB_WEAK)
    {
        ui::ImageView* buffim = ui::ImageView::create("ui_buffer_weak.png",TextureResType::PLIST);
        buffim->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        m_pCharacterBufferList->pushBackCustomItem(buffim);
    }
    if ((flag&PB_FIRE) == PB_FIRE)
    {
        ui::ImageView* buffim = ui::ImageView::create("ui_buffer_fire.png",TextureResType::PLIST);
        buffim->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        m_pCharacterBufferList->pushBackCustomItem(buffim);
    }
    if ((flag&PB_BLOCKRATEUP) == PB_BLOCKRATEUP)
    {
        ui::ImageView* buffim = ui::ImageView::create("ui_buffer_block.png",TextureResType::PLIST);
        buffim->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
        m_pCharacterBufferList->pushBackCustomItem(buffim);
    }

}

void RolePropLayer::updateCharacterProp()
{
    float hpPer =PlayerProperty::getInstance()->getCurrentHP().GetFloatValue()/PlayerProperty::getInstance()->getMaxHP().GetFloatValue() *100.0f;
    float mpPer =PlayerProperty::getInstance()->getCurrentMP().GetFloatValue()/PlayerProperty::getInstance()->getMaxMP().GetFloatValue() *100.0f;
    CCLOG("hpPer:%f mpPer:%f",hpPer,mpPer);
    m_pCharacterMpBar->setPercent(mpPer);
    m_pCharacterHpBar->setPercent(hpPer);
    m_pCharacterName->setString("");//角色名
    m_pCharacterCurHp->setString(Value(int(PlayerProperty::getInstance()->getCurrentHP())).asString());
    m_pCharacterMaxHp->setString(StringUtils::format("/%d",int(PlayerProperty::getInstance()->getMaxHP())));
    m_pCharacterCurMp->setString(Value(int(PlayerProperty::getInstance()->getCurrentMP())).asString());
    m_pCharacterMaxMp->setString(StringUtils::format("/%d",int(PlayerProperty::getInstance()->getMaxMP())));
    m_pCharacterLevel->setString(Value(int(PlayerProperty::getInstance()->getLevel())).asString());

}