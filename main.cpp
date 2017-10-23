#include <jni.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include<cstring>
#include<JNIHelper.h>

// 环境变量PATH在windows下和linux下的分割符定义
#ifdef _WIN32
#define PATH_SEPARATOR ';'
#else
#define PATH_SEPARATOR ':'
#endif


jstring str2jstring(JNIEnv* env,const char* pat)
{
    //定义java String类 strClass
    jclass strClass = (env)->FindClass("Ljava/lang/String;");
    //获取String(byte[],String)的构造器,用于将本地byte[]数组转换为一个新String
    jmethodID ctorID = (env)->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
    //建立byte数组
    jbyteArray bytes = (env)->NewByteArray(strlen(pat));
    //将char* 转换为byte数组
    (env)->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte*)pat);
    // 设置String, 保存语言类型,用于byte数组转换至String时的参数
    jstring encoding = (env)->NewStringUTF("GB2312");
    //将byte数组转换为java String,并输出
    return (jstring)(env)->NewObject(strClass, ctorID, bytes, encoding);
};


std::string jstring2str(JNIEnv* env, jstring jstr)
{
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

int main(void)
{

JavaVMOption options[1];
	JNIEnv *env;
	JavaVM *jvm;
	JavaVMInitArgs vm_args;

	long status;
	jclass cls;
	jmethodID mid;
	jfieldID fid;
	jobject obj;

//options[0].optionString = "-Djava.class.path=/home/innkp/Alluxio-Cpp";
	options[0].optionString = "-Djava.class.path=/home/innkp/pasa/tachyon/assembly/server/target/alluxio-assembly-server-1.6.1-SNAPSHOT-jar-with-dependencies.jar";
	//options[1].optionString = "-Djava.library.path=/"
	memset(&vm_args, 0, sizeof(vm_args));
	vm_args.version = JNI_VERSION_1_8;
	vm_args.nOptions = 1;
	vm_args.options = options;

	// 启动虚拟机
	status = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
	JniHelper::setJavaVM(jvm);

//int  ift = JniHelper::test();
//try {
     //  jclass classID = env->FindClass("alluxio/client/file/FileSystem$Factory");


jobject filesystem = JniHelper::callStaticObjectMethod("alluxio/client/file/FileSystem$Factory", "get", "alluxio/client/file/FileSystem");
std::string path = "/hehe";
jobject alluxiURI = JniHelper::createObjectMethod("alluxio/AlluxioURI", path);
//jobject obj2 = JniHelper::callObjectMethod(obj, "r/Sample2", "sayHello", "r/testObj", ss);
JniHelper::callVoidMethod( "(Lalluxio/AlluxioURI;)V", filesystem, "alluxio/client/file/FileSystem","createDirectory", alluxiURI);
jvm->DestroyJavaVM();
		return 0;
/*
  mid = env->GetMethodID(cls, "out", "()V;");
			if (mid != 0 && obj != 0)
			{
				jstring result = (jstring)env->CallObjectMethod(obj2, mid);
				//if(result !=  null){
                    const char* str = env->GetStringUTFChars(result, 0);
                    printf("Result of sayHello: %s\n", str);
               //     }
				env->ReleaseStringUTFChars(result, 0);
			}
			*/



//jclass cls2 = env->FindClass("Sample2");

}
/*
int main(void)
{
	JavaVMOption options[1];
	JNIEnv *env;
	JavaVM *jvm;
	JavaVMInitArgs vm_args;

	long status;
	jclass cls;
	jmethodID mid;
	jfieldID fid;
	jobject obj;

	options[0].optionString = "-Djava.class.path=.";
	memset(&vm_args, 0, sizeof(vm_args));
	vm_args.version = JNI_VERSION_1_8;
	vm_args.nOptions = 1;
	vm_args.options = options;

	// 启动虚拟机
	status = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);

	if (status != JNI_ERR)
	{


		// 先获得class对象
		cls = env->FindClass("Sample2");
		if (cls != 0)
		{
			// 获取方法ID, 通过方法名和签名, 调用静态方法
			mid = env->GetStaticMethodID(cls, "sayHello", "(Ljava/lang/String;)Ljava/lang/String;");
			if (mid != 0)
			{
				const char* name = "World";
				jstring arg = env->NewStringUTF(name);
				jstring result = (jstring)env->CallStaticObjectMethod(cls, mid, arg);
				const char* str = env->GetStringUTFChars(result, 0);
				printf("Result of sayHello: %s\n", str);
				env->ReleaseStringUTFChars(result, 0);
			}

			//新建一个对象
			// 调用默认构造函数
			//obj = env->AllocObjdect(cls);

			// 调用指定的构造函数, 构造函数的名字叫做<init>
			mid = env->GetMethodID(cls, "<init>", "()V");
			obj = env->NewObject(cls, mid);
			if (obj == 0)
			{
				printf("Create object failed!\n");
			}
			//新建一个对象

			// 获取属性ID, 通过属性名和签名
			fid = env->GetFieldID(cls, "name", "Ljava/lang/String;");
			if (fid != 0)
			{
				const char* name = "icejoywoo";
				jstring arg = env->NewStringUTF(name);
				env->SetObjectField(obj, fid, arg); // 修改属性
			}

			// 调用成员方法
			mid = env->GetMethodID(cls, "sayHello", "()Ljava/lang/String;");
			if (mid != 0)
			{
				jstring result = (jstring)env->CallObjectMethod(obj, mid);
				const char* str = env->GetStringUTFChars(result, 0);
				printf("Result of sayHello: %s\n", str);
				env->ReleaseStringUTFChars(result, 0);
			}
		}


        cls = env->FindClass("r/testObj");
//jclass cls2 = env->FindClass("Sample2");


      mid =  env->GetMethodID(cls, "<init>", "(Ljava/lang/String;I)V");
    //  jmethodID  mid2 = env->GetMethodID(cls, "<init>", "()V");

    jint i = 10L;
    std::string ss = "SA";
    jstring s = str2jstring(env, ss.c_str());
    obj = env->NewObject(cls, mid,s , i);
       if (obj == 0)
        {
				printf("Create object failed!\n");
       }

      mid = env->GetMethodID(cls, "out", "()Ljava/lang/String;");
			if (mid != 0 && obj != 0)
			{
				jstring result = (jstring)env->CallObjectMethod(obj, mid);
				//if(result !=  null){
                    const char* str = env->GetStringUTFChars(result, 0);
                    printf("Result of sayHello: %s\n", str);
               //     }
				env->ReleaseStringUTFChars(result, 0);
			}
		jvm->DestroyJavaVM();
		return 0;
	}
	else
	{
		printf("JVM Created failed!\n");
		return -1;
	}
}
*/
