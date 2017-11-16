#include "FileSystem.h"

FileSystem::FileSystem()
{
    JniHelper::start();
    FileSystem::filesystem = JniHelper::callStaticObjectMethod("", "alluxio/client/file/FileSystem$Factory", "get", "alluxio/client/file/FileSystem");
    //ctor
}
void FileSystem::closeFileSystem()
{
    JNIEnv* env = JniHelper::getEnv();
    env->DeleteLocalRef(FileSystem::filesystem);
    JniHelper::finish();
}
FileSystem::~FileSystem()
{
    FileSystem::closeFileSystem();
}

Status FileSystem::callJNIBydefaultOption(const std::string& path, const std::string& methodName)
{
    jobject alluxiURI = JniHelper::createObjectMethod("alluxio/AlluxioURI", path);
    JniHelper::callVoidMethod(FileSystem::filesystem, "alluxio/client/file/FileSystem",methodName, alluxiURI);
    JniHelper::getEnv()->DeleteLocalRef(alluxiURI);
    return JniHelper::exceptionCheck();
}

Status FileSystem::callJNIBydefaultOption(const std::string& src, const std::string& dst, const std::string& methodName)
{
    jobject alluxiURISrc = JniHelper::createObjectMethod("alluxio/AlluxioURI", src);
    jobject alluxiURIDst =  JniHelper::createObjectMethod("alluxio/AlluxioURI", dst);
    JniHelper::callVoidMethod(FileSystem::filesystem, "alluxio/client/file/FileSystem", methodName, alluxiURISrc, alluxiURIDst);

    JniHelper::getEnv()->DeleteLocalRef(alluxiURISrc);
    JniHelper::getEnv()->DeleteLocalRef(alluxiURIDst);

    return JniHelper::exceptionCheck();
}

Status FileSystem::callJNIByOption(const std::string& path, const std::string& methodName, jobject& option);

Status FileSystem::createDirectory(const std::string& path)
{
    FileSystem::callJNIBydefaultOpt(path, "createDirectory");
}

Status FileSystem::createDirectory(const std::string& path, const CreateDirectoryOptions& options)
{
}

Status FileSystem::createFile(const std::string& path,  FileOutStream** outStream)
{
    jobject alluxiURI = JniHelper::createObjectMethod("alluxio/AlluxioURI", path);
    jobject fileOutStream = JniHelper::callObjectMethod(FileSystem::filesystem,  "alluxio/client/file/FileSystem","createFile","alluxio/client/file/FileOutStream", alluxiURI);
    JniHelper::getEnv()->DeleteLocalRef(alluxiURI);
    Status status = JniHelper::exceptionCheck();
    if (status.ok())
    {
        *outStream = new FileOutStream(fileOutStream);
    }
    return status;
}

Status FileSystem::createFile(const std::string& path, const CreateFileOptions& options,  FileOutStream** outStream)
{


}
Status FileSystem::deletePath(const std::string& path)
{
    return callJNIBydefaultOpt(path, "delete");
}

Status FileSystem::deletePath(const std::string& path, const DeleteOptions& options)
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


Status FileSystem::exists(const std::string& path, const ExistsOptions& options, bool* result)
{


}

Status FileSystem::free(const std::string& path)
{
    return callJNIBydefaultOpt(path, "free");
}

Status FileSystem::free(const std::string& path, const FreeOptions& options)
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

Status FileSystem::getStatus(const std::string& path, const GetStatusOptions& options, URIStatus* result)
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
    for(int i = 0 ; i < listSize; i ++)
    {
        // jobject alluxioURIStatus = JniHelper::callObjectMethod("(I)Ljava/lang/Object", uRIStatusList, "java/util/List", "get", "java/lang/Object", i);
        jobject alluxioURIStatus = JniHelper::callObjectMethod(uRIStatusList, "java/util/List", "get", "java/lang/Object", i);

        URIStatus* uriStatus = new URIStatus(alluxioURIStatus);
        result->push_back(*uriStatus);
    }
    return JniHelper::exceptionCheck();
}

Status FileSystem::listStatus(const std::string& path, const ListStatusOptions& options, vector<URIStatus>* result)
{

}






Status FileSystem::mount(const std::string& alluxioPath, const std::string& ufsPath)
{
    return callJNIBydefaultOpt(alluxioPath, ufsPath, "mount");
}

Status FileSystem::mount(const std::string& alluxioPath, const std::string& ufsPath, const MountOptions& options)
{


}

Status FileSystem::openFile(const std::string& path, FileInStream** inStream)
{
    jobject alluxiURI = JniHelper::createObjectMethod("alluxio/AlluxioURI", path);
    jobject fileInStream = JniHelper::callObjectMethod(FileSystem::filesystem,  "alluxio/client/file/FileSystem","openFile","alluxio/client/file/FileInStream", alluxiURI);
    JniHelper::getEnv()->DeleteLocalRef(alluxiURI);
    Status stus = JniHelper::exceptionCheck();
    if(stus.ok())
    {
        *inStream = new FileInStream(fileInStream);
    }
    return stus;
}

Status FileSystem::openFile(const std::string& path, const OpenFileOptions& options, FileInStream** inStream)
{

}

Status FileSystem::rename(const std::string& src, const std::string& dst)
{
    return callJNIBydefaultOpt(src, dst, "mount");

}

Status FileSystem::rename(const std::string& src, const std::string& dst, const RenameOptions& options)
{

}

Status FileSystem::setAttribute(const std::string& path)
{
    return callJNIBydefaultOpt(path, "mount");
}

Status FileSystem::setAttribute(const std::string& path, const SetAttributeOptions& options)
{
    return callJNIBydefaultOpt(path, "setAttribute");

}

Status FileSystem::unmount(const std::string& path)
{
    return callJNIBydefaultOpt(path, "unmount");
}

Status FileSystem::unmount(const std::string& path, const UnmountOptions& options)
{

}
