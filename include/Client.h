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
#include <Status.h>

using namespace std;
typedef Status*  AlluxioStatus;

class Client
{
public:
    Client();
    AlluxioStatus createDirectory(const std::string& path);
    AlluxioStatus createDirectory(const std::string& path, CreateDirectoryOptions options);
    AlluxioStatus createFile(const std::string& path);
    AlluxioStatus createFile(const std::string& path, CreateFileOptions options);
    AlluxioStatus deletePath(const std::string& path);
    AlluxioStatus deletePath(const std::string& path, DeleteOptions options);
    AlluxioStatus exists(const std::string& path);
    AlluxioStatus exists(const std::string& path, ExistsOptions options);
    AlluxioStatus free(const std::string& path);
    AlluxioStatus free(const std::string& path, FreeOptions options);
    AlluxioStatus getStatus(const std::string& path);
    AlluxioStatus getStatus(const std::string& path, GetStatusOptions options);
    AlluxioStatus listStatus(const std::string& path);
    AlluxioStatus listStatus(const std::string& path, ListStatusOptions options);
    AlluxioStatus mount(const std::string& alluxioPath, const std::string& ufsPath);
    AlluxioStatus mount(const std::string& alluxioPath, const std::string& ufsPath, MountOptions options);
    AlluxioStatus getMountTable();
    AlluxioStatus openFile(const std::string& path);
    AlluxioStatus openFile(const std::string& path, OpenFileOptions options);
    AlluxioStatus rename(const std::string& src, const std::string& dst);
    AlluxioStatus rename(const std::string& src, const std::string& dst, RenameOptions options);
    AlluxioStatus setAttribute(const std::string& path);
    AlluxioStatus setAttribute(const std::string& path, SetAttributeOptions options);
    AlluxioStatus unmount(const std::string& path);
    AlluxioStatus unmount(const std::string& path, UnmountOptions options);
    void closeClient();
    ~Client();
private:
    jobject filesystem;
    jobject createAlluxioURI(const std::string& path);
    AlluxioStatus callJNIBydefaultOpt(const std::string& path, const std::string& methodName);
    AlluxioStatus callJNIBydefaultOpt(const std::string& src, const std::string&dst, const std::string& methodName);
};

#endif // CLIENT_H
