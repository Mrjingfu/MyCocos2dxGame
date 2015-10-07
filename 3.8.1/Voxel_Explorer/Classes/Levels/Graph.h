//
//  Graph.h
//  Voxel_Explorer
//
//  Created by wang haibo on 15/9/24.
//
//

#ifndef __Voxel_Explorer__Graph__
#define __Voxel_Explorer__Graph__

#include "cocos2d.h"
class PathGraphNode
{
public:
    virtual int getDistance() const;
    virtual void setDistance(int distance);
    
    virtual int getWeight() const;
    virtual void setWeight(int weigit);
    
    const std::vector<PathGraphNode*>& getNeigbours();
protected:
    int     m_nDistance;
    int     m_nWeight;
    std::vector<PathGraphNode*>     m_Neigbours;
};
class PathGraph
{
public:
    static void setWeight(const std::list<PathGraphNode*>& nodes, int value);
    static void buildDistanceMap(const std::vector<PathGraphNode*>& nodes, PathGraphNode* focus);
    static std::list<PathGraphNode*> buildPath(const std::vector<PathGraphNode*>& nodes, PathGraphNode* from, PathGraphNode* to);
};
#endif /* defined(__Voxel_Explorer__Graph__) */
