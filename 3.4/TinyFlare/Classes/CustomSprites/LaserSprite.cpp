//
//  LaserSprite.cpp
//  TinyFlare
//
//  Created by wang haibo on 15/3/30.
//
//

#include "LaserSprite.h"
USING_NS_CC;

LaserSprite* LaserSprite::create()
{
    LaserSprite *laser = new (std::nothrow) LaserSprite();
    if (laser && laser->init())
    {
        laser->autorelease();
        return laser;
    }
    CC_SAFE_DELETE(laser);
    return nullptr;
}

LaserSprite::LaserSprite()
{
    m_pMask1Texture     = nullptr;
    m_pMask2Texture     = nullptr;
    m_pNoise1Texture    = nullptr;
    m_pNoise2Texture    = nullptr;
    
    m_pGLprogramstate   = nullptr;
    
    m_fHighlight        = 1.0f;
    m_fTime             = 0.0f;
    m_fPorN             = 1.0f;
    m_fLightColorFactor = 1.0f;
    m_fGlowColorFactor  = 1.0f;
    m_fNoiseScale       = 1.0f;
    m_laserColor = Color4F(1.0f,0.5f,0.0f,1.0f);
    
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    m_pBackgroundListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED,
                                                      [this](EventCustom*)
                                                      {
                                                          auto glProgram = m_pGLprogramstate->getGLProgram();
                                                          glProgram->reset();
                                                          glProgram->initWithByteArrays(m_strVertSource.c_str(), m_strFragSource.c_str());
                                                          glProgram->link();
                                                          glProgram->updateUniforms();
                                                      }
                                                      );
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(m_pBackgroundListener, -1);
#endif
    
}
LaserSprite::~LaserSprite()
{
    CC_SAFE_RELEASE_NULL(m_pMask1Texture);
    CC_SAFE_RELEASE_NULL(m_pMask2Texture);
    CC_SAFE_RELEASE_NULL(m_pNoise1Texture);
    CC_SAFE_RELEASE_NULL(m_pNoise2Texture);
    CC_SAFE_RELEASE_NULL(m_pGLprogramstate);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Director::getInstance()->getEventDispatcher()->removeEventListener(m_pBackgroundListener);
#endif
}
bool LaserSprite::init()
{
    this->initWithFile("light.png");
    {
        Texture2D::TexParams texParams= {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
        this->getTexture()->setTexParameters(texParams);
    }
    m_pMask1Texture = Director::getInstance()->getTextureCache()->getTextureForKey("mask.png");
    m_pMask1Texture->retain();
    {
        Texture2D::TexParams texParams= {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
        m_pMask1Texture->setTexParameters(texParams);
    }
    m_pMask2Texture = Director::getInstance()->getTextureCache()->getTextureForKey("mask2.png");
    m_pMask2Texture->retain();
    {
        Texture2D::TexParams texParams= {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
        m_pMask2Texture->setTexParameters(texParams);
    }
    m_pNoise1Texture = Director::getInstance()->getTextureCache()->getTextureForKey("noise.png");
    m_pNoise1Texture->retain();
    {
        Texture2D::TexParams texParams= {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
        m_pNoise1Texture->setTexParameters(texParams);
    }
    m_pNoise2Texture = Director::getInstance()->getTextureCache()->getTextureForKey("noise2.png");
    m_pNoise2Texture->retain();
    {
        Texture2D::TexParams texParams= {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
        m_pNoise2Texture->setTexParameters(texParams);
    }
    
    if(!initGLProgramState("","laser.fsh"))
    {
        CCLOG("initGLProgramState failed!");
        return false;
    }
    
    m_pGLprogramstate->setUniformTexture("u_maskTex", m_pMask1Texture);
    m_pGLprogramstate->setUniformTexture("u_maskTex2", m_pMask2Texture);
    m_pGLprogramstate->setUniformTexture("u_noiseTex", m_pNoise1Texture);
    m_pGLprogramstate->setUniformTexture("u_noiseTex2", m_pNoise2Texture);
    m_pGLprogramstate->setUniformVec2("u_spriteSize", Vec2(getContentSize().width*getScaleX(),
                                                           getContentSize().height*getScaleY()));
    m_pGLprogramstate->setUniformVec2("u_LUPos", Vec2::ZERO);
    m_pGLprogramstate->setUniformVec2("u_noiseSize", Vec2(m_pNoise1Texture->getContentSize().width,
                                                          m_pNoise1Texture->getContentSize().height));
    m_pGLprogramstate->setUniformFloat("u_highlight", m_fHighlight);
    m_pGLprogramstate->setUniformFloat("u_time", m_fTime);
    m_pGLprogramstate->setUniformFloat("u_PorN", m_fPorN);
    m_pGLprogramstate->setUniformVec2("u_scale", Vec2(getScaleX(),getScaleY()));
    m_pGLprogramstate->setUniformFloat("u_kLightColor", m_fLightColorFactor);
    m_pGLprogramstate->setUniformFloat("u_kGlowColor", m_fGlowColorFactor);
    m_pGLprogramstate->setUniformFloat("u_noiseScale", m_fNoiseScale);
    m_pGLprogramstate->setUniformVec4("u_laserColor", Vec4(m_laserColor.r, m_laserColor.g, m_laserColor.b, m_laserColor.a));
    
    setGLProgramState(m_pGLprogramstate);
    //update
    this->scheduleUpdate();
    
    return true;
}
void LaserSprite::update(float delta)
{
    m_fTime += delta;
    if(m_fTime >= 10000.0f)
        m_fTime = 0.0f;
}
void LaserSprite::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
    // Don't do calculate the culling if the transform was not updated
    _insideBounds = (flags & FLAGS_TRANSFORM_DIRTY) ? renderer->checkVisibility(transform, _contentSize) : _insideBounds;
    if(m_pGLprogramstate)
    {
        m_pGLprogramstate->setUniformTexture("u_maskTex", m_pMask1Texture);
        m_pGLprogramstate->setUniformTexture("u_maskTex2", m_pMask2Texture);
        m_pGLprogramstate->setUniformTexture("u_noiseTex", m_pNoise1Texture);
        m_pGLprogramstate->setUniformTexture("u_noiseTex2", m_pNoise2Texture);
        m_pGLprogramstate->setUniformVec2("u_spriteSize", Vec2(getContentSize().width*getScaleX(),
                                                               getContentSize().height*getScaleY()));
        m_pGLprogramstate->setUniformVec2("u_LUPos", Vec2::ZERO);
        m_pGLprogramstate->setUniformVec2("u_noiseSize", Vec2(m_pNoise1Texture->getContentSize().width,
                                                              m_pNoise1Texture->getContentSize().height));
        m_pGLprogramstate->setUniformFloat("u_highlight", m_fHighlight);
        m_pGLprogramstate->setUniformFloat("u_time", m_fTime);
        m_pGLprogramstate->setUniformFloat("u_PorN", m_fPorN);
        m_pGLprogramstate->setUniformVec2("u_scale", Vec2(getScaleX(),getScaleY()));
        m_pGLprogramstate->setUniformFloat("u_kLightColor", m_fLightColorFactor);
        m_pGLprogramstate->setUniformFloat("u_kGlowColor", m_fGlowColorFactor);
        m_pGLprogramstate->setUniformFloat("u_noiseScale", m_fNoiseScale);
        m_pGLprogramstate->setUniformVec4("u_laserColor", Vec4(m_laserColor.r, m_laserColor.g, m_laserColor.b, m_laserColor.a));
    }
    if(_insideBounds)
    {
        _quadCommand.init(_globalZOrder, _texture->getName(), getGLProgramState(), _blendFunc, &_quad, 1, transform, flags);
        renderer->addCommand(&_quadCommand);
    }
}

bool LaserSprite::initGLProgramState(const std::string& vertFilename, const std::string& fragFilename)
{
    auto fileUtiles = FileUtils::getInstance();
    auto vertexFullPath = fileUtiles->fullPathForFilename(vertFilename);
    auto fragmentFullPath = fileUtiles->fullPathForFilename(fragFilename);
    auto vertSource = fileUtiles->getStringFromFile(vertexFullPath);
    auto fragSource = fileUtiles->getStringFromFile(fragmentFullPath);
    auto glprogram = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource.c_str());
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    m_strVertSource = vertSource;
    m_strFragSource = fragSource;
#endif
    
    m_pGLprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
    m_pGLprogramstate->retain();
    
    //check gl error
    CHECK_GL_ERROR_DEBUG();
    
    return m_pGLprogramstate != nullptr;
}
void LaserSprite::updateStartAndEnd()
{
    Vec2 mid= (m_start+m_end)*0.5f ;
    Vec2 dir= (m_end-m_start).getNormalized();
    float A;
    if(dir.y<=0){
        A=acosf(dir.x)*180/M_PI;
    }else{
        A=(2*M_PI-acosf(dir.x))*180/M_PI;
    }
    ///crush
    this->setPosition(mid);
    this->setRotation(A);
    
    float targetLen = m_start.getDistance(m_end);
    float contentLen = this->getContentSize().width;
    float scaleX = targetLen/contentLen;
    this->setScaleX(scaleX);
}
void LaserSprite::setBlendFunc(GLenum src,GLenum dst){
    BlendFunc blendFunc = { src, dst };
    Sprite::setBlendFunc(blendFunc);
}
void LaserSprite::setStart(const cocos2d::Vec2& start)
{
    m_start=start;
    updateStartAndEnd();
}
void LaserSprite::setEnd(const cocos2d::Vec2& end)
{
    m_end=end;
    updateStartAndEnd();
}