#include "FileOutStream.h"

FileOutStream::FileOutStream()
{
    //ctor
}

FileOutStream::FileOutStream(jobject AlluxioOutStream)
{
    FileOutStream::outStream = AlluxioOutStream;

    //ctor
}

FileOutStream::~FileOutStream()
{
    //dtor
}

Status FileOutStream::write(const unsigned char* b)
{
    return FileOutStream::write(b, 0, strlen((const char *)b));

}

Status FileOutStream::write(const unsigned char* b, int off, int len)
{
int byteLen = strlen((const char *)b);
    JNIEnv *env = JniHelper::getEnv();
    jbyteArray jbytearrays = env->NewByteArray(byteLen);
    env->SetByteArrayRegion(jbytearrays, 0, byteLen, (jbyte*)b);

  //  std::cout<<strlen(b)<< "      "<<b<<std::endl;
    JniHelper::callVoidMethod("([BII)V", FileOutStream::outStream, "alluxio/FileSystem/file/FileOutStream", "write", jbytearrays, off, byteLen);
    FileOutStream::localRefs[env].push_back(jbytearrays);
    return JniHelper::exceptionCheck();
}
Status FileOutStream::close() {
    JniHelper::callVoidMethod("", FileOutStream::outStream, "alluxio/FileSystem/file/FileOutStream", "close");
        return JniHelper::exceptionCheck();

}
