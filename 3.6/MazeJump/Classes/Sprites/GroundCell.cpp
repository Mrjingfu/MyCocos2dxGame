//
//  GroundCell.cpp
//  MazeJump
//
//  Created by wang haibo on 15/6/24.
//
//

#include "GroundCell.h"
#include "OutlineEffect3D.h"
#include "LevelsManager.h"
USING_NS_CC;

GroundCell* GroundCell::create(int level)
{
    auto cell = new (std::nothrow) GroundCell();
    if (cell && cell->initWithFile(LevelsManager::getInstance()->getLevelPlatformModelName(level) + ".c3b"))
    {
        cell->_contentSize = cell->getBoundingBox().size;
        cell->m_fRadius = cell->_contentSize.width*0.5f;
        
        OutlineEffect3D* outline = OutlineEffect3D::create();
        outline->setOutlineColor(Vec3(0.3f, 0.3f, 0.3f));
        outline->setOutlineWidth(0.03f);
        cell->addEffect(outline, 1);
        cell->autorelease();
        return cell;
    }
    CC_SAFE_DELETE(cell);
    return nullptr;
}
GroundCell::GroundCell():m_carryProp(-1)
{
    specialArtCell = nullptr;
}
bool GroundCell::isSpeicalArtCell()
{
    if (m_Type == CT_BOMB|| m_Type == CT_CARRY) {
        return true;
    }
    return false;
}

bool GroundCell::isWalkCell()
{
    if (m_Type == CT_NOT || isSpeicalArtCell()) {
        return true;
    }
    return false;
}
void GroundCell::setCarryProp(int prop)
{
    m_carryProp = prop;
    specialArtCell = EffectSprite3D::create("circle.obj");
    OutlineEffect3D* outline = OutlineEffect3D::create();
    outline->setOutlineColor(Vec3(0.3f, 0.3f, 0.3f));
    outline->setOutlineWidth(0.03f);
    specialArtCell->addEffect(outline, 1);
    specialArtCell->setAnchorPoint(Vec2::ZERO);
    specialArtCell->setPosition3D(Vec3(0, 2, 0));
    specialArtCell->setScale(0.3);
    
    specialArtCell->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.1f, 0.3f),ScaleTo::create(0.3f, 0.5f),ScaleTo::create(0.5f, 0.6f),ScaleTo::create(0.3f, 0.8f) ,ScaleTo::create(0.4f, 0.8f),NULL)));
    
    addChild(specialArtCell);
    
}