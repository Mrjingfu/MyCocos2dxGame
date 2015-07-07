//
//  GroundCell.h
//  MazeJump
//
//  Created by wang haibo on 15/6/24.
//
//

#ifndef __MazeJump__GroundCell__
#define __MazeJump__GroundCell__

#include "EffectSprite3D.h"

class GroundCell : public EffectSprite3D
{
public:
    typedef enum
    {
        CT_HIDE = 0,    ///不显示 RED
        CT_NOT,         ///没翻转 ORANGE
        CT_OK,          ///已翻转 GREEN
        CT_MASTER,      ///有怪物 CYAN
        CT_BOMB,        ///有炸弹 YELLOW
        CT_UNKNOWN
    }
    CellType;
protected:
    GroundCell();
public:
    static GroundCell* create();
    
    float getRadius() const { return m_fRadius; }
    CellType getType() const { return m_Type; }
    void setType(CellType type) { m_Type = type; }
    int getIndexX() const { return m_nIndexX; }
    void setIndexX(int indexX) { m_nIndexX = indexX; }
    int getIndexY() const { return m_nIndexY; }
    void setIndexY(int indexY) { m_nIndexY = indexY; }
protected:
    float       m_fRadius;
    CellType    m_Type;
    int         m_nIndexX;
    int         m_nIndexY;
};

#endif /* defined(__MazeJump__GroundCell__) */
