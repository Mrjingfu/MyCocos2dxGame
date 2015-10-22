//
//  WrapperUILayer.h
//  Tone_Skipper
//
//  Created by 创李 on 15/9/18.
//
//

#ifndef __Tone_Skipper__WrapperUILayer__
#define __Tone_Skipper__WrapperUILayer__

#include "GameConfig.h"
#include "ui/CocosGUI.h"
#include "CloseCallback.h"
#include "editor-support/cocostudio/CocoStudio.h"

#define CHECK_ACTION_WRAPPER(sender, type) \
do{ \
CHECK_ACTION(sender, type); \
if (type != cocos2d::ui::Widget::TouchEventType::ENDED) \
{ \
return; \
} \
}while(0)
#define CHECK_ACTION(sender, type) do{  if(isForbiddenAction(sender,type))  return ;}while(0)
class WrapperUILayer :public cocos2d::Layer,public CloseCallback{
    
public:
    WrapperUILayer();
    virtual ~WrapperUILayer();
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float dt){};
    //刷新UI
    virtual void refreshUIView(){};
    virtual bool addEvents(){return true;};          //cocostudio布局用到
    virtual bool initUi(){return true;}; //手工编写ui布局用到
    bool isForbiddenAction(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    CREATE_FUNC(WrapperUILayer);
    cocos2d::Layer* getRootLayer(){return m_pRootLayer;};
    cocos2d::Node* getRootNode() {return m_pRootNode;}
    
public:
    //可能以后有UI布局文件会用到 m_pRootLayer由布局文件生成了 暂时不会用到
    virtual bool load(const std::string gameUIFile,bool isSceneUi = true);
    
protected:
    cocos2d::Layer*	m_pRootLayer;   //手工编写ui布局用到
    cocos2d::Node*	m_pRootNode;//cocostudio布局用到
    Ref* m_actionRef;
    
    timeval m_actionTime;

    
};


#endif /* defined(__Tone_Skipper__WrapperUILayer__) */
