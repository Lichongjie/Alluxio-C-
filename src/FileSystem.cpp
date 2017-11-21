#include "FileSystem.h"

FileSystem::FileSystem() {
  JniHelper::Start();
  FileSystem::filesystem = JniHelper::CallStaticObjectMethod(
      "alluxio/client/file/FileSystem$Factory", "get",
      "alluxio/client/file/FileSystem");
}

void FileSystem::closeFileSystem() {
  JniHelper::DeleteObjectRef(FileSystem::filesystem);
}

FileSystem::~FileSystem() {
  FileSystem::closeFileSystem();
}

Status FileSystem::callJniBydefaultOption(const std::string& path,
                                          const std::string& methodName) {
  try {
    jobject alluxiURI = JniHelper::CreateObjectMethod("alluxio/AlluxioURI",
                                                      path);
    JniHelper::CallVoidMethod(FileSystem::filesystem,
                              "alluxio/client/file/FileSystem", methodName,
                              alluxiURI);
    JniHelper::DeleteObjectRef(alluxiURI);
  } catch (std::string e) {
    return Status::jniError(e);
  }

  return JniHelper::AlluxioExceptionCheck();
}

Status FileSystem::callJniBydefaultOption(const std::string& src,
                                          const std::string& dst,
                                          const std::string& methodName) {
  try {
    jobject alluxiURISrc = JniHelper::CreateObjectMethod("alluxio/AlluxioURI",
                                                         src);
    jobject alluxiURIDst = JniHelper::CreateObjectMethod("alluxio/AlluxioURI",
                                                         dst);
    JniHelper::CallVoidMethod(FileSystem::filesystem,
                              "alluxio/client/file/FileSystem", methodName,
                              alluxiURISrc, alluxiURIDst);
    JniHelper::DeleteObjectRef(alluxiURISrc);
    JniHelper::DeleteObjectRef(alluxiURIDst);
  } catch (std::string e) {
    return Status::jniError(e);
  }

  return JniHelper::AlluxioExceptionCheck();
}

Status FileSystem::callJniByOption(const std::string& path,
                   const std::string& methodName,
                   const jobject option) {
  try {
    jobject alluxiURI = JniHelper::CreateObjectMethod("alluxio/AlluxioURI",
                                                      path);
    JniHelper::CallVoidMethod(FileSystem::filesystem,
                              "alluxio/client/file/FileSystem", methodName,
                              alluxiURI, option);
    JniHelper::DeleteObjectRef(alluxiURI);
  } catch (std::string e) {
    return Status::jniError(e);
  }

  return JniHelper::AlluxioExceptionCheck();
}

Status FileSystem::callJniByOption(const std::string& src,
                                   const std::string& dst,
                                   const std::string& methodName,
                                   const jobject option) {
  try {
    jobject alluxiURISrc = JniHelper::CreateObjectMethod("alluxio/AlluxioURI",
                                                         src);
    jobject alluxiURIDst =  JniHelper::CreateObjectMethod("alluxio/AlluxioURI",
                                                          dst);
    JniHelper::CallVoidMethod(FileSystem::filesystem,
                              "alluxio/client/file/FileSystem", methodName,
                              alluxiURISrc, alluxiURIDst, option);
    JniHelper::DeleteObjectRef(alluxiURISrc);
    JniHelper::DeleteObjectRef(alluxiURIDst);
  } catch (std::string e) {
    return Status::jniError(e);
  }

  return JniHelper::AlluxioExceptionCheck();
}

Status FileSystem::CreateDirectory(const std::string& path) {
  return FileSystem::callJniBydefaultOption(path, "createDirectory");
}

Status FileSystem::CreateDirectory(const std::string& path,
                                   const CreateDirectoryOptions& options) {
  return FileSystem::callJniByOption(path, "createDirectory", options.getOptions());
}

Status FileSystem::CreateFile(const std::string& path,
                              FileOutStream** outStream) {
  jobject fileOutStream;
  try {
    jobject alluxiURI = JniHelper::CreateObjectMethod("alluxio/AlluxioURI",
                                                      path);
    fileOutStream = JniHelper::CallObjectMethod(FileSystem::filesystem,
        "alluxio/client/file/FileSystem", "createFile",
        "alluxio/client/file/FileOutStream", alluxiURI);
    JniHelper::DeleteObjectRef(alluxiURI);
  } catch (std::string e) {
    return Status::jniError(e);
  }

  Status status = JniHelper::AlluxioExceptionCheck();
  if (status.ok()) {
    *outStream = new FileOutStream(fileOutStream);
  }
  return status;
}

Status FileSystem::CreateFile(const std::string& path,
                              const CreateFileOptions& options,
                              FileOutStream** outStream) {
  jobject fileOutStream;
  try {
		jobject alluxiURI = JniHelper::CreateObjectMethod("alluxio/AlluxioURI",
																											path);
    fileOutStream = JniHelper::CallObjectMethod(FileSystem::filesystem,
        "alluxio/client/file/FileSystem", "createFile",
				"alluxio/client/file/FileOutStream", alluxiURI, options.getOptions());
		JniHelper::DeleteObjectRef(alluxiURI);
  } catch (std::string e) {
    return Status::jniError(e);
  }

  Status status = JniHelper::AlluxioExceptionCheck();
  if (status.ok()) {
    *outStream = new FileOutStream(fileOutStream);
  }
  return status;
}

Status FileSystem::DeletePath(const std::string& path) {
  return callJniBydefaultOption(path, "delete");
}

Status FileSystem::DeletePath(const std::string& path,
                              const DeleteOptions& options) {
  return callJniByOption(path, "delete", options.getOptions());
}

Status FileSystem::Exists(const std::string& path, bool* result) {
  bool res;
  try {
		jobject alluxiURI = JniHelper::CreateObjectMethod("alluxio/AlluxioURI",
																										  path);
		res = JniHelper::CallBooleanMethod(FileSystem::filesystem,
																			 "alluxio/client/file/FileSystem",
																			 "exists", alluxiURI);
		JniHelper::DeleteObjectRef(alluxiURI);
  } catch(std::string e) {
    return Status::jniError(e);
  }

  result = &res;
  return JniHelper::AlluxioExceptionCheck();
}

Status FileSystem::Exists(const std::string& path, const ExistsOptions& options,
                          bool* result) {
  bool res;
  try {
		jobject alluxiURI = JniHelper::CreateObjectMethod("alluxio/AlluxioURI",
																										  path);
		res = JniHelper::CallBooleanMethod(FileSystem::filesystem,
																			 "alluxio/client/file/FileSystem",
																			 "exists", alluxiURI,
																			 options.getOptions());
		JniHelper::DeleteObjectRef(alluxiURI);
  } catch(std::string e) {
    return Status::jniError(e);
  }

  result = &res;
  return JniHelper::AlluxioExceptionCheck();
}

Status FileSystem::Free(const std::string& path) {
  return callJniBydefaultOption(path, "free");
}

Status FileSystem::Free(const std::string& path, const FreeOptions& options) {
  return callJniByOption(path, "free", options.getOptions());
}

Status FileSystem::GetStatus(const std::string& path, URIStatus* result) {

  try {
    jobject alluxiURI = JniHelper::CreateObjectMethod("alluxio/AlluxioURI",
                                                      path);
    jobject uriStatus = JniHelper::CallObjectMethod(
        FileSystem::filesystem, "alluxio/client/file/FileSystem","getStatus",
        "alluxio/client/file/URIStatus", alluxiURI);
    result = new URIStatus(uriStatus);
  } catch(std::string e) {
    return Status::jniError(e);
  }

  return JniHelper::AlluxioExceptionCheck();
}

Status FileSystem::GetStatus(const std::string& path,
                             const GetStatusOptions& options,
                             URIStatus* result) {

  try {
    jobject alluxiURI = JniHelper::CreateObjectMethod("alluxio/AlluxioURI",
                                                      path);
    jobject uriStatus = JniHelper::CallObjectMethod(
        FileSystem::filesystem, "alluxio/client/file/FileSystem","getStatus",
        "alluxio/client/file/URIStatus", alluxiURI, options.getOptions());
    result = new URIStatus(uriStatus);
  } catch(std::string e) {
    return Status::jniError(e);
  }

  return JniHelper::AlluxioExceptionCheck();
}

Status FileSystem::listStatus(const std::string& path,
                              std::vector<URIStatus>* result) {

  try {
    jobject alluxiURI = JniHelper::CreateObjectMethod("alluxio/AlluxioURI",
                                                      path);
    jobject uriStatusList =  JniHelper::CallObjectMethod(
        FileSystem::filesystem, "alluxio/client/file/FileSystem", "getStatus",
        "java/util/List", alluxiURI);
    int listSize = JniHelper::CallIntMethod(uriStatusList, "java/util/List",
                                            "size");

    for (int i = 0; i < listSize; i ++) {
      jobject alluxioUriStatus = JniHelper::CallObjectMethod(
          uriStatusList, "java/util/List", "get", "java/lang/Object", i);
      URIStatus uriStatus = URIStatus(alluxioUriStatus);
      result->push_back(uriStatus);
     }
  } catch(std::string e) {
    return Status::jniError(e);
  }

  return JniHelper::AlluxioExceptionCheck();
}

Status FileSystem::listStatus(const std::string& path,
                              const ListStatusOptions& options,
                              std::vector<URIStatus>* result) {
  try {
    jobject alluxiURI = JniHelper::CreateObjectMethod("alluxio/AlluxioURI",
                                                      path);
    jobject uriStatusList =  JniHelper::CallObjectMethod(
        FileSystem::filesystem, "alluxio/client/file/FileSystem", "getStatus",
        "java/util/List", alluxiURI);
    int listSize = JniHelper::CallIntMethod(uriStatusList, "java/util/List",
                                            "size", options.getOptions());

    for (int i = 0; i < listSize; i ++) {
      jobject alluxioUriStatus = JniHelper::CallObjectMethod(
          uriStatusList, "java/util/List", "get", "java/lang/Object", i);
      URIStatus uriStatus = URIStatus(alluxioUriStatus);
      result->push_back(uriStatus);
    }
  } catch(std::string e) {
    return Status::jniError(e);
  }

  return JniHelper::AlluxioExceptionCheck();
}

Status FileSystem::mount(const std::string& alluxioPath,
                         const std::string& ufsPath) {
  return callJniBydefaultOption(alluxioPath, ufsPath, "mount");
}

Status FileSystem::mount(const std::string& alluxioPath,
                         const std::string& ufsPath,
                         const MountOptions& options) {
  return callJniByOption(alluxioPath, ufsPath, "mount", options.getOptions());
}

Status FileSystem::OpenFile(const std::string& path, FileInStream** inStream) {
  jobject fileInStream;
  try {
    jobject alluxiURI = JniHelper::CreateObjectMethod("alluxio/AlluxioURI",
                                                      path);
   fileInStream = JniHelper::CallObjectMethod(FileSystem::filesystem,
       "alluxio/client/file/FileSystem","openFile",
       "alluxio/client/file/FileInStream", alluxiURI);

    JniHelper::DeleteObjectRef(alluxiURI);
  } catch (std::string e) {
  	return Status::jniError(e);
  }

  Status stus = JniHelper::AlluxioExceptionCheck();
  if (stus.ok()) {
    *inStream = new FileInStream(fileInStream);
  }
  return stus;
}

Status FileSystem::OpenFile(const std::string& path,
                            const OpenFileOptions& options,
                            FileInStream** inStream) {
  jobject fileInStream;
  try {
    jobject alluxiURI = JniHelper::CreateObjectMethod("alluxio/AlluxioURI",
                                                      path);
    fileInStream = JniHelper::CallObjectMethod(
        FileSystem::filesystem, "alluxio/client/file/FileSystem","openFile",
        "alluxio/client/file/FileInStream", alluxiURI, options.getOptions());

    JniHelper::DeleteObjectRef(alluxiURI);
  } catch (std::string e) {
  	return Status::jniError(e);
  }

  Status stus = JniHelper::AlluxioExceptionCheck();
  if (stus.ok()) {
    *inStream = new FileInStream(fileInStream);
  }
  return stus;
}

Status FileSystem::Rename(const std::string& src, const std::string& dst) {
  return callJniBydefaultOption(src, dst, "rename");
}

Status FileSystem::Rename(const std::string& src, const std::string& dst,
                          const RenameOptions& options) {
  return callJniByOption(src, dst, "rename", options.getOptions());
}

Status FileSystem::SetAttribute(const std::string& path) {
  return callJniBydefaultOption(path, "setAttribute");
}

Status FileSystem::SetAttribute(const std::string& path,
                                const SetAttributeOptions& options) {
  return callJniByOption(path, "setAttribute", options.getOptions());
}

Status FileSystem::Unmount(const std::string& path) {
  return callJniBydefaultOption(path, "unmount");
}

Status FileSystem::Unmount(const std::string& path,
                           const UnmountOptions& options) {
  return callJniByOption(path, "unmount", options.getOptions());
}
