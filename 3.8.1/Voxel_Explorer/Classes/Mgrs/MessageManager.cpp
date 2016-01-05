//
//  MessageManager.cpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/9.
//
//

#include "MessageManager.h"
MsgData* MsgData::create(std::string msg, cocos2d::Color3B msgcolor)
{
    MsgData* itemUi = new (std::nothrow) MsgData();
    if (itemUi )
    {
        itemUi->m_msg = msg;
        itemUi->m_msgColor = msgcolor;
        itemUi->autorelease();
        return itemUi;
    }
    CC_SAFE_DELETE(itemUi);
    return nullptr;

}
MessageManager::MessageManager()
{
    
}
MessageManager::~MessageManager()
{
    clear();
}
MessageManager* MessageManager::getInstance()
{
    static MessageManager msg;
    return &msg;
}
void MessageManager::setMsg(std::string msg,cocos2d::Color3B msgColor)
{
    MsgData* msgData = MsgData::create(msg,msgColor);;
    m_Msgs.pushBack(msgData);
}
void MessageManager::removeMsg(int index)
{
    m_Msgs.erase(index);
}

bool MessageManager::isExceedMsgMax()
{
    return m_Msgs.size() >=MESSAGE_MAX;
}
void MessageManager::clear()
{
    m_Msgs.clear();
}