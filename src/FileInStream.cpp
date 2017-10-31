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
AlluxioStatus FileInStream::read(char* b)
{
    return FileInStream::read(b, 0, strlen(b));
}
AlluxioStatus FileInStream::read(char* b, int off, int len)
{
    JNIEnv *env = JniHelper::getEnv();
    jbyteArray jbytearrays = env->NewByteArray(strlen(b));
    env->SetByteArrayRegion(jbytearrays, 0, strlen(b), (jbyte*)b);

    int i  = JniHelper::callIntMethod( "([B)I", FileInStream::inStream,  "alluxio/client/file/FileInStream", "read",  &jbytearrays, off, len);
    delete [] b;
    b =  (char*)env-> GetByteArrayElements(jbytearrays, 0);
    FileInStream::localRefs[env].push_back(jbytearrays);

    AlluxioStatus stus =  JniHelper::exceptionCheck( );
    if(stus->ok()) {
        stus->setResult(&i);
    }
    return stus;

}

