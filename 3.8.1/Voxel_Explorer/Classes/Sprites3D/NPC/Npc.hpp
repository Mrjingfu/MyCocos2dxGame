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
class Npc : public Actor
{
    Npc();
    virtual ~Npc();
public:
    typedef enum{
        NPC_UNKNOWN = 0,
    } NPC_TYPE;
    static Npc* create(NPC_TYPE type);
};

#endif /* Npc_hpp */
