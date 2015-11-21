//
//  ItemUI.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/23.
//
//

#ifndef BagLayerUI_hpp
#define BagLayerUI_hpp

#include "ui/CocosGUI.h"
#include "ChaosNumber.h"
#include "PickableItemProperty.hpp"
class BagLayerUI:public cocos2d::ui::Layout {
    
    BagLayerUI();
public:
    virtual ~BagLayerUI();
    static BagLayerUI* create(cocos2d::Size size);
    bool init(cocos2d::Size size);
    void addItem(int index,int itemId,cocos2d::Vec2 pt,std::string itemIcon);
    void setItemQulity(cocos2d::Vec2 pt,PICKABLEITEM_QUALITY Quality);
    void setItemCount(cocos2d::Vec2 pt,int count);
    void setItemEquipMark(cocos2d::Vec2 pt);
    void removeItems();
    int  getItemId  (int index)const;
protected:
    cocos2d::ui::Layout* m_pItemImgLayer;
    cocos2d::ui::Layout* m_pEquipMarkLayer;
    cocos2d::ui::Layout* m_pItemCountLayer;
    std::map<int,int> m_items;
};

#endif /* BagLyaerUI_hpp */
