#include <string>
#include <stdio.h>
#include <stdlib.h>
#include<cstring>
//#include<JNIHelper.h>


class CreateDirectoryOptions {
public:
    CreateDirectoryOptions() {

    };
    ~CreateDirectoryOptions() {

    };
};

class CreateFileOptions {
    /*
    private:
        jobject createFileOpt;
    public:
        CreateFileOptions();
        ~CreateFileOptions();
        long getBlockSizeBytes() {
                return JniHelper::callLongMethod(createFileOpt, "CreateFileOptions", "getBlockSizeBytes");
        }
        FileWriteLocationPolicy getLocationPolicy() {
                jobject  policyObj = JniHelper::callObjectMethod(createFileOpt,
                "alluxio/FileSystem/file/options/CreateFileOptions", "alluxio/FileSystem/file/policy/FileWriteLocationPolicy");
                return FileWriteLocationPolicy(policyObj);
        }
            CreateFileOptions& setBlockSizeBytes() {
                     createFileOpt =  JniHelper::callObjectMethod(createFileOpt, "CreateFileOptions", "setBlockSizeBytes");
                    return *this;
        }
        CreateFileOptions setLocationPolicy(FileWriteLocationPolicy locationPolicy)  {
                createFileOpt = JniHelper::callObjectMethod(createFileOpt, "CreateFileOptions", "setLocationPolicy", locationPolicy.getJobject());
        }
        // the following functions are similar as the above two functions, so i don't list the detailed code
       std:: string getLocationPolicyClass() {...}
        long getTtl() {...}
        TtlAction getTtlAction() {...}
        Mode getMode(){...}
        int getWriteTier(){...}
         WriteType getWriteType(){...}
         bool isRecursive() {...}
         //

        CreateFileOptions setLocationPolicyClass(std::string className) {...}
       CreateFileOptions setMode(Mode mode) {...}
       CreateFileOptions setRecursive(boolean recursive) {...}
       CreateFileOptions setTtl(long ttl) {...}
       CreateFileOptions setTtlAction(TtlAction ttlAction) {...}
       CreateFileOptions setWriteTier(int writeTier) {...}
       CreateFileOptions setWriteType(WriteType writeType) {...}
       OutStreamOptions toOutStreamOptions() {...}

    */
};

class DeleteOptions {
public:
    DeleteOptions() {

    }
    ~DeleteOptions() {
    }
};

class ExistsOptions {
public :
    ExistsOptions() {

    }
    ~ExistsOptions() {

    }

};

class FreeOptions {
public:
    FreeOptions() {

    }
    ~FreeOptions() {
    }
};

class ListStatusOptions {
public:
    ListStatusOptions() {

    }
    ~ListStatusOptions() {

    }
};

class MountOptions {
public:
    MountOptions() {

    }
    ~MountOptions() {

    }

};

class OpenFileOptions {
public:
    OpenFileOptions() {

    }
    ~OpenFileOptions() {
    }

};

class RenameOptions {
public:
    RenameOptions() {

    }
    ~RenameOptions() {
    }
};

class SetAttributeOptions {
public:
    SetAttributeOptions() {

    }
    ~SetAttributeOptions() {

    }
};

class UnmountOptions {
public:
    UnmountOptions() {

    }
    ~UnmountOptions() {

    }
};
class GetStatusOptions {
public:
    GetStatusOptions() {
    }
    ~GetStatusOptions() {
    }
};

