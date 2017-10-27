#ifndef CLIENT_H
#define CLIENT_H
#include "JNIHelper.h"
#include "Exceptions.hpp"
#include "Options.hpp"
#include "FileOutStream.h"
#include "FileInStream.h"
#include "Wire.hpp"
#include <list>
#include <map>
#include <status.h>

using namespace std;

class Client
{
public:
    Client();
    Status createDirectory(const std::string& path)
    Status createDirectory(const std::string& path, CreateDirectoryOptions options)
    Status createFile(const std::string& path)
    Status createFile(const std::string& path, CreateFileOptions options)
    Status deletePath(const std::string& path)
    Status deletePath(const std::string& path, DeleteOptions options)
    Status exists(const std::string& path)
    Status exists(const std::string& path, ExistsOptions options)
    Status free(const std::string& path)
    Status free(const std::string& path, FreeOptions options)
    Status getStatus(const std::string& path)
    Status getStatus(const std::string& path, GetStatusOptions options)
    Status listStatus(const std::string& path)
    Status listStatus(const std::string& path, ListStatusOptions options)
    Status mount(const std::string& alluxioPath, const std::string& ufsPath)
    Status mount(const std::string& alluxioPath, const std::string& ufsPath, MountOptions options)
    Status getMountTable()
    Status openFile(const std::string& path)
    Status openFile(const std::string& path, OpenFileOptions options)
    Status rename(const std::string& src, const std::string& dst)
    Status rename(const std::string& src, const std::string& dst, RenameOptions options)
    Status setAttribute(const std::string& path)
    Status setAttribute(const std::string& path, SetAttributeOptions options)
    Status unmount(const std::string& path)
    Status unmount(const std::string& path, UnmountOptions options)
    void closeClient();
    ~Client();
private:
    jobject filesystem;
    jobject createAlluxioURI(const std::string& path);
    void callJNIBydefaultOpt(const std::string& path, const std::string& methodName);
    void callJNIBydefaultOpt(const std::string& src, const std::string&dst, const std::string& methodName);
};

#endif // CLIENT_H
