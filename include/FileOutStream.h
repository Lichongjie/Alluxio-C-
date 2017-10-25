#ifndef FILEOUTSTREAM_H
#define FILEOUTSTREAM_H
#include"Exceptions.hpp"
#include<JNIHelper.h>


class FileOutStream
{
    public:
        FileOutStream();
        FileOutStream(jobject AlluxioOutStream);
        void write(int b) throw (IOException);
        void write(const unsigned char* b) throw (IOException);
        void write(const unsigned char* b, int off, int len) throw (IOException);
        void close() throw (IOException);

         ~FileOutStream();

    protected:

    private:
        jobject outStream;
        JniHelper::LocalRefMapType localRefs;

};

#endif // FILEOUTSTREAM_H
