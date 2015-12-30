//
//  RandomDungeon.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/10/21.
//
//

#ifndef RandomDungeon_hpp
#define RandomDungeon_hpp

#include "cocos2d.h"
#include "ChaosNumber.h"
typedef enum{
    DT_UNKNOWN = 0,        ////未知
    
    DT_SEWER,              ////下水道
    DT_PRISON,             ////监狱
    DT_FANE,               ////神殿
    DT_MINES,              ////矿坑
    DT_CAVE,               ////洞穴
    DT_TOMB,               ////古墓
    
    DT_DWARF_CASTLE,       ////矮人城堡
    DT_MAGA_TOWER,         ////法师塔
    DT_ORC_FORTRESS,       ////兽人堡垒
    DT_ELF_FOREST,         ////妖精森林
    DT_TROLL_TEMPLE,       ////巨魔神庙
    
    DT_BEHOLDER_CASTLE,     ////眼魔
    DT_WARP_SPACE,          ////异空间
    DT_DRAGON_LAIR,         ////龙穴
    DT_LICH_TOMB,           ////巫妖墓室
    DT_MAX
}
DUNGEON_TYPE;
extern const char* DUNGEON_NAMES[];
extern const char* DUNGEON_BOSS_NAMES[];
class DungeonNode : public cocos2d::Ref
{
public:
    DungeonNode()
    {
        m_strDungeonName        = "";                       ////地城名称
        m_strDungeonBossName    = "";                       ////Boss地城名称
        m_nTransmutationDepth = 3;                          ////嬗变深度
        m_nCurrentDepth     = 1;                            ////当前深度
        m_nNodeDepth        = 1;                            ////节点深度
        m_nTotalNum         = 10;                           ////地城层数
        m_Type              = DT_UNKNOWN;                   ////类型
        
        m_pParentNode   = nullptr;      ////父节点
        m_pLeftNode     = nullptr;      ////左节点
        m_pRightNode    = nullptr;      ////右节点
    }
    bool isTransmutation()
    {
        return m_nCurrentDepth >= m_nTransmutationDepth;
    }
    bool isBeginTransmutation()
    {
        return m_nCurrentDepth == m_nTransmutationDepth;
    }
    bool isLastDepth()
    {
        return m_nCurrentDepth == m_nTotalNum;
    }
    bool isBossDepth()
    {
        return m_nCurrentDepth > m_nTotalNum;
    }
    bool isFirstDepth()
    {
        return m_nCurrentDepth == 1;
    }
    DUNGEON_TYPE getDungeonNodeType() const { return m_Type; }
    std::string     m_strDungeonName;       ////地城名称
    std::string     m_strDungeonBossName;   ////Boss地城名称
    CChaosNumber    m_nTransmutationDepth;  ////嬗变深度
    CChaosNumber    m_nCurrentDepth;        ////当前深度
    CChaosNumber    m_nNodeDepth;           ////节点深度
    CChaosNumber    m_nTotalNum;            ////地城层数
    DUNGEON_TYPE    m_Type;                 ////类型
    
    DungeonNode*    m_pParentNode;  ////父节点
    DungeonNode*    m_pLeftNode;    ////左节点
    DungeonNode*    m_pRightNode;   ////右节点
};
class RandomDungeon : public cocos2d::Ref
{
    RandomDungeon();
    ~RandomDungeon();
public:
    static RandomDungeon* getInstance();
    
    static std::vector<DUNGEON_TYPE>       SELECT_GROUP1;
    static std::vector<DUNGEON_TYPE>       SELECT_GROUP2;
    static std::vector<DUNGEON_TYPE>       SELECT_GROUP3;
    
    static std::vector<DUNGEON_TYPE>       SELECT_ALL;
    
    void update(float delta);
    
    bool build();
    void selectDungeonNode(bool left);
    
    DungeonNode* getCurrentDungeonNode() const { return m_pCurrentNode; }
    CChaosNumber getDifficultClass() const { return m_nDifficultClass; }
    std::string  getCurrentBossName() const;
    void load();
    void save();
private:
    DUNGEON_TYPE generateDungeonNodeType();
    bool generateNextDungeonNode();
    void assignedDungeonNode(DungeonNode* node);
private:
    DungeonNode*                m_pCurrentNode;         ///当前节点
    
    std::vector<DUNGEON_TYPE>   m_UnSelected;           ///还没有选择的。
    int                         m_nCurrentSelectGroup;  ///当前选择的组
    
    CChaosNumber                m_nDifficultClass;      ////难度等级
};

#endif /* RandomDungeon_hpp */
