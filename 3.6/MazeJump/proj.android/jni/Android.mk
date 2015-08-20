LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos/ui)
$(call import-add-path,$(LOCAL_PATH))
LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

# 遍历目录及子目录的函数




# 遍历Classes目录
ALLFILES := $(call walk, $(LOCAL_PATH)/../../Classes)

FILE_LIST := hellocpp/main.cpp
# 从所有文件中提取出所有.cpp文件
FILE_LIST += $(filter %.cpp, $(ALLFILES))

FILE_INCLUDES := $(shell find $(LOCAL_PATH)/../../Classes -type d)

LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)

LOCAL_LDLIBS := -landroid -llog
LOCAL_C_INCLUDES := $(FILE_INCLUDES)
LOCAL_WHOLE_STATIC_LIBRARIES := PluginGoogleAnalytics sdkbox PluginIAP android_native_app_glue

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_STATIC_LIBRARIES += cocos_localstorage_static
#LOCAL_STATIC_LIBRARIES
#LOCAL_STATIC_LIBRARIES
# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,storage/local-storage)
$(call import-module, ./sdkbox)
$(call import-module, ./plugingoogleanalytics)
$(call import-module, ./pluginiap)
# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
