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
#include "UtilityHelper.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;
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
    
    //PIN_ORNAMENT_BEGIN
    "PIN_ORNAMENT_RING",                  ///银戒指
    "PIN_ORNAMENT_MEDAL",                 ///勋章
    "PIN_ORNAMENT_SHELLNECKLACE",         ///贝壳项链
    "PIN_ORNAMENT_PENDANT",               ///吊坠
    "PIN_ORNAMENT_NECKLACE",              ///项链
    "PIN_ORNAMENT_SUPERMEDAL",            ///高级勋章
    "PIN_ORNAMENT_JEWELS",                ///宝石项链
    //PIN_ORNAMENT_END
    
    //PIN_ORNAMENT_PRO_BEGIN
    "PIN_ORNAMENT_PRO_RING",                  ///翠玉指环 Emerald ring
    "PIN_ORNAMENT_PRO_MEDAL",                 ///金色勇气 Golden courage
    "PIN_ORNAMENT_PRO_SHELLNECKLACE",         ///威廉勋章 William Medal
    "PIN_ORNAMENT_PRO_PENDANT",               ///奥妮克希亚之血 Blood of Onyxia
    "PIN_ORNAMENT_PRO_NECKLACE",              ///圣者遗物  Sacred Relic
    "PIN_ORNAMENT_PRO_SUPERMEDAL",            ///振奋宝石 Hyperstone
    "PIN_ORNAMENT_PRO_JEWELS",                ///海洋之心 Heart of Ocean
    //PIN_ORNAMENT_END
    
    //PIN_SCROLL_BEGIN
    "PIN_SCROLL_INDENTIFY",                    ////辨识卷轴 Scroll of Identify
    "PIN_SCROLL_TELEPORT",                     ////传送卷轴 Scroll of Random Teleport
    "PIN_SCROLL_SPEED",                        ////速度卷轴 Scroll of Speed
    "PIN_SCROLL_STEALTH",                      ////隐身卷轴 Scroll of Stealth
    "PIN_SCROLL_STRONGER",                     ////强壮卷轴 Scroll of Stronger
    "PIN_SCROLL_DESTINY",                      ////命运卷轴 Scroll of Destiny
    //PIN_SCROLL_END
    
    ///PIN_POTION_BEGIN
    "PIN_POTION_MINORHEALTH",                  ///小治疗药水 Minor Health Potion
    "PIN_POTION_LESSERHEALTH",                 ///轻微治疗药水 Lesser Health Potion
    "PIN_POTION_HEALTH",                       ///治疗药水 Health Potion
    "PIN_POTION_MINORMANA",                    ///小魔法药水 Minor Mana Potion
    "PIN_POTION_LESSERMANA",                   ///轻微魔法药水 Lesser Mana Potion
    "PIN_POTION_MANA",                         ///魔法药水 Mana Potion
    "PIN_POTION_MINORRECOVERY",                ///小恢复药水 Minor Recovery Potion
    "PIN_POTION_LESSERRECOVERY",               ///轻微恢复药水 Lesser Recovery Potion
    "PIN_POTION_RECOVERY",                     ///恢复药水 Recovery Potion
    "PIN_POTION_DETOXIFICATION",               ///解毒药水 Detoxification Potion
    "PIN_POTION_SPECIFIC",                     ///特效药水 Specific Potion
    "PIN_POTION_HEALING",                      ///治愈药水 Healing Potion
    "PIN_POTION_UNIVERSAL",                    ///万能药水 Universal Potion
    ///PIN_POTION_END
    
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
        if(item->m_Type >= PIT_DAGGER_DAGGER && item->m_Type <= PIT_ORNAMENT_PRO_JEWELS)
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
    m_LastState = PIS_UNKNOWN;
    m_State = PIS_UNKNOWN;
    m_Type = PIT_UNKNOWN;
    m_nLevel = 1;
}
PickableItem::~PickableItem()
{
}
std::string PickableItem::getDesc()
{
    return UtilityHelper::getLocalString("PICKITEM_DESC");
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
    m_LastState = m_State;
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
    if(m_LastState == PIS_BEGIN_GENERATE)
    {
        if(m_Type <= PIT_KEY_ROOM)
        {
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("KEY_DROP");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        }
        else if(m_Type <= PIT_DAGGER_PRO_RUBYDAGGER)
        {
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("SWORD_DROP");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        }
        else if(m_Type <= PIT_AXE_PRO_DOUBLEBITAX)
        {
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("MACE_DROP");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        }
        else if(m_Type <= PIT_DAGGER_PRO_RUBYDAGGER)
        {
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("SWORD_DROP");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        }
        else if(m_Type <= PIT_MACE_PRO_SLEDGEHAMMER)
        {
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("MACE_DROP");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        }
        else if(m_Type <= PIT_BOW_PRO_GOLDENBOW)
        {
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("BOW_DROP");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        }
        else if(m_Type <= PIT_STAFF_PRO_MONKSTAFF)
        {
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("STAFF_DROP");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        }
        else if(m_Type <= PIT_SHIELD_PRO_TOWERSHIELD)
        {
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("SHIELD_DROP");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        }
        else if(m_Type <= PIT_CLOTH_LEATHERARMOR)
        {
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("CLOTH_DROP");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        }
        else if(m_Type <= PIT_CLOTH_CHAINSHOES)
        {
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("SHOES_DROP");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        }
        else if(m_Type <= PIT_CLOTH_HELEMT)
        {
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("HELEMT_DROP");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        }
        else if(m_Type <= PIT_CLOTH_STEELARMOR)
        {
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("ARMOR_DROP");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        }
        else if(m_Type <= PIT_CLOTH_PRO_MAGA_CAP)
        {
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("CLOTH_DROP");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        }
        else if(m_Type <= PIT_CLOTH_PRO_LEATHERARMOR)
        {
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("ARMOR_DROP");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        }
        else if(m_Type <= PIT_CLOTH_PRO_CHAINSHOES)
        {
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("CLOTH_DROP");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        }
        else if(m_Type <= PIT_CLOTH_PRO_HELEMT)
        {
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("HELEMT_DROP");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        }
        else if(m_Type <= PIT_CLOTH_PRO_STEELARMOR)
        {
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("ARMOR_DROP");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        }
        else if(m_Type <= PIT_ORNAMENT_PRO_JEWELS)
        {
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("ORNAMENT_DROP");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        }
        else if(m_Type <= PIT_SCROLL_DESTINY)
        {
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("SCROLL_DROP");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        }
        else if(m_Type <= PIT_POTION_UNIVERSAL)
        {
            std::string soundName = LevelResourceManager::getInstance()->getCommonSoundEffectRes("POTION_DROP");
            SimpleAudioEngine::getInstance()->playEffect(soundName.c_str());
        }
    }
    
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
    float percentKey = 0.15f;
    float percentUnStackableItem = 0.3f;
    float percentScroll = 0.1f;
    float percentPotion = 1.0 - percentKey - percentUnStackableItem - percentScroll;
    AlisaMethod* globalAm = AlisaMethod::create(percentKey, percentUnStackableItem, percentScroll, percentPotion, -1.0, NULL);
    if(globalAm)
    {
        int randIndex = globalAm->getRandomIndex();
        if(randIndex == 0)
            ret = generateKeyItemType();
        else if(randIndex == 1)
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
                    int randAm = am->getRandomIndex();
                    if(randAm == 0)
                        ret = generate1_5UnStackableItemType();
                    else if(randAm == 1)
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
                    int randAm = am->getRandomIndex();
                    if(randAm == 0)
                        ret = generate11_15UnStackableItemProType();
                    else if(randAm == 1)
                        ret = generate1_5UnStackableItemType();
                    else if(randAm == 2)
                        ret = generate6_10UnStackableItemType();
                    else if(randAm == 3)
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
                    int randAm = am->getRandomIndex();
                    if(randAm == 0)
                        ret = generate11_15UnStackableItemProType();
                    else if(randAm == 1)
                        ret = generate16_20UnStackableItemProType();
                    else if(randAm == 2)
                        ret = generate6_10UnStackableItemType();
                    else if(randAm == 3)
                        ret = generate11_15UnStackableItemType();
                    else if(randAm == 4)
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
                    int randAm = am->getRandomIndex();
                    if(randAm == 0)
                        ret = generate16_20UnStackableItemProType();
                    else if(randAm == 1)
                        ret = generate21_25UnStackableItemProType();
                    else if(randAm == 2)
                        ret = generate11_15UnStackableItemType();
                    else if(randAm == 3)
                        ret = generate16_20UnStackableItemType();
                    else if(randAm == 4)
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
                    int randAm = am->getRandomIndex();
                    if(randAm == 0)
                        ret = generate21_25UnStackableItemProType();
                    else if(randAm == 1)
                        ret = generate26_30UnStackableItemProType();
                    else if(randAm == 2)
                        ret = generate16_20UnStackableItemType();
                    else if(randAm == 3)
                        ret = generate21_25UnStackableItemType();
                    else if(randAm == 4)
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
                    int randAm = am->getRandomIndex();
                    if(randAm == 0)
                        ret = generate26_30UnStackableItemProType();
                    else if(randAm == 1)
                        ret = generate31_35UnStackableItemProType();
                    else if(randAm == 2)
                        ret = generate21_25UnStackableItemType();
                    else if(randAm == 3)
                        ret = generate26_30UnStackableItemType();
                    else if(randAm == 4)
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
                    int randAm = am->getRandomIndex();
                    if(randAm == 0)
                        ret = generate31_35UnStackableItemProType();
                    else if(randAm == 1)
                        ret = generate36_40UnStackableItemProType();
                    else if(randAm == 2)
                        ret = generate41_45UnStackableItemProType();
                    else if(randAm == 3)
                        ret = generate26_30UnStackableItemType();
                    else if(randAm == 4)
                        ret = generate31_35UnStackableItemType();
                }
            }
        }
        else if(randIndex == 2)
        {
            ret = generateScrollType();
        }
        else if(randIndex == 3)
        {
            if(monsterLevel <= 15)
                ret = generate1_15PotionType();
            else if(monsterLevel <= 30)
                ret = generate16_30PotionType();
            else
                ret = generate31_45PotionType();
        }
        else
        {
            CCLOG("fuck am->getRandomIndex() = %d", randIndex);
        }
    }
    return ret;
}
PickableItem::PickableItemType PickableItem::generatePickItemByUseableLevel(int level, UseableItem::UseableItemType type)
{
    PickableItem::PickableItemType ret = PIT_UNKNOWN;
    if(level <= 5)
        ret = generate1_5UnStackableItemType();
    else if(level <= 10)
    {
        float percentStandard1 = 0.4f;
        float percentStandard2 = 1.0 - percentStandard1;
        AlisaMethod* am = AlisaMethod::create(percentStandard1, percentStandard2, -1.0, NULL);
        if(am)
        {
            int randIndex = am->getRandomIndex();
            if(randIndex == 0)
                ret = generate1_5UnStackableItemType();
            else if(randIndex == 1)
                ret = generate6_10UnStackableItemType();
        }
    }
    else if(level <= 15)
    {
        float percentPro = 0.02f;
        if(type == UseableItem::UIT_CHEST_COPPER || type == UseableItem::UIT_CHEST_NO_LOCK_COPPER)
            percentPro += 0.02f;
        else if(type == UseableItem::UIT_CHEST_SILVER || type == UseableItem::UIT_CHEST_NO_LOCK_SILVER)
            percentPro += 0.04f;
        else if(type == UseableItem::UIT_CHEST_GOLD || type == UseableItem::UIT_CHEST_NO_LOCK_GOLD)
            percentPro += 0.06f;
        float percentStandard1 = 0.15f;
        float percentStandard2 = 0.3f;
        float percentStandard3 = 1.0 - percentPro - percentStandard1 - percentStandard2;
        AlisaMethod* am = AlisaMethod::create(percentPro, percentStandard1, percentStandard2, percentStandard3, -1.0, NULL);
        if(am)
        {
            int randIndex = am->getRandomIndex();
            if(randIndex == 0)
                ret = generate11_15UnStackableItemProType();
            else if(randIndex == 1)
                ret = generate1_5UnStackableItemType();
            else if(randIndex == 2)
                ret = generate6_10UnStackableItemType();
            else if(randIndex == 3)
                ret = generate11_15UnStackableItemType();
        }
        
    }
    else if(level <= 20)
    {
        float percentPro1 = 0.01f;
        float percentPro2 = 0.01f;
        if(type == UseableItem::UIT_CHEST_COPPER || type == UseableItem::UIT_CHEST_NO_LOCK_COPPER)
        {
            percentPro1 += 0.01f;
            percentPro2 += 0.01f;
        }
        else if(type == UseableItem::UIT_CHEST_SILVER || type == UseableItem::UIT_CHEST_NO_LOCK_SILVER)
        {
            percentPro1 += 0.02f;
            percentPro2 += 0.02f;
        }
        else if(type == UseableItem::UIT_CHEST_GOLD || type == UseableItem::UIT_CHEST_NO_LOCK_GOLD)
        {
            percentPro1 += 0.03f;
            percentPro2 += 0.03f;
        }
        float percentStandard1 = 0.15f;
        float percentStandard2 = 0.3f;
        float percentStandard3 = 1.0 - percentPro1 - percentPro2 - percentStandard1 - percentStandard2;
        AlisaMethod* am = AlisaMethod::create(percentPro1, percentPro2, percentStandard1, percentStandard2, percentStandard3, -1.0, NULL);
        if(am)
        {
            int randIndex = am->getRandomIndex();
            if(randIndex == 0)
                ret = generate11_15UnStackableItemProType();
            else if(randIndex == 1)
                ret = generate16_20UnStackableItemProType();
            else if(randIndex == 2)
                ret = generate6_10UnStackableItemType();
            else if(randIndex == 3)
                ret = generate11_15UnStackableItemType();
            else if(randIndex == 4)
                ret = generate16_20UnStackableItemType();
        }
    }
    else if(level <= 25)
    {
        float percentPro1 = 0.01f;
        float percentPro2 = 0.01f;
        if(type == UseableItem::UIT_CHEST_COPPER || type == UseableItem::UIT_CHEST_NO_LOCK_COPPER)
        {
            percentPro1 += 0.01f;
            percentPro2 += 0.01f;
        }
        else if(type == UseableItem::UIT_CHEST_SILVER || type == UseableItem::UIT_CHEST_NO_LOCK_SILVER)
        {
            percentPro1 += 0.02f;
            percentPro2 += 0.02f;
        }
        else if(type == UseableItem::UIT_CHEST_GOLD || type == UseableItem::UIT_CHEST_NO_LOCK_GOLD)
        {
            percentPro1 += 0.03f;
            percentPro2 += 0.03f;
        }
        float percentStandard1 = 0.15f;
        float percentStandard2 = 0.3f;
        float percentStandard3 = 1.0 - percentPro1 - percentPro2 - percentStandard1 - percentStandard2;
        AlisaMethod* am = AlisaMethod::create(percentPro1, percentPro2, percentStandard1, percentStandard2, percentStandard3, -1.0, NULL);
        if(am)
        {
            int randIndex = am->getRandomIndex();
            if(randIndex == 0)
                ret = generate16_20UnStackableItemProType();
            else if(randIndex == 1)
                ret = generate21_25UnStackableItemProType();
            else if(randIndex == 2)
                ret = generate11_15UnStackableItemType();
            else if(randIndex == 3)
                ret = generate16_20UnStackableItemType();
            else if(randIndex == 4)
                ret = generate21_25UnStackableItemType();
        }
    }
    else if(level <= 30)
    {
        float percentPro1 = 0.01f;
        float percentPro2 = 0.01f;
        if(type == UseableItem::UIT_CHEST_COPPER || type == UseableItem::UIT_CHEST_NO_LOCK_COPPER)
        {
            percentPro1 += 0.01f;
            percentPro2 += 0.01f;
        }
        else if(type == UseableItem::UIT_CHEST_SILVER || type == UseableItem::UIT_CHEST_NO_LOCK_SILVER)
        {
            percentPro1 += 0.02f;
            percentPro2 += 0.02f;
        }
        else if(type == UseableItem::UIT_CHEST_GOLD || type == UseableItem::UIT_CHEST_NO_LOCK_GOLD)
        {
            percentPro1 += 0.03f;
            percentPro2 += 0.03f;
        }
        float percentStandard1 = 0.15f;
        float percentStandard2 = 0.3f;
        float percentStandard3 = 1.0 - percentPro1 - percentPro2 - percentStandard1 - percentStandard2;
        AlisaMethod* am = AlisaMethod::create(percentPro1, percentPro2, percentStandard1, percentStandard2, percentStandard3, -1.0, NULL);
        if(am)
        {
            int randIndex = am->getRandomIndex();
            if(randIndex == 0)
                ret = generate21_25UnStackableItemProType();
            else if(randIndex == 1)
                ret = generate26_30UnStackableItemProType();
            else if(randIndex == 2)
                ret = generate16_20UnStackableItemType();
            else if(randIndex == 3)
                ret = generate21_25UnStackableItemType();
            else if(randIndex == 4)
                ret = generate26_30UnStackableItemType();
        }
    }
    else if(level <= 35)
    {
        float percentPro1 = 0.01f;
        float percentPro2 = 0.01f;
        if(type == UseableItem::UIT_CHEST_COPPER || type == UseableItem::UIT_CHEST_NO_LOCK_COPPER)
        {
            percentPro1 += 0.01f;
            percentPro2 += 0.01f;
        }
        else if(type == UseableItem::UIT_CHEST_SILVER || type == UseableItem::UIT_CHEST_NO_LOCK_SILVER)
        {
            percentPro1 += 0.02f;
            percentPro2 += 0.02f;
        }
        else if(type == UseableItem::UIT_CHEST_GOLD || type == UseableItem::UIT_CHEST_NO_LOCK_GOLD)
        {
            percentPro1 += 0.03f;
            percentPro2 += 0.03f;
        }
        float percentStandard1 = 0.15f;
        float percentStandard2 = 0.3f;
        float percentStandard3 = 1.0 - percentPro1 - percentPro2 - percentStandard1 - percentStandard2;
        AlisaMethod* am = AlisaMethod::create(percentPro1, percentPro2, percentStandard1, percentStandard2, percentStandard3, -1.0, NULL);
        if(am)
        {
            int randIndex = am->getRandomIndex();
            if(randIndex == 0)
                ret = generate26_30UnStackableItemProType();
            else if(randIndex == 1)
                ret = generate31_35UnStackableItemProType();
            else if(randIndex == 2)
                ret = generate21_25UnStackableItemType();
            else if(randIndex == 3)
                ret = generate26_30UnStackableItemType();
            else if(randIndex == 4)
                ret = generate31_35UnStackableItemType();
        }
    }
    else
    {
        float percentPro1 = 0.01f;
        float percentPro2 = 0.01f;
        float percentPro3 = 0.01f;
        if(type == UseableItem::UIT_CHEST_COPPER || type == UseableItem::UIT_CHEST_NO_LOCK_COPPER)
        {
            percentPro1 += 0.01f;
            percentPro2 += 0.01f;
            percentPro3 += 0.01f;
        }
        else if(type == UseableItem::UIT_CHEST_SILVER || type == UseableItem::UIT_CHEST_NO_LOCK_SILVER)
        {
            percentPro1 += 0.02f;
            percentPro2 += 0.02f;
            percentPro3 += 0.02f;
        }
        else if(type == UseableItem::UIT_CHEST_GOLD || type == UseableItem::UIT_CHEST_NO_LOCK_GOLD)
        {
            percentPro1 += 0.03f;
            percentPro2 += 0.03f;
            percentPro3 += 0.03f;
        }
        float percentStandard1 = 0.2f;
        float percentStandard2 = 1.0 - percentPro1 - percentPro2 - percentPro3 -percentStandard1;
        AlisaMethod* am = AlisaMethod::create(percentPro1, percentPro2, percentPro3,percentStandard1, percentStandard2, -1.0, NULL);
        if(am)
        {
            int randIndex = am->getRandomIndex();
            if(randIndex == 0)
                ret = generate31_35UnStackableItemProType();
            else if(randIndex == 1)
                ret = generate36_40UnStackableItemProType();
            else if(randIndex == 2)
                ret = generate41_45UnStackableItemProType();
            else if(randIndex == 3)
                ret = generate26_30UnStackableItemType();
            else if(randIndex == 4)
                ret = generate31_35UnStackableItemType();
        }
    }
    return ret;
}
PickableItem::PickableItemType PickableItem::generateKeyItemType()
{
    float percent1 = 0.15f;
    float percent2 = 0.25f;
    float percent3 = 1.0 - percent1 - percent2;
    AlisaMethod* am = AlisaMethod::create(percent1, percent2, percent3, -1.0, NULL);
    if(am)
    {
        int randIndex = am->getRandomIndex();
        if(randIndex == 0)
            return PIT_KEY_GOLD;
        else if(randIndex == 1)
            return PIT_KEY_SILVER;
    }
    return PIT_KEY_COPPER;
}
PickableItem::PickableItemType PickableItem::generateScrollType()
{
    float percent1 = 0.4f;
    float percent2 = 0.15f;
    float percent3 = 0.1f;
    float percent4 = 0.1f;
    float percent5 = 0.1f;
    float percent6 = 1.0 - percent1 - percent2 - percent3 - percent4 - percent5;
    AlisaMethod* am = AlisaMethod::create(percent1, percent2, percent3, percent4, percent5, percent6, -1.0, NULL);
    if(am)
    {
        int randIndex = am->getRandomIndex();
        if(randIndex == 0)
            return PIT_SCROLL_INDENTIFY;
        else if(randIndex == 1)
            return PIT_SCROLL_TELEPORT;
        else if(randIndex == 2)
            return PIT_SCROLL_SPEED;
        else if(randIndex == 3)
            return PIT_SCROLL_STEALTH;
        else if(randIndex == 4)
            return PIT_SCROLL_STRONGER;
        else if(randIndex == 5)
            return PIT_SCROLL_DESTINY;
    }
    return PIT_SCROLL_DESTINY;
}
PickableItem::PickableItemType PickableItem::generate1_15PotionType()
{
    float percent1 = 0.5f;
    float percent2 = 0.2f;
    float percent3 = 0.1f;
    float percent4 = 0.05f;
    float percent5 = 0.05f;
    float percent6 = 0.05f;
    float percent7 = 1.0 - percent1 - percent2 - percent3 - percent4 - percent5 - percent6;
    AlisaMethod* am = AlisaMethod::create(percent1, percent2, percent3, percent4, percent5, percent6, percent7, -1.0, NULL);
    if(am)
    {
        int randIndex = am->getRandomIndex();
        if(randIndex == 0)
            return PIT_POTION_MINORHEALTH;
        else if(randIndex == 1)
            return PIT_POTION_MINORMANA;
        else if(randIndex == 2)
            return PIT_POTION_MINORRECOVERY;
        else if(randIndex == 3)
            return PIT_POTION_DETOXIFICATION;
        else if(randIndex == 4)
            return PIT_POTION_SPECIFIC;
        else if(randIndex == 5)
            return PIT_POTION_HEALING;
        else if(randIndex == 6)
            return PIT_POTION_UNIVERSAL;
    }
    return PIT_POTION_UNIVERSAL;
}
PickableItem::PickableItemType PickableItem::generate16_30PotionType()
{
    float percent1 = 0.1f;
    float percent2 = 0.1f;
    float percent3 = 0.1f;
    float percent4 = 0.3f;
    float percent5 = 0.1f;
    float percent6 = 0.1f;
    float percent7 = 0.05f;
    float percent8 = 0.05f;
    float percent9 = 0.05f;
    float percent10 = 1.0 - percent1 - percent2 - percent3 - percent4 - percent5 - percent6 - percent7 - percent8 - percent9;
    AlisaMethod* am = AlisaMethod::create(percent1, percent2, percent3, percent4, percent5, percent6, percent7, percent8, percent9, percent10, -1.0, NULL);
    if(am)
    {
        int randIndex = am->getRandomIndex();
        if(randIndex == 0)
            return PIT_POTION_MINORHEALTH;
        else if(randIndex == 1)
            return PIT_POTION_MINORMANA;
        else if(randIndex == 2)
            return PIT_POTION_MINORRECOVERY;
        else if(randIndex == 3)
            return PIT_POTION_LESSERHEALTH;
        else if(randIndex == 4)
            return PIT_POTION_LESSERMANA;
        else if(randIndex == 5)
            return PIT_POTION_LESSERHEALTH;
        else if(randIndex == 6)
            return PIT_POTION_DETOXIFICATION;
        else if(randIndex == 7)
            return PIT_POTION_SPECIFIC;
        else if(randIndex == 8)
            return PIT_POTION_HEALING;
        else if(randIndex == 9)
            return PIT_POTION_UNIVERSAL;
    }
    return PIT_POTION_UNIVERSAL;
}
PickableItem::PickableItemType PickableItem::generate31_45PotionType()
{
    float percent1 = 0.1f;
    float percent2 = 0.1f;
    float percent3 = 0.1f;
    float percent4 = 0.3f;
    float percent5 = 0.1f;
    float percent6 = 0.1f;
    float percent7 = 0.05f;
    float percent8 = 0.05f;
    float percent9 = 0.05f;
    float percent10 = 1.0 - percent1 - percent2 - percent3 - percent4 - percent5 - percent6 - percent7 - percent8 - percent9;
    AlisaMethod* am = AlisaMethod::create(percent1, percent2, percent3, percent4, percent5, percent6, percent7, percent8, percent9, percent10, -1.0, NULL);
    if(am)
    {
        int randIndex = am->getRandomIndex();
        if(randIndex == 0)
            return PIT_POTION_MINORHEALTH;
        else if(randIndex == 1)
            return PIT_POTION_MINORMANA;
        else if(randIndex == 2)
            return PIT_POTION_MINORRECOVERY;
        else if(randIndex == 3)
            return PIT_POTION_LESSERHEALTH;
        else if(randIndex == 4)
            return PIT_POTION_LESSERMANA;
        else if(randIndex == 5)
            return PIT_POTION_LESSERHEALTH;
        else if(randIndex == 6)
            return PIT_POTION_DETOXIFICATION;
        else if(randIndex == 7)
            return PIT_POTION_SPECIFIC;
        else if(randIndex == 8)
            return PIT_POTION_HEALING;
        else if(randIndex == 9)
            return PIT_POTION_UNIVERSAL;
    }
    return PIT_POTION_UNIVERSAL;
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
        PIT_CLOTH_SHOES,
        PIT_ORNAMENT_RING
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
        PIT_CLOTH_MAGA_CAP,
        PIT_ORNAMENT_MEDAL
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
        PIT_CLOTH_CLOTH,
        PIT_ORNAMENT_SHELLNECKLACE
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
        PIT_CLOTH_LEATHERARMOR,
        PIT_ORNAMENT_PENDANT
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
        PIT_ORNAMENT_NECKLACE
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
        PIT_CLOTH_HELEMT,
        PIT_ORNAMENT_SUPERMEDAL
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
        PIT_ORNAMENT_JEWELS
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
        PIT_CLOTH_PRO_SHOES,
        PIT_ORNAMENT_PRO_RING
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
        PIT_CLOTH_PRO_MAGA_CAP,
        PIT_ORNAMENT_PRO_MEDAL
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
        PIT_CLOTH_PRO_CLOTH,
        PIT_ORNAMENT_PRO_SHELLNECKLACE
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
        PIT_CLOTH_PRO_LEATHERARMOR,
        PIT_ORNAMENT_PRO_PENDANT
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
        PIT_ORNAMENT_PRO_NECKLACE
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
        PIT_CLOTH_PRO_HELEMT,
        PIT_ORNAMENT_PRO_SUPERMEDAL
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
        PIT_ORNAMENT_PRO_JEWELS
    };
    return types[cocos2d::random(0, (int)(types.size()-1))];
}
PickableItem::PickableItemType PickableItem::generate1_5EquipmentShopItemType()
{
    std::vector<PickableItem::PickableItemType> types {
        PIT_DAGGER_DAGGER,
        PIT_AXE_HATCHET,
        PIT_SWORD_SWORD,
        PIT_MACE_ROLLINGPIN,
        PIT_BOW_SHORTBOW,
        PIT_STAFF_OAKSTAFF,
        PIT_SHIELD_WOODENSHIELD
    };
    return types[cocos2d::random(0, (int)(types.size()-1))];
}
PickableItem::PickableItemType PickableItem::generate6_10EquipmentShopItemType()
{
    std::vector<PickableItem::PickableItemType> types {
        PIT_DAGGER_HALFSWORD,
        PIT_AXE_ADZE,
        PIT_SWORD_STEELSWORD,
        PIT_MACE_MALLET,
        PIT_BOW_LONGBOW,
        PIT_STAFF_FIRSTAFF,
        PIT_SHIELD_TRIANGLESHIELD
    };
    return types[cocos2d::random(0, (int)(types.size()-1))];
}
PickableItem::PickableItemType PickableItem::generate11_15EquipmentShopItemType()
{
    std::vector<PickableItem::PickableItemType> types {
        PIT_DAGGER_KNIFE,
        PIT_AXE_STONEAXE,
        PIT_SWORD_SABRE,
        PIT_MACE_MACE,
        PIT_BOW_HORNBOW,
        PIT_STAFF_ASHESSTAFF,
        PIT_SHIELD_STEELSHIELD
    };
    return types[cocos2d::random(0, (int)(types.size()-1))];
}
PickableItem::PickableItemType PickableItem::generate16_20EquipmentShopItemType()
{
    std::vector<PickableItem::PickableItemType> types {
        PIT_DAGGER_COLDSTEELDAGGER,
        PIT_AXE_BROADAX,
        PIT_SWORD_HUGESWORD,
        PIT_MACE_HAMMER,
        PIT_BOW_REFLEXBOW,
        PIT_STAFF_DEMONSTAFF,
        PIT_SHIELD_EAGLESHIELD
    };
    return types[cocos2d::random(0, (int)(types.size()-1))];
}
PickableItem::PickableItemType PickableItem::generate21_25EquipmentShopItemType()
{
    std::vector<PickableItem::PickableItemType> types {
        PIT_DAGGER_RIPPERCUTTER,
        PIT_AXE_TOMAHAWK,
        PIT_SWORD_TRIANGLESWORD,
        PIT_MACE_WOLFFANGSMACE,
        PIT_BOW_EAGLEBOW,
        PIT_STAFF_CITRONSTAFF,
        PIT_SHIELD_OSTEOSCUTE
    };
    return types[cocos2d::random(0, (int)(types.size()-1))];
}
PickableItem::PickableItemType PickableItem::generate26_30EquipmentShopItemType()
{
    std::vector<PickableItem::PickableItemType> types {
        PIT_DAGGER_BLUELIGHTDAGGER,
        PIT_AXE_HUGEAXE,
        PIT_SWORD_JAGGEDSWORD,
        PIT_MACE_BONEHAMMER,
        PIT_BOW_LAMINATEDBOW,
        PIT_STAFF_CLOUDSTAFF,
        PIT_SHIELD_GOLDENSHIELD
    };
    return types[cocos2d::random(0, (int)(types.size()-1))];
}
PickableItem::PickableItemType PickableItem::generate31_35EquipmentShopItemType()
{
    std::vector<PickableItem::PickableItemType> types {
        PIT_DAGGER_RUBYDAGGER,
        PIT_AXE_DOUBLEBITAX,
        PIT_SWORD_CRYSTALSWORD,
        PIT_MACE_SLEDGEHAMMER,
        PIT_BOW_GOLDENBOW,
        PIT_STAFF_MONKSTAFF,
        PIT_SHIELD_TOWERSHIELD
    };
    return types[cocos2d::random(0, (int)(types.size()-1))];
}
PickableItem::PickableItemType PickableItem::generate1_5MagicShopItemType()
{
    std::vector<PickableItem::PickableItemType> types {
        PIT_CLOTH_SHOES,
        PIT_ORNAMENT_RING
    };
    return types[cocos2d::random(0, (int)(types.size()-1))];
}
PickableItem::PickableItemType PickableItem::generate6_10MagicShopItemType()
{
    std::vector<PickableItem::PickableItemType> types {
        PIT_CLOTH_MAGA_CAP,
        PIT_ORNAMENT_MEDAL
    };
    return types[cocos2d::random(0, (int)(types.size()-1))];
}
PickableItem::PickableItemType PickableItem::generate11_15MagicShopItemType()
{
    std::vector<PickableItem::PickableItemType> types {
        PIT_CLOTH_LEATHERARMOR,
        PIT_ORNAMENT_PENDANT
    };
    return types[cocos2d::random(0, (int)(types.size()-1))];
}
PickableItem::PickableItemType PickableItem::generate16_20MagicShopItemType()
{
    std::vector<PickableItem::PickableItemType> types {
        PIT_CLOTH_LEATHERARMOR,
        PIT_ORNAMENT_PENDANT
    };
    return types[cocos2d::random(0, (int)(types.size()-1))];
}
PickableItem::PickableItemType PickableItem::generate21_25MagicShopItemType()
{
    std::vector<PickableItem::PickableItemType> types {
        PIT_CLOTH_CHAINSHOES,
        PIT_ORNAMENT_NECKLACE
    };
    return types[cocos2d::random(0, (int)(types.size()-1))];
}
PickableItem::PickableItemType PickableItem::generate26_30MagicShopItemType()
{
    std::vector<PickableItem::PickableItemType> types {
        PIT_CLOTH_HELEMT,
        PIT_ORNAMENT_SUPERMEDAL
    };
    return types[cocos2d::random(0, (int)(types.size()-1))];
}
PickableItem::PickableItemType PickableItem::generate31_35MagicShopItemType()
{
    std::vector<PickableItem::PickableItemType> types {
        PIT_CLOTH_STEELARMOR,
        PIT_ORNAMENT_JEWELS
    };
    return types[cocos2d::random(0, (int)(types.size()-1))];
}