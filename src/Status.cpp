#include "Status.h"

inline Status::Status(const Status& s)                             // 拷贝构造函数
{
    state_ = (s.state_ == NULL) ? NULL : CopyState(s.state_);
}
inline void Status::operator=(const Status& s)                          // 赋值运算符重载
{
    // The following condition catches both aliasing (when this == &s),
    // and the common case where both s and *this are ok.
    if (state_ != s.state_)
    {
        delete[] state_;
        state_ = (s.state_ == NULL) ? NULL : CopyState(s.state_);
    }
}

const char* Status::CopyState(const char* state)                          // 复制状态字符串
{
    uint32_t size;
    memcpy(&size, state, sizeof(size));
    uint32_t len = size + sizeof(size) + 1 ;
    char* result = new char[len];
    memcpy(result, state, len);
    return result;
}

Status::Status(Code code, const std::string& msg)          // 内部构造函数
{
    assert(code != SUCCESS);
    const uint32_t len = msg.length();
    const uint32_t size = len;
    char* result = new char[size + 6];   // 没有结束符? --- 由于保留了size字段，采用memcpy指定size操作，可以没有结束符
    memcpy(result, &size, sizeof(size));
    result[4] = static_cast<char>(code); // 第5个字节存放code
    //memcpy(result + 5, msg.data(), len1);
    memcpy(result + sizeof(size) + 1, msg.data(), len);
    state_ = result;
}

std::string Status::ToString() const                                // 返回状态字符串
{
    if (state_ == NULL)
    {
        return "OK";
    }
    else
    {
        char tmp[30];
        const char* type;
        switch (code())
        {
        case CANCELED:
            type = "CanceledError";
            break;
        case UNKNOWN:
            type = "UnknownError: ";
            break;
        case INVALID_ARGUMENT:
            type = "InvalidArgumentError: ";
            break;
        case DEADLINE_EXCEEDED:
            type = "DeadlineExceededError: ";
            break;
        case NOT_FOUND:
            type = "NotFoundError: ";
            break;
        case ALREADY_EXISTS:
            type = "AlreadyExistsError: ";
            break;
        case PERMISSION_DENIED:
            type = "PermissionDeniedError: ";
            break;
        case UNAUTHENTICATED:
            type = "UnauthenticatedError: ";
            break;
        case RESOURCE_EXHAUSTED:
            type = "ResourceExhaustedError: ";
            break;
        case FAILED_PRECONDITION:
            type = "FailedPreconditionError: ";
            break;
        case ABORTED:
            type = "AbortedError: ";
            break;
        case OUT_OF_RANGE:
            type = "OutOfRangeError: ";
            break;
        case UNIMPLEMENTED:
            type = "UnimplementedError: ";
            break;
        case INTERNAL:
            type = "InternalError: ";
            break;
        case UNAVAILABLE:
            type = "UnavailableError: ";
            break;
        case DATA_LOSS:
            type = "DataLossError: ";
            break;

        default:
            snprintf(tmp, sizeof(tmp), "Unknown code(%d): ", static_cast<int>(code()));
            type = tmp;
            break;
        }
        std::string result(type);
        uint32_t length;
        memcpy(&length, state_, sizeof(length));
        result.append(state_ + 5, length);              // 状态字符串
        return result;
    }
}
