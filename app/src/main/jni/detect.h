#include <jni.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/inotify.h>
#include <sys/stat.h>

#include <android/log.h>


#define MEM_ZERO(pDest, destSize) memset(pDest, 0, destSize)

#define LOG_INFO(tag, msg) __android_log_write(ANDROID_LOG_INFO, tag, msg);
#define LOG_DEBUG(tag, msg) __android_log_write(ANDROID_LOG_DEBUG, tag, msg);
#define LOG_WARN(tag, msg) __android_log_write(ANDROID_LOG_WARN, tag, msg);
#define LOG_ERROR(tag, msg) __android_log_write(ANDROID_LOG_ERROR, tag, msg);

#ifndef _Included_main_activity_UninstalledObserverActivity
#define _Included_main_activity_UninstalledObserverActivity
#ifdef __cplusplus
extern "C" {
#endif

#undef main_activity_UninstalledObserverActivity_MODE_PRIVATE
#define main_activity_UninstalledObserverActivity_MODE_PRIVATE 0L

#undef main_activity_UninstalledObserverActivity_MODE_WORLD_READABLE
#define main_activity_UninstalledObserverActivity_MODE_WORLD_READABLE 1L

#undef main_activity_UninstalledObserverActivity_MODE_WORLD_WRITEABLE
#define main_activity_UninstalledObserverActivity_MODE_WORLD_WRITEABLE 2L

#undef main_activity_UninstalledObserverActivity_MODE_APPEND
#define main_activity_UninstalledObserverActivity_MODE_APPEND 32768L

#undef main_activity_UninstalledObserverActivity_MODE_MULTI_PROCESS
#define main_activity_UninstalledObserverActivity_MODE_MULTI_PROCESS 4L

#undef main_activity_UninstalledObserverActivity_BIND_AUTO_CREATE
#define main_activity_UninstalledObserverActivity_BIND_AUTO_CREATE 1L

#undef main_activity_UninstalledObserverActivity_BIND_DEBUG_UNBIND
#define main_activity_UninstalledObserverActivity_BIND_DEBUG_UNBIND 2L

#undef main_activity_UninstalledObserverActivity_BIND_NOT_FOREGROUND
#define main_activity_UninstalledObserverActivity_BIND_NOT_FOREGROUND 4L

#undef main_activity_UninstalledObserverActivity_BIND_ABOVE_CLIENT
#define main_activity_UninstalledObserverActivity_BIND_ABOVE_CLIENT 8L

#undef main_activity_UninstalledObserverActivity_BIND_ALLOW_OOM_MANAGEMENT
#define main_activity_UninstalledObserverActivity_BIND_ALLOW_OOM_MANAGEMENT 16L

#undef main_activity_UninstalledObserverActivity_BIND_WAIVE_PRIORITY
#define main_activity_UninstalledObserverActivity_BIND_WAIVE_PRIORITY 32L

#undef main_activity_UninstalledObserverActivity_BIND_IMPORTANT
#define main_activity_UninstalledObserverActivity_BIND_IMPORTANT 64L

#undef main_activity_UninstalledObserverActivity_BIND_ADJUST_WITH_ACTIVITY
#define main_activity_UninstalledObserverActivity_BIND_ADJUST_WITH_ACTIVITY 128L

#undef main_activity_UninstalledObserverActivity_CONTEXT_INCLUDE_CODE
#define main_activity_UninstalledObserverActivity_CONTEXT_INCLUDE_CODE 1L

#undef main_activity_UninstalledObserverActivity_CONTEXT_IGNORE_SECURITY
#define main_activity_UninstalledObserverActivity_CONTEXT_IGNORE_SECURITY 2L

#undef main_activity_UninstalledObserverActivity_CONTEXT_RESTRICTED
#define main_activity_UninstalledObserverActivity_CONTEXT_RESTRICTED 4L

#undef main_activity_UninstalledObserverActivity_RESULT_CANCELED
#define main_activity_UninstalledObserverActivity_RESULT_CANCELED 0L

#undef main_activity_UninstalledObserverActivity_RESULT_OK
#define main_activity_UninstalledObserverActivity_RESULT_OK -1L

#undef main_activity_UninstalledObserverActivity_RESULT_FIRST_USER
#define main_activity_UninstalledObserverActivity_RESULT_FIRST_USER 1L

#undef main_activity_UninstalledObserverActivity_DEFAULT_KEYS_DISABLE
#define main_activity_UninstalledObserverActivity_DEFAULT_KEYS_DISABLE 0L

#undef main_activity_UninstalledObserverActivity_DEFAULT_KEYS_DIALER
#define main_activity_UninstalledObserverActivity_DEFAULT_KEYS_DIALER 1L

#undef main_activity_UninstalledObserverActivity_DEFAULT_KEYS_SHORTCUT
#define main_activity_UninstalledObserverActivity_DEFAULT_KEYS_SHORTCUT 2L

#undef main_activity_UninstalledObserverActivity_DEFAULT_KEYS_SEARCH_LOCAL
#define main_activity_UninstalledObserverActivity_DEFAULT_KEYS_SEARCH_LOCAL 3L

#undef main_activity_UninstalledObserverActivity_DEFAULT_KEYS_SEARCH_GLOBAL
#define main_activity_UninstalledObserverActivity_DEFAULT_KEYS_SEARCH_GLOBAL 4L


JNIEXPORT int JNICALL Java_com_example_deletedetect_UninstallObserver_init(JNIEnv *, jobject, jstring);

#ifdef __cplusplus
}
#endif
#endif

