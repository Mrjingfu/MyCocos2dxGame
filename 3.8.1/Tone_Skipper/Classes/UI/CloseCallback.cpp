//
//  CloseCallback.cpp
//  Tone_Skipper
//
//  Created by 创李 on 15/9/18.
//
//

#include "CloseCallback.h"
CloseCallback::CloseCallback():
    m_pCloseCallbackTargetFunc(nullptr),
    m_pCloseCallbackTargetFuncO(nullptr),
    m_pCloseCallbackTargetFuncParamO(nullptr),
    m_pCloseCallbackTargetFuncD(nullptr),
    m_pCloseCallbackParamD(nullptr)
{
    
}
CloseCallback::~CloseCallback()
{
    
}
void CloseCallback::registerCloseCallback( CloseTarget selector)
{
    if (m_pCloseCallbackTargetFunc)
        m_pCloseCallbackTargetFunc = nullptr;
    m_pCloseCallbackTargetFunc = selector;
}
void CloseCallback::executeCloseBack()
{

    if (m_pCloseCallbackTargetFunc) {
        m_pCloseCallbackTargetFunc();
        m_pCloseCallbackTargetFunc = nullptr;
    }

}

void CloseCallback::registerCloseCallbackO(CloseTarget0 selector)
{
    if (m_pCloseCallbackTargetFuncO)
        m_pCloseCallbackTargetFuncO = nullptr;
    m_pCloseCallbackTargetFuncO = selector;

}
void CloseCallback::setCloseCallbackParamO(cocos2d::Ref *param)
{
    if (m_pCloseCallbackTargetFuncParamO)
        m_pCloseCallbackTargetFuncParamO = nullptr;
    m_pCloseCallbackTargetFuncParamO = param;
}
void CloseCallback::executeCloseBackO()
{

    if (m_pCloseCallbackTargetFuncO) {
        m_pCloseCallbackTargetFuncO(m_pCloseCallbackTargetFuncParamO);
        m_pCloseCallbackTargetFuncO = nullptr;
    }
    
}

void CloseCallback::registerCloseCallbackD(CloseTargetD selector)
{
    if (m_pCloseCallbackTargetFuncD)
        m_pCloseCallbackTargetFuncD = nullptr;
    m_pCloseCallbackTargetFuncD = selector;
    
}

void CloseCallback::setCloseCallbackParamD(void *data)
{
    if (m_pCloseCallbackParamD)
        m_pCloseCallbackParamD = nullptr;

    m_pCloseCallbackParamD = data;
}
void CloseCallback::executeCloseCallbackD()
{
    if (m_pCloseCallbackTargetFuncD) {
        m_pCloseCallbackTargetFuncD(m_pCloseCallbackParamD);
        m_pCloseCallbackTargetFuncD = nullptr;
    }
}

