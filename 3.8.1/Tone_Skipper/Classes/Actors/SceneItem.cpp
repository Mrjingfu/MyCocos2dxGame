//
//  SceneItem.cpp
//  Tone_Skipper
//
//  Created by wang haibo on 15/9/22.
//
//

#include "SceneItem.h"
USING_NS_CC;
SceneItem::SceneItem()
{
    m_pMainSprite = nullptr;
    m_Type = SIT_UNKNOWN;
}
SceneItem::~SceneItem()
{
}
bool SceneItem::loadAnimations()
{
    return true;
}
void SceneItem::onLand()
{
}