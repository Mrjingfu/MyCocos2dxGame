//
//  MenuUILayer.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/20.
//
//

#ifndef MenuUILayer_h
#define MenuUILayer_h

#include "WrapperUILayer.h"
#include "TGridView.h"
class AchievePopupUI;
class MenuUILayer:public WrapperUILayer {
    
public:
    MenuUILayer();
    virtual ~MenuUILayer();
public:
    CREATE_FUNC(MenuUILayer);
    virtual bool addEvents();
protected:
    void onClickStart(Ref* ref);
    void onClickSetting(Ref*);
    void onClickRank(Ref*);
    void onClickRate(Ref*);
    void onClickAchieve(Ref*);
private:
    AchievePopupUI* m_pAchievePopupUI;
    
};

#endif /* MenuUILayer_h */
