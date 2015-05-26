//
//  LaserSprite.h
//  TinyFlare
//
//  Created by wang haibo on 15/3/30.
//
//

#ifndef __TinyFlare__LaserSprite__
#define __TinyFlare__LaserSprite__

#include "cocos2d.h"
class LaserSprite : public cocos2d::Sprite
{
    friend class ActorsManager;
protected:
    LaserSprite();
    virtual ~LaserSprite();
    virtual bool init() override;
    virtual void update(float delta) override;
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
    
    bool initGLProgramState(const std::string& vertFilename, const std::string& fragFilename);
    
    void updateStartAndEnd();
public:
    static LaserSprite* create();
    void setBlendFunc(GLenum src,GLenum dst);
    
    void setStart(const cocos2d::Vec2& start);
    void setEnd(const cocos2d::Vec2& end);
    
    void setHighLight(float hightlight) { m_fHighlight = hightlight; }
    void setPorN(float porN) { m_fPorN = porN; }
    void setLightColorFactor(float factor) { m_fLightColorFactor = factor; }
    void setGlowColorFactor(float factor) { m_fGlowColorFactor = factor; }
    void setNoiseScale(float noiseScale) { m_fNoiseScale = noiseScale; }
    void setLaserColor(const cocos2d::Color4F& color) { m_laserColor = color; }
    cocos2d::Color4F getLaserColor() const { return m_laserColor; }
private:
    cocos2d::Texture2D*    m_pMask1Texture;
    cocos2d::Texture2D*    m_pMask2Texture;
    cocos2d::Texture2D*    m_pNoise1Texture;
    cocos2d::Texture2D*    m_pNoise2Texture;
    
    cocos2d::Vec2           m_start;
    cocos2d::Vec2           m_end;
    float                   m_fHighlight;
    float                   m_fTime;
    float                   m_fPorN;
    float                   m_fScale;
    float                   m_fLightColorFactor;
    float                   m_fGlowColorFactor;
    float                   m_fNoiseScale;
    cocos2d::Color4F        m_laserColor;
    
    cocos2d::GLProgramState*    m_pGLprogramstate;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::string     m_strVertSource;
    std::string     m_strFragSource;
    cocos2d::EventListenerCustom* m_pBackgroundListener;
#endif
};

#endif /* defined(__TinyFlare__LaserSprite__) */
