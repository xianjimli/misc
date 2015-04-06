#ifndef IMY_SERVICE_H
#define IMY_SERVICE_H

#include <stdint.h>
#include <sys/types.h>
#include <utils/Errors.h>
#include <utils/RefBase.h>
#include <binder/IInterface.h>

namespace android {
class IMyService : public IInterface
{
public:
    enum 
    {
        DO_STH1 = IBinder::FIRST_CALL_TRANSACTION,
        DO_STH2
    };

    DECLARE_META_INTERFACE(MyService);

    virtual int doSth1(int arg) = 0;
    virtual int doSth2(int arg) = 0;
};

class BnMyService : public BnInterface<IMyService>
{
public:
   virtual status_t    onTransact( uint32_t code,
                                    const Parcel& data,
                                    Parcel* reply,
                                    uint32_t flags = 0);
};
}; // namespace android

#endif/*IMY_SERVICE_H*/

