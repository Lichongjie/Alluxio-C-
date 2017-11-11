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

Status FileOutStream::write(char b)
{
    return FileOutStream::write((const char*)b, 0, 1);

}

Status FileOutStream::write(const char* buf, size_t off, size_t len)
{
    int byteLen = strlen(buf);
    JNIEnv *env = JniHelper::getEnv();
    jbyteArray jbytearrays = env->NewByteArray(byteLen);
    env->SetByteArrayRegion(jbytearrays, 0, byteLen, (jbyte*)buf);
  //  std::cout<<strlen(b)<< "      "<<b<<std::endl;
    JniHelper::callVoidMethod(FileOutStream::outStream, "alluxio/FileSystem/file/FileOutStream", "write", jbytearrays, off, len);
    FileOutStream::localRefs[env].push_back(jbytearrays);
    return JniHelper::exceptionCheck();
}

Status FileOutStream::close() {
    JniHelper::callVoidMethod(FileOutStream::outStream, "alluxio/FileSystem/file/FileOutStream", "close");
        return JniHelper::exceptionCheck();

}
