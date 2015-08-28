//
//  Actor.cpp
//  Tone_Skipper
//
//  Created by wang haibo on 15/8/26.
//
//

#include "Actor.h"
USING_NS_CC;

Actor::Actor()
{
    m_pSprite = nullptr;
}
Actor::~Actor()
{
}
void Actor::onEnter()
{
    Node::onEnter();
    scheduleUpdate();
}
void Actor::onExit()
{
    unscheduleUpdate();
    Node::onExit();
}