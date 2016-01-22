//
//  ItemMoneyLayer.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/12/2.
//
//

#ifndef ItemMoneyLayer_hpp
#define ItemMoneyLayer_hpp

#include "WrapperUILayer.h"
#include "ChaosNumber.h"
class ItemMoneyLayer :public WrapperUILayer {
    ItemMoneyLayer();
    
public:
    virtual ~ItemMoneyLayer();
    CREATE_FUNC(ItemMoneyLayer);
    virtual bool initUi() override;
    virtual bool addEvents() override;
    void  updateItemMoney(CChaosNumber money);
private:
    cocos2d::ui::TextBMFont*  m_pItemGoldNum;            // 金币
    cocos2d::ui::TextBMFont*  m_pItemSilverNum;          // 银币
    cocos2d::ui::TextBMFont*  m_pItemCopperNum;          // 铜币
    cocos2d::ui::ImageView* m_pItemGoldIcon;
    cocos2d::ui::ImageView* m_pItemSilverIcon;
    cocos2d::ui::ImageView* m_pItemCopperIcon;
};

#endif /* ItemMoneyLayer_hpp */
