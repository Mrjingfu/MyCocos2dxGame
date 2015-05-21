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

#include "CCRandomReward.h"

soomla::CCRandomReward *soomla::CCRandomReward::create(
        cocos2d::__String *id,
        cocos2d::__String *name,
        cocos2d::__Array *rewards,
        CCSchedule *schedule) {

    CCRandomReward *ret = new CCRandomReward();
    if (ret->init(id, name, rewards, schedule)) {
        ret->autorelease();
    }
    else {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

soomla::CCRandomReward::~CCRandomReward() {
    CC_SAFE_RELEASE(mLastGivenReward);
}

const char *soomla::CCRandomReward::getType() const {
    return CCCoreConsts::JSON_JSON_TYPE_RANDOM;
}


bool soomla::CCRandomReward::takeInner() {
    // for now is able to take only last given
    if (mLastGivenReward == NULL) {
        return false;
    }

    bool taken = mLastGivenReward->take();
    setLastGivenReward(NULL);

    return taken;
}

bool soomla::CCRandomReward::giveInner() {
    CCReward *randomReward = (CCReward *) getRewards()->getRandomObject();
    CCLOG("%s", randomReward->getId()->getCString());
    randomReward->give();
    setLastGivenReward(randomReward);

    return true;
}
