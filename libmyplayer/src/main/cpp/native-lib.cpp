#include <jni.h>
#include <string>
#include <android/log.h>

#define LOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"liuqikang", FORMAT, ##__VA_ARGS__)

extern "C"
{
#include "libavcodec/avcodec.h"
}

extern "C"
JNIEXPORT void JNICALL
Java_com_lqk_libmyplayer_JniTest_testJni(JNIEnv *env, jobject instance) {

    LOGE("avcodec_configuration is %s", avcodec_configuration());
}
