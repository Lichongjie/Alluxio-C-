#include "FileSystem.h"

FileSystem::FileSystem() {
    JniHelper::start();
    FileSystem::filesystem = JniHelper::callStaticObjectMethod("", "alluxio/client/file/FileSystem$Factory", "get", "alluxio/client/file/FileSystem");
    //ctor
}
void FileSystem::closeFileSystem() {
    JNIEnv* env = JniHelper::getEnv();
    env->DeleteLocalRef(FileSystem::filesystem);
    JniHelper::finish();
}
FileSystem::~FileSystem() {
    FileSystem::closeFileSystem();
}

Status FileSystem::callJNIBydefaultOption(const std::string& path, const std::string& methodName) {
    jobject alluxiURI = JniHelper::createObjectMethod("alluxio/AlluxioURI", path);
    JniHelper::callVoidMethod(FileSystem::filesystem, "alluxio/client/file/FileSystem",methodName,
                              alluxiURI);
    JniHelper::getEnv()->DeleteLocalRef(alluxiURI);
    return JniHelper::exceptionCheck();
}

Status FileSystem::callJNIBydefaultOption(const std::string& src, const std::string& dst,
        const std::string& methodName) {
    jobject alluxiURISrc = JniHelper::createObjectMethod("alluxio/AlluxioURI", src);
    jobject alluxiURIDst =  JniHelper::createObjectMethod("alluxio/AlluxioURI", dst);
    JniHelper::callVoidMethod(FileSystem::filesystem, "alluxio/client/file/FileSystem", methodName,
                              alluxiURISrc, alluxiURIDst);

    JniHelper::getEnv()->DeleteLocalRef(alluxiURISrc);
    JniHelper::getEnv()->DeleteLocalRef(alluxiURIDst);

    return JniHelper::exceptionCheck();
}

Status FileSystem::callJNIByOption(const std::string& path, const std::string& methodName,
                                   jobject& option) {
    jobject alluxiURI = JniHelper::createObjectMethod("alluxio/AlluxioURI", path);
    JniHelper::callVoidMethod(FileSystem::filesystem, "alluxio/client/file/FileSystem",methodName,
                              alluxiURI, option);
    JniHelper::getEnv()->DeleteLocalRef(alluxiURI);
    return JniHelper::exceptionCheck();

}

Status FileSystem::callJNIByOption(const std::string& src, const std::string& dst,
        const std::string& methodName, jobject& option) {
    jobject alluxiURISrc = JniHelper::createObjectMethod("alluxio/AlluxioURI", src);
    jobject alluxiURIDst =  JniHelper::createObjectMethod("alluxio/AlluxioURI", dst);
    JniHelper::callVoidMethod(FileSystem::filesystem, "alluxio/client/file/FileSystem", methodName,
                              alluxiURISrc, alluxiURIDst, option);

    JniHelper::getEnv()->DeleteLocalRef(alluxiURISrc);
    JniHelper::getEnv()->DeleteLocalRef(alluxiURIDst);

    return JniHelper::exceptionCheck();
}

Status FileSystem::createDirectory(const std::string& path) {
    FileSystem::callJNIBydefaultOption(path, "createDirectory");
}

Status FileSystem::createDirectory(const std::string& path, const CreateDirectoryOptions& options) {
}

Status FileSystem::createFile(const std::string& path,  FileOutStream** outStream) {
    jobject alluxiURI = JniHelper::createObjectMethod("alluxio/AlluxioURI", path);
    jobject fileOutStream = JniHelper::callObjectMethod(FileSystem::filesystem,
                            "alluxio/client/file/FileSystem",
                            "createFile",
                            "alluxio/client/file/FileOutStream",
                            alluxiURI);
    JniHelper::getEnv()->DeleteLocalRef(alluxiURI);
    Status status = JniHelper::exceptionCheck();
    if (status.ok()) {
        *outStream = new FileOutStream(fileOutStream);
    }
    return status;
}

Status FileSystem::createFile(const std::string& path, const CreateFileOptions& options,
                              FileOutStream** outStream) {
              jobject alluxiURI = JniHelper::createObjectMethod("alluxio/AlluxioURI", path);
                 jobject fileOutStream = JniHelper::callObjectMethod(FileSystem::filesystem,
                                         "alluxio/client/file/FileSystem",
                                         "createFile",
                                         "alluxio/client/file/FileOutStream",
                                         alluxiURI, options.getOptions());
                 JniHelper::getEnv()->DeleteLocalRef(alluxiURI);
                 Status status = JniHelper::exceptionCheck();
                 if (status.ok()) {
                     *outStream = new FileOutStream(fileOutStream);
                 }
                 return status;

}
Status FileSystem::deletePath(const std::string& path) {
    return callJNIBydefaultOption(path, "delete");
}

Status FileSystem::deletePath(const std::string& path, const DeleteOptions& options) {
return callJNIByOption(path, "delete", options.getOptions());
}

Status FileSystem::exists(const std::string& path, bool* result) {
    jobject alluxiURI = JniHelper::createObjectMethod("alluxio/AlluxioURI", path);
    *result =  JniHelper::callBooleanMethod(FileSystem::filesystem,
                                            "alluxio/client/file/FileSystem","exists", alluxiURI);

    JniHelper::getEnv()->DeleteLocalRef(alluxiURI);
    return JniHelper::exceptionCheck();

}


Status FileSystem::exists(const std::string& path, const ExistsOptions& options, bool* result) {

jobject alluxiURI = JniHelper::createObjectMethod("alluxio/AlluxioURI", path);
    *result =  JniHelper::callBooleanMethod(FileSystem::filesystem,
                                            "alluxio/client/file/FileSystem","exists", alluxiURI, options.getOptions());

    JniHelper::getEnv()->DeleteLocalRef(alluxiURI);
    return JniHelper::exceptionCheck();
}

Status FileSystem::free(const std::string& path) {
    return callJNIBydefaultOption(path, "free");
}

Status FileSystem::free(const std::string& path, const FreeOptions& options) {
return callJNIByOption(path, "free", options.getOptions())

}

Status FileSystem::getStatus(const std::string& path, URIStatus* result) {
    jobject alluxiURI = JniHelper::createObjectMethod("alluxio/AlluxioURI", path);

    jobject URIStatus = JniHelper::callObjectMethod(FileSystem::filesystem,
                        "alluxio/client/file/FileSystem","getStatus",
                        "alluxio/client/file/URIStatus", alluxiURI);
    return JniHelper::exceptionCheck();
}

Status FileSystem::getStatus(const std::string& path, const GetStatusOptions& options,
                             URIStatus* result) {


}

Status FileSystem::listStatus(const std::string& path, std::vector<URIStatus>* result) {
    jobject alluxiURI = JniHelper::createObjectMethod("alluxio/AlluxioURI", path);
    jobject uRIStatusList =  JniHelper::callObjectMethod(FileSystem::filesystem,
                             "alluxio/client/file/FileSystem",
                             "getStatus","java/util/List", alluxiURI);
    int listSize = JniHelper::callIntMethod(uRIStatusList, "java/util/List", "size");
    for(int i = 0 ; i < listSize; i ++) {
        jobject alluxioURIStatus = JniHelper::callObjectMethod(uRIStatusList, "java/util/List",
                                   "get", "java/lang/Object", i);

        URIStatus* uriStatus = new URIStatus(alluxioURIStatus);
        result->push_back(*uriStatus);
    }
    return JniHelper::exceptionCheck();
}

Status FileSystem::listStatus(const std::string& path, const ListStatusOptions& options,
                              std::vector<URIStatus>* result) {

}

Status FileSystem::mount(const std::string& alluxioPath, const std::string& ufsPath) {
    return callJNIBydefaultOption(alluxioPath, ufsPath, "mount");
}

Status FileSystem::mount(const std::string& alluxioPath, const std::string& ufsPath,
                         const MountOptions& options) {

    return callJNIByOption(alluxioPath, ufsPath, "mount", options.getOptions());

}

Status FileSystem::openFile(const std::string& path, FileInStream** inStream) {
    jobject alluxiURI = JniHelper::createObjectMethod("alluxio/AlluxioURI", path);
    jobject fileInStream = JniHelper::callObjectMethod(FileSystem::filesystem,
                           "alluxio/client/file/FileSystem","openFile",
                           "alluxio/client/file/FileInStream",
                           alluxiURI);
    JniHelper::getEnv()->DeleteLocalRef(alluxiURI);
    Status stus = JniHelper::exceptionCheck();
    if(stus.ok()) {
        *inStream = new FileInStream(fileInStream);
    }
    return stus;
}

Status FileSystem::openFile(const std::string& path, const OpenFileOptions& options,
                            FileInStream** inStream) {
jobject alluxiURI = JniHelper::createObjectMethod("alluxio/AlluxioURI", path);
    jobject fileInStream = JniHelper::callObjectMethod(FileSystem::filesystem,
                           "alluxio/client/file/FileSystem","openFile",
                           "alluxio/client/file/FileInStream",
                           alluxiURI, options.getOptions() );
    JniHelper::getEnv()->DeleteLocalRef(alluxiURI);
    Status stus = JniHelper::exceptionCheck();
    if(stus.ok()) {
        *inStream = new FileInStream(fileInStream);
    }
    return stus;
}

Status FileSystem::rename(const std::string& src, const std::string& dst) {
    return callJNIBydefaultOption(src, dst, "rename");

}

Status FileSystem::rename(const std::string& src, const std::string& dst,
                          const RenameOptions& options) {
    return callJNIByOption(path, "rename", options.getOptions());

}

Status FileSystem::setAttribute(const std::string& path) {
    return callJNIBydefaultOption(path, "setAttribute");
}

Status FileSystem::setAttribute(const std::string& path, const SetAttributeOptions& options) {
    return callJNIByOption(path, "setAttribute", options.getOptions());

}

Status FileSystem::unmount(const std::string& path) {
    return callJNIBydefaultOption(path, "unmount");
}

Status FileSystem::unmount(const std::string& path, const UnmountOptions& options) {
    return callJNIByOption(path, "unmount", options.getOptions());

}
