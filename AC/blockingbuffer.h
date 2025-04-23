#ifndef BLOCKINGBUFFER_H
#define BLOCKINGBUFFER_H

#include <QMutex>
#include <QMutexLocker>
#include <QWaitCondition>

class BlockingBuffer
{
public:
    BlockingBuffer();
    void Put();
    void PutAndSessionStart();
    void endSession();

private:
    size_t sessionStart;
};

#endif // BLOCKINGBUFFER_H
