//
//  NpcDataManager.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/11/26.
//
//

#ifndef NpcDataManager_hpp
#define NpcDataManager_hpp

#include "cocos2d.h"
#include "ChaosNumber.h"
class PickableItemProperty;

class NpcDataManager : public cocos2d::Ref
{
    NpcDataManager();
    ~NpcDataManager();
public:
    static NpcDataManager* getInstance();
    bool initNpcData();
    void clearNpcData();
    
    void update(float delta);
    
    bool removeItemFromEquipmentShopList(CChaosNumber id);
    bool removeItemFromMagicShopList(CChaosNumber id);
    bool removeItemFromAlchemistRoomList(CChaosNumber id);
    bool removeItemFromTheifRoomList(CChaosNumber id);
private:
    bool initEquipmentShop();
    bool initMagicShop();
    bool initAlchemistShop();
    bool initTheifRoom();
private:
    std::vector<PickableItemProperty*>      m_EquipmentShop;
    std::vector<PickableItemProperty*>      m_MagicShop;
    std::vector<PickableItemProperty*>      m_AlchemistRoom;
    std::vector<PickableItemProperty*>      m_TheifRoom;
    
    bool                    m_bDirty;                 ///数据是否修改了
};

#endif /* NpcDataManager_hpp */
