#include "Status.h"

 inline Status::Status(const Status& s) {                           // 拷贝构造函数
        state_ = (s.state_ == NULL) ? NULL : CopyState(s.state_);
    }
    inline void Status::operator=(const Status& s) {                        // 赋值运算符重载
        // The following condition catches both aliasing (when this == &s),
        // and the common case where both s and *this are ok.
        if (state_ != s.state_) {
            delete[] state_;
            state_ = (s.state_ == NULL) ? NULL : CopyState(s.state_);
        }
    }

  const char* Status::CopyState(const char* state) {                        // 复制状态字符串
        uint32_t size;
        memcpy(&size, state, sizeof(size));
        uint32_t len = size + sizeof(size) + 1 ;
        char* result = new char[len];
        memcpy(result, state, len);
        return result;
    }

    Status::Status(Code code, const Slice& msg, const Slice& msg2) {        // 内部构造函数
        assert(code != kOk);
        const uint32_t len1 = msg.size();
        const uint32_t len2 = msg2.size();
        const uint32_t size = len1 + (len2 ? (2 + len2) : 0);
        char* result = new char[size + 6];   // 没有结束符? --- 由于保留了size字段，采用memcpy指定size操作，可以没有结束符
        memcpy(result, &size, sizeof(size));
        result[4] = static_cast<char>(code); // 第5个字节存放code
        //memcpy(result + 5, msg.data(), len1);
        memcpy(result + sizeof(size) + 1, msg.data(), len1);
        if (len2) {
            result[5 + len1] = ':';
            result[6 + len1] = ' ';
            memcpy(result + 7 + len1, msg2.data(), len2);
        }
        state_ = result;
    }

    std::string Status::ToString() const {                              // 返回状态字符串
        if (state_ == NULL) {
            return "OK";
        } else {
            char tmp[30];
            const char* type;
            switch (code()) {
                case kOk:
                    type = "OK";
                    break;
                case kNotFound:
                    type = "NotFound: ";
                    break;
                case kCorruption:
                type = "Corruption: ";
                    break;
                case kNotSupported:
                    type = "Not implemented: ";
                    break;
                case kInvalidArgument:
                    type = "Invalid argument: ";
                    break;
                case kIOError:
                    type = "IO error: ";
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
