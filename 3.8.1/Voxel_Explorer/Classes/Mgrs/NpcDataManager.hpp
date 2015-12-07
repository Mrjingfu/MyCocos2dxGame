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
    
    void update(float delta);
    
    bool removeItemFromEquipmentShopList(CChaosNumber id);
    bool removeItemFromMagicShopList(CChaosNumber id);
    bool removeItemFromAlchemistRoomList(CChaosNumber id);
    bool removeItemFromTheifRoomList(CChaosNumber id);
    
    const std::vector<PickableItemProperty*>& getEquipMentShop() const { return m_EquipmentShop; }
    const std::vector<PickableItemProperty*>& getMagicShop() const { return m_MagicShop; }
    const std::vector<PickableItemProperty*>& getAlchemistRoom() const { return m_AlchemistRoom; }
    const std::vector<PickableItemProperty*>& getTheifRoom() const { return m_TheifRoom; }
    
    PickableItemProperty* getItemFromEquipMentShop(CChaosNumber id) const;
    PickableItemProperty* getItemFromMagicShop(CChaosNumber id) const;
    PickableItemProperty* getItemFromAlchemistRoom(CChaosNumber id) const;
    PickableItemProperty* getItemFromTheifRoom(CChaosNumber id) const;
    
    std::string getOldManRoomInfoByPart(int part, bool& atEnd);
private:
    bool initEquipmentShop();
    bool initMagicShop();
    bool initAlchemistShop();
    bool initTheifRoom();
    bool initOldManRoom();
    
    PickableItemProperty* getItemFormVector(const std::vector<PickableItemProperty*>& datas,CChaosNumber id) const;
private:
    std::vector<PickableItemProperty*>      m_EquipmentShop;
    std::vector<PickableItemProperty*>      m_MagicShop;
    std::vector<PickableItemProperty*>      m_AlchemistRoom;
    std::vector<PickableItemProperty*>      m_TheifRoom;
    
    cocos2d::ValueVector                    m_OldManRoom;
    
    int                     m_nOldManRoomIndex;
    bool                    m_bDirty;                 ///数据是否修改了
};

#endif /* NpcDataManager_hpp */
