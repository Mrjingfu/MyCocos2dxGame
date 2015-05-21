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

#include "CCBadgeReward.h"

soomla::CCBadgeReward *soomla::CCBadgeReward::create(
        cocos2d::__String *id,
        cocos2d::__String *name,
        cocos2d::__String *iconUrl) {

    CCBadgeReward *ret = new CCBadgeReward();
    if (ret->init(id, name, iconUrl)) {
        ret->autorelease();
    }
    else {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool soomla::CCBadgeReward::init(
        cocos2d::__String *id,
        cocos2d::__String *name,
        cocos2d::__String *iconUrl) {

    bool result = CCReward::init(id, name);

    if (result) {
        setIconUrl(iconUrl);
        return true;
    } else {
        return false;
    }
}

bool soomla::CCBadgeReward::initWithDictionary(cocos2d::__Dictionary *dict) {
    CCReward::initWithDictionary(dict);

    fillIconUrlFromDict(dict);

    return true;
}

cocos2d::__Dictionary *soomla::CCBadgeReward::toDictionary() {
    cocos2d::__Dictionary *dict = CCReward::toDictionary();

    putIconUrlToDict(dict);

    return dict;
}

soomla::CCBadgeReward::~CCBadgeReward() {
    CC_SAFE_RELEASE(mIconUrl);
}

const char *soomla::CCBadgeReward::getType() const {
    return CCCoreConsts::JSON_JSON_TYPE_BADGE;
}


bool soomla::CCBadgeReward::takeInner() {
    // nothing to do here... the parent Reward takes in storage
    return true;
}

bool soomla::CCBadgeReward::giveInner() {
    // nothing to do here... the parent Reward gives in storage
    return true;
}
