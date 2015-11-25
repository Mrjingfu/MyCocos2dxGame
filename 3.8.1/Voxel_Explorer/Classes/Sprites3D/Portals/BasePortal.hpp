//
//  BasePortal.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/11/20.
//
//

#ifndef BasePortal_hpp
#define BasePortal_hpp

#include "Actor.hpp"
extern const std::string PORTAL_NAMES[];
class OutlineEffect3D;
class FakeShadow;
class BasePortal : public Actor
{
protected:
    BasePortal();
    virtual ~BasePortal();
    
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta);
    
    bool createFakeShadow();
public:
    typedef enum
    {
        PT_STANDARD = 0,        ///标准传送门， 地图间传送
        PT_SMALL,               ///小传送门， 地图内传送
        PT_UNKNOWN
    }
    PortalType;
    
    virtual bool createCenterModel(bool canUse, OutlineEffect3D* outline) = 0;
    
    virtual std::string getDesc() override;
    
    virtual void setVisited(bool visited) override;
    
    bool isCanUse() const { return m_bIsCanUse; }
    PortalType getProtalType() const { return m_Type; }
protected:
    PortalType      m_Type;
    EffectSprite3D* m_pCenterSprite;
    bool            m_bIsCanUse;
    
    FakeShadow*                 m_pFakeShadow;
};

#endif /* BasePortal_hpp */
