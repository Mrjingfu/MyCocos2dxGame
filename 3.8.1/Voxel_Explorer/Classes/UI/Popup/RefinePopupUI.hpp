//
//  WashPopupUI.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 16/3/15.
//
//

#ifndef RefinePopupUI_hpp
#define RefinePopupUI_hpp
#include "PopupUILayer.h"
class BagRefineLayer;
class BagMangerLayerUI;
class PickableItemProperty;
class  RefinePopupUI : public PopupUILayer{
    RefinePopupUI();
    
public:
    ~RefinePopupUI();
    CREATE_FUNC(RefinePopupUI);
    
    virtual bool initUi() override;
    virtual bool addEvents() override;
    void refreshUIView() override;
    void onEnter() override;
    void onExit() override;
    void update(float dt) override;
private:
     void onClickClose(Ref* ref);
    void updateMaterial(Ref* data);
    void updateEquipFrame(PickableItemProperty* prop);
    void onClickWash(Ref* ref);
    void itemWash();
    void updateMaterialDisplay(bool isWhite,bool isGreen,bool isBlue,bool isPurple);
    void addIconImg( cocos2d::ui::ImageView* sourceImg,std::string iconStr);
private:
    cocos2d::ui::ImageView* m_pBgFrame;
    cocos2d::ui::ImageView* m_pEquipFrame;
    cocos2d::ui::ImageView* m_pWhiteMaterial;
    cocos2d::ui::ImageView* m_pGreenMaterial;
    cocos2d::ui::ImageView* m_pBlueMaterial;
    cocos2d::ui::ImageView* m_pPurpleMaterial;
    
    cocos2d::ui::TextBMFont* m_pWhiteMaterialText;
    cocos2d::ui::TextBMFont* m_pGreenMaterialText;
    cocos2d::ui::TextBMFont* m_pBlueMaterialText;
    cocos2d::ui::TextBMFont* m_pPurpleMaterialText;
    
    cocos2d::ui::TextBMFont* m_pTipText;
    cocos2d::ui::Button* m_pBtnWash;
    
    BagRefineLayer* m_pBagEquipLayer;
    cocos2d::ui::TextBMFont*  m_pEquipTitleText;

    bool m_bIsCallBack;
    int m_nEquipWashId;
    PickableItemProperty* m_pOldProp;
    
};

#endif /* RefinePopupUI_hpp */
