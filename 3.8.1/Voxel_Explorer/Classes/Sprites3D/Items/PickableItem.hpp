//
//  PickableItem.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/20.
//
//

#ifndef PickableItem_hpp
#define PickableItem_hpp

#include "cocos2d.h"
extern const std::string PICKABLE_ITEM_NAMES[];
class PickableItem : public cocos2d::Sprite3D
{
public:
    typedef enum{
        PIT_KEY_BEGIN = 0,
        PIT_KEY_COPPER,             ///铜宝箱钥匙
        PIT_KEY_SILVER,             ///银宝箱钥匙
        PIT_KEY_GOLD,               ///金宝箱钥匙
        PIT_KEY_BOSS,               ///BOSS房间钥匙
        PIT_KEY_ROOM,               ///普通房间钥匙
        PIT_KEY_END,
        
        PIT_DAGGER_BEGIN  = 10,
        PIT_DAGGER_DAGGER,           ///匕首
        PIT_DAGGER_HALFSWORD,        ///短剑
        PIT_DAGGER_KNIFE,            ///小刀
        PIT_DAGGER_COLDSTEELDAGGER,  ///冷钢匕首
        PIT_DAGGER_RIPPERCUTTER,     ///开膛刀
        PIT_DAGGER_BLUELIGHTDAGGER,  ///蓝光匕首
        PIT_DAGGER_RUBYDAGGER,       ///红宝石匕首
        PIT_DAGGER_END,
        
        PIT_DAGGER_PRO_BEGIN  = 20,
        PIT_DAGGER_PRO_DAGGER,           ///烛光 Candlelight
        PIT_DAGGER_PRO_HALFSWORD,        ///星耀 Stars Shine
        PIT_DAGGER_PRO_KNIFE,            ///黄金杀手 Gold Killer
        PIT_DAGGER_PRO_COLDSTEELDAGGER,  ///影子袭击者 Shadow Attacker
        PIT_DAGGER_PRO_RIPPERCUTTER,     ///六刃 Six Blade
        PIT_DAGGER_PRO_BLUELIGHTDAGGER,  ///凝云 Frozen Cloud
        PIT_DAGGER_PRO_RUBYDAGGER,       ///火舌 Flame
        PIT_DAGGER_PRO_END,
        
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
    PickableItemState getPickableItemState() const { return m_State; }
    void setPickableItemState(PickableItemState state);
private:
    PickableItem();
    ~PickableItem();
    
    void onEnterIdle();
    void onExitIdle();
    
    void onEnterFadeOut();
    void onExitFadeOut();
    
    void destroySelf();
private:
    PickableItemState   m_State;
    PickableItemType    m_Type;
};

#endif /* PickableItem_hpp */
