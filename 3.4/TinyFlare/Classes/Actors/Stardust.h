//
//  Stardust.h
//  TinyFlare
//
//  Created by wang haibo on 15/4/20.
//
//

#ifndef __TinyFlare__Stardust__
#define __TinyFlare__Stardust__

#include "GameActor.h"
class Stardust : public GameActor
{
    friend class ActorsManager;
public:
    typedef enum{
        ST_SMALL = 0,
        ST_LARGE,
        ST_UNKNOWN
    } StardustType;
protected:
    Stardust();
    virtual ~Stardust();
    
    virtual void update(float delta) override;
    virtual void onEnterDead() override;
    
    void setStardustType(StardustType stardustType) { m_StardustType = stardustType; }
    StardustType getStardustType() const { return m_StardustType; }
public:
    void loadModel(const std::string& modelName);
private:
    StardustType                    m_StardustType;
};

#endif /* defined(__TinyFlare__Stardust__) */
