//
//  TerrainCell.h
//  MazeJump
//
//  Created by wang haibo on 15/7/22.
//
//

#ifndef __MazeJump__TerrainCell__
#define __MazeJump__TerrainCell__

#include "cocos2d.h"
class TerrainCell : public cocos2d::Sprite3D
{
public:
    typedef enum
    {
        CT_STARTPOINT = 0,
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
