//
//  GameScene.h
//  Voxel_Explorer
//
//  Created by wang haibo on 15/9/24.
//
//

#ifndef __Voxel_Explorer__TestScene__
#define __Voxel_Explorer__TestScene__

#include "cocos2d.h"
#include "WrapperUILayer.h"
#include "TGridView.h"
class TestScene : public WrapperUILayer
{
    TestScene();
public:
    static cocos2d::Scene* createScene();
    
    
    CREATE_FUNC(TestScene);
    
    virtual void onEnter() override;
    virtual void onExit() override;
    
private:
    bool initUi() override;
    bool addEvents() override;
    void selectItemEvent(Ref *pSender, TGridView::EventType type);
    void selectAchieveEvent(Ref *pSender, TGridView::EventType type);
    void selectNpcInfoEvent(Ref *pSender, TGridView::EventType type,cocos2d::ValueVector valueVector);
    void selectRandomEvent(Ref *pSender, TGridView::EventType type,cocos2d::ValueVector valueVector);
    void selectTipsEvent(Ref *pSender, TGridView::EventType type);
private:
    void testItem(TGridView* m_pGridView);
    void testAchieve(TGridView* m_pGridView);
    void testNpcInfo(TGridView* m_pGridView);
    void testRandom(TGridView* m_pGridView);
    void testTips(TGridView* m_pGridView);
};

#endif /* defined(__Voxel_Explorer__TestScene__) */
