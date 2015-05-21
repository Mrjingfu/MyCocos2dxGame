
#ifndef __CCVirtualItemReward_H_
#define __CCVirtualItemReward_H_

#include "CCReward.h"
#include "CCCoreConsts.h"
#include "CCStoreConsts.h"

namespace soomla {
    /**
     A specific type of `CCReward` is the one you'll use to give your
     users some amount of a virtual item when they complete something.
     */
    class CCVirtualItemReward : public CCReward {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__Integer *, mAmount, Amount, CCStoreConsts::JSON_AMOUNT);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__String *, mAssociatedItemId, AssociatedItemId, CCStoreConsts::JSON_ASSOCIATED_ITEM_ID);
    public:
        /**
         Creates a `CCVirtualItemReward`.
         @param rewardId See parent
         @param name See parent
         @param amount The amount of associated items to give when reward is 
         given
         @param associatedItemId The ID of the virtual items to give
         @return The Virtual Item Reward.
         */
        static CCVirtualItemReward *create(
                cocos2d::__String *rewardId,
                cocos2d::__String *name,
                cocos2d::__Integer * amount,
                cocos2d::__String * associatedItemId
        );

        /**
         Creates a `CCVirtualItemReward` from a dictionary.
         @param dict A dictionary containing keys for the reward's properties
         @return The Virtual Item Reward.
         */
        SL_CREATE_WITH_DICTIONARY(CCVirtualItemReward);

        virtual bool init(
                cocos2d::__String *rewardId,
                cocos2d::__String *name,
                cocos2d::__String *associatedItemId,
                cocos2d::__Integer *amount
        );

        virtual bool initWithDictionary(cocos2d::__Dictionary *dict);

        /**
         Converts the reward into a `CCDictionary`.
         @return `CCDictionary` representation of this `CCVirtualItemReward`.
         */
        virtual cocos2d::__Dictionary *toDictionary();

        virtual ~CCVirtualItemReward();

        virtual const char *getType() const;


    protected:
        virtual bool takeInner();

        virtual bool giveInner();
    };
};

#endif //__CCVirtualItemReward_H_
