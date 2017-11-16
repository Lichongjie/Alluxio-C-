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
     static CreateDirectoryOptions& defaults() {
                                        createDirectoryOpt = JniHelper::callStaticObjectMethod("", "alluxio/client/file/options/CreateDirectoryOptions", "defaults", "alluxio/client/file/options/CreateDirectoryOptions");
                                        return *this;
                                    }
                                    jobject& getOptions() {
                                    return createDirectoryOpt;
                                    }
                                 private:
                                 jobject createDirectoryOpt;

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
   static DeleteOptions& defaults() {
                                      deleteOpt = JniHelper::callStaticObjectMethod("", "alluxio/client/file/options/DeleteOptions", "defaults", "alluxio/client/file/options/DeleteOptions");
                                      return *this;
                                  }
                                  jobject& getOptions() {
                                  return deleteOpt;
                                  }
                               private:
                               jobject deleteOpt;
};

class ExistsOptions {
public :
    ExistsOptions() {

    }
    ~ExistsOptions() {

    }
    static ExistsOptions& defaults() {
                                    existsOpt = JniHelper::callStaticObjectMethod("", "alluxio/client/file/options/ExistsOptions", "defaults", "alluxio/client/file/options/ExistsOptions");
                                    return *this;
                                }
                                jobject& getOptions() {
                                return existsOpt;
                                }
                             private:
                             jobject existsOpt;

};

class FreeOptions {
public:
    FreeOptions() {

    }
    ~FreeOptions() {
    }
    static FreeOptions& defaults() {
                                freeOpt = JniHelper::callStaticObjectMethod("", "alluxio/client/file/options/FreeOptions", "defaults", "alluxio/client/file/options/FreeOptions");
                                return *this;
                            }
                            jobject& getOptions() {
                            return freeOpt;
                            }
                         private:
                         jobject freeOpt;
};

class ListStatusOptions {
public:
    ListStatusOptions() {

    }
    ~ListStatusOptions() {

    }

    static ListStatusOptions& defaults() {
                            listStatusOpt = JniHelper::callStaticObjectMethod("", "alluxio/client/file/options/ListStatusOptions", "defaults", "alluxio/client/file/options/ListStatusOptions");
                            return *this;
                        }
                        jobject& getOptions() {
                        return listStatusOpt;
                        }
                     private:
                     jobject listStatusOpt;

};

class MountOptions {
public:
    MountOptions() {

    }
    ~MountOptions() {

    }
        static MountOptions& defaults() {
                        mountOpt = JniHelper::callStaticObjectMethod("", "alluxio/client/file/options/MountOptions", "defaults", "alluxio/client/file/options/MountOptions");
                        return *this;
                    }
                    jobject& getOptions() {
                    return mountOpt;
                    }
                 private:
                 jobject mountOpt;

};

class OpenFileOptions {
public:
    OpenFileOptions() {

    }
    ~OpenFileOptions() {
    }
    static OpenFileOptions& defaults() {
                    openFileOpt = JniHelper::callStaticObjectMethod("", "alluxio/client/file/options/OpenFileOptions", "defaults", "alluxio/client/file/options/OpenFileOptions");
                    return *this;
                }
                jobject& getOptions() {
                return openFileOpt;
                }
             private:
             jobject openFileOpt;

};

class RenameOptions {
public:
    RenameOptions() {

    }
    ~RenameOptions() {
    }
    static RenameOptions& defaults() {
                renameOpt = JniHelper::callStaticObjectMethod("", "alluxio/client/file/options/RenameOptions", "defaults", "alluxio/client/file/options/RenameOptions");
                return *this;
            }
            jobject& getOptions() {
            return renameOpt;
            }
         private:
         jobject renameOpt;
};

class SetAttributeOptions {
public:
    SetAttributeOptions() {

    }
    ~SetAttributeOptions() {

    }
    static SetAttributeOptions& defaults() {
            setAttributeOpt = JniHelper::callStaticObjectMethod("", "alluxio/client/file/options/SetAttributeOptions", "defaults", "alluxio/client/file/options/SetAttributeOptions");
            return *this;
        }
        jobject& getOptions() {
        return setAttributeOpt;
        }
     private:
     jobject setAttributeOpt;
};

class UnmountOptions {
public:
    UnmountOptions() {

    }
    ~UnmountOptions() {

    }
    static UnmountOptions& defaults() {
        ummountOpt = JniHelper::callStaticObjectMethod("", "alluxio/client/file/options/UnmountOptions", "defaults", "alluxio/client/file/options/UnmountOptions");
        return *this;
    }
    jobject& getOptions() {
    return ummountOpt;
    }
 private:
 jobject ummountOpt;
};
class GetStatusOptions {
public:
    GetStatusOptions() {
    }
    ~GetStatusOptions() {
    }
     static GetStatusOptions& defaults() {
            getStatusOpt = JniHelper::callStaticObjectMethod("", "alluxio/client/file/options/GetStatusOptions", "defaults", "alluxio/client/file/options/GetStatusOptions");
            return *this;
        }
        jobject& getOptions() {
        return getStatusOpt;
        }
     private:
     jobject getStatusOpt;
};

