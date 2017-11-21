lib_LTLIBRARIES = liballuxio.la
liballuxio_la_SOURCES = FileSystem.cpp JNIHelper.cpp Status.cpp FileInStream.cpp FileOutStream.cpp
liballuxio_la_CPPFLAGS = $(JNI_INCLUDES)
liballuxio_la_LIBADD = $(JNI_LDFLAGS)

INCLUDES = -I/home/innkp/Alluxio-Cpp/include/

include_liballuxiodir = $(includedir)
#include_liballuxio_HEADERS = FileSystem.h FileInStream.h FileOutStream.h

bin_PROGRAMS = alluxiotest

alluxiotest_SOURCES = main.cpp 
alluxiotest_CPPFLAGS = $(JNI_INCLUDES)
alluxiotest_LDADD = liballuxio.la -lpthread




