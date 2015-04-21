//
//  Stardust.cpp
//  TinyFlare
//
//  Created by wang haibo on 15/4/20.
//
//

#include "Stardust.h"
USING_NS_CC;
Stardust::Stardust()
{
}
Stardust::~Stardust()
{
}
void Stardust::loadModel(const std::string& modelName)
{
    if(m_pModel)
    {
        removeChild(m_pModel);
        m_pModel = nullptr;
    }
    m_pModel = ParticleSystemQuad::create("magicfire.plist");
    if(m_pModel == nullptr)
        CCLOGERROR("Load model magicfire.plist failed!");
    addChild(m_pModel);
}