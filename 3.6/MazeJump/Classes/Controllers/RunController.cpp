//
//  RunController.cpp
//  MazeJump
//
//  Created by wang haibo on 15/7/22.
//
//

#include "RunController.h"
USING_NS_CC;

RunController* g_pGameControllerInstance = nullptr;
RunController* RunController::getInstance()
{
    if( g_pGameControllerInstance == nullptr )
        g_pGameControllerInstance = new RunController();
    
    return g_pGameControllerInstance;
}
RunController::RunController()
{
    m_pMainLayer        = nullptr;
}
RunController::~RunController()
{
}
bool RunController::init(Layer* pMainLayer)
{
    if(pMainLayer == nullptr)
        return false;
    m_pMainLayer = pMainLayer;
    
    return true;
}
void RunController::update(float delta)
{
    
}
void RunController::destroy()
{
    m_pMainLayer->removeAllChildren();
    m_pMainLayer = nullptr;
}