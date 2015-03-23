//
//  EnemiesGenerator.cpp
//  TinyFlare
//
//  Created by wang haibo on 15/3/23.
//
//

#include "EnemiesGenerator.h"
#include "EnemiesGeneratorHelper.h"
#include "GameController.h"
#include "ActorsManager.h"
USING_NS_CC;

EnemiesGenerator::EnemiesGenerator()
{
}
EnemiesGenerator::~EnemiesGenerator()
{
}

void EnemiesGenerator::generateOneEnemyOnRandomPos(cocos2d::Node* node, void* data)
{
    GeneratorInfo* info = static_cast<GeneratorInfo*>(data);
    if(info != nullptr)
    {
        Vec2 playerPos = GameController::getInstance()->getPlayerPos();
        Size boundSize = GameController::getInstance()->getBoundSize();
        Rect rect = Rect(-boundSize.width*0.5f, -boundSize.height*0.5f, boundSize.width, boundSize.height);
        Vec2 enemyPos = EnemiesGeneratorHelper::getRandomPosOutScreenInBoundRect(playerPos, rect);
        Vec2 dir = playerPos - enemyPos;
        dir.normalize();
        ActorsManager::getInstance()->spawnEnemy((Enemy::EnemyType)(info->m_nCurType), enemyPos, dir);
    }
}
void EnemiesGenerator::generateOneEnemyOnPos(cocos2d::Node* node, void* data)
{
    GeneratorInfo* info = static_cast<GeneratorInfo*>(data);
    if(info != nullptr)
    {
        info->m_Dir = info->m_Dir.rotateByAngle(Vec2::ZERO, -M_PI*2/info->m_nNum);
        ActorsManager::getInstance()->spawnEnemy((Enemy::EnemyType)(info->m_nCurType), info->m_Pos, info->m_Dir);
    }
}
void EnemiesGenerator::generateEnemiesByTime(Enemy::EnemyType type, float durationTime, float lastTime)
{
    GeneratorInfo* info = GeneratorInfo::create();
    if(info == nullptr)
        return;
    info->retain(); ///memory leak
    info->m_nCurType = type;
    if(lastTime <= 0.0f)
    {
        DelayTime* duration = DelayTime::create(durationTime);
        __CCCallFuncND* callFuncND = __CCCallFuncND::create(this, CC_CALLFUNCND_SELECTOR(EnemiesGenerator::generateOneEnemyOnRandomPos), (void*)info);
        Sequence* sequence1 = Sequence::createWithTwoActions(callFuncND, duration);
        RepeatForever* repeatForever = RepeatForever::create(sequence1);
        runAction(repeatForever);
    }
    else
    {
        DelayTime* duration = DelayTime::create(durationTime);
        __CCCallFuncND* callFuncND = __CCCallFuncND::create(this, CC_CALLFUNCND_SELECTOR(EnemiesGenerator::generateOneEnemyOnRandomPos), (void*)info);
        Sequence* sequence1 = Sequence::createWithTwoActions(callFuncND, duration);
        CCASSERT(durationTime > 0.0f, "divisor can not be 0!");
        int times = (int)(lastTime / durationTime);
        Repeat* repeat = Repeat::create(sequence1, times);
        runAction(repeat);
    }
}
void EnemiesGenerator::generateEnemiesByNum(Enemy::EnemyType type, float durationTime, int num)
{
    GeneratorInfo* info = GeneratorInfo::create();
    if(info == nullptr)
        return;
    info->retain(); ///memory leak
    info->m_nCurType = type;
    DelayTime* duration = DelayTime::create(durationTime);
    __CCCallFuncND* callFuncND = __CCCallFuncND::create(this, CC_CALLFUNCND_SELECTOR(EnemiesGenerator::generateOneEnemyOnRandomPos), (void*)info);
    Sequence* sequence1 = Sequence::createWithTwoActions(callFuncND, duration);

    Repeat* repeat = Repeat::create(sequence1, num);
    runAction(repeat);
}
void EnemiesGenerator::generateEnemiesByExplosion(Enemy::EnemyType type, const cocos2d::Vec2& pos, int num, float durationTime )
{
    CCASSERT(num >=1, "num must >= 1 !");
    GeneratorInfo* info = GeneratorInfo::create();
    if(info == nullptr)
        return;
    info->retain(); ///memory leak
    info->m_nCurType = type;
    info->m_Pos = pos;
    info->m_Dir = GameController::getInstance()->getPlayerOrientation().rotateByAngle(Vec2::ZERO, -M_PI*0.5f/info->m_nNum);
    info->m_nNum = num;
    if(durationTime <= 0.0f)
    {
        DelayTime* duration = DelayTime::create(durationTime);
        __CCCallFuncND* callFuncND = __CCCallFuncND::create(this, CC_CALLFUNCND_SELECTOR(EnemiesGenerator::generateOneEnemyOnPos), (void*)info);
        Sequence* sequence1 = Sequence::createWithTwoActions(callFuncND, duration);
    
        Repeat* repeat = Repeat::create(sequence1, num);
        runAction(repeat);
    }
    else
    {
        __CCCallFuncND* callFuncND = __CCCallFuncND::create(this, CC_CALLFUNCND_SELECTOR(EnemiesGenerator::generateOneEnemyOnPos), (void*)info);
        Repeat* repeat = Repeat::create(callFuncND, num);
        runAction(repeat);
    }
}
void EnemiesGenerator::reset()
{
    this->stopAllActions();
}