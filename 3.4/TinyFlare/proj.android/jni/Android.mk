LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_DEFAULT_CPP_EXTENSION := cpp

SOURCE_FILES := hellocpp/main.cpp \
                   ../../Classes/*.cpp \
                   ../../Classes/Actors/*.cpp \
                   ../../Classes/Const/*.cpp \
                   ../../Classes/Controllers/*.cpp \
                   ../../Classes/CustomActions/*.cpp \
                   ../../Classes/CustomSprites/*.cpp \
                   ../../Classes/Layers/*.cpp \
                   ../../Classes/UI/*.cpp \
                   ../../Classes/Utilities/*.cpp

LOCAL_SRC_FILES := 	$(foreach F, $(SOURCE_FILES), $(addprefix $(dir $(F)),$(notdir $(wildcard $(LOCAL_PATH)/$(F)))))

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
					$(LOCAL_PATH)/../../Classes/Actors \
					$(LOCAL_PATH)/../../Classes/Const \
					$(LOCAL_PATH)/../../Classes/Controllers \
					$(LOCAL_PATH)/../../Classes/CustomActions \
					$(LOCAL_PATH)/../../Classes/CustomSprites \
					$(LOCAL_PATH)/../../Classes/Layers \
					$(LOCAL_PATH)/../../Classes/UI \
					$(LOCAL_PATH)/../../Classes/Utilities

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_STATIC_LIBRARIES += cocos_ui_static
LOCAL_STATIC_LIBRARIES += cocos_extension_static
LOCAL_STATIC_LIBRARIES += cocos2dx_store_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,audio/android)
$(call import-module,ui)
$(call import-module,extensions)
$(call import-module,extensions/cocos2dx-store)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
