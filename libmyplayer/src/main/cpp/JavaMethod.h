//
// Created by liuqikang on 2018/6/21.
//

#ifndef MYMUSIC_JAVAMETHOD_H
#define MYMUSIC_JAVAMETHOD_H


#include <jni.h>
#include "AndroidLog.h"

class JavaMethod {
public:
    JavaVM* jvm;
    JNIEnv* jenv;
    jobject jobj;
    jmethodID jmid_prepared;

    JavaMethod(JavaVM* vm, JNIEnv* env, jobject obj);
    ~JavaMethod();

    void onCallPrepared(int threadType);
};


#endif //MYMUSIC_JAVAMETHOD_H
