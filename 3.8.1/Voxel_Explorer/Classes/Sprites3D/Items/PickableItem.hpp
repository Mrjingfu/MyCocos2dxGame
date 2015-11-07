//
//  PickableItem.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/20.
//
//

#ifndef PickableItem_hpp
#define PickableItem_hpp

#include "Actor.hpp"
extern const std::string PICKABLE_ITEM_NAMES[];
class PickableItem : public Actor
{
public:
    typedef enum{
        //PIT_KEY_BEGIN
        PIT_KEY_COPPER = 0,         ///铜宝箱钥匙
        PIT_KEY_SILVER,             ///银宝箱钥匙
        PIT_KEY_GOLD,               ///金宝箱钥匙
        PIT_KEY_BOSS,               ///BOSS房间钥匙
        PIT_KEY_ROOM,               ///普通房间钥匙
        //PIT_KEY_END
        
        //PIT_DAGGER_BEGIN
        PIT_DAGGER_DAGGER,           ///匕首
        PIT_DAGGER_HALFSWORD,        ///短剑
        PIT_DAGGER_KNIFE,            ///小刀
        PIT_DAGGER_COLDSTEELDAGGER,  ///冷钢匕首
        PIT_DAGGER_RIPPERCUTTER,     ///开膛刀
        PIT_DAGGER_BLUELIGHTDAGGER,  ///蓝光匕首
        PIT_DAGGER_RUBYDAGGER,       ///红宝石匕首
        //PIT_DAGGER_END
        
        //PIT_DAGGER_PRO_BEGIN
        PIT_DAGGER_PRO_DAGGER,           ///烛光 Candlelight
        PIT_DAGGER_PRO_HALFSWORD,        ///星耀 Stars Shine
        PIT_DAGGER_PRO_KNIFE,            ///黄金杀手 Gold Killer
        PIT_DAGGER_PRO_COLDSTEELDAGGER,  ///影子袭击者 Shadow Attacker
        PIT_DAGGER_PRO_RIPPERCUTTER,     ///六刃 Six Blade
        PIT_DAGGER_PRO_BLUELIGHTDAGGER,  ///凝云 Frozen Cloud
        PIT_DAGGER_PRO_RUBYDAGGER,       ///火舌 Fireflow
        //PIT_DAGGER_PRO_END
        
        //PIT_AXE_BEGIN
        PIT_AXE_HATCHET,            ///小斧
        PIT_AXE_ADZE,               ///手斧
        PIT_AXE_STONEAXE,           ///石斧
        PIT_AXE_BROADAX,            ///大斧
        PIT_AXE_TOMAHAWK,           ///战斧
        PIN_AXE_HUGEAXE,            ///巨斧
        PIT_AXE_DOUBLEBITAX,        ///双刃斧 double-bit ax
        //PIT_AXE_END
        
        //PIT_AXE_PRO_BEGIN,
        PIT_AXE_PRO_HATCHET,            ///黑铁 Dark Iron
        PIT_AXE_PRO_ADZE,               ///半月 Half Moon
        PIT_AXE_PRO_STONEAXE,           ///回旋加速器 Cyclotron
        PIT_AXE_PRO_BROADAX,            ///熔岩 Molten lava
        PIT_AXE_PRO_TOMAHAWK,           ///狂战士 Berserker
        PIT_AXE_PRO_HUGEAXE,            ///骷髅撕裂者 Skull Splitter
        PIT_AXE_PRO_DOUBLEBITAX,        ///脑袋 Brainhew
        //PIT_AXE_PRO_END
        
        //PIT_SWORD_BEGIN
        PIT_SWORD_SWORD,                ///练习剑
        PIT_SWORD_STEELSWORD,           ///长钢剑
        PIT_SWORD_SABRE,                ///军刀
        PIT_SWORD_HUGESWORD,            ///巨剑
        PIT_SWORD_TRIANGLESWORD,        ///三角剑
        PIT_SWORD_JAGGEDSWORD,          ///锯齿剑
        PIT_SWORD_CRYSTALSWORD,         ///水晶剑
        //PIT_SWORD_END
        
        //PIT_SWORD_PRO_BEGIN,
        PIT_SWORD_PRO_SWORD,                ///红莲 Red Lotus
        PIT_SWORD_PRO_STEELSWORD,           ///一闪 Flash
        PIT_SWORD_PRO_SABRE,                ///劈风者 Wind Strike
        PIT_SWORD_PRO_HUGESWORD,            ///阳炎 Solar Flame
        PIT_SWORD_PRO_TRIANGLESWORD,        ///血之使者 Bloodletters
        PIT_SWORD_PRO_JAGGEDSWORD,          ///锐齿 Sawtooth
        PIT_SWORD_PRO_CRYSTALSWORD,         ///诛神 No God
        //PIT_SWORD_PRO_END
        
        //PIT_MACE_BEGIN
        PIT_MACE_ROLLINGPIN,                ///擀面杖
        PIT_MACE_MALLET,                    ///木棒
        PIT_MACE_MACE,                      ///权杖
        PIT_MACE_HAMMER,                    ///钉头锤
        PIT_MACE_WOLFFANGSMACE,             ///狼牙棒
        PIT_MACE_BONEHAMMER,                ///骨锤
        PIT_MACE_SLEDGEHAMMER,              ///碎骨大锤
        //PIT_MACE_END
        
        //PIT_MACE_PRO_BEGIN
        PIT_MACE_PRO_ROLLINGPIN,                ///恐龙骨棒 Dinosaur bone
        PIT_MACE_PRO_MALLET,                    ///食人魔之锤 The hammer of ogre
        PIT_MACE_PRO_MACE,                      ///红宝石权杖 Ruby Mace
        PIT_MACE_PRO_HAMMER,                    ///黄金荣耀 Golden glory
        PIT_MACE_PRO_WOLFFANGSMACE,             ///众神之锤 Mace of the gods
        PIT_MACE_PRO_BONEHAMMER,                ///蓝宝石权杖Sapphire Mace
        PIT_MACE_PRO_SLEDGEHAMMER,              ///死神之力 Azrael Power
        //PIT_MACE_PRO_END
        
        //PIT_BOW_BEGIN
        PIT_BOW_SHORTBOW,                   ///短弓
        PIT_BOW_LONGBOW,                    ///长弓
        PIT_BOW_HORNBOW,                    ///角弓
        PIT_BOW_REFLEXBOW,                  ///反曲弓
        PIT_BOW_EAGLEBOW,                   ///鹰弓
        PIT_BOW_LAMINATEDBOW,               ///复合弓
        PIT_BOW_GOLDENBOW,                  ///黄金弓
        //PIT_BOW_END
        
        //PIT_BOW_PRO_BEGIN
        PIT_BOW_PRO_SHORTBOW,                   ///蝎尾 Scorpion tail
        PIT_BOW_PRO_LONGBOW,                    ///六面火 Hexfire
        PIT_BOW_PRO_HORNBOW,                    ///要你命三千 Life Terminator
        PIT_BOW_PRO_REFLEXBOW,                  ///影袭 Shadow Impact
        PIT_BOW_PRO_EAGLEBOW,                   ///鹰眼 Hawkeye
        PIT_BOW_PRO_LAMINATEDBOW,               ///绿帽 Green Hat
        PIT_BOW_PRO_GOLDENBOW,                  ///群星陨落 Starsfall
        //PIT_BOW_PRO_END
        
        //PIT_STAFF_BEGIN
        PIT_STAFF_OAKSTAFF,                   ///橡木法杖
        PIT_STAFF_FIRSTAFF,                   ///冷杉法杖
        PIT_STAFF_ASHESSTAFF,                 ///灰烬法杖
        PIT_STAFF_DEMONSTAFF,                 ///恶魔法杖
        PIT_STAFF_CITRONSTAFF,                ///枸木法杖
        PIT_STAFF_CLOUDSTAFF,                 ///流云法杖
        PIT_STAFF_MONKSTAFF,                  ///武僧之杖
        //PIT_STAFF_END
        
        //PIT_STAFF_PRO_BEGIN
        PIT_STAFF_PRO_OAKSTAFF,                   ///绿玉 Emerald
        PIT_STAFF_PRO_FIRSTAFF,                   ///启明星 Venus
        PIT_STAFF_PRO_ASHESSTAFF,                 ///地狱之吻 Cerebus' Bite
        PIT_STAFF_PRO_DEMONSTAFF,                 ///招魂者 Exorcist
        PIT_STAFF_PRO_CITRONSTAFF,                ///英普瑞斯之矛 The Prius Spear
        PIT_STAFF_PRO_CLOUDSTAFF,                 ///鲜血勇气 Blood courage
        PIT_STAFF_PRO_MONKSTAFF,                  ///大天使 Archangel
        //PIT_STAFF_PRO_END
        
        //PIT_SHIELD_BEGIN
        PIT_SHIELD_WOODENSHIELD,               ///圆木盾
        PIT_SHIELD_TRIANGLESHIELD,             ///三角盾
        PIT_SHIELD_STEELSHIELD,                ///精钢盾
        PIT_SHIELD_EAGLESHIELD,                ///鹰盾
        PIT_SHIELD_OSTEOSCUTE,                 ///骨盾
        PIT_SHIELD_GOLDENSHIELD,               ///黄金盾
        PIT_SHIELD_TOWERSHIELD,                ///塔盾
        //PIT_SHIELD_END
        
        //PIT_SHIELD_PRO_BEGIN
        PIT_SHIELD_PRO_WOODENSHIELD,               ///黑暗防御者 Dark defender
        PIT_SHIELD_PRO_TRIANGLESHIELD,             ///鬼脸 Grimace
        PIT_SHIELD_PRO_STEELSHIELD,                ///守夜人 The night watchman
        PIT_SHIELD_PRO_EAGLESHIELD,                ///绿魔 Green Goblin
        PIT_SHIELD_PRO_OSTEOSCUTE,                 ///骷髅王的身躯 Skeleton King's body
        PIT_SHIELD_PRO_GOLDENSHIELD,               ///美杜莎的镜子Medusa mirror
        PIT_SHIELD_PRO_TOWERSHIELD,                ///叹息之墙 Wall of sighs
        //PIT_SHIELD_PRO_END
        
        //PIT_CLOTH_BEGIN
        PIT_CLOTH_SHOES,                    ///皮靴
        PIT_CLOTH_MAGA_CAP,                 ///法师帽
        PIT_CLOTH_CLOTH,                    ///布甲
        PIT_CLOTH_LEATHERARMOR,             ///皮甲
        PIT_CLOTH_CHAINSHOES,               ///链靴
        PIT_CLOTH_HELEMT,                   ///头盔
        PIT_CLOTH_STEELARMOR,               ///钢甲
        //PIT_CLOTH_END
        
        //PIT_CLOTH_PRO_BEGIN
        PIT_CLOTH_PRO_SHOES,                    ///旅人之靴 Boots of travel
        PIT_CLOTH_PRO_MAGA_CAP,                 ///大法师之帽 Grand Master's hat
        PIT_CLOTH_PRO_CLOTH,                    ///银色月光 Silver moonlight
        PIT_CLOTH_PRO_LEATHERARMOR,             ///生命牢笼 Life cage
        PIT_CLOTH_PRO_CHAINSHOES,               ///云之足径 Foot diameter of cloud
        PIT_CLOTH_PRO_HELEMT,                   ///骑士容貌 Knight looks
        PIT_CLOTH_PRO_STEELARMOR,               ///寡妇对抗者 No widow
        //PIT_CLOTH_PRO_END
        
        //PIT_COIN_BEGIN
        PIT_COIN_GOLD,                          //金币
        PIT_COIN_SILVER,                        //银币
        PIT_COIN_BRONZE,                        //铜币
        //PIT_COIN_END
        
        PIT_UNKNOWN
    } PickableItemType;
    
    typedef enum{
        PIS_UNKNOWN = 0,
        PIS_IDLE,
        PIS_FADEOUT,
        PIS_
    } PickableItemState;
    static PickableItem* create(PickableItemType type);
    
    PickableItemType getPickableItemType() const { return m_Type; }
    PickableItemState getState() const { return m_State; }
    void setState(PickableItemState state);
private:
    PickableItem();
    virtual ~PickableItem();
    
    void onEnterIdle();
    void onExitIdle();
    
    void onEnterFadeOut();
    void onExitFadeOut();
    
    void beginRotate();
    void destroySelf();
private:
    PickableItemState   m_State;
    PickableItemType    m_Type;
};

#endif /* PickableItem_hpp */
