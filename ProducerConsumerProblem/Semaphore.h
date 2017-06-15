#pragma once
#include <condition_variable>
#include <thread>
#include <mutex>
#include <fstream>
#include <iostream>

class Semaphore
{
public:

    Semaphore(int count) : count_{ count }
    {}

    void up()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        ++count_;
        condVar_.notify_one();
    }

    void down()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        while (count_ == 0)
        {
            condVar_.wait(lock);
        }
        --count_;
    }

private:

    std::condition_variable condVar_;
    std::mutex              mutex_;
    int                     count_;
};