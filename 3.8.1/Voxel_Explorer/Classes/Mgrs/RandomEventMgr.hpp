//
//  RandomEventMgr.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/12/23.
//
//

#ifndef RandomEventMgr_hpp
#define RandomEventMgr_hpp

#include "cocos2d.h"
typedef enum{
    
    RET_WALL_STANDARD = 0,        ////墙壁标准
    RET_TERRAIN_STANDARD = 1,     ////地板标准
    RET_TERRAIN_ADDMONEY,         ////地板加钱

    RET_MAX
} RANDOM_EVENT_TYPE;
class RandomEventMgr : public cocos2d::Ref
{
    RandomEventMgr();
    ~RandomEventMgr();
public:
    static RandomEventMgr* getInstance();
    bool load(const cocos2d::ValueMap& data);
    bool save(cocos2d::ValueMap& data);
    
    const cocos2d::ValueVector& getEventList() const { return m_EventList; }
    
    cocos2d::ValueMap* getRandomEvent();
private:
    cocos2d::ValueMap          m_LastRandomEvent;
    cocos2d::ValueVector       m_EventList;
};
#endif /* RandomEventMgr_hpp */
