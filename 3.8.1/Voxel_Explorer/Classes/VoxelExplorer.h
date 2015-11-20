//
//  VoxelExplorer.h
//  Voxel_Explorer
//
//  Created by wang haibo on 15/9/24.
//
//

#ifndef __Voxel_Explorer__VoxelExplorer__
#define __Voxel_Explorer__VoxelExplorer__

#include "cocos2d.h"
#include "BaseLevel.h"
#include "Player.hpp"
#include "BaseMonster.hpp"
#include "UseableItem.hpp"
class VoxelExplorer : public cocos2d::Ref
{
    VoxelExplorer();
    ~VoxelExplorer();
public:
    static VoxelExplorer* getInstance();
    bool init(cocos2d::Layer* pMainLayer);
    void destroy();
    
    bool checkMovable(TileInfo& info);
    void cameraTrackPlayer();
    void checkPickItem();
    void checkUpdateFogOfWar();
    void checkTriggerTrap();
    bool checkMonsterAlert(BaseMonster* monster);
    bool checkMonsterCanAttack(BaseMonster* monster);
    bool trackToPlayer(BaseMonster* monster, cocos2d::Vec2& nextPos);
    bool fleeFromPlayer(BaseMonster* monster, cocos2d::Vec2& nextPos);
    bool wanderingAround(BaseMonster* monster, cocos2d::Vec2& nextPos);
    void updateFogOfWar(const cocos2d::Rect& areaRect, bool visited);
    void updateMiniMap();
    void searchAndCheck();      ///侦查
    
    void addExplosion(const cocos2d::Vec3& pos);
    void generatePickItem(const cocos2d::Vec2& pos, bool generateItem, int copper, int monsterLevel);
    void generatePickItemByUseableItem(const cocos2d::Vec2& pos, UseableItem::UseableItemType type);
    
    void handleDoor(const cocos2d::Vec2& mapPos);            ///开门
    void handleUseUseableItem(const cocos2d::Vec2& mapPos);
    void handleTriggerTrap(const cocos2d::Vec2& mapPos, TerrainTile::TileType trapType);     ///触发机关
    void handleShowSecretDoor(const cocos2d::Vec2& mapPos);
    void handleShowHiddenTrap(const cocos2d::Vec2& mapPos, TerrainTile::TileType trapType); ///显示隐藏机关
    void handleShowSearchEffect(const cocos2d::Vec2& mapPos);
    void handlePickItem(const cocos2d::Vec2& mapPos);        ///拾取道具
    void handleMonsterHurt(const cocos2d::Vec2& mapPos);     ///处理攻击怪物
    void handlePlayerHurt(const cocos2d::Vec2& mapPos, MonsterProperty* monsterProperty);      ///处理攻击玩家
    void handlePlayerUseScroll(PickableItem::PickableItemType type);
    void handlePlayerUsePotion(PickableItem::PickableItemType type);
    
    void handlePlayerUseStandardPortal();
    void handlePlayerUseSmallPortal();
    void handleUpstairs();
    void handleDownstairs();
    
    cocos2d::Layer* getMainLayer() const { return m_pMainLayer; }
    cocos2d::Layer* get3DLayer() const { return m_p3DLayer; }
    cocos2d::Layer* getTerrainTilesLayer() const { return m_pTerrainTilesLayer; }
    cocos2d::Layer* getTerrainPortalsLayer() const { return m_pTerrainPortalsLayer; }
    cocos2d::Layer* getTerrainDoorsLayer() const { return m_pTerrainDoorsLayer; }
    cocos2d::Layer* getUseableItemsLayer() const { return m_pUseableItemsLayer; }
    cocos2d::Layer* getMonstersLayer() const { return m_pMonstersLayer; }
    cocos2d::Layer* getPickableItemsLayer() const { return m_pPickableItemsLayer; }
    cocos2d::Layer* get2DLayer() const { return m_p2DLayer; }
    cocos2d::Layer* getHUDLayer() const { return m_pHUDLayer; }
    cocos2d::Layer* getUILayer() const { return m_pUILayer; }
    
    cocos2d::Camera* getMainCamera() const { return m_pMainCamera; }
    cocos2d::Camera* getScreenCamera() const { return m_pScreenCamera; }
    
    Player* getPlayer() const { return m_pPlayer; }
    BaseLevel* getCurrentLevel() const { return m_pCurrentLevel; }
private:
    bool createLayers();
    bool createLights();
    bool createLevel();
    bool createCameras();
    bool createPlayer();
private:
    BaseLevel*      m_pCurrentLevel;

    cocos2d::Layer*                         m_pMainLayer;
    cocos2d::Layer*                         m_p3DLayer;
    cocos2d::Layer*                         m_pTerrainTilesLayer;
    cocos2d::Layer*                         m_pTerrainPortalsLayer;
    cocos2d::Layer*                         m_pTerrainDoorsLayer;
    cocos2d::Layer*                         m_pUseableItemsLayer;
    cocos2d::Layer*                         m_pMonstersLayer;
    cocos2d::Layer*                         m_pPickableItemsLayer;
    cocos2d::Layer*                         m_p2DLayer;
    cocos2d::Layer*                         m_pHUDLayer;
    cocos2d::Layer*                         m_pUILayer;
    
    cocos2d::Camera*                        m_pMainCamera;
    cocos2d::Camera*                        m_pScreenCamera;
    
    Player*                                 m_pPlayer;
};

#endif /* defined(__Voxel_Explorer__VoxelExplorer__) */
