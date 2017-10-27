#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include<exception>
#include<string>
#include <string.h>
#include<iostream>

class JavaException {
public:
JavaException(){

}
JavaException(const std::string &errorMsg) {

}
};

class AlluxioException : public JavaException
{
public:
    AlluxioException():JavaException("null"){};
    AlluxioException(const std::string &errorMsg) :JavaException (errorMsg) {};
     ~AlluxioException() {};
};

class IOException :public JavaException
{
public:
    IOException():JavaException("null"){};
    IOException(const std::string &errorMsg) :JavaException(errorMsg) {}
     ~IOException() {}
};

class InvalidPathException: public AlluxioException
{
public:
    InvalidPathException():AlluxioException(){};
    InvalidPathException(const std::string &errorMsg) :AlluxioException(errorMsg) {}
     ~InvalidPathException() {}

};

class FileAlreadyExistsException:public AlluxioException
{
public:
    FileAlreadyExistsException():AlluxioException(){};

    FileAlreadyExistsException(const std::string &errorMsg) :AlluxioException(errorMsg) {};
     ~FileAlreadyExistsException() {};
};

class FileDoesNotExistException:public AlluxioException
{
public:
    FileDoesNotExistException():AlluxioException(){};
    FileDoesNotExistException(const std::string &errorMsg) :AlluxioException(errorMsg) {};
    ~FileDoesNotExistException(){};
};
class DirectoryNotEmptyException:public AlluxioException {
public:
    DirectoryNotEmptyException():AlluxioException() {

    };
    DirectoryNotEmptyException(const std::string &errorMsg) :AlluxioException(errorMsg) {};
    ~DirectoryNotEmptyException(){};
};

/*

*/
#endif // CLIENT_H


