//
//  GlobalPromptLayer.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/12/15.
//
//

#ifndef AchieveItemLayer_hpp
#define AchieveItemLayer_hpp

#include "WrapperUILayer.h"
#include "PopupUILayerManager.h"
class AchieveItemUI;
class AchieveItemLayer: public WrapperUILayer {
    
    AchieveItemLayer();
public:
    CREATE_FUNC(AchieveItemLayer);
    virtual ~AchieveItemLayer();
    virtual void refreshUIView();
    virtual bool initUi();
    void inAction(AchieveItemUI* itemUi) ;
    void outAction(AchieveItemUI* itemUi);
    void moveAction(AchieveItemUI* itemUi,cocos2d::Vec2 pt);
    void showAchieveItem(const std::string icon,const std::string name,const std::string targetDesc);
    void clearAchieveItem();
private:
    void removeAchieveItem(cocos2d::Node* node);
private:
    cocos2d::Vector<AchieveItemUI*> m_vAchieves;
};

#endif /* AchieveItemLayer_hpp */
