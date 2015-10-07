//
//  CloseCallback.h
//  Tone_Skipper
//
//  Created by 创李 on 15/9/18.
//
//

#ifndef __Tone_Skipper__CloseCallback__
#define __Tone_Skipper__CloseCallback__

#include "cocos2d.h"
class CloseCallback
{
public:
    CloseCallback();
    virtual ~CloseCallback();
protected:
    typedef std::function<void()> CloseTarget;
    typedef std::function<void(cocos2d::Ref*)> CloseTarget0;
    typedef std::function<void(void*)> CloseTargetD;
public:
    
    virtual void registerCloseCallback(CloseTarget selector);// 注册关闭时回调
    virtual void executeCloseBack();//执行关闭回调
    
    virtual void registerCloseCallbackO(CloseTarget0 selector);// 注册关闭时回调
    virtual void executeCloseBackO();//执行关闭回调 modified
    virtual void setCloseCallbackParamO(cocos2d::Ref* param);// 设置回调参数
    
    virtual void registerCloseCallbackD(CloseTargetD selector);	// 注册带void*参数的回调
    virtual void executeCloseCallbackD();		// data参数由具体的子类设置m_pCallBackData的值
    virtual void setCloseCallbackParamD(void *data);

protected:
    
    // 不带参：关闭回调参数
    CloseTarget m_pCloseCallbackTargetFunc;

    // 带参： 关闭回调的接受者指针
    CloseTarget0 m_pCloseCallbackTargetFuncO;
    cocos2d::Ref* m_pCloseCallbackTargetFuncParamO;
    
    // 带void*参数的回调
    void *m_pCloseCallbackParamD;	// 注意：必须在closePopup前赋值 
    CloseTargetD m_pCloseCallbackTargetFuncD;

};


#endif /* defined(__Tone_Skipper__CloseCallback__) */
