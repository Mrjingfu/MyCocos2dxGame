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

GroundCell* GroundCell::create(int level,CellType type)
{
    auto cell = new (std::nothrow) GroundCell(level);
    cell->setType(type);
    if (cell && cell->init())
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
GroundCell::GroundCell(int level):m_carryProp(-1),m_level(level)
{
    m_ModelName = "";
    m_reviveCell = nullptr;
}
bool GroundCell::init()
{
    if (!initWithFile(m_ModelName)) {
        return false;
    }
    return true;
}
void GroundCell::setType(CellType type)
{
    m_Type = type;
    
    switch (m_Type) {
        case CT_CARRY:
            m_ModelName = "platform2.c3b";
            break;
        case CT_JUMP:
            m_ModelName = "platform2.c3b";
            break;
        case CT_REVIVE:
            m_ModelName =  "platform3.c3b";
            break;
        case CT_NOT:
        case CT_HIDE:
        case CT_OK:
        case CT_MASTER:
        case CT_UNKNOWN:
            m_ModelName = LevelsManager::getInstance()->getLevelPlatformModelName(m_level) + ".c3b";
            break;
        default:
            break;
    }
}
bool GroundCell::isSpeicalArtCell()
{
    if (m_Type == CT_BOMB|| m_Type == CT_CARRY || m_Type == CT_JUMP ) {
        return true;
    }
    return false;
}

bool GroundCell::isWalkCell()
{
    if (m_Type == CT_NOT || isSpeicalArtCell()|| m_Type == CT_REVIVE) {
        return true;
    }
    return false;
}


