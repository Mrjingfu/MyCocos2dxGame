//
//  Area.h
//  Voxel_Explorer
//
//  Created by wang haibo on 15/9/24.
//
//

#ifndef __Voxel_Explorer__Area__
#define __Voxel_Explorer__Area__

#include "cocos2d.h"
#include "Door.h"
#include "Graph.h"
class Area : public cocos2d::Ref, public PathGraphNode
{
    Area();
public:
    typedef enum{
        AT_UNKNOWN = 0,
        AT_STANDARD,
        AT_ENTRANCE,
        AT_EXIT,
        AT_PASSAGE,      ///通道
        AT_TUNNEL,       ///隧道
        
        AT_SPECIAL_SECRET,      ///秘密地点
        AT_SPECIAL_WEAKFLOOR,   ///坏地板
        AT_SPECIAL_PIT,     ///坑
        AT_MAX
    }
    AREA_TYPE;
    
    static std::vector<AREA_TYPE>       SPECIALS;
    
    static Area* create();
    virtual bool init();
    
    void addNeigbourArea(Area* other );
    void connectArea(Area* other);
    Door* getEntrance();
    
    bool checkInside(int p);
    cocos2d::Vec2 getPos();
    
    AREA_TYPE getAreaType() const;
    void setAreaType(AREA_TYPE type);
    
    cocos2d::Rect getRect() const;
    void setRect(const cocos2d::Rect& rect);
    
    cocos2d::Rect getIntersectRect(Area* other);
    
    std::unordered_map<Area*, Door*>& getConnectedAreas() { return m_ConnectedAreas; }
protected:
    AREA_TYPE           m_Type;
    cocos2d::Rect       m_Rect;
    
    std::unordered_map<Area*, Door*>    m_ConnectedAreas;
};

#endif /* defined(__Voxel_Explorer__Area__) */
