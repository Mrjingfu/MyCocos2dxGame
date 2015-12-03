//
//  Graph.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/9/24.
//
//

#include "Graph.h"
USING_NS_CC;

int PathGraphNode::getDistance() const
{
    return m_nDistance;
}
void PathGraphNode::setDistance(int distance)
{
    m_nDistance = distance;
}

int PathGraphNode::getWeight() const
{
    return m_nWeight;
}
void PathGraphNode::setWeight(int weigit)
{
    m_nWeight = weigit;
}
const std::vector<PathGraphNode*>& PathGraphNode::getNeigbours()
{
    return m_Neigbours;
}
void PathGraph::setWeight(const std::vector<PathGraphNode*>& nodes, int value)
{
    for (PathGraphNode* node : nodes) {
        node->setWeight(value);
    }
}
void PathGraph::buildDistanceMap(const std::vector<PathGraphNode*>& nodes, PathGraphNode* focus)
{
    for (PathGraphNode* node : nodes) {
        node->setDistance(INT_MAX);
    }
    focus->setDistance(0);
    std::queue<PathGraphNode*> queue;
    queue.push(focus);
    
    while (!queue.empty()) {
        PathGraphNode* node = queue.front();
        queue.pop();
        int distance = node->getDistance();
        int weight = node->getWeight();
        
        for (PathGraphNode* edge : node->getNeigbours()) {
            if (edge->getDistance() > distance + weight) {
                queue.push( edge );
                edge->setDistance( distance + weight );
            }
        }
    }
}
std::vector<PathGraphNode*> PathGraph::buildPath(const std::vector<PathGraphNode*>& nodes, PathGraphNode* from, PathGraphNode* to)
{
    std::vector<PathGraphNode*> path;
    
    PathGraphNode* area = from;
    while (area != to) {
        
        int min = area->getDistance();
        PathGraphNode* next = nullptr;
        
        std::vector<PathGraphNode*> edges = area->getNeigbours();
        
        for (PathGraphNode* edge : edges) {
            
            int distance = edge->getDistance();
            if (distance < min) {
                min = distance;
                next = edge;
            }
        }
        
        if (next == nullptr) {
            return path;
        }
        
        path.push_back(next);
        area = next;
    }
    return path;
}