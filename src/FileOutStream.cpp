#include "FileOutStream.h"

using namespace alluxio;

FileOutStream::FileOutStream(jobject alluxioOutStream) {
  FileOutStream::outStream = alluxioOutStream;
}

FileOutStream::~FileOutStream() {
}

Status FileOutStream::Write(char b) {
  return FileOutStream::Write(&b, 0, 1);
}

Status FileOutStream::Write(const char* buf, size_t off, size_t len) {
  try {
    int byteLen = strlen(buf);
    JNIEnv* env = JniHelper::GetEnv();
    jbyteArray jByteArrays = env->NewByteArray(byteLen);
    env->SetByteArrayRegion(jByteArrays, 0, byteLen, (jbyte*)buf);
    JniHelper::CallVoidMethod(FileOutStream::outStream,
                              "alluxio/client/file/FileOutStream", "write",
                              jByteArrays, (int)off, (int)len);
    env->DeleteLocalRef(jByteArrays);
  } catch (std::string e) {
    return Status::jniError(e);
  }

  return JniHelper::AlluxioExceptionCheck();
}

Status FileOutStream::Flush() {
  try {
		JniHelper::CallVoidMethod(FileOutStream::outStream,
        "alluxio/client/file/FileOutStream", "flush");
  } catch (std::string e) {
    return Status::jniError(e);
  }

  return JniHelper::AlluxioExceptionCheck();
}

Status FileOutStream::Cancel() {
  try {
  	JniHelper::CallVoidMethod(FileOutStream::outStream,
                            	"alluxio/client/file/FileOutStream", "cancel");
  	JniHelper::DeleteObjectRef(FileOutStream::outStream);
  } catch (std::string e) {
    return Status::jniError(e);
  }

  return JniHelper::AlluxioExceptionCheck();
}

Status FileOutStream::Close() {
  try {
  	JniHelper::CallVoidMethod(FileOutStream::outStream,
     	                       "alluxio/client/file/FileOutStream", "close");
  	JniHelper::DeleteObjectRef(FileOutStream::outStream);
  } catch (std::string e) {
    return Status::jniError(e);
  }

  return JniHelper::AlluxioExceptionCheck();
}
