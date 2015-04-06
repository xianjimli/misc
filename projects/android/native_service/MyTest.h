#include <utils/threads.h>

#ifndef MY_TEST_H
#define MY_TEST_H

namespace android {

class MyTest: public Thread
{
public:
                MyTest();
    virtual     ~MyTest();
private:
    virtual bool        threadLoop();
    virtual status_t    readyToRun();
    virtual void        onFirstRef();
};

#endif//MY_TEST_H

}; // namespace android

