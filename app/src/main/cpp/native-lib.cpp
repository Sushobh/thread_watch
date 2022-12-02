#include <jni.h>
#include <string>
#include "jvmti.h"
#include "android/log.h"
#include "MLOG.h"
#include "alloca.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

jvmtiEnv *CreateJvmtiEnv(JavaVM *vm) {
    jvmtiEnv *jvmti_env;
    jint result = vm->GetEnv((void **) &jvmti_env, JVMTI_VERSION_1_2);
    if (result != JNI_OK) {
        return nullptr;
    }
    return jvmti_env;

}


void SetAllCapabilities(jvmtiEnv *jvmti) {
    jvmtiCapabilities caps;
    jvmtiError error;
    error = jvmti->GetPotentialCapabilities(&caps);
    error = jvmti->AddCapabilities(&caps);
}

void ObjAllocCallback(jvmtiEnv *jvmti, JNIEnv *jni, jthread thread, jobject object,
                      jclass klass, jlong size) {
    jclass cls = jni->FindClass("java/lang/Class");
    jmethodID mid_getName = jni->GetMethodID(cls, "getName", "()Ljava/lang/String;");
    jstring name = static_cast<jstring>(jni->CallObjectMethod(klass, mid_getName));
    const char *className = jni->GetStringUTFChars(name, JNI_FALSE);
    if (strcmp(className, "java.lang.Thread") == 0) {
        LOGE("Logitech %s",className);
    }

    jni->ReleaseStringUTFChars(name, className);
}

extern "C" JNIEXPORT jint JNICALL Agent_OnAttach(JavaVM *vm, char *options,
                                                 void *reserved) {
    LOGE("Logitech %s","onAttach");
    jvmtiEnv *jvmti_env = CreateJvmtiEnv(vm);
    if (jvmti_env == nullptr) {
        return JNI_ERR;
    }
    SetAllCapabilities(jvmti_env);
    jvmtiEventCallbacks callbacks;
    memset(&callbacks, 0, sizeof(callbacks));
    callbacks.VMObjectAlloc = &ObjAllocCallback;
    int error = jvmti_env->SetEventCallbacks(&callbacks, sizeof(callbacks));
    jvmtiError err = jvmti_env->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_VM_OBJECT_ALLOC,
                                                         nullptr);
    LOGE("Agent_OnAttach");
    return JNI_OK;
}

