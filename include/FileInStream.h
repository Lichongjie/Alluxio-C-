#ifndef FILEINSTREAM_H
#define FILEINSTREAM_H
#include "JNIHelper.h"
using namespace JNIHelper;

namespace alluxio {
class FileInStream {

public:
    FileInStream();
    FileInStream(jobject AlluxioInStream);
    ~FileInStream();
    Status read( ) ;
    Status read(char* b) ;                  // Read len bytes into buf starting offset off of length len,
    Status read(const char* buf, size_t off, size_t len, size_t* result);
    Status seek(size_t pos);
    Status skip(size_t pos);

    Status close();
private:
    jobject inStream;
    JniHelper::LocalRefMapType localRefs;
};

}

#endif // FILEINSTREAM_H
