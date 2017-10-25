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

void FileOutStream::write(const unsigned char* b) throw (IOException)
{
    FileOutStream::write(b, 0, strlen((const char *)b));

}

void FileOutStream::write(const unsigned char* b, int off, int len) throw (IOException)
{
int byteLen = strlen((const char *)b);
    JNIEnv *env = JniHelper::getEnv();
    jbyteArray jbytearrays = env->NewByteArray(byteLen);
    env->SetByteArrayRegion(jbytearrays, 0, byteLen, (jbyte*)b);

  //  std::cout<<strlen(b)<< "      "<<b<<std::endl;
    JniHelper::callVoidMethod("([BII)V", FileOutStream::outStream, "alluxio/client/file/FileOutStream", "write", jbytearrays, off, byteLen);
    FileOutStream::localRefs[env].push_back(jbytearrays);
    JniHelper::exceptionCheck();
}
void FileOutStream::close() throw (IOException) {
    JniHelper::callVoidMethod("", FileOutStream::outStream, "alluxio/client/file/FileOutStream", "close");
}
