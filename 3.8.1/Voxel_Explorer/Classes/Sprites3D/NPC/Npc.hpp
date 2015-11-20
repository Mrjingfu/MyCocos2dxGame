//
//  Npc.hpp
//  Voxel_Explorer
//
//  Created by wang haibo on 15/11/17.
//
//

#ifndef Npc_hpp
#define Npc_hpp

#include "Actor.hpp"
extern const std::string NPC_NAMES[];
class Npc : public Actor
{
    Npc();
    virtual ~Npc();
public:
    typedef enum{
        NPC_CHILD = 0,      ///小孩
        NPC_SHOPGIRL,       ///女售货员
        NPC_OLDLADY,        ///老太太
        NPC_KNIGHT,         ///小骑士
        NPC_WEIRDO,         ///怪蜀黍
        NPC_OLDMAN,         ///老头
        NPC_LITTLEWITCH,    ///小魔女
        NPC_NURSE,          ///小护士
        NPC_UNKNOWN
    } NPC_TYPE;
    static Npc* create(NPC_TYPE type);
    
    virtual std::string getDesc();
    
    NPC_TYPE getNPCType() const { return m_Type; }
private:
    NPC_TYPE    m_Type;
};

#endif /* Npc_hpp */
