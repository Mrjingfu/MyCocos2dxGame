//
//  PopupUILayerManager.h
//  Tone_Skipper
//
//  Created by 创李 on 15/9/18.
//
//

#ifndef __Tone_Skipper__PopupUILayerManager__
#define __Tone_Skipper__PopupUILayerManager__

#include "cocos2d.h"
#include "PopupUILayer.h"
#include "GameConfig.h"
#include "PopupType.h"
class PopupUILayerManager:public cocos2d::Ref
{
public:
    ~PopupUILayerManager();
    
    static PopupUILayerManager* getInstance();
    
    PopupUILayer* openPopup(ePopupType type,int zorder= eZOrderPopupUILayer);
    void closeCurrentPopup();
    void onExitScene();
    void setParentLayer(cocos2d::Layer* parent);
    
    bool isOpenPopup(ePopupType type,PopupUILayer* &pLayer);
    PopupUILayer* getCurrentPopUpLayer();
    PopupUILayer* getPopUpLayerByType(ePopupType type);
    ePopupType getCurrentPopUpType(){return m_pCurrentPopUpType;};
    void resetPopupType(ePopupType type);
    const std::list<ePopupType>& getCurrentPopupTypeList(){ return m_pTypeList; }
private:
    PopupUILayerManager();
    PopupUILayer* initPopUp(ePopupType type);
private:
    PopupUILayer* m_pPopupContainer[ePopupCount];
    cocos2d::Layer* m_pParentLayer;
    
    ePopupType m_pCurrentPopUpType,m_pLastPopUpType;
    std::list<ePopupType> m_pTypeList;
    
};

#endif /* defined(__Tone_Skipper__PopupUILayerManager__) */
