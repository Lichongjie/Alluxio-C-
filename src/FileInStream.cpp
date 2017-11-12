#include "FileInStream.h"

using namespace alluxio;

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
Status FileInStream::read(char* b)
{
    return FileInStream::read(b, 0, strlen(b), NULL);
}


Status FileInStream::read(const char* buf, size_t off, size_t len, size_t* result)
{
    JNIEnv *env = JniHelper::getEnv();
    jbyteArray jbytearrays = env->NewByteArray(strlen(buf));
    env->SetByteArrayRegion(jbytearrays, 0, strlen(buf), (jbyte*)buf);

    *result  = JniHelper::callIntMethod( FileInStream::inStream,  "alluxio/FileSystem/file/FileInStream", "read",  &jbytearrays, (int)off, (int)len);
    //delete [] b;
    buf =  (char*)env-> GetByteArrayElements(jbytearrays, 0);
    FileInStream::localRefs[env].push_back(jbytearrays);

    Status stus =  JniHelper::exceptionCheck( );
    return stus;
}

Status FileInStream::seek(size_t pos) {
    JniHelper::callVoidMethod(FileInStream::inStream, "alluxio/FileSystem/file/FileInStream", "seek", (long)pos);
    return JniHelper::exceptionCheck( );

}

Status FileInStream::skip(size_t pos){
    JniHelper::callVoidMethod(FileInStream::inStream, "alluxio/FileSystem/file/FileInStream", "skip", (long)pos);
    return JniHelper::exceptionCheck( );
}

