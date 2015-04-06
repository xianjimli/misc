#define LOG_TAG "BootSound"
#include <utils/misc.h>
#include <utils/Log.h>
#include "media/mediaplayer.h"
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include <MyService.h>

namespace android {

void MyService::instantiate()
{
    defaultServiceManager()->addService(
            String16("MyService"), new MyService());    
}

void MyService::shutdown()
{
}

MyService::MyService() : Thread(false){
}
 
MyService::~MyService() {
}
    
int MyService::doSth1(int arg) {
    return arg;
}

int MyService::doSth2(int arg) {
    return arg;
}

status_t MyService::onTransact(
        uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
    IPCThreadState* ipc = IPCThreadState::self();
    const int pid = ipc->getCallingPid();
    const int uid = ipc->getCallingUid();

    LOGV("pid=%d uid=%d code=%d", pid, uid, code);
    status_t err = BnMyService::onTransact(code, data, reply, flags);

    return err;
}

void MyService::onFirstRef() {
    LOGV("onFirstRef");
    run("MyService", PRIORITY_DISPLAY);
}

status_t MyService::readyToRun() {
    LOGV("readyToRun");
    return NO_ERROR;
}

bool MyService::threadLoop() {
    LOGV("threadLoop");

    return true;
}

}; // namespace android

