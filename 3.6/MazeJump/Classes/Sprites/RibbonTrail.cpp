//
//  RibbonTrail.cpp
//  MazeJump
//
//  Created by wang haibo on 15/8/5.
//
//

#include "RibbonTrail.h"
USING_NS_CC;

RibbonTrail* RibbonTrail::create(const std::string &textureFile)
{
    if (textureFile.length() < 4)
        CCASSERT(false, "invalid filename for texture file");
    
    auto ribbonTrail = new (std::nothrow) RibbonTrail();
    if (ribbonTrail && ribbonTrail->initWithFile(textureFile))
    {
        ribbonTrail->autorelease();
        return ribbonTrail;
    }
    CC_SAFE_DELETE(ribbonTrail);
    return nullptr;

}
RibbonTrail::RibbonTrail()
:m_pTrail(nullptr), m_BlendFunc(BlendFunc::ADDITIVE)
{
}
RibbonTrail::~RibbonTrail()
{
}
bool RibbonTrail::initWithFile(const std::string &path)
{
    m_pTrail = new (std::nothrow) PURibbonTrail("RibbonTrail", path);
    if(m_pTrail)
    {
        m_pTrail->setTrailLength(50);
        m_pTrail->setInitialColour(0, CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1());
        m_pTrail->setColourChange(0, CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1.0f);
        m_pTrail->setWidthChange(0, 3);
        m_pTrail->setInitialWidth(0, 5);
        m_pTrail->setDepthTest(true);
        m_pTrail->setDepthWrite(true);
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
        m_pTrail->render(renderer, transform, m_BlendFunc);
}
const BlendFunc& RibbonTrail::getBlendFunc() const
{
    return m_BlendFunc;
}

void RibbonTrail::setBlendFunc(const BlendFunc &blendFunc)
{
    m_BlendFunc = blendFunc;
}