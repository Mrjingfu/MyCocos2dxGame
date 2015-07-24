//
//  Arrow.h
//  MazeJump
//
//  Created by wang haibo on 15/7/3.
//
//

#ifndef __MazeJump__Arrow__
#define __MazeJump__Arrow__

#include "EffectSprite3D.h"

class Arrow : public EffectSprite3D
{
public:
    typedef enum
    {
        AT_UP,
        AT_DOWN,
        AT_LEFT,
        AT_RIGHT,
        AT_UNKNOWN
    }
    ArrowType;
protected:
    Arrow();
public:
    static Arrow* create(ArrowType type);
    
    float getRadius() const { return m_fRadius; }
    ArrowType getType() const { return m_Type; }
    void setType(ArrowType type) { m_Type = type; }
    
    int getIndexX() const { return m_nIndexX; }
    void setIndexX(int indexX) { m_nIndexX = indexX; }
    int getIndexY() const { return m_nIndexY; }
    void setIndexY(int indexY) { m_nIndexY = indexY; }
    bool getSpecialArt(){return m_specialArt;}
    void setSpecialArt(bool isSpecialArt){m_specialArt = isSpecialArt;}

protected:
    float           m_fRadius;
    ArrowType       m_Type;
    int             m_nIndexX;
    int             m_nIndexY;
    bool            m_specialArt;   //标记特殊地板
};

#endif /* defined(__MazeJump__Arrow__) */
