//
//  Decorator.cpp
//  MazeJump
//
//  Created by wang haibo on 15/7/29.
//
//

#include "Decorator.h"
#include "OutlineEffect3D.h"
USING_NS_CC;
Decorator* Decorator::create(DecoratorType type)
{
    auto decorator = new (std::nothrow) Decorator();
    if (decorator)
    {
        decorator->setType(type);
        switch (type) {
            case DT_HEART:
                if(decorator->initWithFile("heart.c3b"))
                {
                    decorator->setScale(0.5);
                }
                break;
            case DT_GOLD:
                if(decorator->initWithFile("goldbig.c3b"))
                {
                    decorator->setScale(0.4);
                }
                break;
            case DT_GOLD_BIG:
                if(decorator->initWithFile("goldbig.c3b"))
                {
                    decorator->setScale(0.7);
                }
                break;
            case DT_TURRET:
                if(decorator->initWithFile("goldbig.c3b"))
                {
                }
                break;
            default:
                break;
        }
        decorator->_contentSize = decorator->getBoundingBox().size;
        decorator->m_fRadius = decorator->_contentSize.width*0.5f;
        decorator->setPositionY(5);
        
        OutlineEffect3D* outline = OutlineEffect3D::create();
        outline->setOutlineColor(Vec3(0.3f, 0.3f, 0.3f));
        outline->setOutlineWidth(0.03f);
        decorator->addEffect(outline, 1);
        
        decorator->autorelease();
        return decorator;
    }
    CC_SAFE_DELETE(decorator);
    return nullptr;
}
Decorator::Decorator()
{
    m_bNeedToCollision = true;
}
Decorator::~Decorator()
{
}
void Decorator::deleteSelf()
{
    removeFromParentAndCleanup(true);
}