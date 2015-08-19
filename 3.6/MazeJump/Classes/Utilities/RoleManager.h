//
//  RoleManager.h
//  MazeJump
//
//  
//
//

#ifndef __MazeJump__RoleManager__
#define __MazeJump__RoleManager__

#include "cocos2d.h"
class RoleManager : public cocos2d::Ref
{
    RoleManager();
    ~RoleManager();
public:
    static RoleManager* getInstance();
    bool init();
    int getMaxRoles();
    
    std::string getRoleModel(std::string& roleId);
    bool getRoleLock(std::string& roleId);
    std::string getRoleImg(std::string& roleId);
    int getRolePrice(std::string& roleId);
    std::string getRoleSound(std::string& roleId);
    
    cocos2d::ValueMap getRoleMap(){return m_Roles;};
    void updateRoleLock(std::string roleId,bool _lock);
    std::string valueMapToJsonStr(cocos2d::ValueMap _valueMap);
    std::string valueMapToStr(cocos2d::ValueMap _valueMap);
    std::string getDefaultRoleModel();
    std::string getDefaultRoleSound();
private:
    void updateRoleLock(const std::string& str,cocos2d::ValueMap _lvalueMap);
    cocos2d::ValueMap parseValueMap(const std::string& str);
    
    cocos2d::ValueMap    m_Roles;
};


#endif /* defined(__MazeJump__RoleManager__) */
