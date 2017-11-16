#ifndef FileSystem_H
#define FileSystem_H
#include "JNIHelper.h"
#include "Options.hpp"
#include "FileOutStream.h"
#include "FileInStream.h"
#include "Wire.h"
#include <list>
#include <map>
#include <Status.h>
#include<vector>

using namespace alluxio;

namespace alluxio
{
// Basic file system interface supporting metadata operations and data operations
class FileSystem
{
public:
    // Constructor of FileSystem
    FileSystem();
    // Creates a directory with default option
    Status createDirectory(const std::string& path);
    // Creates a directory
    Status createDirectory(const std::string& path, const CreateDirectoryOptions& options);
    // Creates a file with default option. Sets a ptr to an allocated FileOutStream to outStream
    // when Status::OK, return status code otherwise without setting outStream
    Status createFile(const std::string& path, FileOutStream** outStream);
    // Creates a file.
    Status createFile(const std::string& path, const CreateFileOptions& options,
                      FileOutStream** outStream);
    // Deletes a file or a directory with default option
    Status deletePath(const std::string& path);
    // Deletes a file or a directory
    Status deletePath(const std::string& path, const DeleteOptions& options);
    // Checks whether a path exists in Alluxio space with default option. The result ptr will be set
    // when Java API return a primitive types
    Status exists(const std::string& path, bool* result);
    // Checks whether a path exists in Alluxio space
    Status exists(const std::string& path,const ExistsOptions& options, bool* result);
    // Evicts any data under the given path from Alluxio space, but does not delete the data from
    // the UFS. The metadata will still be present in Alluxio space after this operation
    Status free(const std::string& path);
    // Frees space
    Status free(const std::string& path, const FreeOptions& options);
    // Gets the URIStatus object that represents the metadata of an Alluxio path with default
    // option. The result ptr will be set when Java API return a primitive types of URIStatus
    Status getStatus(const std::string& path, URIStatus* result);
    // Gets the URIStatus object that represents the metadata of an Alluxio path
    Status getStatus(const std::string& path, const GetStatusOptions& options, URIStatus* result);
    // Convenience method for listStatus with default options. The result ptr will be set when Java
    // API return a primitive types of List of URIStatus
    Status listStatus(const std::string& path,  std::vector<URIStatus>* result);
    // If the path is a directory, returns the URIStatus of all the direct entries in it. Otherwise
    // returns a list with a single URIStatus element for the file
    Status listStatus(const std::string& path, const ListStatusOptions& options,
                      std::vector<URIStatus>* result);
    // Mounts a UFS subtree to the given Alluxio path with default option
    Status mount(const std::string& alluxioPath, const std::string& ufsPath);
    // Mounts a UFS subtree to the given Alluxio path
    Status mount(const std::string& alluxioPath, const std::string& ufsPath,
                 const MountOptions& options);
    // Lists all mount points and their corresponding under storage addresses
    Status getMountTable(std::map<std::string, MountPointInfo>* result);
    // Opens a file for reading with default option. Sets a ptr to an allocated FileInStream to
    // inStream when Status::OK, return status code otherwise without setting inStream
    Status openFile(const std::string& path, FileInStream** inStream);
    // Opens a file for reading
    Status openFile(const std::string& path, const OpenFileOptions& options,
                    FileInStream** inStream);
    // Renames an existing Alluxio path to another Alluxio path in Alluxio with default option
    Status rename(const std::string& src, const std::string& dst);
    // Renames an existing Alluxio path to another Alluxio path in Alluxio
    Status rename(const std::string& src, const std::string& dst, const RenameOptions& options);
    // Sets any number of a path's attributes with default option
    Status setAttribute(const std::string& path);
    // Sets any number of a path's attributes
    Status setAttribute(const std::string& path, const SetAttributeOptions& options);
    // Unmounts a UFS subtree identified by the given Alluxio path with default option
    Status unmount(const std::string& path);
    // Unmounts a UFS subtree identified by the given Alluxio path
    Status unmount(const std::string& path, const UnmountOptions& options);
    void closeFileSystem();
    ~FileSystem();
    
private:
    jobject filesystem;
    JniHelper::LocalRefMapType localRefs;

    jobject createAlluxioURI(const std::string& path);
    Status callJNIBydefaultOption(const std::string& path, const std::string& methodName);
    Status callJNIBydefaultOption(const std::string& src, const std::string&dst,
                                  const std::string& methodName);
    Status callJNIByOption(const std::string& path, const std::string& methodName, jobject& option);
    Status callJNIByOption(const std::string& src, const std::string&dst,
                           const std::string& methodName, jobject& option);
};
}

#endif // FileSystem_H
