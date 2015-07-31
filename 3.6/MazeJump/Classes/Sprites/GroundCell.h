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
#include "Decorator.h"
class GroundCell : public EffectSprite3D
{
public:
    typedef enum
    {
        CT_HIDE = 0,    ///不显示  RED
        CT_NOT,         ///没翻转  ORANGE
        CT_OK,          ///已翻转  GREEN
        CT_MASTER,      ///有怪物  CYAN
        CT_BOMB,        ///有炸弹
        CT_CARRY,       ///传送    BLUE
        CT_REVIVE,      ///可以行走两次 YELLOW
        CT_JUMP,        ///跳跃      当前方向位置向前跳跃一格 格数不够停在原地 跳到空格Dead
        CT_UNKNOWN
    }
    CellType;
protected:
    GroundCell(int level);
public:
    static GroundCell* create(int level,CellType type);
    bool init();
    float getRadius() const { return m_fRadius; }
    CellType getType() const { return m_Type; }
    void setType(CellType type);
    int getIndexX() const { return m_nIndexX; }
    void setIndexX(int indexX) { m_nIndexX = indexX; }
    int getIndexY() const { return m_nIndexY; }
    void setIndexY(int indexY) { m_nIndexY = indexY; }
    void setCarryProp(int prop){m_carryProp = prop;};
    int getCarryProp(){return m_carryProp;}
    bool isSpeicalArtCell();//判断是否是特殊地板
    bool isWalkCell();      //判断地板是否可行走
    void setReviveCell(GroundCell* cell){ m_reviveCell = cell;};
    GroundCell* getReviveCell(){return m_reviveCell;};
    void setDeType(Decorator::DecoratorType type){m_deType = type;};
    Decorator::DecoratorType getDetype(){return m_deType;};
protected:
    GroundCell* m_reviveCell;
    float       m_fRadius;
    CellType    m_Type;
    int         m_nIndexX;
    int         m_nIndexY;
    int         m_carryProp;            //传送属性 默认为-1
    std::string m_ModelName;
    int         m_level;
    Decorator::DecoratorType m_deType;
};

#endif /* defined(__MazeJump__GroundCell__) */
