//
//  ItemUI.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/23.
//
//

#ifndef BagMangerLayerUI_hpp
#define BagMangerLayerUI_hpp

#include "ui/CocosGUI.h"
#include "ChaosNumber.h"
#include "PickableItemProperty.hpp"
class AchieveMangerLayerUI:public cocos2d::ui::Layout {
    
    AchieveMangerLayerUI();
public:
    virtual ~AchieveMangerLayerUI();
    static AchieveMangerLayerUI* create(cocos2d::Size size);
    bool init(cocos2d::Size size);
    void addItem(int index,int itemId,cocos2d::Vec2 pt,std::string itemIcon);
    void setItemQulity(int itemId,cocos2d::Vec2 pt,PICKABLEITEM_QUALITY Quality);
    void setItemCount(int itemId,cocos2d::Vec2 pt,int count);

    void removeItems();
    void removeItem(int index);
 
    int  getItemId  (int index)const;
    void setLayerContentSize(const cocos2d::Size &contentSize);
protected:
    cocos2d::ui::Layout* m_pItemImgLayer;
    cocos2d::ui::Layout* m_pEquipMarkLayer;
    cocos2d::ui::Layout* m_pItemCountLayer;

    std::map<int,int> m_items;
};

#endif /* BagMangerLayerUI */
