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
#include "PopupType.h"
#include "GameConfig.h"
class GlobalPromptLayer;
class PopupUILayerManager:public cocos2d::Ref
{
public:
    ~PopupUILayerManager();
    
    static PopupUILayerManager* getInstance();
    
    PopupUILayer* openPopup(ePopupType type,int zorder= eZOrderPopupUILayer);
    //显示重要提示
    void showStatusImport(TipTypes tipType ,std::string text);
    //显示普通提示
    void showStatus(TipTypes tipType ,std::string text,cocos2d::Vec2 pos);
    void closeCurrentPopup();
    void onExitScene();
    void setParentLayer(cocos2d::Layer* parent);
    void closeAllPopup();
    bool isOpenPopup(ePopupType type,PopupUILayer* &pLayer);
    PopupUILayer* getCurrentPopUpLayer();
    PopupUILayer* getPopUpLayerByType(ePopupType type);
    ePopupType getCurrentPopUpType(){return m_cCurrentPopUpType;};
    void resetPopupType(ePopupType type);
    const std::list<ePopupType>& getCurrentPopupTypeList(){ return m_lTypeList; }
    cocos2d::Color3B getTipsColor(TipTypes tipType);
private:
    PopupUILayerManager();
    
    PopupUILayer* initPopUp(ePopupType type);
private:
    PopupUILayer* m_pPopupContainer[ePopupCount];
    cocos2d::Layer* m_pParentLayer;
    GlobalPromptLayer* m_pGlobalPromptlayer;
    ePopupType m_cCurrentPopUpType,m_pLastPopUpType;
    std::list<ePopupType> m_lTypeList;
    
};

#endif /* defined(__Tone_Skipper__PopupUILayerManager__) */
