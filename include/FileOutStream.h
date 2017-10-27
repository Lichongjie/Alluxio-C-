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
        void write(const unsigned char* b);
        void write(const unsigned char* b, int off, int len);
        void close();
         ~FileOutStream();

    protected:

    private:
        jobject outStream;
        JniHelper::LocalRefMapType localRefs;

};

#endif // FILEOUTSTREAM_H
