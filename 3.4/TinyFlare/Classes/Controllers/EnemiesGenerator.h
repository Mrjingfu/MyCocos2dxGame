//
//  EnemiesGenerator.h
//  TinyFlare
//
//  Created by wang haibo on 15/3/23.
//
//

#ifndef __TinyFlare__EnemiesGenerator__
#define __TinyFlare__EnemiesGenerator__

#include "cocos2d.h"
#include "Enemies.h"
class GeneratorInfo : public cocos2d::Ref
{
    GeneratorInfo(){
        m_nCurType = Enemy::ET_UNKNOWN;
        m_Pos = cocos2d::Vec2::ZERO;
        m_Dir = cocos2d::Vec2::UNIT_Y;
        m_nNum = 1;
    };
    virtual ~GeneratorInfo(){};
public:
    static GeneratorInfo* create()
    {
        GeneratorInfo *pRet = new(std::nothrow) GeneratorInfo();
        if (pRet)
        {
            pRet->autorelease();
            return pRet;
        }
        else
        {
            CC_SAFE_DELETE(pRet);
            return nullptr;
        }
    }
public:
    int                 m_nCurType;
    cocos2d::Vec2       m_Pos;
    cocos2d::Vec2       m_Dir;
    int                 m_nNum;
};
class EnemiesGenerator : public cocos2d::Node
{
    EnemiesGenerator();
    virtual ~EnemiesGenerator();
public:
    CREATE_FUNC(EnemiesGenerator);
    
private:
    void generateOneEnemyOnRandomPos(cocos2d::Node* node, void* data);
    void generateOneEnemyOnPos(cocos2d::Node* node, void* data);
public:
    void generateEnemiesByTime(Enemy::EnemyType type, float durationTime, float lastTime = -1);
    void generateEnemiesByNum(Enemy::EnemyType type, float durationTime, int num);
    void generateEnemiesByExplosion(Enemy::EnemyType type, const cocos2d::Vec2& pos, int num, float durationTime = -1);
    
    void reset();
};

#endif /* defined(__TinyFlare__EnemiesGenerator__) */
