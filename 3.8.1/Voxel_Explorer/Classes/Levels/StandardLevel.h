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
class StandardLevel : public BaseLevel
{
protected:
    StandardLevel();
    
    virtual bool build();
    virtual void decorate();
    virtual void createMobs();
    virtual void createItems();
    
    virtual bool initAreas();
    virtual void splitArea(const cocos2d::Rect& rect);
    virtual void assignAreasType();
    
    virtual void generateTerrain();
    
    virtual void showDebug(bool show);
    
private:
    void placeDoors(Area* area);
    void generateTerrainTiles(Area* area);
    void generateWalls(Area* area);
    void generateDoors(Area* area);
    bool mergeStandardArea(Area* area, Area* other);
    void generateSpawnPoint();
protected:
    std::vector<PathGraphNode*>    m_Areas;
    Area*               m_AreaEntrance;
    Area*               m_AreaExit;
    std::vector<Area::AREA_TYPE>       m_SpecailAreas;
    int                 m_nSecretDoors;
    
    int                 m_nMinAreaSize;
    int                 m_nMaxAreaSize;
};

#endif /* defined(__Voxel_Explorer__StandardLevel__) */
