#include "CountQueue.h"
#include <exception>

using namespace trek;

CountQueue::CountQueue(size_t max) : max(max) {}

void CountQueue::push_back(std::unique_ptr<Packet> packet)
{
    // Drop the packet if the queue is full
    if(queue.size() == max) {
        packet->drop();
        return;
    }

    queue.push_back(std::move(packet));
}

bool CountQueue::isFull() { return queue.size() == max; }
