#ifndef FILEOUTSTREAM_H
#define FILEOUTSTREAM_H
#include"Exceptions.hpp"
#include<JNIHelper.h>


class FileOutStream
{
    public:
        FileOutStream();
        FileOutStream(jobject AlluxioOutStream);
        void write(int b);
        Status write(const unsigned char* b);
        Status write(const unsigned char* b, int off, int len);
        Status close();
         ~FileOutStream();

    protected:

    private:
        jobject outStream;
        JniHelper::LocalRefMapType localRefs;

};

#endif // FILEOUTSTREAM_H
