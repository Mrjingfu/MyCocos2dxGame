//
//  TerrainLayer.h
//  MazeJump
//
//  Created by wang haibo on 15/7/22.
//
//

#ifndef __MazeJump__TerrainLayer__
#define __MazeJump__TerrainLayer__

#include "cocos2d.h"
#include "GroundCell.h"

class TerrainLayer : public cocos2d::Layer
{
    TerrainLayer();
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static TerrainLayer* create();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    float getCellRadius() const { return m_fCellRadius; }
protected:
    // 处理输入
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) override;
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event) override;
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event) override;
private:
    void jumpLeft();
    void jumpRight();
    void jumpForward();
    void jumpSuper();
    void clearClick(float time);
    
    bool generatePattern(int index);
private:
    cocos2d::Vec2   m_TouchBegin;
    cocos2d::Vec2   m_TouchEnd;
    int             m_nTouchCount;
    
    float           m_fCellRadius;
    int             m_nCurrentPattern;
};

#endif /* defined(__MazeJump__TerrainLayer__) */
