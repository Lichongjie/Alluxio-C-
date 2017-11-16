#ifndef FILEOUTSTREAM_H
#define FILEOUTSTREAM_H
#include<JNIHelper.h>

namespace alluxio
{

class FileOutStream
{
public:
    Status close();
    Status write(char b);
    Status write(const char* buf, size_t off, size_t len);
    Status flush();
    Status cancel();
    ~FileOutStream();

protected:
    FileOutStream(jobject AlluxioOutStream);

private:
    jobject outStream;
    JniHelper::LocalRefMapType localRefs;
};
}

#endif // FILEOUTSTREAM_H
