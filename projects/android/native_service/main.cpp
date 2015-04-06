#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <MyService.h>

using namespace android;

int main(int argc, char** argv)
{
    sp<ProcessState> proc(ProcessState::self());
    ProcessState::self()->startThreadPool();
    MyService::instantiate();
    IPCThreadState::self()->joinThreadPool();

    return 0;
}

