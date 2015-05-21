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

#include "CCVirtualItemStorage.h"
#include "CCKeyValueStorage.h"
#include "CCSoomlaUtils.h"

namespace soomla {
    
    USING_NS_CC;
    
#define TAG "SOOMLA VirtualItemStorage"
    
    int CCVirtualItemStorage::getBalance(CCVirtualItem *item, CCError **error) {
        const char *itemId = item->getId()->getCString();
        const char *key = keyBalance(itemId);
        const char *val = CCKeyValueStorage::getInstance()->getValue(key);
        
        int balance = 0;
        if (val != NULL) {
            balance = __String::create(val)->intValue();
        }
        
        CCSoomlaUtils::logDebug(TAG, __String::createWithFormat("the balance for %s is %d", itemId, balance)->getCString());
        
        return balance;
    }
    
    int CCVirtualItemStorage::setBalance(CCVirtualItem *item, int balance, bool notify, CCError **error) {
        int oldBalance = getBalance(item);
        if (oldBalance == balance) {
            return balance;
        }
        
        const char *itemId = item->getId()->getCString();
        
        const char *balanceStr = __String::createWithFormat("%d", balance)->getCString();
        const char *key = keyBalance(itemId);
        
        CCKeyValueStorage::getInstance()->setValue(key, balanceStr);
        
        if (notify) {
            postBalanceChangeEvent(item, balance, 0);
        }
        
        return balance;
    }
    
    int CCVirtualItemStorage::add(CCVirtualItem *item, int amount, bool notify, CCError **error) {
        const char *itemId = item->getId()->getCString();
        int balance = getBalance(item);
        if (balance < 0) { /* in case the user "adds" a negative value */
            balance = 0;
            amount = 0;
        }
        
        const char *balanceStr = __String::createWithFormat("%d", balance + amount)->getCString();
        const char *key = keyBalance(itemId);
        
        CCKeyValueStorage::getInstance()->setValue(key, balanceStr);
        
        if (notify) {
            postBalanceChangeEvent(item, balance + amount, amount);
        }
        
        return balance + amount;
    }
    
    int CCVirtualItemStorage::remove(CCVirtualItem *item, int amount, bool notify, CCError **error) {
        const char *itemId = item->getId()->getCString();
        int balance = getBalance(item) - amount;
        if (balance < 0) {
            balance = 0;
            amount = 0;
        }
        
        const char *balanceStr = __String::createWithFormat("%d", balance)->getCString();
        const char *key = keyBalance(itemId);
        
        CCKeyValueStorage::getInstance()->setValue(key, balanceStr);
        
        if (notify) {
            postBalanceChangeEvent(item, balance, -1 * amount);
        }
        
        return balance;
    }
}