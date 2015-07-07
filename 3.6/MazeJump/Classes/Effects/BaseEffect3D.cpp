//
//  BaseEffect3D.cpp
//  Geometry-Wars
//
//  Created by wang haibo on 15/2/5.
//
//

#include "BaseEffect3D.h"
USING_NS_CC;

BaseEffect3D::BaseEffect3D()
: m_pGLprogramstate(nullptr)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    _backgroundListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED,
                                                      [this](EventCustom*)
                                                      {
                                                          auto glProgram = _glprogramstate->getGLProgram();
                                                          glProgram->reset();
                                                          glProgram->initWithByteArrays(m_strVertSource.c_str(), m_strFragSource.c_str());
                                                          glProgram->link();
                                                          glProgram->updateUniforms();
                                                      }
                                                      );
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backgroundListener, -1);
#endif
}

BaseEffect3D::~BaseEffect3D()
{
    CC_SAFE_RELEASE_NULL(m_pGLprogramstate);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Director::getInstance()->getEventDispatcher()->removeEventListener(m_pBackgroundListener);
#endif
}
bool BaseEffect3D::initGLProgramState(const std::string& vertFilename, const std::string& fragFilename)
{
    auto fileUtiles = FileUtils::getInstance();
    auto vertexFullPath = fileUtiles->fullPathForFilename(vertFilename);
    auto fragmentFullPath = fileUtiles->fullPathForFilename(fragFilename);
    auto vertSource = fileUtiles->getStringFromFile(vertexFullPath);
    auto fragSource = fileUtiles->getStringFromFile(fragmentFullPath);
    auto glprogram = GLProgram::createWithByteArrays(vertSource.c_str(), fragSource.c_str());
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    m_strVertSource = vertSource
    m_strFragSource = fragSource;
#endif
    
    m_pGLprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
    m_pGLprogramstate->retain();
    
    return m_pGLprogramstate != nullptr;
}