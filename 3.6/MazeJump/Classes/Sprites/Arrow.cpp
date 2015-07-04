//
//  Arrow.cpp
//  MazeJump
//
//  Created by wang haibo on 15/7/3.
//
//

#include "Arrow.h"
USING_NS_CC;

Arrow* Arrow::create(ArrowType type)
{
    auto arrow = new (std::nothrow) Arrow();
    if (arrow && arrow->initWithFile("arrow.obj"))
    {
        arrow->setTexture("IndexColor.png");
        arrow->setType(type);
        arrow->_contentSize = arrow->getBoundingBox().size;
        arrow->m_fRadius = arrow->_contentSize.width*0.5f;
        arrow->autorelease();
        return arrow;
    }
    CC_SAFE_DELETE(arrow);
    return nullptr;
}
Arrow::Arrow()
{
}