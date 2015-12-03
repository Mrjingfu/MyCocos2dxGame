//
//  StandardLevel.h
//  Voxel_Explorer
//
//  Created by wang haibo on 15/9/24.
//
//

#ifndef __Voxel_Explorer__StandardLevel__
#define __Voxel_Explorer__StandardLevel__

#include "BaseLevel.h"
#include "Area.h"

typedef enum
{
    LS_STANDARD = 0,
    LS_TUNNEL,
    LS_PASSAGE,
    LS_UNKNOWN
} LevelStyle;

class StandardLevel : public BaseLevel
{
protected:
    StandardLevel();
    
    virtual bool build();
    virtual bool createTerrain();
    virtual bool decorateAreas();

    virtual bool initAreas();
    virtual void splitArea(const cocos2d::Rect& rect);
    virtual void generateAreaStyle();
    virtual void assignAreasType();
    virtual void assignSpecialArea(Area* area);
    
    virtual void generate();
    
    virtual bool createUseableItems(Area* area);
    virtual bool decorateSpecialArea(Area* area);
    virtual bool createPickableItems();
    
    virtual void generateSpawnPoint();
    
    virtual void showMap(bool show);
    
    virtual void updateAreaFogOfWarByPos(const cocos2d::Vec2& pos, bool updateSelfArea = false);
protected:
    void placeDoors(Area* area);
    void generateDoors(Area* area);
    bool mergeSmallIntersectArea(Area* area, Area* other, bool generate = true);
    void placeTraps();  ///放置陷阱
    int randomMonsterRespawnCell();
    int randomPickableRespawnCell();
    int calculateLevelMonsterCount();
    int calculateLevelUseableItemCount(const cocos2d::Size& areaSize);
protected:
    std::vector<PathGraphNode*>    m_Areas;
    Area*               m_AreaEntrance;
    Area*               m_AreaExit;
    std::vector<Area::AREA_TYPE>       m_SpecailAreas;
    int                 m_nSecretDoors;
    
    int                 m_nMinAreaSize;
    int                 m_nMaxAreaSize;
    int                 m_nSplitAreaSize;
    
    int                 m_nStandardAreaCount;
    int                 m_nSpecialAreaCount;
    int                 m_nTunnelAreaCount;
    int                 m_nPassageAreaCount;
    
    int                 m_nLockedDoorCount;
    
    LevelStyle          m_Style;
};

#endif /* defined(__Voxel_Explorer__StandardLevel__) */
