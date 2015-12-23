//
//  RandomEventMgr.cpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/12/23.
//
//

#include "RandomEventMgr.hpp"

USING_NS_CC;

RandomEventMgr* g_pRandomEventMgrInstance = nullptr;
RandomEventMgr* RandomEventMgr::getInstance()
{
    if( g_pRandomEventMgrInstance == nullptr )
        g_pRandomEventMgrInstance = new RandomEventMgr();
    
    return g_pRandomEventMgrInstance;
}
RandomEventMgr::RandomEventMgr()
{
    m_EventList.clear();
}
RandomEventMgr::~RandomEventMgr()
{
    m_EventList.clear();
}
bool RandomEventMgr::load(const cocos2d::ValueVector& eventList)
{
    if(eventList.empty())
    {
        LanguageType lt= Application::getInstance()->getCurrentLanguage();
        switch (lt) {
            case LanguageType::CHINESE:
                m_EventList = FileUtils::getInstance()->getValueVectorFromFile("random_events_chinese.plist");
                CCASSERT(!m_EventList.empty(), "cannot create event vector!");
                break;
                
            default:
                m_EventList = FileUtils::getInstance()->getValueVectorFromFile("random_events_english.plist");
                CCASSERT(!m_EventList.empty(), "cannot create event vector!");
                break;
        }
    }
    else
        m_EventList = eventList;
    return true;
}
cocos2d::ValueMap* RandomEventMgr::getRandomEvent()
{
    int index = cocos2d::random(0, (int)(m_EventList.size()-1));
    m_LastRandomEvent = m_EventList.at(index).asValueMap();
    return &m_LastRandomEvent;
}