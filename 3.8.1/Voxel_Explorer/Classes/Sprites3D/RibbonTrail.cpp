//
//  RibbonTrail.cpp
//  MazeJump
//
//  Created by wang haibo on 15/8/5.
//
//

#include "RibbonTrail.h"
USING_NS_CC;

RibbonTrail* RibbonTrail::create(const std::string &textureFile, float width, float length)
{
    if (textureFile.length() < 4)
        CCASSERT(false, "invalid filename for texture file");
    
    auto ribbonTrail = new (std::nothrow) RibbonTrail();
    if (ribbonTrail && ribbonTrail->initWithFile(textureFile, width, length))
    {
        ribbonTrail->autorelease();
        return ribbonTrail;
    }
    CC_SAFE_DELETE(ribbonTrail);
    return nullptr;

}
RibbonTrail::RibbonTrail()
:m_pTrail(nullptr)
{
}
RibbonTrail::~RibbonTrail()
{
    m_pTrail = nullptr;
}
bool RibbonTrail::initWithFile(const std::string &path, float width, float length )
{
    m_pTrail = new (std::nothrow) PURibbonTrail("RibbonTrail", path);
    if(m_pTrail)
    {
        m_pTrail->setNumberOfChains(1);
        m_pTrail->setMaxChainElements(100);
        m_pTrail->setTrailLength(length);
        m_pTrail->setUseVertexColours(true);
        m_pTrail->setInitialColour(0, Vec4(1, 1, 1, 1));
        m_pTrail->setColourChange(0, Vec4(0.8, 0.8, 0.8, 0.8));
        m_pTrail->setInitialWidth(0, width);
        m_pTrail->setWidthChange(0, 0.8f);
        m_pTrail->setDepthTest(true);
        m_pTrail->setDepthWrite(true);
        m_pTrail->setBlendFunc(BlendFunc::ADDITIVE);
        m_pTrail->addNode(this);
        return true;
    }
    return false;
}
void RibbonTrail::update(float delta)
{
    if(m_pTrail)
        m_pTrail->update(delta);
}
void RibbonTrail::draw(Renderer* renderer, const Mat4& transform, uint32_t flags)
{
    if(m_pTrail)
        m_pTrail->render(renderer, transform, nullptr);
}