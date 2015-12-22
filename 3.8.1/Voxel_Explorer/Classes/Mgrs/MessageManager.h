//
//  MessageManager.hpp
//  Voxel_Explorer
//
//  Created by 创李 on 15/11/9.
//
//

#ifndef MessageManager_hpp
#define MessageManager_hpp

#define MESSAGE_MAX 50

#include "cocos2d.h"

class MsgData:public cocos2d::Ref{
    MsgData(){};
public:
    virtual ~MsgData(){};
    std::string getMsg () const{return m_msg;}
    cocos2d::Color3B getMsgColor() const {return m_msgColor;}
    static MsgData* create(std::string msg , cocos2d::Color3B msgcolor);
private:
    std::string m_msg;
    cocos2d::Color3B m_msgColor;
};
class MessageManager {
    MessageManager();
public:
    virtual ~MessageManager();
    static MessageManager* getInstance();
    void setMsg(std::string msg,cocos2d::Color3B msgColor);
    void removeMsg(int index);
    bool isExceedMsgMax();
    const cocos2d::Vector<MsgData*>& getMsgList() const {return m_Msgs;};
    void clear();
private:
    cocos2d::Vector<MsgData*> m_Msgs;
};

#endif /* MessageManager_hpp */
