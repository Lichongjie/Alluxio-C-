#include "Client.hpp"

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


void Client::callJNIBydefaultOpt(const std::string& path, const std::string& methodName)
{
    jobject alluxiURI = JniHelper::createObjectMethod("alluxio/AlluxioURI", path);
    JniHelper::callVoidMethod( "(Lalluxio/AlluxioURI;)V", Client::filesystem, "alluxio/client/file/FileSystem",methodName, alluxiURI);
    JniHelper::getEnv()->DeleteLocalRef(alluxiURI);
    JniHelper::exceptionCheck();
}

void Client::callJNIBydefaultOpt(const std::string& src, const std::string& dst, const std::string& methodName)
{
    jobject alluxiURISrc = JniHelper::createObjectMethod("alluxio/AlluxioURI", src);
    jobject alluxiURIDst =  JniHelper::createObjectMethod("alluxio/AlluxioURI", dst);
    JniHelper::callVoidMethod( "(Lalluxio/AlluxioURI;)V", Client::filesystem, "alluxio/client/file/FileSystem", methodName, alluxiURISrc, alluxiURIDst);
    JniHelper::getEnv()->DeleteLocalRef(alluxiURISrc);
    JniHelper::getEnv()->DeleteLocalRef(alluxiURIDst);
    JniHelper::exceptionCheck();
}

void Client::createDirectory(const std::string& path) throw (FileAlreadyExistsException, InvalidPathException, IOException, AlluxioException)
{
    Client::callJNIBydefaultOpt(path, "createDirectory");
}
void Client::createDirectory(const std::string& path, CreateDirectoryOptions options)
throw (FileAlreadyExistsException, InvalidPathException, IOException,AlluxioException)
{


}
FileOutStream Client::createFile(const std::string& path)
throw (FileAlreadyExistsException, InvalidPathException, IOException, AlluxioException)
{
    jobject alluxiURI = JniHelper::createObjectMethod("alluxio/AlluxioURI", path);
    jobject fileOutStream = JniHelper::callObjectMethod("(Lalluxio/AlluxioURI;)Lalluxio/client/file/FileOutStream;",  Client::filesystem,  "alluxio/client/file/FileSystem","createFile","alluxio/client/file/FileOutStream", alluxiURI);
    JniHelper::getEnv()->DeleteLocalRef(alluxiURI);
    JniHelper::exceptionCheck();
    return FileOutStream(fileOutStream);
}
FileOutStream Client::createFile(const std::string& path, CreateFileOptions options)
throw(FileAlreadyExistsException, InvalidPathException, IOException, AlluxioException)
{


}
void Client::deletePath(const std::string& path)
throw(DirectoryNotEmptyException, FileDoesNotExistException, IOException, AlluxioException)
{
    callJNIBydefaultOpt(path, "delete");
}

void Client::deletePath(const std::string& path, DeleteOptions options)
throw (DirectoryNotEmptyException, FileDoesNotExistException, IOException, AlluxioException)
{

}

bool Client::exists(const std::string& path) throw (InvalidPathException, IOException, AlluxioException)
{
    callJNIBydefaultOpt(path, "exists");
}


bool Client::exists(const std::string& path, ExistsOptions options)
throw( InvalidPathException, IOException, AlluxioException)
{


}

void Client::free(const std::string& path) throw( FileDoesNotExistException, IOException, AlluxioException)
{
    callJNIBydefaultOpt(path, "free");
}

void Client::free(const std::string& path, FreeOptions options)
throw( FileDoesNotExistException, IOException,AlluxioException)
{


}




void Client::mount(const std::string& alluxioPath, const std::string& ufsPath) throw (IOException,AlluxioException)
{
    callJNIBydefaultOpt(alluxioPath, ufsPath, "mount");
}

void Client::mount(const std::string& alluxioPath, const std::string& ufsPath, MountOptions options)
throw (IOException, AlluxioException)
{


}

FileInStream Client::openFile(const std::string& path)
throw( FileDoesNotExistException, IOException, AlluxioException)
{
 jobject alluxiURI = JniHelper::createObjectMethod("alluxio/AlluxioURI", path);
    jobject fileInStream = JniHelper::callObjectMethod("(Lalluxio/AlluxioURI;)Lalluxio/client/file/FileInStream",  Client::filesystem,  "alluxio/client/file/FileSystem","openFile","alluxio/client/file/FileInStream", alluxiURI);
    JniHelper::getEnv()->DeleteLocalRef(alluxiURI);
    JniHelper::exceptionCheck();
    return FileInStream(fileInStream);

}

FileInStream Client::openFile(const std::string& path, OpenFileOptions options)
throw( FileDoesNotExistException, IOException,AlluxioException)
{

}

void Client::rename(const std::string& src, const std::string& dst)
throw (FileDoesNotExistException, IOException, AlluxioException)
{
    callJNIBydefaultOpt(src, dst, "mount");

}

void Client::rename(const std::string& src, const std::string& dst, RenameOptions options)
throw(FileDoesNotExistException, IOException, AlluxioException)
{


}


void Client::setAttribute(const std::string& path)
throw( FileDoesNotExistException, IOException, AlluxioException)
{
    callJNIBydefaultOpt(path, "mount");
}

void Client::setAttribute(const std::string& path, SetAttributeOptions options)
throw( FileDoesNotExistException, IOException, AlluxioException)
{
    callJNIBydefaultOpt(path, "setAttribute");

}

void Client::unmount(const std::string& path) throw( IOException, AlluxioException)
{

    callJNIBydefaultOpt(path, "unmount");

}

void Client::unmount(const std::string& path, UnmountOptions options) throw( IOException, AlluxioException)
{



}


















