//
//  ItemUI.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/23.
//
//

#ifndef BagManngerLayerUI_hpp
#define BagManngerLayerUI_hpp

#include "ui/CocosGUI.h"
#include "ChaosNumber.h"
#include "PickableItemProperty.hpp"
class BagManngerLayerUI:public cocos2d::ui::Layout {
    
    BagManngerLayerUI();
public:
    virtual ~BagManngerLayerUI();
    static BagManngerLayerUI* create(cocos2d::Size size);
    bool init(cocos2d::Size size);
    void addItem(int index,int itemId,cocos2d::Vec2 pt,std::string itemIcon);
    void setItemQulity(cocos2d::Vec2 pt,PICKABLEITEM_QUALITY Quality);
    void setItemCount(cocos2d::Vec2 pt,int count);
    void setItemEquipMark(cocos2d::Vec2 pt);
    void setItemInIentify(cocos2d::Vec2 pt);
    void removeItems();
    int  getItemId  (int index)const;
    void setLayerContentSize(const cocos2d::Size &contentSize);
protected:
    cocos2d::ui::Layout* m_pItemImgLayer;
    cocos2d::ui::Layout* m_pEquipMarkLayer;
    cocos2d::ui::Layout* m_pItemCountLayer;
    cocos2d::ui::Layout* m_pIteminIentifyLayer;
    std::map<int,int> m_items;
};

#endif /* BagManngerLayerUI_hpp */
