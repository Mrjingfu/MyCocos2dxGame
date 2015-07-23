//
//  TerrainCell.h
//  MazeJump
//
//  Created by wang haibo on 15/7/22.
//
//

#ifndef __MazeJump__TerrainCell__
#define __MazeJump__TerrainCell__

#include "EffectSprite3D.h"
class TerrainCell : public EffectSprite3D
{
public:
    typedef enum
    {
        CT_STARTPOINT = 0,
        CT_SLIDBAR,
        CT_NORMAL_PLATFORM,
        CT_UNKNOWN
    }
    CellType;
    static TerrainCell* create(const std::string& modelName);
    TerrainCell();
    virtual ~TerrainCell();
    
    CellType getType() const { return m_Type; }
    void setType(CellType type) { m_Type = type; }
protected:
    CellType        m_Type;
};

#endif /* defined(__MazeJump__TerrainCell__) */
