#ifndef STATUS_H
#define STATUS_H
#include <string>
#include<cstring>
#include <assert.h>

class Status {
public:
    // Create a success status.
    Status() : state_(NULL) { }                     // 构造函数，默认状态为success
    ~Status() {
        delete[] state_;    // 析构函数，释放状态字符串
    }
    // Copy the specified status.
    Status(const Status& s);

    void operator=(const Status& s);

    static Status OK() {
        return   Status();    // 返回一个success的状态
    }

    static Status canceled(const std::string& msg) {
        return  Status(CANCELED, msg );
    }
    static Status unknown(const std::string& msg) {
        return Status(UNKNOWN, msg);
    }
    static Status invalidArgument(const std::string& msg) {
        return Status(INVALID_ARGUMENT, msg);
    }
    static Status deadlineExceeded(const std::string& msg) {
        return Status(DEADLINE_EXCEEDED, msg);
    }
    static Status notFound(const std::string& msg) {
        return Status(NOT_FOUND, msg);
    }
    static Status alreadyExist(const std::string& msg) {
        return Status(ALREADY_EXISTS, msg);
    }
    static Status permissionDenied(const std::string& msg) {
        return Status(PERMISSION_DENIED, msg);
    }
    static Status unAuthenticated(const std::string& msg) {
        return  Status(UNAUTHENTICATED, msg);
    }
    static Status resourceExhausted(const std::string& msg) {
        return  Status(RESOURCE_EXHAUSTED, msg);
    }
    static Status failedPrecondition(const std::string& msg) {
        return  Status(FAILED_PRECONDITION, msg);
    }
    static Status aborted(const std::string& msg) {
        return  Status(ABORTED, msg);
    }
    static Status outOfRange(const std::string& msg) {
        return  Status(OUT_OF_RANGE, msg);
    }
    static Status unImplemented(const std::string& msg) {
        return  Status(UNIMPLEMENTED, msg);
    }
    static Status internal(const std::string& msg) {
        return Status(INTERNAL, msg);
    }
    static Status unavailable(const std::string& msg) {
        return Status(UNAVAILABLE, msg);
    }
    static Status dataLoss(const std::string& msg) {
        return  Status(DATA_LOSS, msg);
    }

    bool ok() const {
        return (state_ == NULL);
    }

    // Returns true iff the status indicates a NotFound error.
    /*
    bool IsNotFound() const
    {
        return code() == kNotFound;
    }*/
    // Return a string representation of this status suitable for printing.
    // Returns the string "OK" for success.
    std::string ToString() const;

private:
    // 为了节省空间Status并没有用std::string来存储错误信息，
    // 而是将返回码(Code), 错误信息msg及长度打包存储于一个字符串数组中。
    // OK status has a NULL state_.  Otherwise, state_ is a new[] array of the following form:
    //    state_[0..3] == length of message
    //    state_[4]    == code
    //    state_[5..]  == message
    const char* state_;

    enum Code {

        CANCELED = 0,
        UNKNOWN = 1,
        INVALID_ARGUMENT = 2,
        DEADLINE_EXCEEDED = 3,
        NOT_FOUND = 4,
        ALREADY_EXISTS = 5,
        PERMISSION_DENIED = 6,
        UNAUTHENTICATED = 7,
        RESOURCE_EXHAUSTED = 8,
        FAILED_PRECONDITION = 9,
        ABORTED = 10,
        OUT_OF_RANGE = 11,
        UNIMPLEMENTED = 12,
        INTERNAL = 13,
        UNAVAILABLE =14,
        DATA_LOSS =15,
        SUCCESS = 16
    };

    Code code() const {
        return (state_ == NULL) ? SUCCESS : static_cast<Code>(state_[4]);
    }

    Status(Code code, const std::string& msg) ;
    static const char* CopyState(const char* s);
};

#endif // STATUS_H
