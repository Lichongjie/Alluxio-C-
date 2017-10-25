#include "FileInStream.h"

FileInStream::FileInStream()
{
    //ctor
}

FileInStream::FileInStream(jobject AlluxioInStream)
{
        FileInStream::inStream =AlluxioInStream;

}

FileInStream::~FileInStream()
{
    JNIEnv *env = JniHelper::getEnv();
    JniHelper::deleteLocalRefs(env, FileInStream::localRefs);
    //dtor
}
//TODO clear *b
int FileInStream::read(char* b) throw (IOException)
{
    FileInStream::read(b, 0, strlen(b));
}
int FileInStream::read(char* b, int off, int len)  throw (IOException)
{
    JNIEnv *env = JniHelper::getEnv();
    jbyteArray jbytearrays = env->NewByteArray(strlen(b));
    env->SetByteArrayRegion(jbytearrays, 0, strlen(b), (jbyte*)b);

    JniHelper::callIntMethod( "([B)I", FileInStream::inStream,  "alluxio/client/file/FileInStream", "read",  &jbytearrays, off, len);
    delete [] b;
    b =  (char*)env-> GetByteArrayElements(jbytearrays, 0);
    FileInStream::localRefs[env].push_back(jbytearrays);

     JniHelper::exceptionCheck( );

}

