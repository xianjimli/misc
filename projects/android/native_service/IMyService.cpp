#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>

#include <binder/Parcel.h>
#include <binder/IMemory.h>
#include <binder/IPCThreadState.h>
#include "IMyService.h"

namespace android {

class BpMyService: public BpInterface<IMyService> {
public:
    BpMyService(const sp<IBinder>& impl)
        : BpInterface<IMyService>(impl) {
    }

    virtual int doSth1(int arg) {
        Parcel data, reply;
        data.writeInt32(arg);
        remote()->transact(DO_STH1, data, &reply);
        return reply.readInt32();
    }

    virtual int doSth2(int arg) {
        Parcel data, reply;
        data.writeInt32(arg);
        remote()->transact(DO_STH2, data, &reply);
        return reply.readInt32();
    }
};

IMPLEMENT_META_INTERFACE(MyService, "com.lxj.IMyService");

status_t BnMyService::onTransact(
    uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags){
    switch(code)
    {  
        case DO_STH1: {
            CHECK_INTERFACE(IMyService, data, reply);
            int arg = data.readInt32();
            int ret = this->doSth1(arg);
            reply->writeInt32(ret);
        }
        case DO_STH2: {
            CHECK_INTERFACE(IMyService, data, reply);
            int arg = data.readInt32();
            int ret = this->doSth2(arg);
            reply->writeInt32(ret);
        }
        default: return BBinder::onTransact(code, data, reply, flags);
    }

    return NO_ERROR;
}
};//end of android

