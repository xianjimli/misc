#define LOG_TAG "BootSound"
#include <utils/misc.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include <utils/Log.h>
#include <MyTest.h>
#include <IMyService.h>

namespace android {
MyTest::MyTest() : Thread(false){
}
 
MyTest::~MyTest() {
}

void MyTest::onFirstRef() {
    run("MyTest", PRIORITY_DISPLAY);
}

status_t MyTest::readyToRun() {
    return NO_ERROR;
}

static sp<IMyService> sMyService;
sp<IMyService>& getMyService()
{
    sp<IBinder> binder;
    sp<IServiceManager> sm = defaultServiceManager();
    do {
        binder = sm->getService(String16("MyService"));
        if (binder != 0)
            break;
        LOGW("MyService not published, waiting...");
        usleep(500000); // 0.5 s
    } while(true);
    sMyService = interface_cast<IMyService>(binder);
    LOGE_IF(sMyService = NULL, "no MyService!?");

    return sMyService;
}

bool MyTest::threadLoop() {
    LOGI("threadLoop");
    getMyService();
    sMyService->doSth1(100);
    LOGI("done.");
    return false;
}

}; // namespace android

