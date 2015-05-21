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

#include "base/CCUserDefault.h"

#include "CCBridgelessKeyValueStorage.h"

namespace soomla {
    
    USING_NS_CC;
    
    #define KEY_VALUE_STORAGE_KEY "soomla.kvs.keys"
    
    CCBridgelessKeyValueStorage::CCBridgelessKeyValueStorage() {
        mStoredKeys = __Set::create();
        mStoredKeys->retain();
        
        loadStoredKeys();
    }
    
    const char *CCBridgelessKeyValueStorage::getValue(const char *key) const {
        std::string defaultValue = "";
        std::string result = UserDefault::getInstance()->getStringForKey(key, defaultValue);
        if (result == defaultValue) {
            return NULL;
        }
        
        // Using this for pooling facilities, so c_str won't go away when returned
        __String *returnedValue = __String::create(result);
        return returnedValue->getCString();
    }
    
    void CCBridgelessKeyValueStorage::setValue(const char *key, const char *val) {
        UserDefault::getInstance()->setStringForKey(key, val);
        UserDefault::getInstance()->flush();
        
        addStoredKeys(key);
        saveStoredKeys();
    }
    
    void CCBridgelessKeyValueStorage::deleteKeyValue(const char *key) {
        UserDefault::getInstance()->setStringForKey(key, "");
        UserDefault::getInstance()->flush();
        
        removeStoredKeys(key);
        saveStoredKeys();
    }
    
    void CCBridgelessKeyValueStorage::purge() {
        for(__SetIterator i = mStoredKeys->begin(); i != mStoredKeys->end(); i++) {
            if (!(*i)) {
                break;
            }
            
            __String *key = dynamic_cast<__String *>(*i);
            deleteKeyValue(key->getCString());
        }
        
        mStoredKeys->removeAllObjects();
        
        UserDefault::getInstance()->setStringForKey(KEY_VALUE_STORAGE_KEY, "");
        UserDefault::getInstance()->flush();
    }
    
    void CCBridgelessKeyValueStorage::addStoredKeys(const char *key) {
        __String *wrapKey = __String::create(key);
        
        if (mStoredKeys->containsObject(wrapKey)) {
            return;
        }
        
        mStoredKeys->addObject(wrapKey);
    }
    
    void CCBridgelessKeyValueStorage::removeStoredKeys(const char *key) {
        __String *wrapKey = __String::create(key);
        
        mStoredKeys->removeObject(wrapKey);
    }
    
    void CCBridgelessKeyValueStorage::saveStoredKeys() {
        std::string joinedKeys = "";
        for(__SetIterator i = mStoredKeys->begin(); i != mStoredKeys->end(); i++) {
            if (!(*i)) {
                break;
            }
            
            __String *key = dynamic_cast<__String *>(*i);
            joinedKeys.append("#").append(key->getCString());
        }
        
        UserDefault::getInstance()->setStringForKey(KEY_VALUE_STORAGE_KEY, joinedKeys);
        UserDefault::getInstance()->flush();
    }
    
    void CCBridgelessKeyValueStorage::loadStoredKeys() {
        std::string joinedKeys = UserDefault::getInstance()->getStringForKey(KEY_VALUE_STORAGE_KEY, "");
        
        std::stringstream ss(joinedKeys);
        std::string item;
        while(std::getline(ss, item, '#')) {
            addStoredKeys(item.c_str());
        }
    }
}
