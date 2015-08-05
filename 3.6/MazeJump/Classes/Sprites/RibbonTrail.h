//
//  RibbonTrail.h
//  MazeJump
//
//  Created by wang haibo on 15/8/5.
//
//

#ifndef __MazeJump__RibbonTrail__
#define __MazeJump__RibbonTrail__

#include "cocos2d.h"
#include "extensions/Particle3D/PU/CCPURibbonTrail.h"
class RibbonTrail : public cocos2d::Node, public cocos2d::BlendProtocol
{
    RibbonTrail();
    virtual ~RibbonTrail();
public:
    static RibbonTrail* create(const std::string &textureFile);
    bool initWithFile(const std::string &path);
    virtual void update(float delta);
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;
    // overrides
    virtual void setBlendFunc(const cocos2d::BlendFunc &blendFunc) override;
    virtual const cocos2d::BlendFunc &getBlendFunc() const override;
    
    cocos2d::PURibbonTrail* getTrail() const { return m_pTrail; }
private:
    cocos2d::PURibbonTrail*             m_pTrail;
    cocos2d::BlendFunc                  m_BlendFunc;
};


#endif /* defined(__MazeJump__RibbonTrail__) */
