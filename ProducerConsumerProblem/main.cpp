#include "Semaphore.h"

Semaphore        mutex(1);
Semaphore        full(5);
Semaphore        empty(0);
std::ofstream    outFile;
std::mutex       coutMutex;
int              syncVar = 1;
int              count = 0;

void producer()
{
    while (true)
    {
        full.down();
        mutex.down();
        outFile << "Produced: " << syncVar++ << "    Items count: " << ++count << std::endl;
        if (syncVar == 6) outFile << "Producer is waiting\n";
        mutex.up();
        empty.up();
    }
}

void consumer()
{
    while (true)
    {
        empty.down();
        mutex.down();
        outFile << "Consumed: " << --syncVar << "    Items count: " << --count << std::endl;
        if (syncVar == 1) outFile << "Consumer is waiting\n";
        mutex.up();
        full.up();
    }
}

int main()
{
    outFile.open("OutputFile.txt");

    std::thread producer_thread(producer);
    std::thread consumer_thread(consumer);

    producer_thread.join();
    consumer_thread.join();

    outFile.close();
}