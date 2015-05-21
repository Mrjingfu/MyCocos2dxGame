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

#include "CCAggregateReward.h"

bool soomla::CCAggregateReward::init(
        cocos2d::__String *id,
        cocos2d::__String *name,
        cocos2d::__Array *rewards,
        CCSchedule *schedule) {

    bool result = CCReward::init(id, name, schedule);

    if (result) {
        setRewards(rewards);
        return true;
    } else {
        return false;
    }
}

bool soomla::CCAggregateReward::initWithDictionary(cocos2d::__Dictionary *dict) {
    CCReward::initWithDictionary(dict);

    cocos2d::__Array *dictArray = dynamic_cast<cocos2d::__Array *>(dict->objectForKey(CCCoreConsts::JSON_REWARDS));
    CC_ASSERT(dictArray);
    setRewards(this->getDomainsFromDictArray(dictArray));

    return true;
}

cocos2d::__Dictionary *soomla::CCAggregateReward::toDictionary() {
    cocos2d::__Dictionary *dict = CCReward::toDictionary();

    cocos2d::__Array *dictArray = this->getDictArrayFromDomains(this->getDictArrayFromDomains(getRewards()));
    if (dictArray != nullptr) {
        dict->setObject(dictArray, CCCoreConsts::JSON_REWARDS);
    }

    return dict;
}

soomla::CCAggregateReward::~CCAggregateReward() {
    CC_SAFE_RELEASE(mRewards);
}
