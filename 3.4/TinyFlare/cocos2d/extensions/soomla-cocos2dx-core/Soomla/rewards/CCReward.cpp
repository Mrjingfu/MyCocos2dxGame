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
#include "CCRewardStorage.h"
#include "CCSoomlaUtils.h"

#define TAG "SOOMLA Reward"

bool soomla::CCReward::init(cocos2d::__String *id, cocos2d::__String *name, CCSchedule *schedule) {
    bool ret = CCSoomlaEntity::init(id, name);

    if (ret) {
        setSchedule(schedule != NULL ? schedule : CCSchedule::createAnyTimeOnce());
        addReward(this);
        return true;
    }

    return ret;
}

bool soomla::CCReward::initWithDictionary(cocos2d::__Dictionary *dict) {
    bool ret = CCSoomlaEntity::initWithDictionary(dict);

    if (ret) {
        CCSchedule *schedule;
        if (dict->objectForKey(CCCoreConsts::JSON_SCHEDULE)) {
            schedule = CCSchedule::createWithDictionary((cocos2d::__Dictionary *) dict->objectForKey(CCCoreConsts::JSON_SCHEDULE));
        }
        else {
            schedule = CCSchedule::createAnyTimeOnce();
        }
        setSchedule(schedule);
        addReward(this);
        return true;
    }

    return ret;
}

cocos2d::__Dictionary *soomla::CCReward::toDictionary() {
    cocos2d::__Dictionary* dict = CCSoomlaEntity::toDictionary();

    if (mSchedule) {
        dict->setObject(mSchedule->toDictionary(), CCCoreConsts::JSON_SCHEDULE);
    }

    return dict;
}

soomla::CCReward::~CCReward() {
    CC_SAFE_RELEASE(mSchedule);
}

bool soomla::CCReward::take() {
    if (!CCRewardStorage::getInstance()->isRewardGiven(this)) {
        CCSoomlaUtils::logDebug(TAG,
                cocos2d::__String::createWithFormat("Reward not given. id: %s", getId()->getCString())->getCString());
        return false;
    }

    if (takeInner()) {
        CCRewardStorage::getInstance()->setRewardStatus(this, false);
        return true;
    }

    return false;
}

bool soomla::CCReward::give() {
    if (!mSchedule->approve(CCRewardStorage::getInstance()->getTimesGiven(this))) {
        CCSoomlaUtils::logDebug(TAG,
                cocos2d::__String::createWithFormat("(Give) Reward is not approved by Schedule. id: %s", getId()->getCString())->getCString());
        return false;
    }

    if (giveInner()) {
        CCRewardStorage::getInstance()->setRewardStatus(this, true);
        return true;
    }

    return false;
}

bool soomla::CCReward::isOwned() {
    return CCRewardStorage::getInstance()->isRewardGiven(this);
}

cocos2d::__Dictionary *soomla::CCReward::rewardsMap = NULL;

void soomla::CCReward::addReward(CCReward *reward) {
    if (rewardsMap == NULL) {
        rewardsMap = cocos2d::__Dictionary::create();
        rewardsMap->retain();
    }
    
    rewardsMap->setObject(reward, reward->getId()->getCString());
}

soomla::CCReward *soomla::CCReward::getReward(cocos2d::__String *id) {
    if (rewardsMap == NULL) {
        return NULL;
    }
    
    return dynamic_cast<CCReward *>(rewardsMap->objectForKey(id->getCString()));
}
