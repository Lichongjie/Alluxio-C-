#ifndef WIRE_H
#define WIRE_H

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

#endif // WIRE_H
