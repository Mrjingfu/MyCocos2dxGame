//
//  UseableItem.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/24.
//
//

#include "UseableItem.hpp"
#include "LevelResourceManager.h"
#include "BaseLevel.h"
#include "AlisaMethod.h"
USING_NS_CC;
const std::string USEABLE_ITEM_NAMES[] = {
    
    //UIN_CHEST_BEGIN
    "UIN_CHEST_COPPER",             ///铜宝箱
    "UIN_CHEST_SILVER",             ///银宝箱
    "UIN_CHEST_GOLD",               ///金宝箱
    //UIN_CHEST_END
    
    //UIN_JAR_BEGIN
    "UIN_JAR_1",                    ///罐子1
    "UIN_JAR_2",                    ///罐子2
    "UIN_JAR_3",                    ///罐子3
    //UIN_JAR_END
    
    "UIN_UNKNOWN"
};
UseableItem* UseableItem::create(UseableItemType type)
{
    std::string model = LevelResourceManager::getInstance()->getItemModelRes(USEABLE_ITEM_NAMES[type]);
    auto item = new (std::nothrow) UseableItem();
    if (item && item->initWithFile(model))
    {
        item->m_Type = type;
        item->setCameraMask((unsigned int)CameraFlag::USER1);
        item->setLightMask((unsigned int)LightFlag::LIGHT0);
        item->setCascadeOpacityEnabled(true);
        item->autorelease();
        return item;
    }
    CC_SAFE_DELETE(item);
    return nullptr;
}
UseableItem::UseableItem()
{
    m_State = UIS_UNKNOWN;
    m_Type = UIT_UNKNOWN;
}
UseableItem::~UseableItem()
{
}
void UseableItem::setState(UseableItemState state)
{
    if(m_State == state)
        return;
    ///处理上一个状态退出逻辑
    switch (m_State) {
        case UseableItem::UIS_IDLE:
            onExitIdle();
            break;
        case UseableItem::UIS_FADEOUT:
            onExitFadeOut();
            break;
            break;
        default:
            break;
    }
    m_State = state;
    ///处理下一个状态进入逻辑
    switch (m_State) {
        case UseableItem::UIS_IDLE:
            onEnterIdle();
            break;
        case UseableItem::UIS_FADEOUT:
            onEnterFadeOut();
            break;
        default:
            break;
    }
}
void UseableItem::setActorDir( ActorDir dir )
{
    if(m_dir == dir)
        return;
    m_dir = dir;
    switch (m_dir) {
        case AD_FORWARD:
            setRotation3D(Vec3(0,180,0));
            break;
        case AD_LEFT:
            setRotation3D(Vec3(0,-90,0));
            break;
        case AD_RIGHT:
            setRotation3D(Vec3(0,90,0));
            break;
        case AD_BACK:
            setRotation3D(Vec3(0,0,0));
            break;
        default:
            break;
    }
}
void UseableItem::onEnterIdle()
{
    addTerrainTileFlag(TileInfo::USEABLE);
}
void UseableItem::onExitIdle()
{
}

void UseableItem::onEnterFadeOut()
{
    removeTerrainTileFlag(TileInfo::USEABLE);
    EaseSineOut* fadeOut = EaseSineOut::create(FadeOut::create(1.0f));
    CallFunc* callback = CallFunc::create(CC_CALLBACK_0(UseableItem::destroySelf, this));
    Sequence* sequence = Sequence::create(fadeOut, callback, nullptr);
    this->runAction(sequence);
}
void UseableItem::onExitFadeOut()
{
}
void UseableItem::destroySelf()
{
    this->removeFromParentAndCleanup(true);
}