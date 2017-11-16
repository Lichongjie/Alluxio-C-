#ifndef   JNI_HELPER_H__
#define  JNI_HELPER_H__

#include <jni.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include<cstdlib>
#include <stdio.h>
#include <string.h>
#include<iostream>
#include<Status.h>
#include<map>
#include<Wire.h>

static std::map<jobject, const std::string>  mObjectToTypeNameMap;

using namespace std;


typedef struct JniMethodInfo_
{
    JNIEnv *    env;
    jclass      classID;
    jmethodID   methodID;
} JniMethodInfo;

class  JniHelper
{
public:
    typedef std::unordered_map<JNIEnv*, std::vector<jobject>> LocalRefMapType;

    static void setJavaVM(JavaVM *javaVM);
    static JavaVM* getJavaVM();
    static JNIEnv* getEnv();
    static jobject getActivity();

    static void start()
    {
        JNIEnv *env;
        JavaVM *jvm;
        JavaVMOption options[1];
        JavaVMInitArgs vm_args;

        char *classpath = getenv("CLASSPATH");
        if (classpath == NULL)
        {
            throw std::runtime_error("CLASSPATH env variable is not set");
        }
        const char *classpath_opt = "-Djava.class.path=";
        size_t cp_len = strlen(classpath) + strlen(classpath_opt) + 1;

        // Construct the CLASSPATH argument.  We add in the alluxio jar, as well
        // as the Jackson jars
        std::string classpathString(classpath_opt);
        classpathString.append(classpath);

        // For base alluxio support
      //  classpathString.append(":");
       // classpathString.append(CLASSPATH_ALLUXIO_JAR);

        options[0].optionString = const_cast<char *>(classpathString.c_str());

        //options[0].optionString = "-Djava.class.path=/home/innkp/Alluxio-Cpp";
      //  options[0].optionString = "-Djava.class.path=/home/innkp/pasa/tachyon/assembly/client/target/alluxio-assembly-client-1.7.0-SNAPSHOT-jar-with-dependencies.jar";
     //  options[0].optionString = "-Djava.class.path=./:/home/innkp/jdk1.8.0_144/lib/dt.jar:$HOME/jdk1.8.0_144/lib/tools.jar:/home/innkp/pasa/tachyon/assembly/client/target/alluxio-assembly-client-1.7.0-SNAPSHOT-jar-with-dependencies.jar";

        memset(&vm_args, 0, sizeof(vm_args));
        vm_args.version = JNI_VERSION_1_8;
        vm_args.nOptions = 1;
        vm_args.options = options;

        // 启动虚拟机
        JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
        JniHelper::setJavaVM(jvm);
        JniHelper::cacheEnv(jvm);
    }

    static void finish()
    {
        getJavaVM()->DestroyJavaVM();
        mObjectToTypeNameMap.clear();
    }

    static bool setClassLoaderFrom(jobject activityInstance);
    static bool getStaticMethodInfo(JniMethodInfo &methodinfo,
                                    const char *className,
                                    const char *methodName,
                                    const char *paramCode);
    static bool getMethodInfo(JniMethodInfo &methodinfo,
                              const char *className,
                              const char *methodName,
                              const char *paramCode);

    static std::string jstring2string(jstring str);

    static jmethodID loadclassMethod_methodID;
    static jobject classloader;
    static std::function<void()> classloaderCallback;

    template <typename... Ts>
    static void callVoidMethod( jobject& obj, const std::string& className,
                                const std::string& methodName,
                                Ts... xs)
    {
        JniMethodInfo t;
        std::string signature = "(" + std::string(getJNISignature(xs...)) + ")V";
        /*
        if(default_signature.length() != 0 )
        {
            signature = default_signature;
        }
        else
        {
            signature  = "(" + std::string(getJNISignature(xs...)) + ")V";
        }
        */

        if (JniHelper::getMethodInfo_DefaultClassLoader(t, className.c_str(), methodName.c_str(), signature.c_str()))
        {
            LocalRefMapType localRefs;
            t.env->CallVoidMethod(obj, t.methodID, convert(localRefs, t, xs)...);
            t.env->DeleteLocalRef(t.classID);
            deleteLocalRefs(t.env, localRefs);
        }
        else
        {
            reportError(className, methodName, signature);
        }
    }



    template <typename... Ts>
    static jobject callObjectMethod( jobject& obj, const std::string& className,
                                     const std::string& methodName, const std::string& returnClassName,
                                     Ts... xs)
    {
        jobject res;
        JniMethodInfo t;
        std::string signature = "(" + std::string(getJNISignature(xs...)) + ")L" + returnClassName +";";
        if (JniHelper::getMethodInfo_DefaultClassLoader(t, className.c_str(), methodName.c_str(), signature.c_str()))
        {
            LocalRefMapType localRefs;
            res =  t.env->CallObjectMethod(obj,  t.methodID,  convert(localRefs, t, xs)...);
            t.env->DeleteLocalRef(t.classID);
            deleteLocalRefs(t.env, localRefs);
        }
        else
        {
            reportError(className, methodName, signature);
            return NULL;
        }
        add(res, returnClassName);
        return res;
    }

    template <typename... Ts>
    static jobject createObjectMethod(const std::string& className, Ts... xs)
    {
        jobject res;
        JniMethodInfo t;
        std::string methodName = "<init>";
        std::string signature = "(" + std::string(getJNISignature(xs...)) + ")V";

        if (JniHelper::getMethodInfo_DefaultClassLoader(t, className.c_str(), methodName.c_str(), signature.c_str()))
        {

            LocalRefMapType localRefs;
            res = t.env->NewObject(t.classID, t.methodID,convert(localRefs, t, xs)...);
            t.env->DeleteLocalRef(t.classID);
            deleteLocalRefs(t.env, localRefs);
        }
        else
        {
            reportError(className, methodName, signature);
            return 0;
        }
        add(res,className );
        return res;
    }

    template <typename... Ts>
    static bool callBooleanMethod(jobject& obj, const std::string& className,
                                  const std::string& methodName,
                                  Ts... xs)
    {
        jboolean jret = JNI_FALSE;
        JniMethodInfo t;
        std::string signature = "(" + std::string(getJNISignature(xs...)) + ")Z";
        if (JniHelper::getMethodInfo_DefaultClassLoader(t, className.c_str(), methodName.c_str(), signature.c_str()))
        {
            LocalRefMapType localRefs;
            jret = t.env->CallBooleanMethod(obj, t.methodID, convert(localRefs, t, xs)...);
            t.env->DeleteLocalRef(t.classID);
            deleteLocalRefs(t.env, localRefs);
        }
        else
        {
            reportError(className, methodName, signature);
        }
        return (jret == JNI_TRUE);
    }

    template <typename... Ts>
    static int callIntMethod(jobject obj, const std::string& className, const std::string& methodName, Ts... xs)
    {

        jint jret;
        JniMethodInfo t;
        std::string signature = "(" + std::string(getJNISignature(xs...)) + ")Z";
        if (JniHelper::getMethodInfo_DefaultClassLoader(t, className.c_str(), methodName.c_str(), signature.c_str()))
        {
            LocalRefMapType localRefs;
            jret = t.env->CallIntMethod(obj, t.methodID, convert(localRefs, t, xs)...);
            t.env->DeleteLocalRef(t.classID);
            deleteLocalRefs(t.env, localRefs);
        }
        else
        {
            reportError(className, methodName, signature);
        }
        return (int)jret;

    }

    template <typename... Ts>
    static jobject callStaticObjectMethod(const std::string& default_signature, const std::string& className,
                                          const std::string& methodName, const std::string& returnClassName,
                                          Ts... xs)
    {
        jobject ret;
        JniMethodInfo t;
        std::string signature;
        if(default_signature.length() != 0 )
        {
            signature = default_signature;
        }
        else
        {
            signature  = "(" + std::string(getJNISignature(xs...)) + ")L" + returnClassName +";";
        }

        if (JniHelper::getStaticMethodInfo(t, className.c_str(), methodName.c_str(), signature.c_str()))
        {

            LocalRefMapType localRefs;
            ret = t.env->CallStaticObjectMethod(t.classID, t.methodID, convert(localRefs, t, xs)...);
            t.env->DeleteLocalRef(t.classID);
            deleteLocalRefs(t.env, localRefs);
        }
        else
        {
            reportError(className, methodName, signature);
        }
        add(ret, returnClassName) ;
        return ret;
    }

    template <typename... Ts>
    static std::string callStringMethod(jobject obj, const std::string& className,
                                        const std::string& methodName,
                                        Ts... xs)
    {
        std::string ret;
        JniMethodInfo t;
        std::string signature = "(" + std::string(getJNISignature(xs...)) + ")Ljava/lang/String;";
        if (JniHelper::getMethodInfo_DefaultClassLoader(t, className.c_str(), methodName.c_str(), signature.c_str()))
        {
            LocalRefMapType localRefs;
            jstring jret = (jstring)t.env->CallObjectMethod(obj, t.methodID, convert(localRefs, t, xs)...);
            ret =JniHelper::jstring2string(jret);
            t.env->DeleteLocalRef(t.classID);
            t.env->DeleteLocalRef(jret);
            deleteLocalRefs(t.env, localRefs);
        }
        else
        {
            reportError(className, methodName, signature);
        }
        return ret;
    }

    static jboolean ToJBool(bool value)
    {
        return value ? JNI_TRUE : JNI_FALSE;
    }

    static std::string getObjectClassName(jobject obj)
    {
        jobject classObj = JniHelper::callObjectMethod( obj, "java/lang/Object", "getClass", "java/lang/Class");
        std::string  className = JniHelper::callStringMethod(classObj, "java/lang/Class", "getName");
        JniHelper::getEnv()->DeleteLocalRef(classObj);
        return className;
    }

    static void deleteLocalRefs(JNIEnv* env, LocalRefMapType& localRefs);

    static Status getStatusFromJavaException(const std::string& statusName, const std::string& errorMsg)
    {
        using namespace std;
        if(statusName.compare("CANCELED") == 0)
        {
            return  Status::canceled(errorMsg);

        }
        else if(statusName.compare("UNKNOWN") == 0)
        {
            return  Status::unknown(errorMsg);
        }
        else if(statusName.compare("INVALID_ARGUMENT") == 0)
        {
            return  Status::invalidArgument(errorMsg);
        }
        else if(statusName.compare("DEADLINE_EXCEEDED") == 0)
        {
            return  Status::deadlineExceeded(errorMsg);
        }
        else if(statusName.compare("NOT_FOUND") == 0)
        {
            return  Status::notFound(errorMsg);
        }
        else if(statusName.compare("ALREADY_EXISTS") == 0)
        {
            return  Status::alreadyExist(errorMsg);
        }
        else if(statusName.compare("PERMISSION_DENIED") == 0)
        {
            return  Status::permissionDenied(errorMsg);
        }
        else if(statusName.compare("UNAUTHENTICATED") == 0)
        {
            return  Status::unAuthenticated(errorMsg);
        }
        else if(statusName.compare("RESOURCE_EXHAUSTED") == 0)
        {
            return Status::resourceExhausted(errorMsg);
        }
        else if(statusName.compare("FAILED_PRECONDITION") == 0)
        {
            return  Status::failedPrecondition(errorMsg);
        }
        else if(statusName.compare("ABORTED") == 0)
        {
            return  Status::aborted(errorMsg);
        }
        else if(statusName.compare("OUT_OF_RANGE") == 0)
        {
            return Status::outOfRange(errorMsg);
        }
        else if(statusName.compare("UNIMPLEMENTED") == 0)
        {
            return  Status::unImplemented(errorMsg);
        }
        else if(statusName.compare("INTERNAL") == 0)
        {
            return  Status::internal(errorMsg);
        }
        else if(statusName.compare("UNAVAILABLE") == 0)
        {
            return  Status::unavailable(errorMsg);
        }
        else if(statusName.compare("DATA_LOSS") == 0)
        {
            return  Status::dataLoss(errorMsg);
        }

        return Status::OK();

    };

    static Status exceptionCheck()
    {
        JNIEnv *env = getEnv();
        jthrowable exc;
        exc = env->ExceptionOccurred();
        jboolean error = env->ExceptionCheck();
        if(error)
        {
            env->ExceptionDescribe();
            env->ExceptionClear();
            std::string exceptionName =  JniHelper::getObjectClassName((jobject)exc);
            std::string errorMsg = JniHelper::callStringMethod((jobject)exc, "java/lang/Throwable", "getMessage");
            if(exceptionName.compare("alluxio/exception/FileDoesNotExistException") == 0 )
            {
                return Status::notFound(errorMsg);
            }
            else if(exceptionName.compare("alluxio/exception/UnavailableException") == 0)
            {
                return Status::unavailable(errorMsg);
            }
            jobject StatusException = JniHelper::callStaticObjectMethod("(Lalluxio/exception/AlluxioException;)Lalluxio/exception/status/StatusException;"
                                      , "alluxio/exception/status/StatusException", "fromAlluxioException", "alluxio/exception/status/StatusException", (jobject)exc);
            jobject statusInAlluxio = JniHelper::callObjectMethod((jobject& )exc,
                                      "alluxio/exception/status/StatusException", "getStatus","alluxio/exception/status/Status");
            std::string statusName = JniHelper::callStringMethod((jobject)exc, "java/lang/enum", "name");
            return getStatusFromJavaException(statusName, errorMsg);
            // env->ThrowNew(newExcCls, "thrown from C code");
        }
        else
        {
            return Status();
        }
    }

private:
    static jstring  string2jstring(JNIEnv* env,const char* pat);
    static JNIEnv* cacheEnv(JavaVM* jvm);
    static bool getMethodInfo_DefaultClassLoader(JniMethodInfo &methodinfo,
            const char *className,
            const char *methodName,
            const char *paramCode);

    static JavaVM* _psJavaVM;

    static jobject _activity;

    static void add(jobject obj, const std::string& classname)
    {
        mObjectToTypeNameMap.insert(std::make_pair(obj, classname));
    }

    static jstring convert(LocalRefMapType& localRefs, JniMethodInfo& t, const char* x);

    static jstring convert(LocalRefMapType& localRefs, JniMethodInfo& t, const std::string& x);

    template <typename T>
    static T convert(LocalRefMapType& localRefs, JniMethodInfo&, T x)
    {
        return x;
    }


    static std::string getJNISignature()
    {
        return "";
    }

    static std::string getJNISignature(bool)
    {
        return "Z";
    }

    static std::string getJNISignature(char)
    {
        return "C";
    }

    static std::string getJNISignature(short)
    {
        return "S";
    }

    static std::string getJNISignature(int)
    {
        return "I";
    }

    static std::string getJNISignature(long)
    {
        return "J";
    }

    static std::string getJNISignature(float)
    {
        return "F";
    }

    static  std::string getJNISignature(double)
    {
        return "D";
    }

    static std::string getJNISignature(const char*)
    {
        // return "Ljava/lang/String;";
        return "[B";
    }

    static std::string getJNISignature(const std::string&)
    {
        return "Ljava/lang/String;";
    }

    static std::string getJNISignature(jobject& obj)
    {
        std::map<jobject, const std::string>::iterator itr = mObjectToTypeNameMap.find(obj);
        if( itr != mObjectToTypeNameMap.end() )
        {
            return "L" + (std::string) itr->second + ";";
        }
        return getObjectClassName(obj);
    }


    template <typename T>
    static std::string getJNISignature(T x)
    {
        // This template should never be instantiated
        // static_assert(sizeof(x) == 0, "Unsupported argument type");
        return "";
    }
    template <typename T, typename... Ts>
    static std::string getJNISignature(T x, Ts... xs)
    {

        return getJNISignature(x) + getJNISignature(xs...);
    }
    static void reportError(const std::string& className, const std::string& methodName, const std::string& signature);

};
#endif //JNI_HELPER_H__

