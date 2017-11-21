#include "FileInStream.h"

using namespace alluxio;

FileInStream::FileInStream(jobject alluxioInStream) {
  FileInStream::inStream = alluxioInStream;
}

FileInStream::~FileInStream() {
}

Status FileInStream::Read(char* b) {
  return FileInStream::Read(b, 0, strlen(b), NULL);
}

Status FileInStream::Read(char*  buf, size_t off, size_t len,
             size_t* result) {
  try {
    JNIEnv *env = JniHelper::GetEnv();
  	jbyteArray jByteArrays = env->NewByteArray(len + off);
 	  env->SetByteArrayRegion(jByteArrays, off, len, (jbyte*)buf);
  	size_t res = JniHelper::CallIntMethod(FileInStream::inStream,
                                    			"alluxio/client/file/FileInStream",
                                          "read", jByteArrays, (int)off, (int)len);

  	result = &res;
 	  if (res > 0) {
      env->GetByteArrayRegion(jByteArrays, 0, res, (jbyte*)buf);
    }
    env->DeleteLocalRef(jByteArrays);
  } catch (std::string e) {
    return Status::jniError(e);
  }

  return JniHelper::AlluxioExceptionCheck( );
}

Status FileInStream::Seek(size_t pos) {
  try {
    JniHelper::CallVoidMethod(FileInStream::inStream,
                              "alluxio/client/file/FileInStream",
                              "seek", (long)pos);
  } catch (std::string e) {
    return Status::jniError(e);
  }

  return JniHelper::AlluxioExceptionCheck( );
}

Status FileInStream::Skip(size_t pos) {
  try {
 	  JniHelper::CallVoidMethod(FileInStream::inStream,
                              "alluxio/client/file/FileInStream", "skip",
                              (long)pos);
  } catch (std::string e) {
    return Status::jniError(e);
  }

  return JniHelper::AlluxioExceptionCheck( );
}

Status FileInStream::Close() {
  JniHelper::DeleteObjectRef(FileInStream::inStream);
  return Status::OK();
}
