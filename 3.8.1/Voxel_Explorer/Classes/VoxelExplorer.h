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
#include "BaseBoss.hpp"
#include "UseableItem.hpp"
class GameUILayer;
extern const std::string P3D_EFFECT_NAMES[];
typedef enum
{
    P3D_PLAYER_DEATH = 0,
    P3D_PLAYER_LEVELUP = 1,
    P3D_PLAYER_USE_POTION_TAKE_EFFECT = 2,
    P3D_SMALL_PORTAL = 3,
    P3D_STANDARD_PORTAL = 4,
    P3D_STRONGER_BUFFER = 5,
    P3D_STEALTH_BUFFER = 6,
    P3D_SPEEDUP_BUFFER = 7,
    P3D_POISIONING_BUFFER = 8,
    P3D_PARALYTIC_BUFFER = 9,
    P3D_FROZEN_BUFFER = 10,
    P3D_MAX
}
P3D_EFFECT_TYPE;
class VoxelExplorer : public cocos2d::Ref
{
    VoxelExplorer();
    ~VoxelExplorer();
public:
    static VoxelExplorer* getInstance();
    bool init(cocos2d::Layer* pMainLayer);
    void destroy();
    void update(float delta);
    void gamePause();
    void gameResume();
    
    std::string getScreenPickDesc(const cocos2d::Vec2& screenPos, std::string& strIcon, const cocos2d::ValueMap* event, bool& isTraps, bool& isCanRemove, cocos2d::Vec2& checkpos);
    bool checkMovable(TileInfo& info);
    void cameraTrackPlayer();
    void checkPickItem();
    void checkUpdateFogOfWar();
    void checkTriggerTrap();
    bool checkMonsterAlert(BaseMonster* monster);
    bool checkBossAlert(BaseBoss* boss);
    bool checkMonsterCanAttack(BaseMonster* monster);
    bool checkBossFleeFromPlayer(BaseBoss* boss);
    bool checkBossCanAttack(BaseBoss* boss);
    bool trackToPlayer(Actor* tracker, cocos2d::Vec2& nextPos);
    bool fleeFromPlayer(Actor* runaway, cocos2d::Vec2& nextPos);
    bool wanderingAround(Actor* wanderer, cocos2d::Vec2& nextPos);
    void updateFogOfWar(const cocos2d::Rect& areaRect, bool visited);
    void updateMiniMap();
    void updateBossRoomDoor();
    bool checkBossRoomDoorClosed();
    void clearBoosRoom();
    void searchAndCheck();      ///侦查
    void updateStatisticsAreaDatas();
    
    void shakeScreen();     ////屏幕晃动
    
    void setPlayerLightColor(const cocos2d::Color3B& color);
    
    void updateTerrainTile(int x, int y, TerrainTile::TileType type);
    
    void addParticle3DEffect(const cocos2d::Vec3& pos, P3D_EFFECT_TYPE type);
    void addParticle3DEffectToPlayer(P3D_EFFECT_TYPE type, bool keepLocal = true);
    void removeParticle3D3DEffectFromPlayer(P3D_EFFECT_TYPE type);
    void addParticle3DEffectToActor(Actor* actor, P3D_EFFECT_TYPE type);
    void generatePickItem(const cocos2d::Vec2& pos, bool generateItem, int copper, int monsterLevel);
    void generatePickItemByUseableItem(const cocos2d::Vec2& pos, UseableItem::UseableItemType type);
    void generatePickItemByBoss(const cocos2d::Vec2& pos, int copper);
    
    void handleDoor(const cocos2d::Vec2& mapPos);            ///开门
    void handleUseUseableItem(const cocos2d::Vec2& mapPos);
    void handleTriggerTrap(const cocos2d::Vec2& mapPos, TerrainTile::TileType trapType);     ///触发机关
    void handleShowSecretDoor(const cocos2d::Vec2& mapPos);
    void handleShowHiddenTrap(const cocos2d::Vec2& mapPos, TerrainTile::TileType trapType); ///显示隐藏机关
    void handleShowSearchEffect(const cocos2d::Vec2& mapPos);
    void handlePickItem(const cocos2d::Vec2& mapPos);        ///拾取道具
    void handleMonsterHurt(const cocos2d::Vec2& mapPos);     ///处理攻击怪物
    void handlePlayerHurt(const cocos2d::Vec2& mapPos, BaseMonster* monster);      ///处理攻击玩家
    void handlePlayerHurtByBoss(const cocos2d::Vec2& mapPos, BaseBoss* boss); ///处理boss攻击
    void handlePlayerUseScroll(PickableItem::PickableItemType type);
    void handlePlayerUsePotion(PickableItem::PickableItemType type);
    
    void handlePlayerUseStandardPortal(const cocos2d::Vec2& pos);
    void handlePlayerUseSmallPortal();
    void handleUpstairs();
    void handleDownstairs();
    void handleGoChasm();
    
    void handleRemoveTrap(const cocos2d::Vec2& mapPos);
    
    cocos2d::Layer* getMainLayer() const { return m_pMainLayer; }
    cocos2d::Layer* get3DLayer() const { return m_p3DLayer; }
    cocos2d::Layer* getTerrainTilesLayer() const { return m_pTerrainTilesLayer; }
    cocos2d::Layer* getFakeShadowLayer() const { return m_pFakeShadowLayer; }
    cocos2d::Layer* getTerrainPortalsLayer() const { return m_pTerrainPortalsLayer; }
    cocos2d::Layer* getTerrainDoorsLayer() const { return m_pTerrainDoorsLayer; }
    cocos2d::Layer* getUseableItemsLayer() const { return m_pUseableItemsLayer; }
    cocos2d::Layer* getBossLayer() const { return m_pBossLayer; }
    cocos2d::Layer* getNPCsLayer() const { return m_pNPCsLayer; }
    cocos2d::Layer* getMonstersLayer() const { return m_pMonstersLayer; }
    cocos2d::Layer* getPickableItemsLayer() const { return m_pPickableItemsLayer; }
    cocos2d::Layer* get2DLayer() const { return m_p2DLayer; }
    cocos2d::Layer* getHUDLayer() const { return m_pHUDLayer; }
    GameUILayer* getUILayer() const { return m_pUILayer; }
    
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
    cocos2d::Layer*                         m_pShakeLayer;
    cocos2d::Layer*                         m_pTerrainTilesLayer;
    cocos2d::Layer*                         m_pFakeShadowLayer;
    cocos2d::Layer*                         m_pTerrainPortalsLayer;
    cocos2d::Layer*                         m_pTerrainDoorsLayer;
    cocos2d::Layer*                         m_pUseableItemsLayer;
    cocos2d::Layer*                         m_pBossLayer;
    cocos2d::Layer*                         m_pNPCsLayer;
    cocos2d::Layer*                         m_pMonstersLayer;
    cocos2d::Layer*                         m_pPickableItemsLayer;
    cocos2d::Layer*                         m_p2DLayer;
    cocos2d::Layer*                         m_pHUDLayer;
    GameUILayer*                            m_pUILayer;
    
    cocos2d::Camera*                        m_pMainCamera;
    cocos2d::Camera*                        m_pScreenCamera;
    
    Player*                                 m_pPlayer;
    bool                                    m_bIsGamePause;
};

#endif /* defined(__Voxel_Explorer__VoxelExplorer__) */
