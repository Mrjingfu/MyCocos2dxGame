//
//  Arrow.cpp
//  MazeJump
//
//  Created by wang haibo on 15/7/3.
//
//

#include "Arrow.h"
#include "OutlineEffect3D.h"
USING_NS_CC;

Arrow* Arrow::create(ArrowType type)
{
    auto arrow = new (std::nothrow) Arrow();
    if (arrow && arrow->initWithFile("arrow.c3b"))
    {
        arrow->setTexture("arrow.png");
        arrow->setType(type);
        arrow->_contentSize = arrow->getBoundingBox().size;
        arrow->m_fRadius = arrow->_contentSize.width*0.5f;
        
        OutlineEffect3D* outline = OutlineEffect3D::create();
        outline->setOutlineColor(Vec3(0.4f, 0.4f, 0.4f));
        outline->setOutlineWidth(0.03f);
        arrow->addEffect(outline, 1);
        
        arrow->autorelease();
        return arrow;
    }
    CC_SAFE_DELETE(arrow);
    return nullptr;
}
Arrow::Arrow():m_specialArt(false)
{
   
}