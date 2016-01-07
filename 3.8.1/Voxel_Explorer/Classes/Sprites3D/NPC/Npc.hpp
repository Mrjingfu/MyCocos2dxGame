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
    typedef enum{
        NPCS_UNKNOWN = 0,
        NPCS_IDLE,
        NPCS_ANSWER,
        NPCS_FADEOUT,
        NPCS_MAX
    } NPCState;
    static Npc* create(NPC_TYPE type);
    
    std::string getIconRes();
    virtual std::string getDesc();
    std::string getNpcName();
    std::string getNpcContent();
    
    NPC_TYPE getNPCType() const { return m_Type; }
    
    NPCState getState() const { return m_State; }
    void setState(NPCState state);
    
    void endAnswer();
    
    virtual void setActorDir( ActorDir dir );
    virtual void setVisited(bool visited);
protected:
    virtual void onEnterIdle();
    virtual void onExitIdle();
    
    virtual void onEnterAnswer();
    virtual void onExitAnswer();
    
    virtual void onEnterFadeOut();
    virtual void onExitFadeOut();
    
    void destroySelf();
    void doAnswer();
    bool createNpcLight();
private:
    NPC_TYPE    m_Type;
    NPCState   m_State;
};

#endif /* Npc_hpp */
