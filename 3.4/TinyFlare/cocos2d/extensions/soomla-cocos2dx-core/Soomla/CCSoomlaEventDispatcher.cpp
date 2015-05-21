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

#include "CCSoomlaEventDispatcher.h"

namespace soomla {

    USING_NS_CC;

    static CCSoomlaEventDispatcher *s_SharedInstance = NULL;

    CCSoomlaEventDispatcher *CCSoomlaEventDispatcher::getInstance() {
        if (!s_SharedInstance) {
            s_SharedInstance = new CCSoomlaEventDispatcher();
        }

        return s_SharedInstance;
    }

	void CCSoomlaEventDispatcher::registerEventHandler(const char *key, std::function<void(__Dictionary *)> handler) {
		mEventHandlers[key] = handler;
	}

    void CCSoomlaEventDispatcher::unregisterEventHandler(const char *key) {
        mEventHandlers.erase(key);
    }

    void CCSoomlaEventDispatcher::ndkCallback(__Dictionary *parameters) {
        __String *eventName = dynamic_cast<__String *>(parameters->objectForKey("method"));
        if (eventName == NULL) {
            // Suppress any events without callbacks (push event probably)
            return;
        }

        std::function<void(__Dictionary *)> handler = mEventHandlers[eventName->getCString()];

        if (handler) {
            handler(parameters);
        }
		else {
            log("Unregistered event happened: %s", eventName->getCString());
        }
    }
}
