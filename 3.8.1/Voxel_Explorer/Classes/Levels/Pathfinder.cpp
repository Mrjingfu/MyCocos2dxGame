//
//  Pathfinder.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/11/5.
//
//

#include "Pathfinder.hpp"
USING_NS_CC;

Pathfinder* g_pPathfinderInstance = nullptr;
Pathfinder* Pathfinder::getInstance()
{
    if( g_pPathfinderInstance == nullptr )
        g_pPathfinderInstance = new Pathfinder();
    
    return g_pPathfinderInstance;
}
Pathfinder::Pathfinder()
{
    m_nSize = 0;
}
Pathfinder::~Pathfinder()
{
}

bool Pathfinder::init(int width, int height)
{
    int size = width * height;
    
    if (m_nSize != size) {
        
        m_nSize = size;
        m_Distance.resize(m_nSize);
        m_Goals.resize(m_nSize);
        m_Queue.resize(m_nSize);
        
        m_Dir = {-1, +1, -width, +width, -width-1, -width+1, +width-1, +width+1};
        
        return true;
    }
    return false;
}
std::list<int> Pathfinder::findPath(int from, int to, const std::vector<TileInfo>& tilesInfo )
{
    std::list<int> result;
    if (!buildDistanceMap( from, to, tilesInfo )) {
        return result;
    }
    int s = from;
    
    // From the starting position we are moving downwards,
    // until we reach the ending point
    do {
        int minD = m_Distance[s];
        int mins = s;
        
        for (int i=0; i < m_Dir.size(); i++) {
            
            int n = s + m_Dir[i];
            
            int thisD = m_Distance[n];
            if (thisD < minD) {
                minD = thisD;
                mins = n;
            }
        }
        s = mins;
        result.push_back(s);
    } while (s != to);
    
    return result;
}
int Pathfinder::getStep(int from, int to, const std::vector<TileInfo>& tilesInfo)
{
    if (!buildDistanceMap( from, to, tilesInfo )) {
        return -1;
    }
    
    // From the starting position we are making one step downwards
    int minD = m_Distance[from];
    int best = from;
    
    int step, stepD;
    
    for (int i = 0; i < m_Dir.size(); i++) {
        
        if ((stepD = m_Distance[step = from + m_Dir[i]]) < minD) {
            minD = stepD;
            best = step;
        }
    }
    
    return best;
}
int Pathfinder::getStepBack(int cur, int from, const std::vector<TileInfo>& tilesInfo)
{
    int d = buildEscapeDistanceMap( cur, from, 2.0f, tilesInfo );
    for (int i=0; i < m_nSize; i++) {
        m_Goals[i] = m_Distance[i] == d;
    }
    if (!buildDistanceMap( cur, m_Goals, tilesInfo )) {
        return -1;
    }
    
    int s = cur;
    
    // From the starting position we are making one step downwards
    int minD = m_Distance[s];
    int mins = s;
    
    for (int i=0; i < m_Dir.size(); i++) {
        
        int n = s + m_Dir[i];
        int thisD = m_Distance[n];
        
        if (thisD < minD) {
            minD = thisD;
            mins = n;
        }
    }
    
    return mins;
}

void Pathfinder::buildDistanceMap(int to, const std::vector<TileInfo>& tilesInfo, int limit)
{
    for(int i = 0; i < m_Distance.size(); i++) {
        m_Distance[i] = INT_MAX;
    }
    
    int head = 0;
    int tail = 0;
    
    // Add to queue
    m_Queue[tail++] = to;
    m_Distance[to] = 0;
    
    while (head < tail) {
        
        // Remove from queue
        int step = m_Queue[head++];
        
        int nextDistance = m_Distance[step] + 1;
        if (nextDistance > limit) {
            return;
        }
        
        for (int i=0; i < m_Dir.size(); i++) {
            
            int n = step + m_Dir[i];
            if (n >= 0 && n < m_nSize && tilesInfo[n].isPassable() && (m_Distance[n] > nextDistance)) {
                // Add to queue
                m_Queue[tail++] = n;
                m_Distance[n] = nextDistance;
            }
            
        }
    }
}

bool Pathfinder::buildDistanceMap(int from, int to, const std::vector<TileInfo>& tilesInfo)
{
    if (from == to) {
        return false;
    }
    for(int i = 0; i < m_Distance.size(); i++) {
        m_Distance[i] = INT_MAX;
    }
    
    bool pathFound = false;
    
    int head = 0;
    int tail = 0;
    
    // Add to queue
    m_Queue[tail++] = to;
    m_Distance[to] = 0;
    
    while (head < tail) {
        
        // Remove from queue
        int step = m_Queue[head++];
        if (step == from) {
            pathFound = true;
            break;
        }
        int nextDistance = m_Distance[step] + 1;
        
        for (int i=0; i < m_Dir.size(); i++) {
            
            int n = step + m_Dir[i];
            if (n == from || (n >= 0 && n < m_nSize && tilesInfo[n].isPassable() && (m_Distance[n] > nextDistance))) {
                // Add to queue
                m_Queue[tail++] = n;
                m_Distance[n] = nextDistance;
            }
            
        }
    }
    
    return pathFound;
}
bool Pathfinder::buildEscapeDistanceMap(int cur, int from, float factor,const std::vector<TileInfo>& tilesInfo)
{
    for(int i = 0; i < m_Distance.size(); i++) {
        m_Distance[i] = INT_MAX;
    }
    
    int destDist = INT_MAX;
    
    int head = 0;
    int tail = 0;
    
    // Add to queue
    m_Queue[tail++] = from;
    m_Distance[from] = 0;
    
    int dist = 0;
    
    while (head < tail) {
        
        // Remove from queue
        int step = m_Queue[head++];
        dist = m_Distance[step];
        
        if (dist > destDist) {
            return destDist;
        }
        
        if (step == cur) {
            destDist = (int)(dist * factor) + 1;
        }
        
        int nextDistance = dist + 1;
        
        for (int i=0; i < m_Dir.size(); i++) {
            
            int n = step + m_Dir[i];
            if (n >= 0 && n < m_nSize && tilesInfo[n].isPassable() && m_Distance[n] > nextDistance) {
                // Add to queue
                m_Queue[tail++] = n;
                m_Distance[n] = nextDistance;
            }
            
        }
    }
    
    return dist;
}
bool Pathfinder::buildDistanceMap(int from, const std::vector<bool>& to, const std::vector<TileInfo>& tilesInfo)
{
    if (to[from]) {
        return false;
    }
    
    for(int i = 0; i < m_Distance.size(); i++) {
        m_Distance[i] = INT_MAX;
    }
    
    bool pathFound = false;
    
    int head = 0;
    int tail = 0;
    
    // Add to queue
    for (int i=0; i < m_nSize; i++) {
        if (to[i]) {
            m_Queue[tail++] = i;
            m_Distance[i] = 0;
        }
    }
    
    while (head < tail) {
        
        // Remove from queue
        int step = m_Queue[head++];
        if (step == from) {
            pathFound = true;
            break;
        }
        int nextDistance = m_Distance[step] + 1;
        
        for (int i=0; i < m_Dir.size(); i++) {
            
            int n = step + m_Dir[i];
            if (n == from || (n >= 0 && n < m_nSize && tilesInfo[n].isPassable() && (m_Distance[n] > nextDistance))) {
                // Add to queue
                m_Queue[tail++] = n;
                m_Distance[n] = nextDistance;
            }
            
        }
    }
    
    return pathFound;
}