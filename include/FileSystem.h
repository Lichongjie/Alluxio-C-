#ifndef FileSystem_H
#define FileSystem_H
#include "JNIHelper.h"
#include "Exceptions.hpp"
#include "Options.hpp"
#include "FileOutStream.h"
#include "FileInStream.h"
#include "Wire.hpp"
#include <list>
#include <map>
#include <Status.h>
#include<vector>

using namespace alluxio;

class FileSystem
{
public:
    FileSystem();
    Status createDirectory(const std::string& path);
    Status createDirectory(const std::string& path, CreateDirectoryOptions& options);
    Status createFile(const std::string& path, FileOutStream** outStream);
    Status createFile(const std::string& path, CreateFileOptions& options, FileOutStream** outStream);
    Status deletePath(const std::string& path);
    Status deletePath(const std::string& path, DeleteOptions& options);
    Status exists(const std::string& path, bool* result);
    Status exists(const std::string& path, ExistsOptions& options, bool* result);
    Status free(const std::string& path);
    Status free(const std::string& path, FreeOptions& options);
    Status getStatus(const std::string& path, URIStatus* result);
    Status getStatus(const std::string& path, GetStatusOptions& options, URIStatus* result);
    Status listStatus(const std::string& path,  vector<URIStatus>* result);
    Status listStatus(const std::string& path, ListStatusOptions& options, vector<URIStatus>* result);
    Status mount(const std::string& alluxioPath, const std::string& ufsPath);
    Status mount(const std::string& alluxioPath, const std::string& ufsPath, MountOptions& options);
    Status getMountTable(map<std::string, MountPointInfo>* result);
    Status openFile(const std::string& path, FileInStream** inStream);
    Status openFile(const std::string& path, OpenFileOptions& options, FileInStream** inStream);
    Status rename(const std::string& src, const std::string& dst);
    Status rename(const std::string& src, const std::string& dst, RenameOptions& options);
    Status setAttribute(const std::string& path);
    Status setAttribute(const std::string& path, SetAttributeOptions& options);
    Status unmount(const std::string& path);
    Status unmount(const std::string& path, UnmountOptions& options);
    void closeFileSystem();
    ~FileSystem();
private:
    jobject filesystem;
    jobject createAlluxioURI(const std::string& path);
    Status callJNIBydefaultOpt(const std::string& path, const std::string& methodName);
    Status callJNIBydefaultOpt(const std::string& src, const std::string&dst, const std::string& methodName);
};

#endif // FileSystem_H
