#ifndef FILEOUTSTREAM_H
#define FILEOUTSTREAM_H
#include<JNIHelper.h>

namespace alluxio
{

class FileOutStream
{
public:
    FileOutStream();
    FileOutStream(jobject AlluxioOutStream);
    Status close();
    Status write(char b);
    Status write(const char* buf, size_t off, size_t len);
    Status flush();
    Status cancel();
    ~FileOutStream();

protected:

private:
    jobject outStream;
    JniHelper::LocalRefMapType localRefs;

};
}

#endif // FILEOUTSTREAM_H
