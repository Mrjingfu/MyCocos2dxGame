/*
 Copyright (C) 2012-2014 Soomla Inc.
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#include "CCReward.h"
#include "CCSequenceReward.h"
#include "CCNativeRewardStorage.h"
#include "CCKeyValueStorage.h"
#include "CCCoreEventDispatcher.h"

#define TAG "SOOMLA RewardStorage"

namespace soomla {
    
    USING_NS_CC;
    
    static CCRewardStorage *s_SharedRewardStorage = NULL;

    CCRewardStorage *CCRewardStorage::getInstance() {
        if (!s_SharedRewardStorage) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            s_SharedRewardStorage = new CCNativeRewardStorage();
#else
            s_SharedRewardStorage = new CCRewardStorage();
#endif
            s_SharedRewardStorage->retain();
        }

        return s_SharedRewardStorage;
    }

    bool CCRewardStorage::isRewardGiven(CCReward *reward) {
        return getTimesGiven(reward) > 0;
    }

    void CCRewardStorage::setRewardStatus(CCReward *reward, bool give) {
        setRewardStatus(reward, give, true);
    }
    
    void CCRewardStorage::setRewardStatus(CCReward *reward, bool give, bool notify) {
        this->setTimesGiven(reward, give, notify);
    }
    
    int CCRewardStorage::getTimesGiven(CCReward *reward) {
        const char *key = keyRewardTimesGiven(reward->getId()->getCString());
        const char *val = CCKeyValueStorage::getInstance()->getValue(key);
        if (val == NULL) {
            return 0;
        }
        return __String::create(val)->intValue();
    }
    
    int CCRewardStorage::getLastSeqIdxGiven(CCSequenceReward *sequenceReward) {
        const char *key = keyRewardIdxSeqGiven(sequenceReward->getId()->getCString());
        const char *val = CCKeyValueStorage::getInstance()->getValue(key);
        if (val == NULL) {
            return -1;
        }
        return __String::create(val)->intValue();
    }
    
    void CCRewardStorage::setLastSeqIdxGiven(CCSequenceReward *sequenceReward, unsigned int idx) {
        const char *key = keyRewardIdxSeqGiven(sequenceReward->getId()->getCString());
        CCKeyValueStorage::getInstance()->setValue(key, __String::createWithFormat("%d", idx)->getCString());
    }
    
    void CCRewardStorage::setTimesGiven(CCReward *reward, bool up, bool notify) {
        int total = getTimesGiven(reward) + (up ? 1 : -1);
        if(total<0) total = 0;
        
        const char *key = keyRewardTimesGiven(reward->getId()->getCString());
        CCKeyValueStorage::getInstance()->setValue(key, __String::createWithFormat("%d", total)->getCString());
        
        if (up) {
            key = keyRewardLastGiven(reward->getId()->getCString());
            
            time_t currentTime;
            time(&currentTime);
            __String *val = __String::createWithFormat("%lld", (long long)(((double)currentTime) * 1000));
            
            CCKeyValueStorage::getInstance()->setValue(key, val->getCString());
        }
        
        if (notify) {
            if (up) {
                CCCoreEventDispatcher::getInstance()->onRewardGivenEvent(reward);
            } else {
                CCCoreEventDispatcher::getInstance()->onRewardTakenEvent(reward);
            }
        }
    }
    
    const char* CCRewardStorage::keyRewards(const char* rewardId, const char* postfix) {
        return __String::createWithFormat("%srewards.%s.%s", DB_KEY_PRFIX, rewardId, postfix)->getCString();
    }
    
    const char* CCRewardStorage::keyRewardIdxSeqGiven(const char* rewardId) {
        return keyRewards(rewardId, "seq.id");
    }
    
    const char* CCRewardStorage::keyRewardTimesGiven(const char* rewardId) {
        return keyRewards(rewardId, "timesGiven");
    }
    
    const char* CCRewardStorage::keyRewardLastGiven(const char* rewardId) {
        return keyRewards(rewardId, "lastGiven");
    }
}
