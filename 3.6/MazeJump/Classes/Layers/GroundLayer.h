//
//  GroundLayer.h
//  MazeJump
//
//  Created by wang haibo on 15/6/24.
//
//

#ifndef __MazeJump__GroundLayer__
#define __MazeJump__GroundLayer__

#include "cocos2d.h"
#include "GroundCell.h"
#include "Arrow.h"
#include "Player.h"
#include "Decorator.h"
class GroundLayer : public cocos2d::Layer
{
    GroundLayer();
public:
    typedef enum {
        RD_START,
        RD_NEXT,
        RD_END
    } RecordState;
    
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static GroundLayer* create(int level,bool _isPlaying);
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(int level);
    
    cocos2d::Vec3 getOffset() const { return m_Offset; }
    float getGroundRadius() { return MAX(m_fCellRadius*m_MapSize.width, m_fCellRadius*m_MapSize.height); }
    cocos2d::Size  getMapSize() const { return m_MapSize; }
    
    void setCamera(cocos2d::Camera* camera) { m_pCamera = camera; }
    
    cocos2d::Vector<GroundCell*> getNeighborCells(GroundCell* currentCell);
    
    float getCellRadius() const { return m_fCellRadius; }
    
    GroundCell* getNextCell(int nextIndexX, int nextIndexY);
    
    void flipIndexCell(int indexX, int indexY);
    void carryCell(int indexX,int indexY);
    void setCurrentCellTypeOK();
    void showArrow();
    void checkWinOrLose();
    //移动检测
    void checkSildeHandle( bool isTouchDown , bool isToucLeft,bool isToucRight , bool isToucUp  );
    //选择主角开始位置
    void seleckStartRolePlace(int index);
    
    bool getPlaying(){return m_Playing;};
    void setPlaying(bool _isPlaying){m_Playing = _isPlaying;}
    
    void playRecord();
    void initEnd();
    void setRecordState(RecordState state);
    void generateDecorator(GroundCell* cell);
    void decoratorOpe(Node* node,GroundCell* cell);
    void setPattentIndex(int index){m_pattentIndex = index;};
    int getPattentIndex(){return m_pattentIndex;}
protected:
    // 处理输入
    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event) override;
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event) override;
    virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event) override;
private:
    cocos2d::Vector<GroundCell*>   m_GroundCellList;
    GroundCell*     m_pCurrentCell;
    Arrow*          m_pArrowUp;
    Arrow*          m_pArrowDown;
    Arrow*          m_pArrowLeft;
    Arrow*          m_pArrowRight;
    
    Player*         m_pPlayer;
    
    cocos2d::Size   m_MapSize;
    float           m_fCellRadius;
    cocos2d::Vec3   m_Offset;
    
    cocos2d::Camera*    m_pCamera;
    cocos2d::Vec2   m_GroundTouchBegin;
    int             m_Level;
    bool m_Playing;
    bool m_isInit;
    cocos2d::ValueVector recordSteps;
    cocos2d::Map<int, Decorator*>   m_DecoratorList;
    int m_pattentIndex;
};

#endif /* defined(__MazeJump__GroundLayer__) */
