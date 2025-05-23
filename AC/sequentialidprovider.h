#ifndef SEQUENTIALIDPROVIDER_H
#define SEQUENTIALIDPROVIDER_H

#include<atomic>
#include<mutex>

class SequentialIdProvider
{
    static SequentialIdProvider singleton;
    SequentialIdProvider() : cur{ 0 }, cur_cel{ 0 } {
    }

    std::atomic<long long> cur;
    std::atomic<long long> cur_cel;
    std::mutex m_mutex;
public:
    SequentialIdProvider(const SequentialIdProvider&)
        = delete;
    SequentialIdProvider&
        operator=(const SequentialIdProvider&) = delete;

    static SequentialIdProvider& get();
    std::atomic<long long> next();
    std::atomic<long long> next_cel();
};

#endif // SEQUENTIALIDPROVIDER_H
