#include <utils/threads.h>
#include "IMyService.h"

#ifndef MY_SERVICE_H
#define MY_SERVICE_H

namespace android {


class MyService: public BnMyService, protected Thread
{
public:
    static void instantiate();
    static void shutdown();

                MyService();
    virtual     ~MyService();

private:
    virtual bool        threadLoop();
    virtual status_t    readyToRun();
    virtual void        onFirstRef();
    virtual status_t onTransact(
        uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags);

    virtual int doSth1(int arg);
    virtual int doSth2(int arg);
};

#endif//MY_SERVICE_H

}; // namespace android
