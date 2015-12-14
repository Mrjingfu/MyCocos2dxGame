//
//  Pathfinder.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/11/5.
//
//

#ifndef Pathfinder_hpp
#define Pathfinder_hpp

#include "cocos2d.h"
#include "BaseLevel.h"
class Pathfinder : public cocos2d::Ref
{
    Pathfinder();
    virtual ~Pathfinder();
public:
    static Pathfinder* getInstance();
    bool init(int width, int height);
    
    std::list<int> findPath(int from, int to, const std::vector<TileInfo>& tilesInfo );
    int getStep(int from, int to, const std::vector<TileInfo>& tilesInfo);
    int getStepBack(int cur, int from, const std::vector<TileInfo>& tilesInfo);
    void buildDistanceMap(int to, const std::vector<TileInfo>& tilesInfo, int limit);
private:
    bool buildDistanceMap(int from, int to, const std::vector<TileInfo>& tilesInfo);
    int buildEscapeDistanceMap(int cur, int from, float factor,const std::vector<TileInfo>& tilesInfo);
    bool buildDistanceMap(int from, const std::vector<bool>& to, const std::vector<TileInfo>& tilesInfo);
private:
    int                 m_nSize;
    std::vector<int>    m_Distance;
    std::vector<bool>   m_Goals;
    std::vector<int>    m_Queue;
    std::vector<int>    m_Dir;
};

#endif /* Pathfinder_hpp */
