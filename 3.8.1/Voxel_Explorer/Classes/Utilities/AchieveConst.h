//
//  AchieveConst.h
//  Voxel_Explorer
//
//  Created by 创李 on 15/12/14.
//
//

#ifndef AchieveConst_h
#define AchieveConst_h

#include "cocos2d.h"

const std::vector<std::string> STATIST_TYPE_NAME = {
    "ST_MONSTER_RAT",             ///老鼠
    "ST_MONSTER_BAT",             ///蝙蝠
    "ST_MONSTER_SNAKE",           ///蛇
    "ST_MONSTER_SPIDER",          ///蜘蛛
    "ST_MONSTER_SLIME",           ///史莱姆
    "ST_MONSTER_ALLIP",           ///怨魂
    "ST_MONSTER_PRISONER",        ///囚犯
    "ST_MONSTER_PRISONGUARD",     ///监狱守卫
    "ST_MONSTER_TORTURE",         ///拷问者
    "ST_MONSTER_MOB",             ///暴徒
    "ST_MONSTER_BELIEVER",        ///信徒
    "ST_MONSTER_GATEKEEPER",      ///看门人
    "ST_MONSTER_APOLOGIST",       ///辩护者
    "ST_MONSTER_ADJUDICATOR",     ///审判者
    "ST_MONSTER_PRIEST",          ///牧师
    "ST_MONSTER_DEATHMINER",      ///死亡矿工
    "ST_MONSTER_KOBOLD",          ///狗头人
    "ST_MONSTER_OOZE",            ///软泥怪
    "ST_MONSTER_SHADOW",          ///阴影怪
    "ST_MONSTER_ANKHEG",          ///掘地虫
    "ST_MONSTER_WOLF",            ///狼
    "ST_MONSTER_BEAR",            ///熊
    "ST_MONSTER_GOBLIN",          ///地精
    "ST_MONSTER_DINOSAUR",        ///恐龙
    "ST_MONSTER_GNOLL",           ///豺狼人
    "ST_MONSTER_SKELETON",        ///骷髅
    "ST_MONSTER_ZOMBIE",          ///僵尸
    "ST_MONSTER_GARGOYLE",        ///石像鬼
    "ST_MONSTER_GHOST",           ///幽灵
    "ST_MONSTER_GHOUL",           ///食尸鬼


    "ST_DEAD_MONSTER_ATTACK",                 //怪物攻击导致死亡
    "ST_DEAD_TRIGGER_GRIPPING_TRAP",          //夹子夹死
    "ST_DEAD_BUFFER_FIRE",                    //着火
    "ST_DEAD_BUFFER_POISONING",               //中毒
    "ST_DEAD_FALL",                           //摔死        ///NEW


    "ST_FOUND_HIDE_MSG",              //隐藏信息
    "ST_FOUND_HIDE_DOOR",             //隐藏门
    "ST_FOUND_HIDE_TRAP",             //隐藏陷阱

    "ST_BOSS_SLIMEKING",               ///史莱姆王        ///NEW
    "ST_BOSS_WARDEN",                  ///典狱长          ///NEW
    "ST_BOSS_ARCHBISHOP",              ///大主教          ///NEW
    "ST_BOSS_KOBOLDLEADER",            ///狗头人首领      ///NEW
    "ST_BOSS_GIANT",                   ///巨人格鲁尔德    ///NEW
    "ST_BOSS_SKELETONKING",            ///骷髅王          ///NEW

    "ST_DT_SEWER",              ////下水道
    "ST_DT_PRISON",             ////监狱
    "ST_DT_FANE",               ////神殿
    "ST_DT_MINES",              ////矿坑
    "ST_DT_CAVE",               ////洞穴
    "ST_DT_TOMB",               ////古墓
    "ST_DT_DWARF_CASTLE",       ////矮人城堡
    "ST_DT_MAGA_TOWER",         ////法师塔
    "ST_DT_ORC_FORTRESS",       ////兽人堡垒
    "ST_DT_ELF_FOREST",         ////妖精森林
    "ST_DT_TROLL_TEMPLE",       ////巨魔神庙
    "ST_DT_BEHOLDER_CASTLE",     ////眼魔
    "ST_DT_WARP_SPACE",          ////异空间
    "ST_DT_DRAGON_LAIR",         ////龙穴
    "ST_DT_LICH_TOMB",           ////巫妖墓室
    
    "ST_TOTAL_COPPER",
    "ST_TOTAL_STEP",
    "ST_TOTAL_MONSTER_KILL",
    "ST_TOTAL_USE_KEY",
    "ST_TOTAL_CRITICAL",
    "ST_TOTAL_DODGE",
    "ST_TOTAL_BLOCK",
    "ST_TOTAL_ROLE_DEAD",
    "ST_TOTAL_CHEST_COPPER",
    "ST_TOTAL_CHEST_SILVER",
    "ST_TOTAL_CHEST_GOLD",
    "ST_TOTAL_JAR",
    "ST_TOTAL_ROLE_LEVEL",
    "ST_TOTAL_ELITE_MONSTER",                                     ///NEW
    "ST_TOTAL_IDENTIFY",                                          ///NEW
    "ST_TOTAL_IDENTIFY_BEOW_TOW",         ///鉴定属性超过两条次数   ///NEW
    "ST_TOTAL_IDENTIFY_QUALITY",          //鉴定品质               ///NEW
    "ST_TOTAL_BAG_EXTEND",                //背包扩容次数           ///NEW
    "ST_TOTAL_BAG_FULL",                  //背包装满               ///NEW
    "ST_TOTAL_DISCARD_ITEM",              //道具丢弃总计            ///NEW
    "ST_TOTAL_DISCARD_EQUIP",             //丢弃装备                ///NEW
    "ST_TOTAL_PICK_ITEM",                 //拾取道具                ///new
    "ST_TOTAL_PICK_NOT_MARIC",            //拾取费魔法物品           ///new
    "ST_TOTAL_NINE_STEP",                 //9秒移动超过10步          ///new
    "ST_TOTAL_THIRTY_NOT_MOVE",           //30秒不动                 ///new
    "ST_TOTAL_EXPLORE_ALL_AREA",          //探索区域                  ///NEW
    "ST_TOTAL_FOUND_DOOR_TRAP",            //隐藏门_陷阱               ///NEW
    "ST_TOTAL_SEARCH",                    //检索                    ///NEW
    "ST_TOTAL_CHEST_BOX",                 //开启宝箱
    "ST_TOTAL_MEET_THIEF",                //遇见盗贼
    "ST_TOTAL_MEET_HAG",                  //遇见魔女
    "ST_TOTAL_MEET_SAGE",                 //遇见智者
    "ST_TOTAL_NURSE_TREAT",               //护士治疗
    "ST_TOTAL_BUY_EQUIP",                 //购买装备
    "ST_TOTAL_BUY_POTION",                //购买药水
    "ST_TOTAL_BUY_SCROLL",                //购买卷轴
    "ST_TOTAL_ROLE_HP",                   //生命值
    "ST_TOTAL_ROLE_MAX_ATTACK",           //攻击力
    "ST_TOTAL_STEALTH",                   //隐身
    "ST_TOTAL_NOT_FAIL_DEAD",             //没有摔死
    "ST_TOTAL_WEAK_RECOVER",              //虚弱恢复
    "ST_TOTAL_POISON_RECOVER",            //中毒恢复
    "ST_TOTAL_SPEED_UP",                  //加速
    "ST_TOTAL_STRONG",                    //进入强壮

};

enum eStatistType{
    ST_MONSTER_RAT=0,             ///老鼠
    ST_MONSTER_BAT,             ///蝙蝠
    ST_MONSTER_SNAKE,           ///蛇
    ST_MONSTER_SPIDER,          ///蜘蛛
    ST_MONSTER_SLIME,           ///史莱姆
    ST_MONSTER_ALLIP,           ///怨魂
    ST_MONSTER_PRISONER,        ///囚犯
    ST_MONSTER_PRISONGUARD,     ///监狱守卫
    ST_MONSTER_TORTURE,         ///拷问者
    ST_MONSTER_MOB,             ///暴徒
    ST_MONSTER_BELIEVER,        ///信徒
    ST_MONSTER_GATEKEEPER,      ///看门人
    ST_MONSTER_APOLOGIST,       ///辩护者
    ST_MONSTER_ADJUDICATOR,     ///审判者
    ST_MONSTER_PRIEST,          ///牧师
    ST_MONSTER_DEATHMINER,      ///死亡矿工
    ST_MONSTER_KOBOLD,          ///狗头人
    ST_MONSTER_OOZE,            ///软泥怪
    ST_MONSTER_SHADOW,          ///阴影怪
    ST_MONSTER_ANKHEG,          ///掘地虫
    ST_MONSTER_WOLF,            ///狼
    ST_MONSTER_BEAR,            ///熊
    ST_MONSTER_GOBLIN,          ///地精
    ST_MONSTER_DINOSAUR,        ///恐龙
    ST_MONSTER_GNOLL,           ///豺狼人
    ST_MONSTER_SKELETON,        ///骷髅
    ST_MONSTER_ZOMBIE,          ///僵尸
    ST_MONSTER_GARGOYLE,        ///石像鬼
    ST_MONSTER_GHOST,           ///幽灵
    ST_MONSTER_GHOUL,           ///食尸鬼


    ST_DEAD_MONSTER_ATTACK,                 //怪物攻击导致死亡
    ST_DEAD_TRIGGER_GRIPPING_TRAP,          //夹子夹死
    ST_DEAD_BUFFER_FIRE,                    //着火
    ST_DEAD_BUFFER_POISONING,               //中毒
    ST_DEAD_FALL,                           //摔死


    ST_FOUND_HIDE_MSG,              //隐藏信息
    ST_FOUND_HIDE_DOOR,             //隐藏门
    ST_FOUND_HIDE_TRAP,             //隐藏陷阱

    ST_BOSS_SLIMEKING,               ///史莱姆王
    ST_BOSS_WARDEN,                  ///典狱长
    ST_BOSS_ARCHBISHOP,              ///大主教
    ST_BOSS_KOBOLDLEADER,            ///狗头人首领
    ST_BOSS_GIANT,                   ///巨人格鲁尔德
    ST_BOSS_SKELETONKING,            ///骷髅王

    ST_DT_SEWER,              ////下水道
    ST_DT_PRISON,             ////监狱
    ST_DT_FANE,               ////神殿
    ST_DT_MINES,              ////矿坑
    ST_DT_CAVE,               ////洞穴
    ST_DT_TOMB,               ////古墓
    ST_DT_DWARF_CASTLE,       ////矮人城堡
    ST_DT_MAGA_TOWER,         ////法师塔
    ST_DT_ORC_FORTRESS,       ////兽人堡垒
    ST_DT_ELF_FOREST,         ////妖精森林
    ST_DT_TROLL_TEMPLE,       ////巨魔神庙
    ST_DT_BEHOLDER_CASTLE,     ////眼魔
    ST_DT_WARP_SPACE,          ////异空间
    ST_DT_DRAGON_LAIR,         ////龙穴
    ST_DT_LICH_TOMB,           ////巫妖墓室
    
    ST_TOTAL_COPPER,
    ST_TOTAL_STEP,
    ST_TOTAL_MONSTER_KILL,
    ST_TOTAL_USE_KEY,
    ST_TOTAL_CRITICAL,
    ST_TOTAL_DODGE,
    ST_TOTAL_BLOCK,
    ST_TOTAL_ROLE_DEAD,
    ST_TOTAL_CHEST_COPPER,
    ST_TOTAL_CHEST_SILVER,
    ST_TOTAL_CHEST_GOLD,
    ST_TOTAL_JAR,
    ST_TOTAL_ROLE_LEVEL,
    ST_TOTAL_ELITE_MONSTER,
    ST_TOTAL_IDENTIFY,
    ST_TOTAL_IDENTIFY_BEOW_TOW,         ///鉴定属性超过两条次数
    ST_TOTAL_IDENTIFY_QUALITY,          //鉴定品质
    ST_TOTAL_BAG_EXTEND,                //背包扩容次数
    ST_TOTAL_BAG_FULL,                  //背包装满
    ST_TOTAL_DISCARD_ITEM,              //道具丢弃总计
    ST_TOTAL_DISCARD_EQUIP,             //丢弃装备
    ST_TOTAL_PICK_ITEM,                 //拾取道具
    ST_TOTAL_PICK_NOT_MARIC,            //拾取费魔法物品
    ST_TOTAL_NINE_STEP,                 //9秒移动超过10步
    ST_TOTAL_THIRTY_NOT_MOVE,           //30秒不动
    ST_TOTAL_EXPLORE_ALL_AREA,          //探索区域
    ST_TOTAL_FOUND_DOOR_TRAP,           //隐藏门_陷阱
    ST_TOTAL_SEARCH,                    //检索

    ST_TOTAL_CHEST_BOX,                 //开启宝箱
    ST_TOTAL_MEET_THIEF,                //遇见盗贼
    ST_TOTAL_MEET_HAG,                  //遇见魔女
    ST_TOTAL_MEET_SAGE,                 //遇见智者
    ST_TOTAL_NURSE_TREAT,               //护士治疗
    ST_TOTAL_BUY_EQUIP,                 //购买装备
    ST_TOTAL_BUY_POTION_SCROLL,         //购买药水
    ST_TOTAL_BUY_MARICORAM,             //购买卷轴
    ST_TOTAL_ROLE_HP,                   //生命值
    ST_TOTAL_ROLE_MAX_ATTACK,           //攻击力
    ST_TOTAL_STEALTH,                   //隐身
    ST_TOTAL_NOT_FAIL_DEAD,             //没有摔死
    ST_TOTAL_WEAK_RECOVER,              //虚弱恢复
    ST_TOTAL_POISON_RECOVER,            //中毒恢复
    ST_TOTAL_SPEED_UP,                  //加速
    ST_TOTAL_STRONG,                    //进入强壮
    ST_MAX

};
const std::vector<std::string> ACHIEVEMENT_DATAIL_TYPE_NAME = {
    //敌人

    //怪物猎手
    "ADT_MONSTER_1",           //第一滴血
    "ADT_MONSTER_2",           //牛刀小试
    "ADT_MONSTER_3",           //百人斩
    "ADT_MONSTER_4",           //冷血屠夫
    "ADT_MONSTER_5",           //血流成河
    "ADT_MONSTER_6",           //超神
    //end

    //定点清除
    "ADT_SPECIFIED_MONSTER_1", //行尸走肉
    "ADT_SPECIFIED_MONSTER_2", //野兽猎人
    "ADT_SPECIFIED_MONSTER_3", //亡灵杀手
    "ADT_SPECIFIED_MONSTER_4", //清洁工
    "ADT_SPECIFIED_MONSTER_5", //王牌精英
    "ADT_SPECIFIED_MONSTER_6", //标本收集者
    //end

    //地牢主人
    "ADT_BOSS_KILL_1",        //勇闯下水道
    "ADT_BOSS_KILL_2",        //监狱风云
    "ADT_BOSS_KILL_3",        //网红教覆灭记
    "ADT_BOSS_KILL_4",        //死亡矿井
    "ADT_BOSS_KILL_5",        //洞穴历险记
    "ADT_BOSS_KILL_6",        //墓穴回魂夜
    //end

    //end

    //死亡
    "ADT_ROLE_FALL_DEAD",     //失足青年
    "ADT_ROLE_POISON_DEAD",   //娘娘赐你死
    "ADT_ROLE_CLIP_DEAD",     //大刑伺候
    "ADT_ROLE_FILE_DEAD",     //追寻布鲁偌

    //新的墓碑
    "ADT_ROLE_DEAD_1",        //第一次墓碑
    "ADT_ROLE_DEAD_2",        //无可救药
    "ADT_ROLE_DEAD_3",        //春哥已死
    "ADT_ROLE_DEAD_4",        //你就是死神
    //end

    //end

    //道具

    //鉴定家
    "ADT_IDENTIFY_1",         //初出茅庐
    "ADT_IDENTIFY_2",         //小有名气
    "ADT_IDENTIFY_3",         //锋芒毕露
    "ADT_IDENTIFY_4",         //大鉴定师
    //end

    //收藏家
    "ADT_EXTEND_BAG",         //背包还不够大
    "ADT_BAG_FULL",           //满载而归
    "ADT_EXTEND_BAG_MAX",     //有钱人就是要买包包
    "ADT_WEALTHY_MEN",        //有钱人
    "ADT_SPENDERS_MEN",       //败家子
    "ADT_PICK_ITEM",          //走路要低头
    "ADT_PICK_NOT_MARIC_ITEM",//破烂王
    //end
    //end

    //冒险家
    "ADT_MARATHON",             //马拉松
    "ADT_WORLD_RECORD",         //世界纪录保持者
    "ADT_THIRTY_NOT_MOVE",      //稳如泰山
    "ADT_OBSESSION_MEN",        //强迫症患者
    "ADT_FOUND_HIDDEN_DOOR",    //逃不过我的法眼
    "ADT_FOUND_HIDDEN_TRAP_FIRST",    //哎哟,吓死宝宝了
    "ADT_FOUND_HIDDEN_TRAP",    //火眼金睛
    "ADT_FOUND_HIDDEN_MSG_FIRST",     //这是什么
    "ADT_FOUND_HIDDEN_MSG",           //维基百科
    "ADT_SEARCH_KING",          //问题王
    "ADT_LOVE_QUESTION",        //爱提问的小盆友
    "ADT_ALL_ARRIVE_DUNGEON",   //大冒险家
    //end

    //盗贼工会
    "ADT_BREAK_JAR_1",        //破罐破摔
    "ADT_BREAK_JAR_2",        //破坏王
    "ADT_COPPER_BOX_FIRST",   //小盗贼
    "ADT_SILVER_BOX_FIRST",   //盗贼高手
    "ADT_GOLD_BOX_FIRST",     //盗贼精英
    "ADT_OPEN_BOX",           //盗贼大王
    "ADT_USE_KEY",            //天下无贼
    "ADT_MEET_THIEF_FIRST",   //加入盗贼工会
    "ADT_NURSE_TREAT",        //制服诱惑
    "ADT_MEET_HAG_FIRST",     //魔女的条件
    "ADT_SAGE_STORY",         //听爷爷讲故事
    "ADT_BUY_EQUIP",          //北市买长鞭
    "ADT_BUY_MARICORIM",         //穷家富路
    "ADT_BUY_SCROLL_POTION",         //我需要卷轴
    //end


    //致富之路
    "ADT_HAVE_GOLD_1",        //第一桶金
    "ADT_HAVE_GOLD_2",        //小富即安
    "ADT_HAVE_GOLD_3",        //大富翁
    "ADT_HAVE_GOLD_4",        //富可帝国
    //END

    //成长的烦恼
    "ADT_ROLE_LEVEL_1",       //成年
    "ADT_ROLE_LEVEL_2",       //熟透
    "ADT_ROLE_HP",            //血牛

    "ADT_ROLE_ATTACK",        //赛亚人变身
    "ADT_ROLE_DODGE",         //凌波微步
    "ADT_ROLE_CRIT",          //扎你苦胆
    "ADT_ROLE_BLOCK",         //当当当

    "ADT_ROLE_LUCK_NOT_DEAD",//大难不死
    "ADT_STEALTHY_FIRST",     //阴影下成长
    "ADT_WEAK_RECOVER",       //大病康复
    "ADT_POISON_NOT_DEAD",    //毒不死的小强

    "ADT_SPEED_UP_FIRST",     //飞一般的感觉
    "ADT_STRONG_FIRST",       //挡我者死
    //end

};
enum eAchievementDetailType
{
    ADT_UNKOWN=-1,

    //敌人

    //怪物猎手
    ADT_MONSTER_1   =0,           //第一滴血
    ADT_MONSTER_2,           //牛刀小试
    ADT_MONSTER_3,           //百人斩
    ADT_MONSTER_4,           //冷血屠夫
    ADT_MONSTER_5,           //血流成河
    ADT_MONSTER_6,           //超神
    //end

    //定点清除
    ADT_SPECIFIED_MONSTER_1, //行尸走肉
    ADT_SPECIFIED_MONSTER_2, //野兽猎人
    ADT_SPECIFIED_MONSTER_3, //亡灵杀手
    ADT_SPECIFIED_MONSTER_4, //清洁工
    ADT_SPECIFIED_MONSTER_5, //王牌精英
    ADT_SPECIFIED_MONSTER_6, //标本收集者
    //end

    //地牢主人
    ADT_BOSS_KILL_1,        //勇闯下水道
    ADT_BOSS_KILL_2,        //监狱风云
    ADT_BOSS_KILL_3,        //网红教覆灭记
    ADT_BOSS_KILL_4,        //死亡矿井
    ADT_BOSS_KILL_5,        //洞穴历险记
    ADT_BOSS_KILL_6,        //墓穴回魂夜
    //end

    //end

    //死亡
    ADT_ROLE_FALL_DEAD,     //失足青年
    ADT_ROLE_POISON_DEAD,   //娘娘赐你死
    ADT_ROLE_CLIP_DEAD,     //大刑伺候
    ADT_ROLE_FILE_DEAD,     //追寻布鲁偌

    //新的墓碑
    ADT_ROLE_DEAD_1,        //第一次墓碑
    ADT_ROLE_DEAD_2,        //无可救药
    ADT_ROLE_DEAD_3,        //春哥已死
    ADT_ROLE_DEAD_4,        //你就是死神
    //end

    //end

    //道具

    //鉴定家
    ADT_IDENTIFY_1,         //初出茅庐
    ADT_IDENTIFY_2,         //小有名气
    ADT_IDENTIFY_3,         //锋芒毕露
    ADT_IDENTIFY_4,         //大鉴定师
    //end

    //收藏家
    ADT_EXTEND_BAG,         //背包还不够大
    ADT_BAG_FULL,           //满载而归
    ADT_EXTEND_BAG_MAX,     //有钱人就是要买包包
    ADT_WEALTHY_MEN,        //有钱人
    ADT_SPENDERS_MEN,       //败家子
    ADT_PICK_ITEM,          //走路要低头
    ADT_PICK_NOT_MARIC_ITEM,//破烂王
    //end
    //end

    //冒险家
    ADT_MARATHON,             //马拉松
    ADT_WORLD_RECORD,         //世界纪录保持者
    ADT_THIRTY_NOT_MOVE,      //稳如泰山
    ADT_OBSESSION_MEN,        //强迫症患者
    ADT_FOUND_HIDDEN_DOOR,    //逃不过我的法眼
    ADT_FOUND_HIDDEN_TRAP_FIRST,    //哎哟,吓死宝宝了
    ADT_FOUND_HIDDEN_TRAP,    //火眼金睛
    ADT_FOUND_HIDDEN_MSG_FIRST,     //这是什么
    ADT_FOUND_HIDDEN_MSG,           //维基百科
    ADT_SEARCH_KING,          //问题王
    ADT_LOVE_QUESTION,        //爱提问的小盆友
    ADT_ALL_ARRIVE_DUNGEON,   //大冒险家
    //end

    //盗贼工会
    ADT_BREAK_JAR_1,        //破罐破摔
    ADT_BREAK_JAR_2,        //破坏王
    ADT_COPPER_BOX_FIRST,   //小盗贼
    ADT_SILVER_BOX_FIRST,   //盗贼高手
    ADT_GOLD_BOX_FIRST,     //盗贼精英
    ADT_OPEN_BOX,           //盗贼大王
    ADT_USE_KEY,            //天下无贼
    ADT_MEET_THIEF_FIRST,   //加入盗贼工会
    ADT_NURSE_TREAT,        //制服诱惑
    ADT_MEET_HAG_FIRST,     //魔女的条件
    ADT_SAGE_STORY,         //听爷爷讲故事
    ADT_BUY_EQUIP,          //北市买长鞭
    ADT_BUY_MARICORIM,         //穷家富路
    ADT_BUY_SCROLL_POTION,         //我需要卷轴
    //end


    //致富之路
    ADT_HAVE_GOLD_1,        //第一桶金
    ADT_HAVE_GOLD_2,        //小富即安
    ADT_HAVE_GOLD_3,        //大富翁
    ADT_HAVE_GOLD_4,        //富可帝国
    //END

    //成长的烦恼
    ADT_ROLE_LEVEL_1,       //成年
    ADT_ROLE_LEVEL_2,       //熟透
    ADT_ROLE_HP,            //血牛

    ADT_ROLE_ATTACK,        //赛亚人变身
    ADT_ROLE_DODGE,         //凌波微步
    ADT_ROLE_CRIT,          //扎你苦胆
    ADT_ROLE_BLOCK,         //当当当

    ADT_ROLE_LUCK_NOT_DEAD,//大难不死
    ADT_STEALTHY_FIRST,     //阴影下成长
    ADT_WEAK_RECOVER,       //大病康复
    ADT_POISON_NOT_DEAD,    //毒不死的小强

    ADT_SPEED_UP_FIRST,     //飞一般的感觉
    ADT_STRONG_FIRST,       //挡我者死
    //end

    ADT_COUNT
};

#endif /* AchieveConst_h */
