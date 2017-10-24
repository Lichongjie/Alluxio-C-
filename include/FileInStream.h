#ifndef FILEINSTREAM_H
#define FILEINSTREAM_H
#include "JNIHelper.h"
#include "Exceptions.hpp"

typedef unsigned char byte;

class FileInStream
{
    public:
        FileInStream();
        FileInStream(jobject& AlluxioInStream);
         ~FileInStream();
        int read( ) throw (IOException) ;
        int read(char* b) throw (IOException) ;
        int read(char* b, int off, int len)throw (IOException);

    protected:

    private:
         jobject inStream;
        JniHelper::LocalRefMapType localRefs;

};

#endif // FILEINSTREAM_H
