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

#include "CCSoomlaEntity.h"
#include "CCSoomlaUtils.h"
#include "CCDomainFactory.h"

namespace soomla {

    #define TAG "SOOMLA SoomlaEntity"

    using namespace cocos2d;

    bool CCSoomlaEntity::init(cocos2d::__String *id,cocos2d::__String *name, cocos2d::__String *description) {
        setId(id);
        setName(name);
        setDescription(description);

        return true;
    }

    bool CCSoomlaEntity::initWithDictionary(cocos2d::__Dictionary *dict) {
        fillIdFromDict(dict);
        fillNameFromDict(dict);
        fillDescriptionFromDict(dict);

        if (mId == NULL) {
            CCSoomlaUtils::logError(TAG, "This is BAD! We don't have ID in the given dict. Stopping here.");
            CC_ASSERT(false);
        }
        if (mName == NULL) {
            setName(__String::create(""));
        }
        if (mDescription == NULL) {
            setDescription(__String::create(""));
        }

        return true;
    }


    CCSoomlaEntity::~CCSoomlaEntity() {
        CC_SAFE_RELEASE(mId);
        CC_SAFE_RELEASE(mName);
        CC_SAFE_RELEASE(mDescription);
    }

    cocos2d::__Dictionary *CCSoomlaEntity::toDictionary() {
        if (mId == NULL) {
            CCSoomlaUtils::logError(TAG, "This is BAD! We don't have ID in the this SoomlaEntity. Stopping here.");
            CC_ASSERT(false);
            return NULL;
        }

        __Dictionary* dict = __Dictionary::create();
        putIdToDict(dict);
        putNameToDict(dict);
        putDescriptionToDict(dict);

        return putTypeData(dict, getType());
    }

    bool CCSoomlaEntity::equals(cocos2d::Ref *obj) const {
        // If parameter is null return false.
        if (obj == NULL) {
            return false;
        }

        CCSoomlaEntity *castedObj = dynamic_cast<CCSoomlaEntity *>(obj);
        if (!castedObj) {
            return false;
        }

        if (strcmp(castedObj->getType(), getType()) != 0) {
            return false;
        }

        if (castedObj->getId()->compare(getId()->getCString()) != 0) {
            return false;
        }

        return true;
    }

    CCSoomlaEntity *CCSoomlaEntity::clone(const char *newId) {
        cocos2d::__Dictionary *dict = this->toDictionary();
        dict->setObject(cocos2d::__String::create(newId), CCCoreConsts::JSON_ITEM_ITEM_ID);
        return (CCSoomlaEntity *) CCDomainFactory::getInstance()->createWithDictionaryAndType(dict, getType());
    }
}
