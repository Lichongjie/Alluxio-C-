#include "JNIHelper.h"
#include <string.h>
#include <pthread.h>
#include<iostream>

#define  LOG_TAG    "JniHelper"
using namespace JNIHelper;

static pthread_key_t g_key;
jclass _getClassID(const char *className)
{
    if (nullptr == className)
    {
        return nullptr;
    }

    JNIEnv* env = JniHelper::getEnv();

    jstring _jstrClassName = env->NewStringUTF(className);

    jclass _clazz = (jclass) env->CallObjectMethod(JniHelper::classloader,
                    JniHelper::loadclassMethod_methodID,
                    _jstrClassName);

    if (nullptr == _clazz)
    {
        env->ExceptionClear();
    }

    env->DeleteLocalRef(_jstrClassName);

    return _clazz;
}

void _detachCurrentThread(void* a)
{
    JniHelper::getJavaVM()->DetachCurrentThread();
}



JavaVM* JniHelper::_psJavaVM = nullptr;
jmethodID JniHelper::loadclassMethod_methodID = nullptr;
jobject JniHelper::classloader = nullptr;
std::function<void()> JniHelper::classloaderCallback = nullptr;

jobject JniHelper::_activity = nullptr;

JavaVM* JniHelper::getJavaVM()
{
    pthread_t thisthread = pthread_self();
    return _psJavaVM;
}

void JniHelper::setJavaVM(JavaVM *javaVM)
{
    pthread_t thisthread = pthread_self();
    _psJavaVM = javaVM;

    pthread_key_create(&g_key, _detachCurrentThread);
}

JNIEnv* JniHelper::cacheEnv(JavaVM* jvm)
{
    JNIEnv* _env = nullptr;
    jint ret = jvm->GetEnv((void**)&_env, JNI_VERSION_1_8);

    switch (ret)
    {
    case JNI_OK :
        pthread_setspecific(g_key, _env);
        return _env;

    case JNI_EDETACHED :
        if (jvm->AttachCurrentThread((void**)_env, nullptr) < 0)
        {
            return nullptr;
        }
        else
        {
            pthread_setspecific(g_key, _env);
            return _env;
        }

    case JNI_EVERSION :
    // Cannot recover from this error
    //     LOGE("JNI interface version 1.4 not supported");
    default :
        return nullptr;
    }
}

JNIEnv* JniHelper::getEnv()
{
    JNIEnv *_env = (JNIEnv *)pthread_getspecific(g_key);
    if (_env == nullptr)
        _env = JniHelper::cacheEnv(_psJavaVM);
    return _env;
}

jobject JniHelper::getActivity()
{
    return _activity;
}

bool JniHelper::setClassLoaderFrom(jobject activityinstance)
{
    JniMethodInfo _getclassloaderMethod;
    if (!JniHelper::getMethodInfo_DefaultClassLoader(_getclassloaderMethod,
            "android/content/Context",
            "getClassLoader",
            "()Ljava/lang/ClassLoader;"))
    {
        return false;
    }

    jobject _c = JniHelper::getEnv()->CallObjectMethod(activityinstance,
                 _getclassloaderMethod.methodID);

    if (nullptr == _c)
    {
        return false;
    }

    JniMethodInfo _m;
    if (!JniHelper::getMethodInfo_DefaultClassLoader(_m,
            "java/lang/ClassLoader",
            "loadClass",
            "(Ljava/lang/String;)Ljava/lang/Class;"))
    {
        return false;
    }

    JniHelper::classloader = JniHelper::getEnv()->NewGlobalRef(_c);
    JniHelper::loadclassMethod_methodID = _m.methodID;
    JniHelper::_activity =JniHelper::getEnv()->NewGlobalRef(activityinstance);
    if (JniHelper::classloaderCallback != nullptr)
    {
        JniHelper::classloaderCallback();
    }

    return true;
}

bool JniHelper::getStaticMethodInfo(JniMethodInfo &methodinfo,
                                    const char *className,
                                    const char *methodName,
                                    const char *paramCode)
{
    if ((nullptr == className) ||
            (nullptr == methodName) ||
            (nullptr == paramCode))
    {
        return false;
    }

    JNIEnv *env = JniHelper::getEnv();
    if (!env)
    {
        //  LOGE("Failed to get JNIEnv");
        return false;
    }
    //   jclass classID = _getClassID(className);
    jclass classID = env->FindClass(className);
    if (! classID)
    {
        //      LOGE("Failed to find class %s", className);
        env->ExceptionClear();
        return false;
    }
    jmethodID methodID = env->GetStaticMethodID(classID, methodName, paramCode);
    if (! methodID)
    {
        //  LOGE("Failed to find static method id of %s", methodName);
        env->ExceptionClear();
        return false;
    }
    methodinfo.classID = classID;
    methodinfo.env = env;
    methodinfo.methodID = methodID;
    return true;
}

bool JniHelper::getMethodInfo_DefaultClassLoader(JniMethodInfo &methodinfo,
        const char *className,
        const char *methodName,
        const char *paramCode)
{

    if ((nullptr == className) ||
            (nullptr == methodName) ||
            (nullptr == paramCode))
    {
        return false;
    }

    JNIEnv *env = JniHelper::getEnv();
    if (!env)
    {
        return false;
    }

    jclass classID = env->FindClass(className);

    if (! classID)
    {
        //  LOGE("Failed to find class %s", className);
        env->ExceptionClear();
        return false;
    }

    jmethodID methodID = env->GetMethodID(classID, methodName, paramCode);
    if (! methodID)
    {
        //   LOGE("Failed to find method id of %s", methodName);
        env->ExceptionClear();
        return false;
    }

    methodinfo.classID = classID;
    methodinfo.env = env;
    methodinfo.methodID = methodID;

    return true;
}

bool JniHelper::getMethodInfo(JniMethodInfo &methodinfo,
                              const char *className,
                              const char *methodName,
                              const char *paramCode)
{
    if ((nullptr == className) ||
            (nullptr == methodName) ||
            (nullptr == paramCode))
    {
        return false;
    }

    JNIEnv *env = JniHelper::getEnv();
    if (!env)
    {
        return false;
    }

    jclass classID = _getClassID(className);
    if (! classID)
    {
        //   LOGE("Failed to find class %s", className);
        env->ExceptionClear();
        return false;
    }

    jmethodID methodID = env->GetMethodID(classID, methodName, paramCode);
    if (! methodID)
    {
        // LOGE("Failed to find method id of %s", methodName);
        env->ExceptionClear();
        return false;
    }

    methodinfo.classID = classID;
    methodinfo.env = env;
    methodinfo.methodID = methodID;

    return true;
}

jstring  JniHelper::string2jstring(JNIEnv* env,const char* pat)
{
    jclass strClass = (env)->FindClass("Ljava/lang/String;");
    jmethodID ctorID = (env)->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
    jbyteArray bytes = (env)->NewByteArray(strlen(pat));
    (env)->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte*)pat);
    jstring encoding = (env)->NewStringUTF("GB2312");
    return (jstring)(env)->NewObject(strClass, ctorID, bytes, encoding);
};

std::string JniHelper:: jstring2string(jstring jstr)
{
    JNIEnv *env = JniHelper::getEnv();
    char*   rtn   =   NULL;
    jclass   clsstring   =   env->FindClass("java/lang/String");
    jstring   strencode   =   env->NewStringUTF("GB2312");
    jmethodID   mid   =   env->GetMethodID(clsstring,   "getBytes",   "(Ljava/lang/String;)[B");
    jbyteArray   barr=   (jbyteArray)env->CallObjectMethod(jstr,mid,strencode);
    jsize   alen   =   env->GetArrayLength(barr);
    jbyte*   ba   =   env->GetByteArrayElements(barr,JNI_FALSE);
    if(alen   >   0)
    {
        rtn   =   (char*)malloc(alen+1);
        memcpy(rtn,ba,alen);
        rtn[alen]=0;
    }
    env->ReleaseByteArrayElements(barr,ba,0);
    std::string stemp(rtn);
    free(rtn);
    return   stemp;
};

jstring JniHelper::convert(LocalRefMapType& localRefs, JniMethodInfo& t, const char* x)
{
    jstring ret =JniHelper::string2jstring(t.env, x);
    localRefs[t.env].push_back(ret);
    return ret;
}

jstring JniHelper::convert(LocalRefMapType& localRefs, JniMethodInfo& t, const std::string& x)
{
    jstring ret =JniHelper::string2jstring(t.env, x.c_str());
    localRefs[t.env].push_back(ret);
    return ret;
}

void JniHelper::deleteLocalRefs(JNIEnv* env, LocalRefMapType& localRefs)
{
    if (!env)
    {
        return;
    }

    for (const auto& ref : localRefs[env])
    {
        env->DeleteLocalRef(ref);
    }
    localRefs[env].clear();
}

void JniHelper::reportError(const std::string& className, const std::string& methodName, const std::string& signature)
{
    //    LOGE("Failed to find static java method. Class name: %s, method name: %s, signature: %s ",  className.c_str(), methodName.c_str(), signature.c_str());
}


//namespace cocos2d

