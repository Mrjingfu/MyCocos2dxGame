//
//  TerrainPatternLayer.h
//  MazeJump
//
//  Created by wang haibo on 15/7/23.
//
//

#ifndef __MazeJump__TerrainPatternLayer__
#define __MazeJump__TerrainPatternLayer__

#include "cocos2d.h"
#include "TerrainCell.h"
#include "Decorator.h"
#include "Runner.h"
class TerrainPatternLayer : public cocos2d::Layer
{
    TerrainPatternLayer();
public:
    typedef enum {
        FIT_NONE = 0,
        FIT_RANDOM_UP
    } FadeInType;
    
    typedef enum {
        PT_STARTER = 0,
        PT_DOUBLESIDEBAR = 1,
        PT_LEFTSIDEBAR = 2,
        PT_RIGHTSIDEBAR = 3,
        PT_NOBAR = 4,
        PT_CHECKPOINT = 5
    } PatternType;

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static TerrainPatternLayer* create(int index, bool generateCheckPoint);
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(int index, bool generateCheckPoint);
    
    virtual void update(float delta);
    
    void reset();
    
    PatternType getPatternType() const { return m_patternType; }

    bool checkRunnerDrop();
    void beginCollapse();
    void checkCollisionDecorator();
private:
    void onLand(TerrainCell* cell);
    void generateDecorator(TerrainCell* cell, int patternIndex);
    void generateCheckPointDecorator();
private:
    int         m_nIndex;
    cocos2d::Vector<TerrainCell*>   m_TerrainCellList;
    cocos2d::Vector<Decorator*>   m_DecoratorList;
    FadeInType  m_fadeInType;
    PatternType m_patternType;
};

#endif /* defined(__MazeJump__TerrainPatternLayer__) */
