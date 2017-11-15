#include "FileSystem.h"

FileSystem::FileSystem()
{
    JniHelper::start();

    //FileSystem::filesystem = const_cast<jobject*> (filesystem);
    FileSystem::filesystem = JniHelper::callStaticObjectMethod("", "alluxio/client/file/FileSystem$Factory", "get", "alluxio/client/file/FileSystem");
    //ctor


}
void FileSystem::closeFileSystem()
{
    JNIEnv* env = JniHelper::getEnv();
    //env->DeleteLocalRef(FileSystem::filesystem);
    JniHelper::finish();
}
FileSystem::~FileSystem()
{
    FileSystem::closeFileSystem();
    //	return 0;
}


Status FileSystem::callJNIBydefaultOpt(const std::string& path, const std::string& methodName)
{
    jobject alluxiURI = JniHelper::createObjectMethod("alluxio/AlluxioURI", path);

    //JniHelper::callVoidMethod( "(Lalluxio/AlluxioURI;)V", FileSystem::filesystem, "alluxio/FileSystem/file/FileSystem",methodName, alluxiURI);
    JniHelper::callVoidMethod( FileSystem::filesystem, "alluxio/client/file/FileSystem",methodName, alluxiURI);

    JniHelper::getEnv()->DeleteLocalRef(alluxiURI);
    return JniHelper::exceptionCheck();
}

Status FileSystem::callJNIBydefaultOpt(const std::string& src, const std::string& dst, const std::string& methodName)
{
    jobject alluxiURISrc = JniHelper::createObjectMethod("alluxio/AlluxioURI", src);
    jobject alluxiURIDst =  JniHelper::createObjectMethod("alluxio/AlluxioURI", dst);
   // JniHelper::callVoidMethod( "(Lalluxio/AlluxioURI;)V", FileSystem::filesystem, "alluxio/FileSystem/file/FileSystem", methodName, alluxiURISrc, alluxiURIDst);
    JniHelper::callVoidMethod( FileSystem::filesystem, "alluxio/client/file/FileSystem", methodName, alluxiURISrc, alluxiURIDst);

    JniHelper::getEnv()->DeleteLocalRef(alluxiURISrc);
    JniHelper::getEnv()->DeleteLocalRef(alluxiURIDst);
    return JniHelper::exceptionCheck();
}

Status FileSystem::createDirectory(const std::string& path)
{
    FileSystem::callJNIBydefaultOpt(path, "createDirectory");
}
Status FileSystem::createDirectory(const std::string& path, CreateDirectoryOptions& options)
{


}
Status FileSystem::createFile(const std::string& path,  FileOutStream** outStream)
{
    jobject alluxiURI = JniHelper::createObjectMethod("alluxio/AlluxioURI", path);

   // jobject fileOutStream = JniHelper::callObjectMethod("(Lalluxio/AlluxioURI;)Lalluxio/FileSystem/file/FileOutStream;",  FileSystem::filesystem,  "alluxio/FileSystem/file/FileSystem","createFile","alluxio/FileSystem/file/FileOutStream", alluxiURI);
       // cout<< mObjectToTypeNameMap.size()<<endl;
    jobject fileOutStream = JniHelper::callObjectMethod( FileSystem::filesystem,  "alluxio/client/file/FileSystem","createFile","alluxio/client/file/FileOutStream", alluxiURI);
    JniHelper::getEnv()->DeleteLocalRef(alluxiURI);
    *outStream = new FileOutStream(fileOutStream);
    return JniHelper::exceptionCheck();

}
Status FileSystem::createFile(const std::string& path, CreateFileOptions& options,  FileOutStream** outStream)
{


}
Status FileSystem::deletePath(const std::string& path)
{
    return callJNIBydefaultOpt(path, "delete");
}

Status FileSystem::deletePath(const std::string& path, DeleteOptions& options)
{

}

Status FileSystem::exists(const std::string& path, bool* result)
{
    jobject alluxiURI = JniHelper::createObjectMethod("alluxio/AlluxioURI", path);
//   bool result =  JniHelper::callBooleanMethod("(Lalluxio/AlluxioURI;)V", FileSystem::filesystem, "alluxio/FileSystem/file/FileSystem","exists", alluxiURI);
     *result =  JniHelper::callBooleanMethod( FileSystem::filesystem, "alluxio/client/file/FileSystem","exists", alluxiURI);

    JniHelper::getEnv()->DeleteLocalRef(alluxiURI);
     return JniHelper::exceptionCheck();

}


Status FileSystem::exists(const std::string& path, ExistsOptions& options, bool* result)
{


}

Status FileSystem::free(const std::string& path)
{
    return callJNIBydefaultOpt(path, "free");
}

Status FileSystem::free(const std::string& path, FreeOptions& options)
{


}

Status FileSystem::getStatus(const std::string& path, URIStatus* result)
{
    jobject alluxiURI = JniHelper::createObjectMethod("alluxio/AlluxioURI", path);
    //jobject URIStatus = JniHelper::callObjectMethod("(Lalluxio/AlluxioURI;)Lalluxio/FileSystem/file/URIStatus;",FileSystem::filesystem,
    //                    "alluxio/FileSystem/file/FileSystem","getStatus","alluxio/FileSystem/file/URIStatus", alluxiURI);
    jobject URIStatus = JniHelper::callObjectMethod(FileSystem::filesystem,
                       "alluxio/client/file/FileSystem","getStatus","alluxio/client/file/URIStatus", alluxiURI);
    return JniHelper::exceptionCheck();

}

Status FileSystem::getStatus(const std::string& path, GetStatusOptions& options, URIStatus* result)
{


}

Status FileSystem::listStatus(const std::string& path, vector<URIStatus>* result)
{
        jobject alluxiURI = JniHelper::createObjectMethod("alluxio/AlluxioURI", path);
        //jobject uRIStatusList =  JniHelper::callObjectMethod("(Lalluxio/AlluxioURI;)Ljava/util/List;",FileSystem::filesystem,
      //                  "alluxio/FileSystem/file/FileSystem","getStatus","java/util/List", alluxiURI);
      jobject uRIStatusList =  JniHelper::callObjectMethod(FileSystem::filesystem,
                       "alluxio/client/file/FileSystem","getStatus","java/util/List", alluxiURI);
        int listSize = JniHelper::callIntMethod(uRIStatusList, "java/util/List", "size");
        for(int i = 0 ; i < listSize; i ++) {
            // jobject alluxioURIStatus = JniHelper::callObjectMethod("(I)Ljava/lang/Object", uRIStatusList, "java/util/List", "get", "java/lang/Object", i);
            jobject alluxioURIStatus = JniHelper::callObjectMethod(uRIStatusList, "java/util/List", "get", "java/lang/Object", i);

             URIStatus* uriStatus = new URIStatus(alluxioURIStatus);
             result->push_back(*uriStatus);
        }
    return JniHelper::exceptionCheck();
}

Status FileSystem::listStatus(const std::string& path, ListStatusOptions& options, vector<URIStatus>* result)
{

}






Status FileSystem::mount(const std::string& alluxioPath, const std::string& ufsPath)
{
    return callJNIBydefaultOpt(alluxioPath, ufsPath, "mount");
}

Status FileSystem::mount(const std::string& alluxioPath, const std::string& ufsPath, MountOptions& options)
{


}

Status FileSystem::openFile(const std::string& path, FileInStream** inStream)
{
    jobject alluxiURI = JniHelper::createObjectMethod("alluxio/AlluxioURI", path);
   // jobject fileInStream = JniHelper::callObjectMethod("(Lalluxio/AlluxioURI;)Lalluxio/FileSystem/file/FileInStream",  FileSystem::filesystem,  "alluxio/FileSystem/file/FileSystem","openFile","alluxio/FileSystem/file/FileInStream", alluxiURI);
    jobject fileInStream = JniHelper::callObjectMethod(FileSystem::filesystem,  "alluxio/client/file/FileSystem","openFile","alluxio/client/file/FileInStream", alluxiURI);
    JniHelper::getEnv()->DeleteLocalRef(alluxiURI);
    Status stus = JniHelper::exceptionCheck();
    if(stus.ok()){
        *inStream = new FileInStream(fileInStream);
    }
    return stus;
}

Status FileSystem::openFile(const std::string& path, OpenFileOptions& options, FileInStream** inStream)
{

}

Status FileSystem::rename(const std::string& src, const std::string& dst)
{
    return callJNIBydefaultOpt(src, dst, "mount");

}

Status FileSystem::rename(const std::string& src, const std::string& dst, RenameOptions& options)
{


}


Status FileSystem::setAttribute(const std::string& path)
{
    return callJNIBydefaultOpt(path, "mount");
}

Status FileSystem::setAttribute(const std::string& path, SetAttributeOptions& options)
{
    return callJNIBydefaultOpt(path, "setAttribute");

}

Status FileSystem::unmount(const std::string& path)
{

    return callJNIBydefaultOpt(path, "unmount");

}

Status FileSystem::unmount(const std::string& path, UnmountOptions& options)
{

}
