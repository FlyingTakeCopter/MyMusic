#include <jni.h>
#include <string>
#include "AndroidLog.h"
#include "JavaMethod.h"
#include "FFmpeg.h"

extern "C"
{
#include "libavcodec/avcodec.h"
}
JavaVM* javaVm = NULL;
JavaMethod*javaMethod = NULL;
FFmpeg*ffmpeg = NULL;

//extern "C"
//JNIEXPORT
//jint JNI_OnLoad(JavaVM*vm, void*res){
//    av_jni_set_java_vm(vm, 0);// 硬解码需要把java虚拟机环境传给ffmpeg
//    return JNI_VERSION_1_4;
//}

extern "C"
JNIEXPORT
jint JNICALL JNI_OnLoad(JavaVM*vm, void* res)
{
    jint result = -1;
    javaVm = vm;
    JNIEnv*env;
    if (vm->GetEnv((void **) env, JNI_VERSION_1_4) != JNI_OK)
    {
        return result;
    }
    return JNI_VERSION_1_4;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_lqk_libmyplayer_JniTest_testJni(JNIEnv *env, jobject instance) {

    LOGE("avcodec_configuration is %s", avcodec_configuration());
}







extern "C"
JNIEXPORT void JNICALL
Java_com_lqk_libmyplayer_player_LqkPlayer_n_1prepared(JNIEnv *env, jobject instance,
                                                      jstring source_) {
    const char *source = env->GetStringUTFChars(source_, 0);

    if (javaMethod == NULL)
    {
        javaMethod = new JavaMethod(javaVm, env, instance);
    }

    if (ffmpeg == NULL)
    {
        ffmpeg = new FFmpeg(javaMethod, source);
    }

    ffmpeg->prepared();

    env->ReleaseStringUTFChars(source_, source);
}