#ifndef COMMON_H
#define COMMON_H

class FileInfo {

public:
    FileInfo(){

    };
    ~FileInfo() {

    };
};

class FileBlockInfo {
public:
    FileBlockInfo() {

    };
    ~FileBlockInfo() {

    };
};

class BlockInfo {
public:
    BlockInfo() {

    };
    ~BlockInfo() {

    };
};

class WorkerNetAddress {
public:
    WorkerNetAddress() {

    };
    ~WorkerNetAddress() {
    };

};

class MountPointInfo {
public:
    MountPointInfo() {
    }
    ~MountPointInfo() {
    }
};

class URIStatus {
public:
URIStatus(jobject URIStatus) {
jURIStatus = URIStatus;
}

private:
jobject jURIStatus;


};






#endif // COMMON_H
