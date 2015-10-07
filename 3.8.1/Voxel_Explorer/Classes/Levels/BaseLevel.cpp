//
//  BaseLevel.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/9/24.
//
//

#include "BaseLevel.h"
USING_NS_CC;

BaseLevel::BaseLevel()
{
    m_Type = LT_STANDARD;
    m_BoundaryType = LBT_NONE;
    m_pDebugDrawNode = nullptr;
}
void BaseLevel::create()
{
    build();
}

BaseLevel::LEVEL_TYPE BaseLevel::getLevelType() const
{
    return m_Type;
}
void BaseLevel::setLevelType(BaseLevel::LEVEL_TYPE type)
{
    m_Type = type;
}