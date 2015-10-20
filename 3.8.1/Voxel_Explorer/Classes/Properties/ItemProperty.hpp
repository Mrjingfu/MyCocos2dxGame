//
//  ItemProperty.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/20.
//
//

#ifndef ItemProperty_hpp
#define ItemProperty_hpp

#include "cocos2d.h"
#include "ChaosNumber.h"
class ItemProperty : public cocos2d::Ref
{
public:
    ItemProperty();
    ~ItemProperty();
private:
    CChaosNumber        m_nInstanceID;
    CChaosNumber        m_nItemType;
    
};

#endif /* ItemProperty_hpp */
