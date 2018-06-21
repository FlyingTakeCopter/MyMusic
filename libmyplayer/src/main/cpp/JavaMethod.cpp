//
// Created by liuqikang on 2018/6/21.
//

#include "JavaMethod.h"

#define MAIN_THREAD 0
#define CHILD_THREAD 1

JavaMethod::JavaMethod(JavaVM *vm, JNIEnv *env, jobject obj) {
    jvm = vm;
    jenv = env;
    jobj = env->NewGlobalRef(obj);

    jclass clz = env->GetObjectClass(obj);
    if (!clz)
    {
        if (LOG_DEBUG)
        {
            LOGE("GetObjectClass failed");
        }
        return ;
    }

    jmid_prepared = env->GetMethodID(clz, "onCallPrepared", "()V");
}

JavaMethod::~JavaMethod() {

}

void JavaMethod::onCallPrepared(int threadType) {
    if (threadType == MAIN_THREAD)
    {
        jenv->CallVoidMethod(jobj, jmid_prepared);
    } else if (threadType == CHILD_THREAD)
    {
        JNIEnv*env;
        if (jvm->AttachCurrentThread((JNIEnv **) env, 0) != JNI_OK)
        {
            if (LOG_DEBUG)
            {
                LOGD("AttachCurrentThread failed");
            }
            return;
        }

        env->CallVoidMethod(jobj, jmid_prepared);

        jvm->DetachCurrentThread();
    }
}
