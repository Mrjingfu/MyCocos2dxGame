//
//  TerrainCell.cpp
//  MazeJump
//
//  Created by wang haibo on 15/7/22.
//
//

#include "TerrainCell.h"
USING_NS_CC;

TerrainCell* TerrainCell::create(const std::string& modelName)
{
    auto cell = new (std::nothrow) TerrainCell();
    if (cell && cell->initWithFile(modelName))
    {
        cell->_contentSize = cell->getBoundingBox().size;        
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
