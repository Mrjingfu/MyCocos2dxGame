//
//  ItemUI.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/10/23.
//
//

#ifndef ItemUI_hpp
#define ItemUI_hpp

#include "ui/CocosGUI.h"
#include "ChaosNumber.h"
#include "PickableItemProperty.hpp"
class ItemUI:public cocos2d::ui::Layout {
    
    ItemUI();
public:
    virtual ~ItemUI();
    static ItemUI* create();
    bool init();
    bool isHaveItem()const{return _isHaveItem;}
    void setEquipEnable(bool enable);
    bool isEquipEnable(){return _isEquip;}
    void addItem(int _itemId,std::string itemIcon,PICKABLEITEM_QUALITY Quality);
    void addItem(int _itemId,std::string itemIcon,PICKABLEITEM_QUALITY Quality,int itemNum);
    void setIndentify();
    int  getItemId() const{return m_nItemId;}
    void removeItem();
protected:
    bool _isHaveItem;
    bool _isEquip;
    
    cocos2d::ui::ImageView* m_pItemImage;
    cocos2d::ui::ImageView* m_pEquipmark;
    cocos2d::ui::ImageView* m_pIndentifymark;
    cocos2d::ui::Text*      m_pItemCount;
    int m_nItemId;
};

#endif /* ItemUI_hpp */
