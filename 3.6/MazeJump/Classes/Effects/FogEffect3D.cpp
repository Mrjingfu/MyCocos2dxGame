//
//  FogEffect3D.cpp
//  MazeJump
//
//  Created by wang haibo on 15/7/20.
//
//

#include "FogEffect3D.h"
#include "EffectSprite3D.h"
USING_NS_CC;

FogEffect3D::FogEffect3D()
    :m_FogColor(1.0f,1.0f,1.0f,1.0f), m_fFogStart(10), m_fFogEnd(60), m_nFogEquation(0),m_fFogDensity(0.03f), m_Type(FT_LINEAR)
{
    m_bSpriteSelfDraw = true;
}
FogEffect3D::~FogEffect3D()
{
}
bool FogEffect3D::init()
{
    bool ret = initGLProgramState("fog.vert", "fog.frag");
    if(ret)
    {
        m_pGLprogramstate->setUniformVec4("u_fogColor", Vec4(m_FogColor.r,m_FogColor.g,m_FogColor.b,m_FogColor.a));
        m_pGLprogramstate->setUniformFloat("u_fogStart", m_fFogStart);
        m_pGLprogramstate->setUniformFloat("u_fogEnd", m_fFogEnd);
        m_pGLprogramstate->setUniformInt("u_fogEquation", m_nFogEquation);
        m_pGLprogramstate->setUniformFloat("u_fogDensity", m_fFogDensity);
        m_pGLprogramstate->setUniformVec4("u_color", Vec4(1.0f, 1.0f, 1.0f, 1.0f));
        m_bDirty = true;
    }
    return ret;
}

void FogEffect3D::drawWithSprite3D(EffectSprite3D* sprite, const cocos2d::Mat4 &transform)
{
    if(m_bDirty)
    {
        auto mesh = sprite->getMesh();
        long offset = 0;
        for (auto i = 0; i < mesh->getMeshVertexAttribCount(); i++)
        {
            auto meshvertexattrib = mesh->getMeshVertexAttribute(i);
            
            m_pGLprogramstate->setVertexAttribPointer(s_attributeNames[meshvertexattrib.vertexAttrib], meshvertexattrib.size, meshvertexattrib.type, GL_FALSE, mesh->getVertexSizeInBytes(), (GLvoid*)offset);
            offset += meshvertexattrib.attribSizeBytes;
        }
        m_pGLprogramstate->apply(transform);
        sprite->setGLProgramState(m_pGLprogramstate);
        m_bDirty = false;
    }

}
void FogEffect3D::setFogColor(const cocos2d::Color4F& color)
{
    if(m_FogColor != color)
    {
        m_FogColor = color;
        m_pGLprogramstate->setUniformVec4("u_fogColor", Vec4(m_FogColor.r,m_FogColor.g,m_FogColor.b,m_FogColor.a));
        m_bDirty = true;
    }
}
void FogEffect3D::setFogStart(float start)
{
    if(m_fFogStart != start)
    {
        m_fFogStart = start;
        m_pGLprogramstate->setUniformFloat("u_fogStart", m_fFogStart);
        m_bDirty = true;
    }
}
void FogEffect3D::setFogEnd(float end)
{
    if(m_fFogEnd != end)
    {
        m_fFogEnd = end;
        m_pGLprogramstate->setUniformFloat("u_fogEnd", m_fFogEnd);
        m_bDirty = true;
    }
}
void FogEffect3D::setFogEquation(float equation)
{
    if(m_nFogEquation != equation)
    {
        m_nFogEquation = equation;
        m_pGLprogramstate->setUniformInt("u_fogEquation", m_nFogEquation);
        m_bDirty = true;
    }
}
void FogEffect3D::setFogDensity(float density)
{
    if(m_fFogDensity != density)
    {
        m_fFogDensity = density;
        m_pGLprogramstate->setUniformFloat("u_fogDensity", m_fFogDensity);
        m_bDirty = true;
    }
}
void FogEffect3D::setFogType(FogType type)
{
    if(m_Type == type)
        return;
    m_Type = type;
    if(m_Type == FT_LINEAR)
    {
        setFogEquation(0);
        setFogColor(Color4F(1.0f,1.0f,1.0f,1.0f));
        setFogStart(50);
        setFogEnd(80);
    }
    else if(m_Type == FT_EXP)
    {
        setFogEquation(1);
        setFogColor(Color4F(1.0f,1.0f,1.0f,1.0f));
        setFogDensity(0.01f);
    }
    else if(m_Type == FT_EXP2)
    {
        setFogEquation(2);
        setFogColor(Color4F(1.0f,1.0f,1.0f,1.0f));
        setFogDensity(0.01f);
    }
}