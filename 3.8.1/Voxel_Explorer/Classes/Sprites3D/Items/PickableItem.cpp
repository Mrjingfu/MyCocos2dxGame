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
#include "AlisaMethod.h"
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

PickableItem* PickableItem::create(PickableItemType type, CChaosNumber level)
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
        if(item->m_Type >= PIT_DAGGER_DAGGER && item->m_Type <= PIT_CLOTH_PRO_STEELARMOR)
            item->m_nLevel = level;
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
    m_nLevel = 1;
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

PickableItem::PickableItemType PickableItem::generatePickItemByMonsterLevel(int monsterLevel)
{
    PickableItem::PickableItemType ret = PIT_UNKNOWN;
    float percentKey = 0.05f;
    float percentUnStackableItem = 1.0 - percentKey;
    AlisaMethod* am = AlisaMethod::create(percentKey, percentUnStackableItem, -1.0, NULL);
    if(am)
    {
        if(am->getRandomIndex() == 0)
            ret = generateKeyItemType();
        else if(am->getRandomIndex() == 1)
        {
            if(monsterLevel <= 5)
                ret = generate1_5UnStackableItemType();
            else if(monsterLevel <= 10)
            {
                float percentStandard1 = 0.4f;
                float percentStandard2 = 1.0 - percentStandard1;
                AlisaMethod* am = AlisaMethod::create(percentStandard1, percentStandard2, -1.0, NULL);
                if(am)
                {
                    if(am->getRandomIndex() == 0)
                        ret = generate1_5UnStackableItemType();
                    else if(am->getRandomIndex() == 1)
                        ret = generate6_10UnStackableItemType();
                }
            }
            else if(monsterLevel <= 15)
            {
                float percentPro = 0.02f;
                float percentStandard1 = 0.15f;
                float percentStandard2 = 0.3f;
                float percentStandard3 = 1.0 - percentPro - percentStandard1 - percentStandard2;
                AlisaMethod* am = AlisaMethod::create(percentPro, percentStandard1, percentStandard2, percentStandard3, -1.0, NULL);
                if(am)
                {
                    if(am->getRandomIndex() == 0)
                        ret = generate11_15UnStackableItemProType();
                    else if(am->getRandomIndex() == 1)
                        ret = generate1_5UnStackableItemType();
                    else if(am->getRandomIndex() == 2)
                        ret = generate6_10UnStackableItemType();
                    else if(am->getRandomIndex() == 3)
                        ret = generate11_15UnStackableItemType();
                }

            }
            else if(monsterLevel <= 20)
            {
                float percentPro1 = 0.01f;
                float percentPro2 = 0.01f;
                float percentStandard1 = 0.15f;
                float percentStandard2 = 0.3f;
                float percentStandard3 = 1.0 - percentPro1 - percentPro2 - percentStandard1 - percentStandard2;
                AlisaMethod* am = AlisaMethod::create(percentPro1, percentPro2, percentStandard1, percentStandard2, percentStandard3, -1.0, NULL);
                if(am)
                {
                    if(am->getRandomIndex() == 0)
                        ret = generate11_15UnStackableItemProType();
                    else if(am->getRandomIndex() == 1)
                        ret = generate16_20UnStackableItemProType();
                    else if(am->getRandomIndex() == 2)
                        ret = generate6_10UnStackableItemType();
                    else if(am->getRandomIndex() == 3)
                        ret = generate11_15UnStackableItemType();
                    else if(am->getRandomIndex() == 4)
                        ret = generate16_20UnStackableItemType();
                }
            }
            else if(monsterLevel <= 25)
            {
                float percentPro1 = 0.01f;
                float percentPro2 = 0.01f;
                float percentStandard1 = 0.15f;
                float percentStandard2 = 0.3f;
                float percentStandard3 = 1.0 - percentPro1 - percentPro2 - percentStandard1 - percentStandard2;
                AlisaMethod* am = AlisaMethod::create(percentPro1, percentPro2, percentStandard1, percentStandard2, percentStandard3, -1.0, NULL);
                if(am)
                {
                    if(am->getRandomIndex() == 0)
                        ret = generate16_20UnStackableItemProType();
                    else if(am->getRandomIndex() == 1)
                        ret = generate21_25UnStackableItemProType();
                    else if(am->getRandomIndex() == 2)
                        ret = generate11_15UnStackableItemType();
                    else if(am->getRandomIndex() == 3)
                        ret = generate16_20UnStackableItemType();
                    else if(am->getRandomIndex() == 4)
                        ret = generate21_25UnStackableItemType();
                }
            }
            else if(monsterLevel <= 30)
            {
                float percentPro1 = 0.01f;
                float percentPro2 = 0.01f;
                float percentStandard1 = 0.15f;
                float percentStandard2 = 0.3f;
                float percentStandard3 = 1.0 - percentPro1 - percentPro2 - percentStandard1 - percentStandard2;
                AlisaMethod* am = AlisaMethod::create(percentPro1, percentPro2, percentStandard1, percentStandard2, percentStandard3, -1.0, NULL);
                if(am)
                {
                    if(am->getRandomIndex() == 0)
                        ret = generate21_25UnStackableItemProType();
                    else if(am->getRandomIndex() == 1)
                        ret = generate26_30UnStackableItemProType();
                    else if(am->getRandomIndex() == 2)
                        ret = generate16_20UnStackableItemType();
                    else if(am->getRandomIndex() == 3)
                        ret = generate21_25UnStackableItemType();
                    else if(am->getRandomIndex() == 4)
                        ret = generate26_30UnStackableItemType();
                }
            }
            else if(monsterLevel <= 35)
            {
                float percentPro1 = 0.01f;
                float percentPro2 = 0.01f;
                float percentStandard1 = 0.15f;
                float percentStandard2 = 0.3f;
                float percentStandard3 = 1.0 - percentPro1 - percentPro2 - percentStandard1 - percentStandard2;
                AlisaMethod* am = AlisaMethod::create(percentPro1, percentPro2, percentStandard1, percentStandard2, percentStandard3, -1.0, NULL);
                if(am)
                {
                    if(am->getRandomIndex() == 0)
                        ret = generate26_30UnStackableItemProType();
                    else if(am->getRandomIndex() == 1)
                        ret = generate31_35UnStackableItemProType();
                    else if(am->getRandomIndex() == 2)
                        ret = generate21_25UnStackableItemType();
                    else if(am->getRandomIndex() == 3)
                        ret = generate26_30UnStackableItemType();
                    else if(am->getRandomIndex() == 4)
                        ret = generate31_35UnStackableItemType();
                }
            }
            else
            {
                float percentPro1 = 0.01f;
                float percentPro2 = 0.01f;
                float percentPro3 = 0.01f;
                float percentStandard1 = 0.2f;
                float percentStandard2 = 1.0 - percentPro1 - percentPro2 - percentPro3 -percentStandard1;
                AlisaMethod* am = AlisaMethod::create(percentPro1, percentPro2, percentPro3,percentStandard1, percentStandard2, -1.0, NULL);
                if(am)
                {
                    if(am->getRandomIndex() == 0)
                        ret = generate31_35UnStackableItemProType();
                    else if(am->getRandomIndex() == 1)
                        ret = generate36_40UnStackableItemProType();
                    else if(am->getRandomIndex() == 2)
                        ret = generate41_45UnStackableItemProType();
                    else if(am->getRandomIndex() == 3)
                        ret = generate26_30UnStackableItemType();
                    else if(am->getRandomIndex() == 4)
                        ret = generate31_35UnStackableItemType();
                }
            }
        }
    }
    return ret;
}

PickableItem::PickableItemType PickableItem::generateKeyItemType()
{
    float percent1 = 0.2f;
    float percent2 = 0.3f;
    float percent3 = 1.0 - percent1 - percent2;
    AlisaMethod* am = AlisaMethod::create(percent1, percent2, percent3, -1.0, NULL);
    if(am)
    {
        if(am->getRandomIndex() == 0)
            return PIT_KEY_GOLD;
        else if(am->getRandomIndex() == 1)
            return PIT_KEY_SILVER;
    }
    return PIT_KEY_COPPER;
}

PickableItem::PickableItemType PickableItem::generate1_5UnStackableItemType()
{
    std::vector<PickableItem::PickableItemType> types {
        PIT_DAGGER_DAGGER,
        PIT_AXE_HATCHET,
        PIT_SWORD_SWORD,
        PIT_MACE_ROLLINGPIN,
        PIT_BOW_SHORTBOW,
        PIT_STAFF_OAKSTAFF,
        PIT_SHIELD_WOODENSHIELD,
        PIT_CLOTH_SHOES
    };
    return types[cocos2d::random(0, (int)(types.size()-1))];
}
PickableItem::PickableItemType PickableItem::generate6_10UnStackableItemType()
{
    std::vector<PickableItem::PickableItemType> types {
        PIT_DAGGER_HALFSWORD,
        PIT_AXE_ADZE,
        PIT_SWORD_STEELSWORD,
        PIT_MACE_MALLET,
        PIT_BOW_LONGBOW,
        PIT_STAFF_FIRSTAFF,
        PIT_SHIELD_TRIANGLESHIELD,
        PIT_CLOTH_MAGA_CAP
    };
    return types[cocos2d::random(0, (int)(types.size()-1))];
}
PickableItem::PickableItemType PickableItem::generate11_15UnStackableItemType()
{
    std::vector<PickableItem::PickableItemType> types {
        PIT_DAGGER_KNIFE,
        PIT_AXE_STONEAXE,
        PIT_SWORD_SABRE,
        PIT_MACE_MACE,
        PIT_BOW_HORNBOW,
        PIT_STAFF_ASHESSTAFF,
        PIT_SHIELD_STEELSHIELD,
        PIT_CLOTH_CLOTH
    };
    return types[cocos2d::random(0, (int)(types.size()-1))];
}
PickableItem::PickableItemType PickableItem::generate16_20UnStackableItemType()
{
    std::vector<PickableItem::PickableItemType> types {
        PIT_DAGGER_COLDSTEELDAGGER,
        PIT_AXE_BROADAX,
        PIT_SWORD_HUGESWORD,
        PIT_MACE_HAMMER,
        PIT_BOW_REFLEXBOW,
        PIT_STAFF_DEMONSTAFF,
        PIT_SHIELD_EAGLESHIELD,
        PIT_CLOTH_LEATHERARMOR
    };
    return types[cocos2d::random(0, (int)(types.size()-1))];
}
PickableItem::PickableItemType PickableItem::generate21_25UnStackableItemType()
{
    std::vector<PickableItem::PickableItemType> types {
        PIT_DAGGER_RIPPERCUTTER,
        PIT_AXE_TOMAHAWK,
        PIT_SWORD_TRIANGLESWORD,
        PIT_MACE_WOLFFANGSMACE,
        PIT_BOW_EAGLEBOW,
        PIT_STAFF_CITRONSTAFF,
        PIT_SHIELD_OSTEOSCUTE,
        PIT_CLOTH_CHAINSHOES,
    };
    return types[cocos2d::random(0, (int)(types.size()-1))];
}
PickableItem::PickableItemType PickableItem::generate26_30UnStackableItemType()
{
    std::vector<PickableItem::PickableItemType> types {
        PIT_DAGGER_BLUELIGHTDAGGER,
        PIT_AXE_HUGEAXE,
        PIT_SWORD_JAGGEDSWORD,
        PIT_MACE_BONEHAMMER,
        PIT_BOW_LAMINATEDBOW,
        PIT_STAFF_CLOUDSTAFF,
        PIT_SHIELD_GOLDENSHIELD,
        PIT_CLOTH_HELEMT
    };
    return types[cocos2d::random(0, (int)(types.size()-1))];
}
PickableItem::PickableItemType PickableItem::generate31_35UnStackableItemType()
{
    std::vector<PickableItem::PickableItemType> types {
        PIT_DAGGER_RUBYDAGGER,
        PIT_AXE_DOUBLEBITAX,
        PIT_SWORD_CRYSTALSWORD,
        PIT_MACE_SLEDGEHAMMER,
        PIT_BOW_GOLDENBOW,
        PIT_STAFF_MONKSTAFF,
        PIT_SHIELD_TOWERSHIELD,
        PIT_CLOTH_STEELARMOR,
    };
    return types[cocos2d::random(0, (int)(types.size()-1))];
}
PickableItem::PickableItemType PickableItem::generate11_15UnStackableItemProType()
{
    std::vector<PickableItem::PickableItemType> types {
        PIT_DAGGER_PRO_DAGGER,
        PIT_AXE_PRO_HATCHET,
        PIT_SWORD_PRO_SWORD,
        PIT_MACE_PRO_ROLLINGPIN,
        PIT_BOW_PRO_SHORTBOW,
        PIT_STAFF_PRO_OAKSTAFF,
        PIT_SHIELD_PRO_WOODENSHIELD,
        PIT_CLOTH_PRO_SHOES
    };
    return types[cocos2d::random(0, (int)(types.size()-1))];
}
PickableItem::PickableItemType PickableItem::generate16_20UnStackableItemProType()
{
    std::vector<PickableItem::PickableItemType> types {
        PIT_DAGGER_PRO_HALFSWORD,
        PIT_AXE_PRO_ADZE,
        PIT_SWORD_PRO_STEELSWORD,
        PIT_MACE_PRO_MALLET,
        PIT_BOW_PRO_LONGBOW,
        PIT_STAFF_PRO_FIRSTAFF,
        PIT_SHIELD_PRO_TRIANGLESHIELD,
        PIT_CLOTH_PRO_MAGA_CAP
    };
    return types[cocos2d::random(0, (int)(types.size()-1))];
}
PickableItem::PickableItemType PickableItem::generate21_25UnStackableItemProType()
{
    std::vector<PickableItem::PickableItemType> types {
        PIT_DAGGER_PRO_KNIFE,
        PIT_AXE_PRO_STONEAXE,
        PIT_SWORD_PRO_SABRE,
        PIT_MACE_PRO_MACE,
        PIT_BOW_PRO_HORNBOW,
        PIT_STAFF_PRO_ASHESSTAFF,
        PIT_SHIELD_PRO_STEELSHIELD,
        PIT_CLOTH_PRO_CLOTH
    };
    return types[cocos2d::random(0, (int)(types.size()-1))];
}
PickableItem::PickableItemType PickableItem::generate26_30UnStackableItemProType()
{
    std::vector<PickableItem::PickableItemType> types {
        PIT_DAGGER_PRO_COLDSTEELDAGGER,
        PIT_AXE_PRO_BROADAX,
        PIT_SWORD_PRO_HUGESWORD,
        PIT_MACE_PRO_HAMMER,
        PIT_BOW_PRO_REFLEXBOW,
        PIT_STAFF_PRO_DEMONSTAFF,
        PIT_SHIELD_PRO_EAGLESHIELD,
        PIT_CLOTH_PRO_LEATHERARMOR
    };
    return types[cocos2d::random(0, (int)(types.size()-1))];
}
PickableItem::PickableItemType PickableItem::generate31_35UnStackableItemProType()
{
    std::vector<PickableItem::PickableItemType> types {
        PIT_DAGGER_PRO_RIPPERCUTTER,
        PIT_AXE_PRO_TOMAHAWK,
        PIT_SWORD_PRO_TRIANGLESWORD,
        PIT_MACE_PRO_WOLFFANGSMACE,
        PIT_BOW_PRO_EAGLEBOW,
        PIT_STAFF_PRO_CITRONSTAFF,
        PIT_SHIELD_PRO_OSTEOSCUTE,
        PIT_CLOTH_PRO_CHAINSHOES,
    };
    return types[cocos2d::random(0, (int)(types.size()-1))];
}
PickableItem::PickableItemType PickableItem::generate36_40UnStackableItemProType()
{
    std::vector<PickableItem::PickableItemType> types {
        PIT_DAGGER_PRO_BLUELIGHTDAGGER,
        PIT_AXE_PRO_HUGEAXE,
        PIT_SWORD_PRO_JAGGEDSWORD,
        PIT_MACE_PRO_BONEHAMMER,
        PIT_BOW_PRO_LAMINATEDBOW,
        PIT_STAFF_PRO_CLOUDSTAFF,
        PIT_SHIELD_PRO_GOLDENSHIELD,
        PIT_CLOTH_PRO_HELEMT
    };
    return types[cocos2d::random(0, (int)(types.size()-1))];
}
PickableItem::PickableItemType PickableItem::generate41_45UnStackableItemProType()
{
    std::vector<PickableItem::PickableItemType> types {
        PIT_DAGGER_PRO_RUBYDAGGER,
        PIT_AXE_PRO_DOUBLEBITAX,
        PIT_SWORD_PRO_CRYSTALSWORD,
        PIT_MACE_PRO_SLEDGEHAMMER,
        PIT_BOW_PRO_GOLDENBOW,
        PIT_STAFF_PRO_MONKSTAFF,
        PIT_SHIELD_PRO_TOWERSHIELD,
        PIT_CLOTH_PRO_STEELARMOR,
    };
    return types[cocos2d::random(0, (int)(types.size()-1))];
}