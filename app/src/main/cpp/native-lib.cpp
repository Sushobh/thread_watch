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


void wrappperVMInit(jvmtiEnv *jvmti_env,
                    JNIEnv *jni_env,
                    jthread thread) {
    LOGE("Logitech %s","wrappperVMInit");
}

void wrapperVMDeath(jvmtiEnv *jvmti_env,
                    JNIEnv *jni_env) {
    LOGE("Logitech %s","wrapperVMDeath");
}

void wrapperThreadStart(jvmtiEnv *jvmti_env,
                        JNIEnv *jni_env,
                        jthread thread) {
    LOGE("Logitech %s","wrapperThreadStart");
}

void wrapperThreadEnd(jvmtiEnv *jvmti_env,
                      JNIEnv *jni_env,
                      jthread thread) {
    LOGE("Logitech %s","wrapperThreadEnd");
}

void wrapperClassFileLoadHook(jvmtiEnv *jvmti_env,
                              JNIEnv *jni_env,
                              jclass class_being_redefined,
                              jobject loader,
                              const char *name,
                              jobject protection_domain,
                              jint class_data_len,
                              const unsigned char *class_data,
                              jint *new_class_data_len,
                              unsigned char **new_class_data) {
    LOGE("Logitech %s","wrapperClassFileLoadHook");
}

void wrapperClassLoad(jvmtiEnv *jvmti_env,
                      JNIEnv *jni_env,
                      jthread thread,
                      jclass klass) {
    LOGE("Logitech %s","wrapperClassLoad");
}

void wrapperClassPrepare(jvmtiEnv *jvmti_env,
                         JNIEnv *jni_env,
                         jthread thread,
                         jclass klass) {
    LOGE("Logitech %s","wrapperClassPrepare");
}

void wrapperMethodEntry(jvmtiEnv *jvmti_env,
                        JNIEnv *jni_env,
                        jthread thread,
                        jmethodID method) {
    char *mName = new char[300];
    char *signature = new char[300];
    char *genericSignature = new char[300];
    char *classSignature = new char[300];
    jvmti_env->GetMethodName(method,&mName,&signature,&genericSignature);
    jclass methodDeclearingClass;
    jvmti_env->GetMethodDeclaringClass(method,&methodDeclearingClass);
    jvmti_env->GetClassSignature(methodDeclearingClass,&classSignature, nullptr);

    if(strcmp(mName,"helloWorld") == 0){
        LOGE("Logitech method Name %s",mName);
        LOGE("Logitech class Name %s",classSignature);
    }
}

void wrapperMethodExit(jvmtiEnv *jvmti_env,
                       JNIEnv *jni_env,
                       jthread thread,
                       jmethodID method,
                       jboolean was_popped_by_exception,
                       jvalue return_value) {
    LOGE("Logitech %s","wrapperMethodExit");
}

void wrapperNativeMethodBind(jvmtiEnv *jvmti_env,
                             JNIEnv *jni_env,
                             jthread thread,
                             jmethodID method,
                             void *address,
                             void **new_address_ptr) {

}

void wrapperCompiledMethodLoad(jvmtiEnv *jvmti_env,
                               jmethodID method,
                               jint code_size,
                               const void *code_addr,
                               jint map_length,
                               const jvmtiAddrLocationMap *map,
                               const void *compile_info) {
    LOGE("Logitech %s","wrapperCompiledMethodLoad");
}

void wrapperCompiledMethodUnload(jvmtiEnv *jvmti_env,
                                 jmethodID method,
                                 const void *code_addr) {
    LOGE("Logitech %s","wrapperCompiledMethodUnload");
}

void wrapperDynamicCodeGenerated(jvmtiEnv *jvmti_env,
                                 const char *name,
                                 const void *address,
                                 jint length) {
    LOGE("Logitech %s","wrapperDynamicCodeGenerated");
}

void wrapperDataDumpRequest(jvmtiEnv *jvmti_env) {
    LOGE("Logitech %s","wrapperDataDumpRequest");
}

void wrapperMonitorWait(jvmtiEnv *jvmti_env,
                        JNIEnv *jni_env,
                        jthread thread,
                        jobject object,
                        jlong timeout) {
    LOGE("Logitech %s","wrapperMonitorWait");
}

void wrapperMonitorWaited(jvmtiEnv *jvmti_env,
                          JNIEnv *jni_env,
                          jthread thread,
                          jobject object,
                          jboolean timed_out) {
    LOGE("Logitech %s","wrapperMonitorWaited");
}

void wrapperMonitorContendedEnter(jvmtiEnv *jvmti_env,
                                  JNIEnv *jni_env,
                                  jthread thread,
                                  jobject object) {
    LOGE("Logitech %s","wrapperMonitorContendedEnter");
}

void wrapperMonitorContendedEntered(jvmtiEnv *jvmti_env,
                                    JNIEnv *jni_env,
                                    jthread thread,
                                    jobject object) {
    LOGE("Logitech %s","wrapperMonitorContendedEntered");
}

void wrapperResourceExhausted(jvmtiEnv *jvmti_env,
                              JNIEnv *jni_env,
                              jint flags,
                              const void *reserved,
                              const char *description) {
    LOGE("Logitech %s","wrapperResourceExhausted");
}

void wrapperGarbageCollectionStart(jvmtiEnv *jvmti_env) {
    LOGE("Logitech %s","wrapperGarbageCollectionStart");
}

void wrapperGarbageCollectionFinish(jvmtiEnv *jvmti_env) {
    LOGE("Logitech %s","GarbageCollectionFinish");
}

void ObjFreeCallback(jvmtiEnv *jvmti_env, jlong tag) {
    LOGE("Logitech %s","Object free");
}




void ObjAllocCallback(jvmtiEnv *jvmti, JNIEnv *jni, jthread thread, jobject object,
                      jclass klass, jlong size) {
    jclass cls = jni->FindClass("java/lang/Class");
    jmethodID mid_getName = jni->GetMethodID(cls, "getName", "()Ljava/lang/String;");
    jstring name = static_cast<jstring>(jni->CallObjectMethod(klass, mid_getName));
    const char *className = jni->GetStringUTFChars(name, JNI_FALSE);
    LOGE("Logitech allocated %s",className);
    jni->ReleaseStringUTFChars(name, className);
}

extern "C" JNIEXPORT jint JNICALL Agent_OnAttach(JavaVM *vm, char *options,
                                                 void *reserved) {

    jvmtiEnv *jvmti_env = CreateJvmtiEnv(vm);
    if (jvmti_env == nullptr) {
        return JNI_ERR;
    }
    SetAllCapabilities(jvmti_env);
    jvmtiEventCallbacks callbacks;
    memset(&callbacks, 0, sizeof(callbacks));
    callbacks.VMInit = &wrappperVMInit;
    callbacks.VMDeath = &wrapperVMDeath;
    callbacks.ThreadStart = &wrapperThreadStart;
    callbacks.ThreadEnd = &wrapperThreadEnd;
    callbacks.ClassFileLoadHook = &wrapperClassFileLoadHook;
    callbacks.ClassLoad = &wrapperClassLoad;
    callbacks.ClassPrepare = &wrapperClassPrepare;
    callbacks.MethodEntry = &wrapperMethodEntry;
    callbacks.MethodExit = &wrapperMethodExit;
    callbacks.NativeMethodBind = &wrapperNativeMethodBind;
    callbacks.CompiledMethodLoad = &wrapperCompiledMethodLoad;
    callbacks.CompiledMethodUnload = &wrapperCompiledMethodUnload;
    callbacks.DynamicCodeGenerated = &wrapperDynamicCodeGenerated;
    callbacks.DataDumpRequest = &wrapperDataDumpRequest;
    callbacks.MonitorWait = &wrapperMonitorWait;
    callbacks.MonitorWaited = &wrapperMonitorWaited;
    callbacks.MonitorContendedEnter = &wrapperMonitorContendedEnter;
    callbacks.MonitorContendedEntered = &wrapperMonitorContendedEntered;
    callbacks.ResourceExhausted = &wrapperResourceExhausted;
    callbacks.GarbageCollectionStart = &wrapperGarbageCollectionStart;
    callbacks.GarbageCollectionFinish = &wrapperGarbageCollectionFinish;
    callbacks.VMObjectAlloc = &ObjAllocCallback;
    callbacks.ObjectFree = &ObjFreeCallback;

    int error = jvmti_env->SetEventCallbacks(&callbacks, sizeof(callbacks));
    jvmtiError err = jvmti_env->SetEventNotificationMode(JVMTI_ENABLE,
                                                         JVMTI_EVENT_METHOD_ENTRY,
                                                         nullptr);

    LOGE("Agent_OnAttach");
    return JNI_OK;
}

