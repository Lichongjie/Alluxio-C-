#include "Client.h"

Client::Client()
{
    JniHelper::start();

    //Client::filesystem = const_cast<jobject*> (filesystem);
    Client::filesystem = JniHelper::callStaticObjectMethod("alluxio/client/file/FileSystem$Factory", "get", "alluxio/client/file/FileSystem");


    //ctor
}
void Client::closeClient() {
    JNIEnv* env = JniHelper::getEnv();
    //env->DeleteLocalRef(Client::filesystem);
    JniHelper::finish();
}
Client::~Client()
{
Client::closeClient();
    //	return 0;
}


AlluxioStatus Client::callJNIBydefaultOpt(const std::string& path, const std::string& methodName)
{
    jobject alluxiURI = JniHelper::createObjectMethod("alluxio/AlluxioURI", path);
    JniHelper::callVoidMethod( "(Lalluxio/AlluxioURI;)V", Client::filesystem, "alluxio/client/file/FileSystem",methodName, alluxiURI);
    JniHelper::getEnv()->DeleteLocalRef(alluxiURI);
    return JniHelper::exceptionCheck();
}

AlluxioStatus Client::callJNIBydefaultOpt(const std::string& src, const std::string& dst, const std::string& methodName)
{
    jobject alluxiURISrc = JniHelper::createObjectMethod("alluxio/AlluxioURI", src);
    jobject alluxiURIDst =  JniHelper::createObjectMethod("alluxio/AlluxioURI", dst);
    JniHelper::callVoidMethod( "(Lalluxio/AlluxioURI;)V", Client::filesystem, "alluxio/client/file/FileSystem", methodName, alluxiURISrc, alluxiURIDst);
    JniHelper::getEnv()->DeleteLocalRef(alluxiURISrc);
    JniHelper::getEnv()->DeleteLocalRef(alluxiURIDst);
    return JniHelper::exceptionCheck();
}

AlluxioStatus Client::createDirectory(const std::string& path)
{
    Client::callJNIBydefaultOpt(path, "createDirectory");
}
AlluxioStatus Client::createDirectory(const std::string& path, CreateDirectoryOptions options)
{


}
AlluxioStatus Client::createFile(const std::string& path)
{
    jobject alluxiURI = JniHelper::createObjectMethod("alluxio/AlluxioURI", path);
    jobject fileOutStream = JniHelper::callObjectMethod("(Lalluxio/AlluxioURI;)Lalluxio/client/file/FileOutStream;",  Client::filesystem,  "alluxio/client/file/FileSystem","createFile","alluxio/client/file/FileOutStream", alluxiURI);
    JniHelper::getEnv()->DeleteLocalRef(alluxiURI);
    AlluxioStatus stus = JniHelper::exceptionCheck();
    if(stus->ok())
        return stus->setResult(new FileOutStream(fileOutStream));
    return stus;
}
AlluxioStatus Client::createFile(const std::string& path, CreateFileOptions options)
{


}
AlluxioStatus Client::deletePath(const std::string& path)
{
    return callJNIBydefaultOpt(path, "delete");
}

AlluxioStatus Client::deletePath(const std::string& path, DeleteOptions options)
{

}

AlluxioStatus Client::exists(const std::string& path)
{
    jobject alluxiURI = JniHelper::createObjectMethod("alluxio/AlluxioURI", path);
//   bool result =  JniHelper::callBooleanMethod("(Lalluxio/AlluxioURI;)V", Client::filesystem, "alluxio/client/file/FileSystem","exists", alluxiURI);
   bool result =  JniHelper::callBooleanMethod( Client::filesystem, "alluxio/client/file/FileSystem","exists", alluxiURI);

    JniHelper::getEnv()->DeleteLocalRef(alluxiURI);
    AlluxioStatus stus = JniHelper::exceptionCheck();
    if(stus->ok()) {
    stus->setResult(&result);
    }

    bool* r = stus->getResult<bool>();
    return stus;
}


AlluxioStatus Client::exists(const std::string& path, ExistsOptions options)
{


}

AlluxioStatus Client::free(const std::string& path)
{
   return callJNIBydefaultOpt(path, "free");
}

AlluxioStatus Client::free(const std::string& path, FreeOptions options)
{


}




AlluxioStatus Client::mount(const std::string& alluxioPath, const std::string& ufsPath)
{
    return callJNIBydefaultOpt(alluxioPath, ufsPath, "mount");
}

AlluxioStatus Client::mount(const std::string& alluxioPath, const std::string& ufsPath, MountOptions options)
{


}

AlluxioStatus Client::openFile(const std::string& path)
{
 jobject alluxiURI = JniHelper::createObjectMethod("alluxio/AlluxioURI", path);
    jobject fileInStream = JniHelper::callObjectMethod("(Lalluxio/AlluxioURI;)Lalluxio/client/file/FileInStream",  Client::filesystem,  "alluxio/client/file/FileSystem","openFile","alluxio/client/file/FileInStream", alluxiURI);
    JniHelper::getEnv()->DeleteLocalRef(alluxiURI);
   AlluxioStatus stus = JniHelper::exceptionCheck();
    if(stus->ok())
        return stus->setResult(new FileInStream(fileInStream));
    return stus;
}

AlluxioStatus Client::openFile(const std::string& path, OpenFileOptions options)
{

}

AlluxioStatus Client::rename(const std::string& src, const std::string& dst)
{
    return callJNIBydefaultOpt(src, dst, "mount");

}

AlluxioStatus Client::rename(const std::string& src, const std::string& dst, RenameOptions options)
{


}


AlluxioStatus Client::setAttribute(const std::string& path)
{
    return callJNIBydefaultOpt(path, "mount");
}

AlluxioStatus Client::setAttribute(const std::string& path, SetAttributeOptions options)
{
    return callJNIBydefaultOpt(path, "setAttribute");

}

AlluxioStatus Client::unmount(const std::string& path)
{

    return callJNIBydefaultOpt(path, "unmount");

}

AlluxioStatus Client::unmount(const std::string& path, UnmountOptions options)
{



}



