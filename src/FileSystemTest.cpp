#include "FileSystem.h"

#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <functional>
#include <thread>
#include "JNIHelper.h"

using namespace alluxio;

void CreateDirectoryTest(FileSystem* fileSystem, const char* dirPath) {
    std::cout << std::endl << "TEST - CREATE DIRECTORY: ";
    Status status = fileSystem->createDirectory(dirPath);
    if(status.ok()) {
        std::cout << "SUCCESS - Created alluxio dir " << dirPath << std::endl;
    } else {
        std::cout << "FAILED - Created alluxio dir " << dirPath <<  "REASION: " << status.ToString() << std::endl;
    }
}

void deletePathTest(FileSystem* fileSystem) {


}
