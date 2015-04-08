//
//  Item.h
//  TinyFlare
//
//  Created by wang haibo on 15/4/7.
//
//

#ifndef __TinyFlare__Item__
#define __TinyFlare__Item__

#include "GameActor.h"
class Item : public GameActor
{
    friend class ActorsManager;
public:
    typedef enum{
        IT_ACCEL = 0,
        IT_BOOM,
        IT_MULTI,
        IT_PROTETED,
        IT_TIME,
        IT_UNKNOWN
    } ItemType;
protected:
    Item();
    virtual ~Item();
    virtual void update(float delta) override;
    void setItemType(ItemType itemType) { m_ItemType = itemType; }
    ItemType getItemType() const { return m_ItemType; }
public:
    void loadTexture(const std::string& textureName);
private:
    cocos2d::Sprite*                m_pBoundModel;
    ItemType                        m_ItemType;
    float                           m_fLifeTime;
    bool                            m_bHasBeginFadeOut;
};

#endif /* defined(__TinyFlare__Item__) */
