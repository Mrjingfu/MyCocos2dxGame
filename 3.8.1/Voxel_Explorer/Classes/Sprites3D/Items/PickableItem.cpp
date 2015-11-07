//
//  PickableItem.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/20.
//
//

#include "PickableItem.hpp"
#include "LevelResourceManager.h"
#include "BaseLevel.h"
USING_NS_CC;
const std::string PICKABLE_ITEM_NAMES[] = {
    
    //PIN_KEY_BEGIN
    "PIN_KEY_COPPER",             ///铜宝箱钥匙
    "PIN_KEY_SILVER",             ///银宝箱钥匙
    "PIN_KEY_GOLD",               ///金宝箱钥匙
    "PIN_KEY_BOSS",               ///BOSS房间钥匙
    "PIN_KEY_ROOM",               ///普通房间钥匙
    //PIN_KEY_END
    
    //PIN_DAGGER_BEGIN
    "PIN_DAGGER_DAGGER",           ///匕首
    "PIN_DAGGER_HALFSWORD",        ///短剑
    "PIN_DAGGER_KNIFE",            ///小刀
    "PIN_DAGGER_COLDSTEELDAGGER",  ///冷钢匕首
    "PIN_DAGGER_RIPPERCUTTER",     ///开膛刀
    "PIN_DAGGER_BLUELIGHTDAGGER",  ///蓝光匕首
    "PIN_DAGGER_RUBYDAGGER",       ///红宝石匕首
    //PIN_DAGGER_END
    
    //PIN_DAGGER_PRO_BEGIN
    "PIN_DAGGER_PRO_DAGGER",           ///烛光 Candlelight
    "PIN_DAGGER_PRO_HALFSWORD",        ///星耀 Stars Shine
    "PIN_DAGGER_PRO_KNIFE",            ///黄金杀手 Gold Killer
    "PIN_DAGGER_PRO_COLDSTEELDAGGER",  ///影子袭击者 Shadow Attacker
    "PIN_DAGGER_PRO_RIPPERCUTTER",     ///六刃 Six Blade
    "PIN_DAGGER_PRO_BLUELIGHTDAGGER",  ///凝云 Frozen Cloud
    "PIN_DAGGER_PRO_RUBYDAGGER",       ///火舌 Fireflow
    //PIN_DAGGER_PRO_END
    
    //PIN_AXE_BEGIN
    "PIN_AXE_HATCHET",            ///小斧
    "PIN_AXE_ADZE",               ///手斧
    "PIN_AXE_STONEAXE",           ///石斧
    "PIN_AXE_BROADAX",            ///大斧
    "PIN_AXE_TOMAHAWK",           ///战斧
    "PIN_AXE_HUGEAXE",            ///巨斧
    "PIN_AXE_DOUBLEBITAX",        ///双刃斧 double-bit ax
    //PIN_AXE_END
    
    //PIN_AXE_PRO_BEGIN
    "PIN_AXE_PRO_HATCHET",            ///黑铁 Dark Iron
    "PIN_AXE_PRO_ADZE",               ///半月 Half Moon
    "PIN_AXE_PRO_STONEAXE",           ///回旋加速器 Cyclotron
    "PIN_AXE_PRO_BROADAX",            ///熔岩 Molten lava
    "PIN_AXE_PRO_TOMAHAWK",           ///狂战士 Berserker
    "PIN_AXE_PRO_HUGEAXE",            ///骷髅撕裂者 Skull Splitter
    "PIN_AXE_PRO_DOUBLEBITAX",        ///脑袋 Brainhew
    //PIN_AXE_PRO_END
    
    //PIN_SWORD_BEGIN
    "PIN_SWORD_SWORD",                ///练习剑
    "PIN_SWORD_STEELSWORD",           ///长钢剑
    "PIN_SWORD_SABRE",                ///军刀
    "PIN_SWORD_HUGESWORD",            ///巨剑
    "PIN_SWORD_TRIANGLESWORD",        ///三角剑
    "PIN_SWORD_JAGGEDSWORD",          ///锯齿剑
    "PIN_SWORD_CRYSTALSWORD",         ///水晶剑
    //PIN_SWORD_END
    
    //PIN_SWORD_PRO_BEGIN
    "PIN_SWORD_PRO_SWORD",                ///红莲 Red Lotus
    "PIN_SWORD_PRO_STEELSWORD",           ///一闪 Flash
    "PIN_SWORD_PRO_SABRE",                ///劈风者 Wind Strike
    "PIN_SWORD_PRO_HUGESWORD",            ///阳炎 Solar Flame
    "PIN_SWORD_PRO_TRIANGLESWORD",        ///血之使者 Bloodletters
    "PIN_SWORD_PRO_JAGGEDSWORD",          ///锐齿 Sawtooth
    "PIN_SWORD_PRO_CRYSTALSWORD",         ///诛神 No God
    //PIN_SWORD_PRO_END
    
    //PIN_MACE_BEGIN
    "PIN_MACE_ROLLINGPIN",                ///擀面杖
    "PIN_MACE_MALLET",                    ///木棒
    "PIN_MACE_MACE",                      ///权杖
    "PIN_MACE_HAMMER",                    ///钉头锤
    "PIN_MACE_WOLFFANGSMACE",             ///狼牙棒
    "PIN_MACE_BONEHAMMER",                ///骨锤
    "PIN_MACE_SLEDGEHAMMER",              ///碎骨大锤
    //PIN_MACE_END
    
    //PIN_MACE_PRO_BEGIN
    "PIN_MACE_PRO_ROLLINGPIN",                ///恐龙骨棒 Dinosaur bone
    "PIN_MACE_PRO_MALLET",                    ///食人魔之锤 The hammer of ogre
    "PIN_MACE_PRO_MACE",                      ///红宝石权杖 Ruby Mace
    "PIN_MACE_PRO_HAMMER",                    ///黄金荣耀 Golden glory
    "PIN_MACE_PRO_WOLFFANGSMACE",             ///众神之锤 Mace of the gods
    "PIN_MACE_PRO_BONEHAMMER",                ///蓝宝石权杖Sapphire Mace
    "PIN_MACE_PRO_SLEDGEHAMMER",              ///死神之力 Azrael Power
    //PIN_MACE_PRO_END
    
    //PIN_BOW_BEGIN
    "PIN_BOW_SHORTBOW",                   ///短弓
    "PIN_BOW_LONGBOW",                    ///长弓
    "PIN_BOW_HORNBOW",                    ///角弓
    "PIN_BOW_REFLEXBOW",                  ///反曲弓
    "PIN_BOW_EAGLEBOW",                   ///鹰弓
    "PIN_BOW_LAMINATEDBOW",               ///复合弓
    "PIN_BOW_GOLDENBOW",                  ///黄金弓
    //PIN_BOW_END
    
    //PIN_BOW_PRO_BEGIN
    "PIN_BOW_PRO_SHORTBOW",                   ///蝎尾 Scorpion tail
    "PIN_BOW_PRO_LONGBOW",                    ///六面火 Hexfire
    "PIN_BOW_PRO_HORNBOW",                    ///要你命三千 Life Terminator
    "PIN_BOW_PRO_REFLEXBOW",                  ///影袭 Shadow Impact
    "PIN_BOW_PRO_EAGLEBOW",                   ///鹰眼 Hawkeye
    "PIN_BOW_PRO_LAMINATEDBOW",               ///绿帽 Green Hat
    "PIN_BOW_PRO_GOLDENBOW",                  ///群星陨落 Starsfall
    //PIN_BOW_PRO_END
    
    //PIN_STAFF_BEGIN
    "PIN_STAFF_OAKSTAFF",                   ///橡木法杖
    "PIN_STAFF_FIRSTAFF",                   ///冷杉法杖
    "PIN_STAFF_ASHESSTAFF",                 ///灰烬法杖
    "PIN_STAFF_DEMONSTAFF",                 ///恶魔法杖
    "PIN_STAFF_CITRONSTAFF",                ///枸木法杖
    "PIN_STAFF_CLOUDSTAFF",                 ///流云法杖
    "PIN_STAFF_MONKSTAFF",                  ///武僧之杖
    //PIN_STAFF_END
    
    //PIN_STAFF_PRO_BEGIN
    "PIN_STAFF_PRO_OAKSTAFF",                   ///绿玉 Emerald
    "PIN_STAFF_PRO_FIRSTAFF",                   ///启明星 Venus
    "PIN_STAFF_PRO_ASHESSTAFF",                 ///地狱之吻 Cerebus' Bite
    "PIN_STAFF_PRO_DEMONSTAFF",                 ///招魂者 Exorcist
    "PIN_STAFF_PRO_CITRONSTAFF",                ///英普瑞斯之矛 The Prius Spear
    "PIN_STAFF_PRO_CLOUDSTAFF",                 ///鲜血勇气 Blood courage
    "PIN_STAFF_PRO_MONKSTAFF",                  ///大天使 Archangel
    //PIN_STAFF_PRO_END
    
    //PIN_SHIELD_BEGIN
    "PIN_SHIELD_WOODENSHIELD",               ///圆木盾
    "PIN_SHIELD_TRIANGLESHIELD",             ///三角盾
    "PIN_SHIELD_STEELSHIELD",                ///精钢盾
    "PIN_SHIELD_EAGLESHIELD",                ///鹰盾
    "PIN_SHIELD_OSTEOSCUTE",                 ///骨盾
    "PIN_SHIELD_GOLDENSHIELD",               ///黄金盾
    "PIN_SHIELD_TOWERSHIELD",                 ///塔盾
    //PIN_SHIELD_END
    
    //PIN_SHIELD_PRO_BEGIN
    "PIN_SHIELD_PRO_WOODENSHIELD",               ///黑暗防御者 Dark defender
    "PIN_SHIELD_PRO_TRIANGLESHIELD",             ///鬼脸 Grimace
    "PIN_SHIELD_PRO_STEELSHIELD",                ///守夜人 The night watchman
    "PIN_SHIELD_PRO_EAGLESHIELD",                ///绿魔 Green Goblin
    "PIN_SHIELD_PRO_OSTEOSCUTE",                 ///骷髅王的身躯 Skeleton King's body
    "PIN_SHIELD_PRO_GOLDENSHIELD",               ///美杜莎的镜子 Medusa's mirror
    "PIN_SHIELD_PRO_TOWERSHIELD",                ///叹息之墙 Wall of sighs
    //PIN_SHIELD_PRO_END
    
    //PIN_CLOTH_BEGIN
    "PIN_CLOTH_SHOES",                    ///皮靴
    "PIN_CLOTH_MAGA_CAP",                 ///法师帽
    "PIN_CLOTH_CLOTH",                    ///布甲
    "PIN_CLOTH_LEATHERARMOR",             ///皮甲
    "PIN_CLOTH_CHAINSHOES",               ///链靴
    "PIN_CLOTH_HELEMT",                   ///头盔
    "PIN_CLOTH_STEELARMOR",               ///钢甲
    //PIN_CLOTH_END
    
    //PIN_CLOTH_PRO_BEGIN
    "PIN_CLOTH_PRO_SHOES",                    ///旅人之靴 Boots of travel
    "PIN_CLOTH_PRO_MAGA_CAP",                 ///大法师之帽 Grand Master's hat
    "PIN_CLOTH_PRO_CLOTH",                    ///银色月光 Silver moonlight
    "PIN_CLOTH_PRO_LEATHERARMOR",             ///生命牢笼 Life cage
    "PIN_CLOTH_PRO_CHAINSHOES",               ///云之足径 Foot diameter of cloud
    "PIN_CLOTH_PRO_HELEMT",                   ///骑士容貌 Knight looks
    "PIN_CLOTH_PRO_STEELARMOR",               ///寡妇对抗者 No widow
    //PIN_CLOTH_PRO_END
    
    "PIN_UNKNOWN"
};

PickableItem* PickableItem::create(PickableItemType type)
{
    std::string model = LevelResourceManager::getInstance()->getItemModelRes(PICKABLE_ITEM_NAMES[type]);
    auto item = new (std::nothrow) PickableItem();
    if (item && item->initWithFile(model))
    {
        auto tex = Director::getInstance()->getTextureCache()->addImage("item_color.png");
        if(tex)
            tex->setAliasTexParameters();
        item->setTexture(tex);
        item->m_Type = type;
        item->setCameraMask((unsigned int)CameraFlag::USER1);
        item->setLightMask((unsigned int)LightFlag::LIGHT0);
        item->setOpacity(0);
        item->setCascadeOpacityEnabled(true);
        item->setScale(0.25f, 0.25f);
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
void PickableItem::setState(PickableItemState state)
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
        case PickableItem::PIS_BEGIN_GENERATE:
            onExitBeginGenerate();
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
        case PickableItem::PIS_BEGIN_GENERATE:
            onEnterBeginGenerate();
            break;
        default:
            break;
    }
}

void PickableItem::onEnterIdle()
{
    addTerrainTileFlag(TileInfo::PICKABLE);
    
    EaseSineOut* fadeIn = EaseSineOut::create(FadeIn::create(1.0f));
    RotateBy* rotateBy = RotateBy::create(1.0f, Vec3(0, 180, 0));
    Spawn* spawn = Spawn::create(fadeIn, rotateBy, nullptr);
    CallFunc* callback = CallFunc::create(CC_CALLBACK_0(PickableItem::beginRotate, this));
    Sequence* sequence = Sequence::create(spawn, callback, nullptr);
    this->runAction(sequence);
}
void PickableItem::onExitIdle()
{
    this->stopAllActions();
}
void PickableItem::onEnterFadeOut()
{
    removeTerrainTileFlag(TileInfo::PICKABLE);
    EaseSineOut* moveTo = EaseSineOut::create(MoveTo::create(0.25f, Vec3(getPositionX(),TerrainTile::CONTENT_SCALE*0.5f, getPositionZ())));
    EaseSineOut* fadeOut = EaseSineOut::create(FadeOut::create(1.0f));
    CallFunc* callback = CallFunc::create(CC_CALLBACK_0(PickableItem::destroySelf, this));
    Sequence* sequence = Sequence::create(moveTo, fadeOut, callback, nullptr);
    RotateBy* rotateBy = RotateBy::create(1.0f, Vec3(0, 180, 0));
    Spawn* spawn = Spawn::create(sequence, rotateBy, nullptr);
    this->runAction(spawn);
}
void PickableItem::onExitFadeOut()
{
    this->stopAllActions();
}
void PickableItem::onEnterBeginGenerate()
{
    EaseSineOut* moveTo1 = EaseSineOut::create(MoveTo::create(0.25f, Vec3(getPositionX(),TerrainTile::CONTENT_SCALE*0.5f, getPositionZ())));
    EaseSineOut* moveTo2 = EaseSineOut::create(MoveTo::create(0.25f, Vec3(getPositionX(),-0.5f*TerrainTile::CONTENT_SCALE, getPositionZ())));
    
    EaseSineIn* fadeIn = EaseSineIn::create(FadeIn::create(1.5f));
    DelayTime* delay = DelayTime::create(1.0f);
    CallFunc* callback = CallFunc::create(CC_CALLBACK_0(PickableItem::setState, this, PIS_IDLE));
    Sequence* sequence = Sequence::create(delay, moveTo1, moveTo2, callback, nullptr);
    RotateBy* rotateBy = RotateBy::create(1.0f, Vec3(0, 180, 0));
    Spawn* spawn = Spawn::create(fadeIn, sequence, rotateBy, nullptr);
    this->runAction(spawn);
}
void PickableItem::onExitBeginGenerate()
{
}
void PickableItem::beginRotate()
{
    this->stopAllActions();
    RotateBy* rotateBy = RotateBy::create(1.0f, Vec3(0, 180, 0));
    RepeatForever* repeat = RepeatForever::create(rotateBy);
    this->runAction(repeat);
}
void PickableItem::destroySelf()
{
    this->removeFromParentAndCleanup(true);
}