//
// Created by yexiaokang on 2015/11/7.
//

#include <jni.h>
#include <android/log.h>
#include <stdlib.h>

#ifndef NELEM
# define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))
#endif

#define LOG_TAG "android_native"

#ifndef LOGI
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#endif

#ifndef LOGE
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#endif


const char *className = "com/example/ndksample/myapplication/MainActivity";     // the jni class


/*
 * Class:     com_example_ndksample_myapplication_MainActivity
 * Method:    stringFromJni
 * Signature: ()Ljava/lang/String;
 */
jstring stringFromJni(JNIEnv *env, jclass clazz) {
    return env->NewStringUTF("this message is from jni");
}


/**
 * name:      stringFromJni
 * signature: ()Ljava/lang/String;
 * fnPtr:     stringFromJni
 *
 * jni.h struct JNINativeMethod
 */
static const JNINativeMethod sMethods[] = {                                  // jni methods table
        {"stringFromJni", "()Ljava/lang/String;", (void *) stringFromJni},
};


jint JNI_OnLoad(JavaVM *vm, void *reserved) {

    JNIEnv *env = NULL;
    jint result = -1;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {
        LOGE("GetEnv failed!");
        return result;
    }
    LOGI("Retrieve the env success !");

    jclass clazz = env->FindClass(className);              // find the jni class
    if (clazz == NULL) {
        LOGE("FindClass Failed !");
        return JNI_ERR;
    }

    if (env->RegisterNatives(clazz, sMethods, NELEM(sMethods)) < 0) {      //register jni methods
        LOGE("RegisterNatives Failed !");
        return JNI_ERR;
    }

    return JNI_VERSION_1_4;                              // use jni version 1.4
}