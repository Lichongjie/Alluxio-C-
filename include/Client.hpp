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

using namespace std;

class Client
{
public:
    Client();
    void createDirectory(const std::string& path)
    throw (FileAlreadyExistsException, InvalidPathException,IOException, AlluxioException);
    void createDirectory(const std::string& path, CreateDirectoryOptions options)
    throw (FileAlreadyExistsException, InvalidPathException, IOException,AlluxioException);
    FileOutStream createFile(const std::string& path)
    throw (FileAlreadyExistsException, InvalidPathException, IOException, AlluxioException);
    FileOutStream createFile(const std::string& path, CreateFileOptions options)
    throw(FileAlreadyExistsException, InvalidPathException, IOException, AlluxioException);
    void deletePath(const std::string& path)
    throw(DirectoryNotEmptyException, FileDoesNotExistException, IOException, AlluxioException);
    void deletePath(const std::string& path, DeleteOptions options)
    throw (DirectoryNotEmptyException, FileDoesNotExistException, IOException, AlluxioException);
    bool exists(const std::string& path) throw (InvalidPathException, IOException, AlluxioException);
    bool exists(const std::string& path, ExistsOptions options)
    throw( InvalidPathException, IOException, AlluxioException);
    void free(const std::string& path) throw( FileDoesNotExistException, IOException, AlluxioException);
    void free(const std::string& path, FreeOptions options)
    throw( FileDoesNotExistException, IOException,AlluxioException);
    FileInfo getStatus(const std::string& path)
    throw( FileDoesNotExistException, IOException, AlluxioException);
    FileInfo getStatus(const std::string& path, GetStatusOptions options)
    throw( FileDoesNotExistException, IOException, AlluxioException);
    list<FileInfo> listStatus(const std::string& path)
    throw( FileDoesNotExistException, IOException, AlluxioException);
    list<FileInfo> listStatus(const std::string& path, ListStatusOptions options)
    throw( FileDoesNotExistException, IOException, AlluxioException);
    void mount(const std::string& alluxioPath, const std::string& ufsPath) throw (IOException,AlluxioException);
    void mount(const std::string& alluxioPath, const std::string& ufsPath, MountOptions options)
    throw (IOException, AlluxioException);
    map<string, MountPointInfo> getMountTable() throw( IOException, AlluxioException);
    FileInStream openFile(const std::string& path)
    throw( FileDoesNotExistException, IOException, AlluxioException);
    FileInStream openFile(const std::string& path, OpenFileOptions options)
    throw( FileDoesNotExistException, IOException,AlluxioException);
    void rename(const std::string& src, const std::string& dst)
    throw (FileDoesNotExistException, IOException, AlluxioException);
    void rename(const std::string& src, const std::string& dst, RenameOptions options)
    throw(FileDoesNotExistException, IOException, AlluxioException);
    void setAttribute(const std::string& path)
    throw( FileDoesNotExistException, IOException, AlluxioException);
    void setAttribute(const std::string& path, SetAttributeOptions options)
    throw( FileDoesNotExistException, IOException, AlluxioException);
    void unmount(const std::string& path) throw( IOException, AlluxioException);
    void unmount(const std::string& path, UnmountOptions options) throw( IOException, AlluxioException);

    void closeClient();

    // FileOutStream createFile(AlluxioURI path);
 //  FileOutStream createFile(AlluxioURI path, CreateFileOptions options)
 // void delete(AlluxioURI path)
    //void delete(AlluxioURI path, DeleteOptions options)
    ~Client();

protected:

private:
    jobject filesystem;
    jobject createAlluxioURI(const std::string& path);
    void callJNIBydefaultOpt(const std::string& path, const std::string& methodName);
    void callJNIBydefaultOpt(const std::string& src, const std::string&dst, const std::string& methodName);

};

#endif // CLIENT_H
