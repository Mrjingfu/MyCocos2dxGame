//
//  OutlineEffect3D.cpp
//  Geometry-Wars
//
//  Created by wang haibo on 15/3/5.
//
//

#include "OutlineEffect3D.h"
#include "EffectSprite3D.h"
USING_NS_CC;

OutlineEffect3D::OutlineEffect3D()
: m_fOutlineWidth(1.0f), m_OutlineColor(Vec3(1,1,1))
{
    m_strProgramName = "outline_program";
}
OutlineEffect3D::~OutlineEffect3D()
{
}
bool OutlineEffect3D::init()
{
    bool ret = initGLProgramState("outLine.vert", "outLine.frag");
    if(ret)
    {
        m_pGLprogramstate->setUniformVec3("u_outlineColor", m_OutlineColor);
        m_pGLprogramstate->setUniformFloat("u_outlineWidth", m_fOutlineWidth);
        m_bDirty = true;
    }
    return ret;
}
void OutlineEffect3D::drawWithSprite3D(EffectSprite3D* sprite, const cocos2d::Mat4 &transform)
{
    if(m_bDirty && sprite)
    {
        auto mesh = sprite->getMesh();
        long offset = 0;
        for (auto i = 0; i < mesh->getMeshVertexAttribCount(); i++)
        {
            auto meshvertexattrib = mesh->getMeshVertexAttribute(i);
            
            m_pGLprogramstate->setVertexAttribPointer(s_attributeNames[meshvertexattrib.vertexAttrib], meshvertexattrib.size, meshvertexattrib.type, GL_FALSE, mesh->getVertexSizeInBytes(), (GLvoid*)offset);
            offset += meshvertexattrib.attribSizeBytes;
        }
        m_bDirty = false;
    }
    //draw
    {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        glEnable(GL_DEPTH_TEST);
        GL::blendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        Color4F color(sprite->getDisplayedColor());
        color.a = sprite->getDisplayedOpacity() / 255.0f;
        
        m_pGLprogramstate->setUniformVec4("u_color", Vec4(color.r, color.g, color.b, color.a));
        
        auto mesh = sprite->getMesh();
        glBindBuffer(GL_ARRAY_BUFFER, mesh->getVertexBuffer());
        m_pGLprogramstate->apply(transform);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getIndexBuffer());
        glDrawElements((GLenum)mesh->getPrimitiveType(), (GLsizei)mesh->getIndexCount(), (GLenum)mesh->getIndexFormat(), (GLvoid*)0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDisable(GL_DEPTH_TEST);
        glCullFace(GL_BACK);
        glDisable(GL_CULL_FACE);
    }
}
void OutlineEffect3D::setOutlineColor(const cocos2d::Vec3& color)
{
    if(m_OutlineColor != color)
    {
        m_OutlineColor = color;
        m_pGLprogramstate->setUniformVec3("u_outlineColor", m_OutlineColor);
        m_bDirty = true;
    }
}
void OutlineEffect3D::setOutlineWidth(float width)
{
    if(m_fOutlineWidth != width)
    {
        m_fOutlineWidth = width;
        m_pGLprogramstate->setUniformFloat("u_outlineWidth", m_fOutlineWidth);
        m_bDirty = true;
    }
}