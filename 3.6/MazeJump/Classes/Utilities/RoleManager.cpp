//
//  RoleManager.cpp
//  MazeJump
//
//
//

#include "RoleManager.h"
#include "GameConst.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "storage/local-storage/LocalStorage.h"
USING_NS_CC;

RoleManager* g_pRoleManagerInstance = nullptr;
RoleManager::RoleManager()
{
}
RoleManager::~RoleManager()
{
}
RoleManager* RoleManager::getInstance()
{
    if( g_pRoleManagerInstance == nullptr )
        g_pRoleManagerInstance = new RoleManager();
    
    return g_pRoleManagerInstance;
}
bool RoleManager::init()
{
    std::string roleStr = FileUtils::getInstance()->getStringFromFile("roles.json");

    std::string userRoleStr = localStorageGetItem(USER_ROLE_DATA);
    if (userRoleStr.length() <=0) {
         CCLOG("roleStr:%s",roleStr.c_str());
        localStorageSetItem(USER_ROLE_DATA, roleStr);
    }else{
        //对比
        ValueMap userRoles = parseValueMap(userRoleStr);
        ValueMap fileRoles = parseValueMap(roleStr);
        for(std::unordered_map<std::string, Value>::iterator it = userRoles.begin(); it!=userRoles.end();)
        {
            std::string userRoleIdStr = it->first;
            ValueMap userRoleMap = it->second.asValueMap();
            auto userFindRoleIt = fileRoles.find(userRoleIdStr);
            if (userFindRoleIt==fileRoles.end()) {
                userRoles.erase(it++);
            }else
            {
                ++it;
            }
           
        }
        
        for(std::unordered_map<std::string, Value>::iterator it = fileRoles.begin(); it!=fileRoles.end();it++)
        {
            std::string RoleIdStr = it->first;
            ValueMap roleMap = it->second.asValueMap();
            auto usereIt = userRoles.find(RoleIdStr);
            if (usereIt!=userRoles.end()) {
                
                ValueMap userMap = usereIt->second.asValueMap();
                userRoles[RoleIdStr].asValueMap()["RoleModel"] = roleMap["RoleModel"];
//                userRoles[RoleIdStr].asValueMap()["RoleLock"] = roleMap["RoleLock"];
                userRoles[RoleIdStr].asValueMap()["RoleSound"] = roleMap["RoleSound"];
                userRoles[RoleIdStr].asValueMap()["RoleImg"] = roleMap["RoleImg"];
                userRoles[RoleIdStr].asValueMap()["RolePrice"] = roleMap["RolePrice"];
                
                CCLOG("userMap RoleId:%s",RoleIdStr.c_str());
                CCLOG("userMap RoleModel:%s",userMap["RoleModel"].asString().c_str());
                CCLOG("userMap RoleSound:%s",userMap["RoleSound"].asString().c_str());
                CCLOG("userMap RoleImg:%s",userMap["RoleImg"].asString().c_str());
                CCLOG("userMap RoleLock:%d",userMap["RoleLock"].asBool());
                CCLOG("userMap RolePrice:%d",userMap["RolePrice"].asInt());
                CCLOG("             ");
                CCLOG("roleMap RoleId:%s",RoleIdStr.c_str());
                CCLOG("roleMap RoleModel:%s",roleMap["RoleModel"].asString().c_str());
                CCLOG("roleMap RoleSound:%s",roleMap["RoleSound"].asString().c_str());
                CCLOG("roleMap oleImg:%s",roleMap["RoleImg"].asString().c_str());
                CCLOG("roleMap RoleLock:%d",roleMap["RoleLock"].asBool());
                CCLOG("roleMap RolePrice:%d",roleMap["RolePrice"].asInt());
                CCLOG("             ");
            }else
            {
                userRoles.insert(std::pair<std::string, Value>(RoleIdStr,Value(roleMap)));
            }

        }

//        CCLOG("valueMapToJsonStr:%s",valueMapToJsonStr(userRoles).c_str());
          CCLOG("valueMapToStr:%s",valueMapToStr(userRoles).c_str());
          localStorageSetItem(USER_ROLE_DATA, valueMapToStr(userRoles).c_str());
    }
    
    m_Roles = parseValueMap(localStorageGetItem(USER_ROLE_DATA));
    return !m_Roles.empty();
}
std::string RoleManager::valueMapToStr(cocos2d::ValueMap _valueMap)
{
    std::string str="{\"roles\":[";
    int count = 0;
    for(std::unordered_map<std::string, Value>::iterator it = _valueMap.begin(); it!=_valueMap.end();it++)
    {
        count++;
        rapidjson::Value object(rapidjson::kObjectType);
        std::string RoleIdStr = it->first;
        ValueMap roleMap = it->second.asValueMap();
        std::string itemStr = "{";
        int pos = 0;
        itemStr.append("\"");
        itemStr.append("RoleId");
        itemStr.append("\":\"");
        itemStr.append(RoleIdStr);
        itemStr.append("\",");
        for(std::unordered_map<std::string, Value>::iterator orit = roleMap.begin(); orit!=roleMap.end();orit++)
        {
            pos++;
           std::string sss = "\"";
            sss.append(orit->first);
            sss.append("\":");
            if (!strcmp(orit->first.c_str(), "RolePrice")) {
                sss.append(Value(orit->second.asInt()).asString());
            }else if (!strcmp(orit->first.c_str(), "RoleLock"))
            {
                if (orit->second.asBool()) {
                     sss.append("true");
                }else
                {
                    sss.append("false");
                }
               
            }else
            {
                sss.append("\"");
                sss.append(orit->second.asString());
                sss.append("\"");
            }
            
            if (pos!=roleMap.size()) {
             
                sss.append(",");
            }
            
            itemStr.append(sss);
            
        }
        
        if (count==_valueMap.size() ) {
            itemStr.append("}");
        }else
        {
            itemStr.append("},");
        }
        str.append(itemStr);
    }
    str.append("]}");
    return str;
}
std::string RoleManager::valueMapToJsonStr(cocos2d::ValueMap _valueMap)
{
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    rapidjson::Value array(rapidjson::kArrayType);
    
    for(std::unordered_map<std::string, Value>::iterator it = _valueMap.begin(); it!=_valueMap.end();it++)
    {
        rapidjson::Value object(rapidjson::kObjectType);
        std::string RoleIdStr = it->first;
        ValueMap roleMap = it->second.asValueMap();
        object.AddMember("RoleId",RoleIdStr.c_str(),allocator);
        for(std::unordered_map<std::string, Value>::iterator orit = roleMap.begin(); orit!=roleMap.end();orit++)
        {
            if (!strcmp(orit->first.c_str(), "RolePrice")) {
                object.AddMember(orit->first.c_str(), orit->second.asInt(), allocator);
            }else if (!strcmp(orit->first.c_str(), "RoleLock"))
            {
                object.AddMember(orit->first.c_str(), orit->second.asBool(), allocator);
            }else
            {
                
                
                std::string str = orit->second.asString();
                std::string::size_type loc = 0;
                while (loc != std::string::npos)
                {
                    str.erase(loc,1);
                    loc = str.find(' ',loc);
                }
                CCLOG(" orit->second.asString():%s", str.c_str());
                
                object.AddMember(orit->first.c_str(), str.c_str(), allocator);
            }
        }
        array.PushBack(object, allocator);
    }
    document.AddMember("roles", array, allocator);
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    return buffer.GetString();
}

ValueMap RoleManager::parseValueMap(const std::string &str)
{
 
    rapidjson::Document doc;
    doc.Parse<0>(str.c_str());
    if (doc.HasParseError())
    {
        CCLOG("LevelManager::loadLevelData parse json error!");
        return ValueMap();
    }
    if (doc.IsObject() && doc.HasMember("roles")) {
        const rapidjson::Value& roleArrValue = doc["roles"];
        if (roleArrValue.IsArray()) {
               ValueMap lvalueMap;
            CCLOG("roleArrValue:%d",roleArrValue.Size());
            for (int i =0 ; i<roleArrValue.Size(); i++) {
                const rapidjson::Value& roleValue = roleArrValue[i];
                if (roleValue.IsObject())
                {
                    ValueMap roleMap;
                    roleMap.insert(std::pair<std::string, Value>("RoleModel",Value(roleValue["RoleModel"].GetString())));
                    roleMap.insert(std::pair<std::string, Value>("RoleLock",Value(roleValue["RoleLock"].GetBool())));
                    roleMap.insert(std::pair<std::string, Value>("RoleSound",Value(roleValue["RoleSound"].GetString())));
                    roleMap.insert(std::pair<std::string, Value>("RoleImg",Value(roleValue["RoleImg"].GetString())));
                    roleMap.insert(std::pair<std::string, Value>("RolePrice",Value(roleValue["RolePrice"].GetInt())));
                    lvalueMap.insert(std::pair<std::string, Value>(Value(roleValue["RoleId"].GetString()).asString(),Value(roleMap)));
                }
            }
            return lvalueMap;
        }
        
    }
    return ValueMap();
}
void RoleManager::updateRoleLock(const std::string& str,cocos2d::ValueMap _lvalueMap)
{
    rapidjson::Document doc;
    doc.Parse<0>(str.c_str());
    if (doc.HasParseError())
    {
        CCLOG("LevelManager::loadLevelData parse json error!");
        return ;
    }
    if (doc.IsObject() && doc.HasMember("roles")) {
        rapidjson::Value& roleArrValue = doc["roles"];
        if (roleArrValue.IsArray()) {
            ValueMap lvalueMap;
            for (int i =0 ; i<roleArrValue.Size(); i++) {
                rapidjson::Value& roleValue = roleArrValue[i];
                if (roleValue.IsObject())
                {
                    ValueMap roleMap;
                    rapidjson::Value& locakValue = roleValue["RoleLock"];
                    CCLOG("ROLEID:%s isLock:%d",roleValue["RoleId"].GetString(),_lvalueMap[roleValue["RoleId"].GetString()].asValueMap()["RoleLock"].asBool());
                    locakValue.SetBool(_lvalueMap[roleValue["RoleId"].GetString()].asValueMap()["RoleLock"].asBool());
                    CCLOG("locakValue:%d",roleValue["RoleLock"].GetBool());
                }
            }
        }
        
    }
    rapidjson::StringBuffer  buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
    localStorageSetItem(USER_ROLE_DATA, buffer.GetString());

}

std::string RoleManager::getRoleModel(std::string &roleId)
{
    return m_Roles[roleId].asValueMap()["RoleModel"].asString();
}
std::string RoleManager::getRoleImg(std::string &roleId)
{
    return m_Roles[roleId].asValueMap()["RoleImg"].asString();
}
std::string RoleManager::getRoleSound(std::string &roleId)
{
    return m_Roles[roleId].asValueMap()["RoleSound"].asString();
}
bool RoleManager::getRoleLock(std::string &roleId)
{
    return m_Roles[roleId].asValueMap()["RoleLock"].asBool();
}
int RoleManager::getRolePrice(std::string &roleId)
{
    return m_Roles[roleId].asValueMap()["RolePrice"].asInt();
}

void RoleManager::updateRoleLock(std::string roleId,bool _lock)
{
     CCLOG(" isLock:%d",m_Roles[roleId].asValueMap()["RoleLock"].asBool());
    if (m_Roles[roleId].asValueMap()["RoleLock"].asBool() == _lock) {
        return;
    }
    m_Roles[roleId].asValueMap()["RoleLock"] = Value(_lock);
    CCLOG(" replace isLock:%d",m_Roles[roleId].asValueMap()["RoleLock"].asBool());
    
    updateRoleLock(localStorageGetItem(USER_ROLE_DATA),m_Roles);
}
std::string RoleManager::getDefaultRoleModel()
{
    std::string ldefaultModel;
    std::string defaultRolelId = localStorageGetItem(USER_DEFAULT_ROLE_ID);
    if (!defaultRolelId.empty()) {
        ldefaultModel = getRoleModel(defaultRolelId);
    }
    return ldefaultModel;
}
std::string RoleManager::getDefaultRoleSound()
{
    std::string ldefaultSound;
    std::string defaultRolelId = localStorageGetItem(USER_DEFAULT_ROLE_ID);
    if (!defaultRolelId.empty()) {
        ldefaultSound = getRoleSound(defaultRolelId);
    }
    return ldefaultSound;

}
std::string RoleManager::getSelectRoleModel()
{
    std::string ldefaultModel;
    std::string defaultRolelId = localStorageGetItem(USER_SELECT_ROLE_ID);
    if (!defaultRolelId.empty()) {
        ldefaultModel = getRoleModel(defaultRolelId);
    }
    return ldefaultModel;
}
std::string RoleManager::getSelectRoleSound()
{
    std::string ldefaultSound;
    std::string defaultRolelId = localStorageGetItem(USER_SELECT_ROLE_ID);
    if (!defaultRolelId.empty()) {
        ldefaultSound = getRoleSound(defaultRolelId);
    }
    return ldefaultSound;
    
}
