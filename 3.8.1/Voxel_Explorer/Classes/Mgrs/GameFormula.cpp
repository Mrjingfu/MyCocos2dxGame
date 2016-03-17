//
//  GameFormula.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/20.
//
//

#include "GameFormula.hpp"
#include "AlisaMethod.h"
USING_NS_CC;

static const CChaosNumber gsMaxBlockRate = 0.2f;
static const CChaosNumber gsMaxCriticalStrikeRate = 0.3f;
static const CChaosNumber gsMaxDodgeRate = 0.2f;
static const CChaosNumber gsMaxMagicItemFindRate = 0.65f;
bool GameFormula::generateMagicItem(float magicFindRate)
{
    if(magicFindRate <= 0)
        return false;
    float percentNoMagic = 1.0 - magicFindRate;
    AlisaMethod* am = AlisaMethod::create(magicFindRate, percentNoMagic, -1.0, NULL);
    if(!am)
        return false;
    return am->getRandomIndex() == 0;
}
bool GameFormula::generatePickItemByMonster(bool isElite, bool isBoss)
{
    if(isElite)
        return true;
    else if(isBoss)
        return true;
    else
    {
        float percent1 = 0.6f;
        float percent2 = 1.0 - percent1;
        AlisaMethod* am = AlisaMethod::create(percent1, percent2, -1.0, NULL);
        if(!am)
            return false;
        return am->getRandomIndex() == 0;
    }
}
UseableItem::UseableItemType GameFormula::generateUseItemType()
{
    UseableItem::UseableItemType ret = UseableItem::UIT_UNKNOWN;
    float percent1 = 0.7f;
    float percent2 = 0.23f;
    float percent3 = 0.05f;
    float percent4 = 1.0 - percent1 - percent2 - percent3;
    AlisaMethod* am = AlisaMethod::create(percent1,percent2,percent3,percent4,-1.0, NULL);
    if(am)
    {
        int randIndex = am->getRandomIndex();
        if(randIndex == 1)
            ret = UseableItem::UIT_CHEST_COPPER;
        else if(randIndex == 2)
            ret = UseableItem::UIT_CHEST_SILVER;
        else if(randIndex == 3)
            ret = UseableItem::UIT_CHEST_GOLD;
        else
            ret = (UseableItem::UseableItemType)(cocos2d::random((int)UseableItem::UIT_JAR_1, (int)UseableItem::UIT_JAR_3));
    }
    return ret;
}
int GameFormula::getNextLevelExp(int currentLevel)
{
    ///按每4秒杀一怪
    int exp = floor((pow((currentLevel-1), 3)+60)/4*((currentLevel-1)*2+60)+60);
    int mod = exp%50;
    return exp - mod;
}
int GameFormula::getKillNormalMonsterExp(int currentLevel, int monsterLevel)
{
    int monsterExp = (monsterLevel-1)*10+80;
    int diff = monsterLevel - currentLevel;
    if(diff>=0)
    {
        if(diff>=5)
            monsterExp = monsterExp*3;
        else
            monsterExp = monsterExp*pow(1.2f, diff);
    }
    else
    {
        if(diff<=-5)
            monsterExp = cocos2d::random(5, 20);
        else
            monsterExp = monsterExp*pow(0.9f, abs(diff));
    }
    return monsterExp;
}
int GameFormula::getKillEliteMonsterExp(int currentLevel, int monsterLevel)
{
    int monsterExp = (monsterLevel-1)*15+160;
    int diff =  monsterLevel - currentLevel;
    if(diff>=0)
    {
        if(diff>=5)
            monsterExp = monsterExp*8;
        else
            monsterExp = monsterExp*pow(1.5f, diff);
    }
    else
    {
        if(diff<=-8)
            monsterExp = cocos2d::random(20, 60);
        else
            monsterExp = monsterExp*pow(0.9f, abs(diff));
    }
    return monsterExp;
}
int GameFormula::getKillBossExp(int currentLevel, int bossLevel)
{
    return (bossLevel-1)*20+320;
}

void GameFormula::exchangeMoney(CChaosNumber srcCopper, CChaosNumber& gold, CChaosNumber& silver, CChaosNumber& copper)
{
    gold = srcCopper/10000;
    silver = (srcCopper.GetLongValue()%10000)/100;
    copper = srcCopper.GetLongValue()%100;
}
CChaosNumber GameFormula::exchangeMoney(CChaosNumber srcGold, CChaosNumber srcSilver, CChaosNumber srcCopper)
{
    return srcGold*100*100 + srcSilver*100 + srcCopper*1;
}