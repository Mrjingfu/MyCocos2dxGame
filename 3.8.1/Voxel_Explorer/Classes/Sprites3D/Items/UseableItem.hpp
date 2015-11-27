//
//  UseableItem.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/24.
//
//

#ifndef UseableItem_hpp
#define UseableItem_hpp

#include "Actor.hpp"
extern const std::string USEABLE_ITEM_NAMES[];
class UseableItem : public Actor
{
public:
    typedef enum{
        
        //UIT_CHEST_NO_LOCK_BEGIN
        UIT_CHEST_NO_LOCK_COPPER = 0,         ///无锁铜宝箱
        UIT_CHEST_NO_LOCK_SILVER,             ///无锁银宝箱
        UIT_CHEST_NO_LOCK_GOLD,               ///无锁金宝箱
        //UIT_CHEST_NO_LOCK_END
        
        //UIT_CHEST_BEGIN
        UIT_CHEST_COPPER,               ///铜宝箱
        UIT_CHEST_SILVER,               ///银宝箱
        UIT_CHEST_GOLD,                 ///金宝箱
        //UIT_CHEST_END
        
        //UIT_JAR_BEGIN
        UIT_JAR_1,                  ///罐子1
        UIT_JAR_2,                  ///罐子2
        UIT_JAR_3,                  ///罐子3
        //UIT_JAR_END
        
        UIT_UNKNOWN
    } UseableItemType;
    
    typedef enum{
        UIS_UNKNOWN = 0,
        UIS_IDLE,
        UIS_FADEOUT,
        UIS_MAX
    } UseableItemState;
    static UseableItem* create(UseableItemType type);
    
    virtual std::string getDesc() override;
    
    UseableItemType getUseableItemType() const { return m_Type; }
    UseableItemState getState() const { return m_State; }
    void setState(UseableItemState state);
    
    virtual void setActorDir( ActorDir dir ) override;
    
private:
    UseableItem();
    virtual ~UseableItem();
    
    void onEnterIdle();
    void onExitIdle();
    
    void onEnterFadeOut();
    void onExitFadeOut();
    
    void destroySelf();
private:
    UseableItemState   m_State;
    UseableItemType    m_Type;
};

#endif /* UseableItem_hpp */
