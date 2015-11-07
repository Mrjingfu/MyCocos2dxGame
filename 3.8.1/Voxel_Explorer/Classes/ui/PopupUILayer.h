//
//  PopupUILayer.h
//  Tone_Skipper
//
//  Created by 创李 on 15/9/18.
//
//

#ifndef __Tone_Skipper__PopupUILayer__
#define __Tone_Skipper__PopupUILayer__

#include "WrapperUILayer.h"
#include "PopupType.h"

class PopupUILayer:public WrapperUILayer {

public:
    enum eActionType
    {
        eNone,
        eCenterScale,
        eDownCenter,
        eTopCenter,
        eLeftCenter,
        eRightCenter
    };
    
public:
    PopupUILayer();
    virtual ~PopupUILayer();
public:
    virtual bool init();
    CREATE_FUNC(PopupUILayer);
    virtual void onEnter();
    virtual void onExit();
    virtual void openPopup();
    virtual void closePopup();
    virtual void onKeyBackClick();
    
    /*
     *自定义动作模式
     */
    virtual void inAction();
    virtual void outAction();
    virtual void removeSelfCallFunc();
    
    void setActionType(eActionType type);
    virtual void inActionCallFunc();
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

    void setDarkLayerVisble(bool visble);
    void setPopupType(ePopupType type){m_pPopupType = type;};
    ePopupType getPopupType(){return m_pPopupType;};

protected:
    void enableDarkLayer(bool bEnable);
private:
    void inActionCenterScale();
    void outActionCenterScale();
    
    void inActionDownCenter();
    void outActionDownCenter();
    
    void inActionTopCenter();
    void outActionTopCenter();

    void inActionLeftCenter();
    void outActionLeftCenter();
    
    void inActionRightCenter();
    void outActionRightCenter();
    
    

protected:
    bool m_nIsPause;
    eActionType m_cActionType;
    cocos2d::LayerColor* m_pDarkLayer;
    ePopupType m_pPopupType;
};

#endif /* defined(__Tone_Skipper__PopupUILayer__) */
