//
//  AlisaMethod.cpp
//  TinyFlare
//
//  Created by wang haibo on 15/4/8.
//
// http://www.keithschwarz.com/darts-dice-coins/

#include "AlisaMethod.h"
USING_NS_CC;

AlisaMethod* AlisaMethod::createWithOnePercent(float percent)
{
    AlisaMethod* ret = new (std::nothrow) AlisaMethod();
    if (ret && ret->initWithPercent(percent))
    {
        ret->autorelease();
    }
    return ret;

}
AlisaMethod* AlisaMethod::create(float percent1, ...)
{
    va_list params;
    va_start(params, percent1);
    AlisaMethod *ret = AlisaMethod::createWithVariableList(percent1, params);
    va_end(params);
    return ret;
}
AlisaMethod* AlisaMethod::createWithTwoPercent(float percent1, float percent2)
{
    AlisaMethod* ret = new (std::nothrow) AlisaMethod();
    if (ret && ret->initWithTwoPercent(percent1, percent2))
    {
        ret->autorelease();
    }
    return ret;

}
AlisaMethod* AlisaMethod::createWithVariableList(float percent1, va_list args)
{
    AlisaMethod* ret = new (std::nothrow) AlisaMethod();
    if (ret && ret->initWithPercentVariableList(percent1, args))
    {
        ret->autorelease();
    }
    return ret;
}
AlisaMethod* AlisaMethod::createWithPercentArray(std::vector<float>& percentArray)
{
    AlisaMethod* ret = new (std::nothrow) AlisaMethod();
    if (ret && ret->initWithPercentArray(percentArray))
    {
        ret->autorelease();
    }
    return ret;
}
bool AlisaMethod::initWithPercent(float percent)
{
    CCASSERT(percent <= 1.0f && percent >= 0.0f, "percent must between 0.0f-1.0f");
    return initWithTwoPercent(percent, 1.0f - percent);
}
bool AlisaMethod::initWithTwoPercent(float percent1, float percent2)
{
    CCASSERT(percent1+percent2 == 1.0f, "percent1 add percent2 must be 1.0f");
    std::vector<float> percentArray;
    percentArray.push_back(percent1);
    percentArray.push_back(percent2);
    std::deque<float> small, large;
    for (int i = 0; i < percentArray.size(); ++i) {
        percentArray[i] *= percentArray.size();
        if(percentArray[i] < 1.0f)
            small.push_back(i);
        else
            large.push_back(i);
    }
    
    m_probArray.resize(percentArray.size());
    m_alisaArray.resize(percentArray.size());
    while (small.size() != 0 && large.size() != 0) {
        float s_index = small.front();
        small.pop_front();
        float l_index = large.front();
        large.pop_front();
        m_probArray[s_index] = percentArray[s_index];
        m_alisaArray[s_index] = l_index;
        percentArray[l_index] -= 1.0f - percentArray[s_index];
        if(percentArray[l_index] < 1.0f)
            small.push_back(l_index);
        else
            large.push_back(l_index);
    }
    
    while (!small.empty()) {
        m_probArray[small.front()] = 1.0f;
        small.pop_front();
    }
    while (!large.empty()) {
        m_probArray[large.front()] = 1.0f;
        large.pop_front();
    }
    return true;
}
bool AlisaMethod::initWithPercentVariableList(float percent1, va_list args)
{
    std::vector<float> percentArray;
    percentArray.push_back(percent1);
    float total = percent1;
    while (1)
    {
        float nextPercent = va_arg(args, double);
        if (nextPercent < 1.0f)
        {
            total += nextPercent;
            percentArray.push_back(nextPercent);
        }
        else
            break;
    }
    CCASSERT(total == 1.0f, "the sum of those percents must be 1.0f");
    
    return initWithPercentArray(percentArray);
}
bool AlisaMethod::initWithPercentArray(std::vector<float>& percentArray)
{
    std::deque<float> small, large;
    for (int i = 0; i < percentArray.size(); ++i) {
        percentArray[i] *= percentArray.size();
        if(percentArray[i] < 1.0f)
            small.push_back(i);
        else
            large.push_back(i);
    }
    
    m_probArray.resize(percentArray.size());
    m_alisaArray.resize(percentArray.size());
    while (small.size() != 0 && large.size() != 0) {
        float s_index = small.front();
        small.pop_front();
        float l_index = large.front();
        large.pop_front();
        m_probArray[s_index] = percentArray[s_index];
        m_alisaArray[s_index] = l_index;
        percentArray[l_index] -= 1.0f - percentArray[s_index];
        if(percentArray[l_index] < 1.0f)
            small.push_back(l_index);
        else
            large.push_back(l_index);
    }
    
    while (!small.empty()) {
        m_probArray[small.front()] = 1.0f;
        small.pop_front();
    }
    while (!large.empty()) {
        m_probArray[large.front()] = 1.0f;
        large.pop_front();
    }
    return true;
}
int AlisaMethod::getRandomIndex()
{
    int index = cocos2d::random(0, (int)(m_probArray.size()-1));
    return cocos2d::rand_0_1() < m_probArray[index] ? index : m_alisaArray[index];
}
void AlisaMethod::printProbArray()
{
    CCLOG("ProbArray: ");
    for (int i = 0; i < m_probArray.size(); ++i) {
        CCLOG("%f, ", m_probArray[i]);
    }
    CCLOG("\n");
}
void AlisaMethod::printAlisaArray()
{
    CCLOG("AlisaArray: ");
    for (int i = 0; i < m_alisaArray.size(); ++i) {
        CCLOG("%d, ", m_alisaArray[i]);
    }
    CCLOG("\n");
}
///test
//AlisaMethod* am = AlisaMethod::create(0.1f,0.2f,0.3f,0.4f,NULL);
//if(am)
//{
//    am->printProbArray();
//    am->printAlisaArray();
//    int a,b,c,d = 0;
//    for (int i = 0; i<10000; ++i) {
//        int index = am->getRandomIndex();
//        if(index == 0)
//            a++;
//        if(index == 1)
//            b++;
//        if(index == 2)
//            c++;
//        if(index == 3)
//            d++;
//    }
//    CCLOG("random a = %d, b= %d, c= %d d = %d", a,b,c,d);
//}