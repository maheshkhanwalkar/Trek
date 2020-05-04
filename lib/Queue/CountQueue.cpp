#include "CountQueue.h"
#include <exception>

using namespace trek;

CountQueue::CountQueue(size_t max) : max(max) {}

void CountQueue::push_back(std::shared_ptr<Packet>&& packet)
{
    if(queue.size() == max) {
        throw std::runtime_error("attempt to add to full queue");
    }

    queue.push_back(packet);
}

bool CountQueue::isFull() { return queue.size() == max; }
