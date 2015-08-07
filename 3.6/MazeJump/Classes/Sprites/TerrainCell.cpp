//
//  TerrainCell.cpp
//  MazeJump
//
//  Created by wang haibo on 15/7/22.
//
//

#include "TerrainCell.h"
#include "OutlineEffect3D.h"
USING_NS_CC;

TerrainCell* TerrainCell::create(const std::string& modelName)
{
    auto cell = new (std::nothrow) TerrainCell();
    if (cell && cell->initWithFile(modelName))
    {
        cell->_contentSize = cell->getBoundingBox().size;
        
        OutlineEffect3D* outline = OutlineEffect3D::create();
        outline->setOutlineColor(Vec3(0.3f, 0.3f, 0.3f));
        outline->setOutlineWidth(0.03f);
        cell->addEffect(outline, 1);
        
        cell->setLightMask((unsigned int)LightFlag::LIGHT1);
        cell->autorelease();
        return cell;
    }
    CC_SAFE_DELETE(cell);
    return nullptr;
}

TerrainCell::TerrainCell()
{
    m_Type = CT_UNKNOWN;
}
TerrainCell::~TerrainCell()
{}
