#include <jni.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include<cstring>
#include<JNIHelper.h>
#include<sstream>
#include <iostream>
#include<FileSystem.h>
#include <sys/time.h>    // for gettimeofday()
//#include<json.h>
using namespace std;

// 环境变量PATH在windows下和linux下的分割符定义
#ifdef _WIN32
#define PATH_SEPARATOR ';'
#else
#define PATH_SEPARATOR ':'

#endif
/*
string fa_getSysTime()
{
     struct timeval tv;
     gettimeofday(&tv,NULL);
     struct tm* pTime;
     pTime = localtime(&tv.tv_sec);

     char sTemp[30] = {0};
     snprintf(sTemp, sizeof(sTemp), "%04d %02d %02d %02d %02d %02d %03d %03d", pTime->tm_year+1900, \
            pTime->tm_mon+1, pTime->tm_mday, pTime->tm_hour, pTime->tm_min, pTime->tm_sec, \
            tv.tv_usec/1000,tv.tv_usec%1000);
     return (string)sTemp;
}*/

int main(void)
{
 //struct timeval start, endd;
   // printf("start : %d.%d\n", start.tv_sec, start.tv_usec);

   // cout<< "当前时间：" << fa_getSysTime() << endl;
 FileSystem* fileSystem = new  FileSystem();
 FileOutStream* out;
   //  gettimeofday( &start, NULL );
  //  printf("start : %d.%d\n", start.tv_sec, start.tv_usec);
//for(int i = 0 ;i <1000;i++) {
// FileSystem->deletePath("/hehehe");
cout<<"adad"<<endl;
 fileSystem->createFile("/hehe",  &out);
//}
//    gettimeofday( &endd, NULL );
   // printf("endd : %d.%d\n", endd.tv_sec, endd.tv_usec);

//long time_use=(endd.tv_sec-start.tv_sec)*1000000+(endd.tv_usec-start.tv_usec);//微秒 //const unsigned char *s = (const unsigned char*)"testreerfewgtest";
 //std::cout<<time_use<<std::endl;
 //os.write(s);
 //os.close();
 fileSystem->closeFileSystem();


    /*
        jobject filesystem = JniHelper::callStaticObjectMethod("alluxio/FileSystem/file/FileSystem$Factory", "get", "alluxio/FileSystem/file/FileSystem");
        std::string path = "/hehehe";
        jobject alluxiURI = JniHelper::createObjectMethod("alluxio/AlluxioURI", path);
    //jobject obj2 = JniHelper::callObjectMethod(obj, "r/Sample2", "sayHello", "r/testObj", ss);
        JniHelper::callVoidMethod( "(Lalluxio/AlluxioURI;)V", filesystem, "alluxio/FileSystem/file/FileSystem","createDirectory", alluxiURI);
        jvm->DestroyJavaVM();
        return 0;
        */
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
