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
class PickableItemProperty;
class NpcDataManager : public cocos2d::Ref
{
    NpcDataManager();
    ~NpcDataManager();
public:
    static NpcDataManager* getInstance();
    bool initNpcData();
    void clearNpcData();
private:
    std::vector<PickableItemProperty*>      m_EquipmentShop;
    std::vector<PickableItemProperty*>      m_MagicShop;
    std::vector<PickableItemProperty*>      m_AlchemistRoom;
    std::vector<PickableItemProperty*>      m_TheifRoom;
};

#endif /* NpcDataManager_hpp */
