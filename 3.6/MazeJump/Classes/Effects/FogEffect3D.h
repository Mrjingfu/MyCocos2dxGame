//
//  FogEffect3D.h
//  MazeJump
//
//  Created by wang haibo on 15/7/20.
//
//

#ifndef __MazeJump__FogEffect3D__
#define __MazeJump__FogEffect3D__

#include "BaseEffect3D.h"

class FogEffect3D : public BaseEffect3D
{
    FogEffect3D();
    virtual ~FogEffect3D();
public:
    typedef enum {
        FT_LINEAR = 0,
        FT_EXP,
        FT_EXP2,
    } FogType;
    CREATE_FUNC(FogEffect3D);
    virtual bool init();
    virtual void drawWithSprite3D(EffectSprite3D* sprite, const cocos2d::Mat4 &transform);
    
    void setFogColor(const cocos2d::Color4F& color);
    void setFogStart(float start);
    void setFogEnd(float end);
    void setFogEquation(float equation);
    void setFogDensity(float density);
    
    void setFogType(FogType type);
private:
    cocos2d::Color4F    m_FogColor;
    float               m_fFogStart;
    float               m_fFogEnd;
    int                 m_nFogEquation;
    float               m_fFogDensity;
    FogType             m_Type;
};

#endif /* defined(__MazeJump__FogEffect3D__) */
