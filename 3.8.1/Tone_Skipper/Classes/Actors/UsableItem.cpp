//
//  UsableItem.cpp
//  Tone_Skipper
//
//  Created by wang haibo on 15/9/22.
//
//

#include "UsableItem.h"
USING_NS_CC;
UsableItem::UsableItem()
{
    m_pMainSprite = nullptr;
    m_Type = UIT_UNKNOWN;
}
UsableItem::~UsableItem()
{
}
bool UsableItem::loadAnimations()
{
    return true;
}
void UsableItem::onLand()
{
}