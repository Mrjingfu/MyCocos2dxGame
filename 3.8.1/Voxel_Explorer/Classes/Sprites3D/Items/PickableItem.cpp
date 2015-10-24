//
//  PickableItem.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/20.
//
//

#include "PickableItem.hpp"
#include "LevelResourceManager.h"
#include "TerrainTile.hpp"
USING_NS_CC;
const std::string PICKABLE_ITEM_NAMES[] = {
    
    "PIN_KEY_BEGIN",
    "PIN_KEY_COPPER",             ///铜宝箱钥匙
    "PIN_KEY_SILVER",             ///银宝箱钥匙
    "PIN_KEY_GOLD",               ///金宝箱钥匙
    "PIN_KEY_BOSS",               ///BOSS房间钥匙
    "PIN_KEY_ROOM",               ///普通房间钥匙
    "PIN_KEY_END",
    
    "PIN_DAGGER_BEGIN",
    "PIN_DAGGER_DAGGER",           ///匕首
    "PIN_DAGGER_HALFSWORD",        ///短剑
    "PIN_DAGGER_KNIFE",            ///小刀
    "PIN_DAGGER_COLDSTEELDAGGER",  ///冷钢匕首
    "PIN_DAGGER_RIPPERCUTTER",     ///开膛刀
    "PIN_DAGGER_BLUELIGHTDAGGER",  ///蓝光匕首
    "PIN_DAGGER_RUBYDAGGER",       ///红宝石匕首
    "PIN_DAGGER_END",
    
    "PIN_DAGGER_PRO_BEGIN",
    "PIN_DAGGER_PRO_DAGGER",           ///烛光 Candlelight
    "PIN_DAGGER_PRO_HALFSWORD",        ///星耀 Stars Shine
    "PIN_DAGGER_PRO_KNIFE",            ///黄金杀手 Gold Killer
    "PIN_DAGGER_PRO_COLDSTEELDAGGER",  ///影子袭击者 Shadow Attacker
    "PIN_DAGGER_PRO_RIPPERCUTTER",     ///六刃 Six Blade
    "PIN_DAGGER_PRO_BLUELIGHTDAGGER",  ///凝云 Frozen Cloud
    "PIN_DAGGER_PRO_RUBYDAGGER",       ///火舌 Flame
    "PIN_DAGGER_PRO_END",
    
    "PIN_UNKNOWN"
};

PickableItem* PickableItem::create(PickableItemType type)
{
    std::string model = LevelResourceManager::getInstance()->getItemModelRes(PICKABLE_ITEM_NAMES[type]);
    auto item = new (std::nothrow) PickableItem();
    if (item && item->initWithFile(model))
    {
        item->m_Type = type;
        item->setCameraMask((unsigned int)CameraFlag::USER1);
        item->setLightMask((unsigned int)LightFlag::LIGHT0);
        item->setOpacity(0);
        item->autorelease();
        return item;
    }
    CC_SAFE_DELETE(item);
    return nullptr;
}
PickableItem::PickableItem()
{
    m_State = PIS_UNKNOWN;
    m_Type = PIT_UNKNOWN;
}
PickableItem::~PickableItem()
{
}
void PickableItem::setPickableItemState(PickableItemState state)
{
    if(m_State == state)
        return;
    ///处理上一个状态退出逻辑
    switch (m_State) {
        case PickableItem::PIS_IDLE:
            onExitIdle();
            break;
        case PickableItem::PIS_FADEOUT:
            onExitFadeOut();
            break;
        default:
            break;
    }
    m_State = state;
    ///处理下一个状态进入逻辑
    switch (m_State) {
        case PickableItem::PIS_IDLE:
            onEnterIdle();
            break;
        case PickableItem::PIS_FADEOUT:
            onEnterFadeOut();
            break;
        default:
            break;
    }
}

void PickableItem::onEnterIdle()
{
    EaseSineOut* fadeIn = EaseSineOut::create(FadeIn::create(1.0f));
    RotateBy* rotateBy = RotateBy::create(1.0f, 360);
    Spawn* spawn = Spawn::create(fadeIn, rotateBy, nullptr);
    this->runAction(spawn);
}
void PickableItem::onExitIdle()
{
    this->stopAllActions();
}
void PickableItem::onEnterFadeOut()
{
    
    EaseSineOut* moveTo = EaseSineOut::create(MoveTo::create(0.5f, Vec3(getPositionX(), 2*TerrainTile::CONTENT_SCALE, getPositionZ())));
    EaseSineOut* fadeOut = EaseSineOut::create(FadeOut::create(1.0f));
    CallFunc* callback = CallFunc::create(CC_CALLBACK_0(PickableItem::destroySelf, this));
    Sequence* sequence = Sequence::create(moveTo, fadeOut, callback, nullptr);
    RotateBy* rotateBy = RotateBy::create(1.0f, 360);
    Spawn* spawn = Spawn::create(rotateBy, sequence, nullptr);
    this->runAction(spawn);
}
void PickableItem::onExitFadeOut()
{
    this->stopAllActions();
}

void PickableItem::destroySelf()
{
    
    this->removeFromParentAndCleanup(true);
}