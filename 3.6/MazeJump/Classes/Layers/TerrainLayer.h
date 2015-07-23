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
#include "TerrainPatternLayer.h"
#include "Runner.h"
class TerrainLayer : public cocos2d::Layer
{
    TerrainLayer();
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static TerrainLayer* create();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    virtual void update(float delta);
    
    float getCellBaseRadius() const { return m_fCellBaseRadius; }
    int getCurrentPatternIndex() const { return m_nCurrentPatternIndex; }
    void setCurrentPatternIndex( int index );
    
    int getCurrentColumn() const { return m_nColumn; }
    void setCurrentColumn( int column );
    
    int getCurrentRow() const { return m_nRow; }
    void setCurrentRow( int row );
    bool checkRunnerDrop();
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
    void jumpLocal();
    void clearClick(float time);
    
    bool generateStartPoint();
    void generatePattern(int index);
private:
    cocos2d::Vec2   m_TouchBegin;
    cocos2d::Vec2   m_TouchEnd;
    int             m_nTouchCount;
    
    int             m_nCurrentPatternIndex;
    int             m_nColumn;  //-2, -1, -, 1, 2
    int             m_nRow;
    
    float           m_fCellBaseRadius;
    
    cocos2d::Vector<TerrainPatternLayer*>   m_TerrainPatternList;
};

#endif /* defined(__MazeJump__TerrainLayer__) */
