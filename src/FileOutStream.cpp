#include "FileOutStream.h"

using namespace alluxio;

FileOutStream::FileOutStream(jobject AlluxioOutStream)
{
    FileOutStream::outStream = AlluxioOutStream;

}

FileOutStream::~FileOutStream()
{

}

Status FileOutStream::write(char b)
{
    return FileOutStream::write(&b, 0, 1);

}

Status FileOutStream::write(const char* buf, size_t off, size_t len)
{
    int byteLen = strlen(buf);
    JNIEnv *env = JniHelper::getEnv();
    jbyteArray jbytearrays = env->NewByteArray(byteLen);
    env->SetByteArrayRegion(jbytearrays, 0, byteLen, (jbyte*)buf);
    JniHelper::callVoidMethod(FileOutStream::outStream, "alluxio/FileSystem/file/FileOutStream",
                              "write", jbytearrays, (int)off, (int)len);
    FileOutStream::localRefs[env].push_back(jbytearrays);
    return JniHelper::exceptionCheck();
}

Status FileOutStream::flush() {
    JniHelper::callVoidMethod(FileOutStream::outStream, "alluxio/FileSystem/file/FileOutStream",
                              "flush");
    return JniHelper::exceptionCheck();
}

Status FileOutStream::cancel() {
    JniHelper::callVoidMethod(FileOutStream::outStream, "alluxio/FileSystem/file/FileOutStream",
                              "cancel");
    return JniHelper::exceptionCheck();
}

Status FileOutStream::close() {
    JniHelper::callVoidMethod(FileOutStream::outStream, "alluxio/FileSystem/file/FileOutStream",
                              "close");
    return JniHelper::exceptionCheck();
}
