#include "FileOutStream.h"

FileOutStream::FileOutStream()
{
    //ctor
}

FileOutStream::~FileOutStream()
{
    //dtor
}

void FileOutStream::write(const char* b) throw (IOException) {
    FileOutStream::write(b, 0, strlen(b));

}

void FileOutStream::write(const char* b, int off, int len) throw (IOException)
{
    JNIEnv *env = JniHelper::getEnv();
        jbyteArray jbytearrays = env->NewByteArray(strlen(b));
    env->SetByteArrayRegion(jbytearrays, 0, strlen(b), (jbyte*)b);
 JniHelper::callVoidMethod("([BII)V", FileOutStream::outStream, "alluxio/client/file/FileOutStream", "write", jbytearrays);
    FileOutStream::localRefs[env].push_back(jbytearrays);
     JniHelper::exceptionCheck(env);


}
