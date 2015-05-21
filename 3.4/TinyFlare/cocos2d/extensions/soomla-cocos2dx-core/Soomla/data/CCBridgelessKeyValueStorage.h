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

#ifndef __CCBridgelessKeyValueStorage_H
#define __CCBridgelessKeyValueStorage_H

#include "CCKeyValueStorage.h"



namespace soomla {
    
    /**
     The bridgeless implementation of CCKeyValueStorage, uses Cocos2dx 
     facilities to store key-value data.
     
     See parent for all functions.
     */
    class CCBridgelessKeyValueStorage : public CCKeyValueStorage {
    public:
        CCBridgelessKeyValueStorage();
        virtual const char *getValue(const char *key) const;
        virtual void setValue(const char *key, const char *val);
        virtual void deleteKeyValue(const char *key);
        virtual void purge();
    protected:
        cocos2d::__Set *mStoredKeys;
        void addStoredKeys(const char* key);
        void removeStoredKeys(const char *key);
        void saveStoredKeys();
        void loadStoredKeys();
    };
}

#endif // __CCBridgelessKeyValueStorage_H
