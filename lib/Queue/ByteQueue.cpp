#include "ByteQueue.h"
#include <exception>

using namespace trek;

ByteQueue::ByteQueue(uint64_t b_max) : b_max(b_max), b_curr(0) {}

void ByteQueue::push_back(const std::shared_ptr<Packet>& packet)
{
    if(b_curr + packet->getSize() == b_max) {
        throw std::runtime_error("attempt to add to full queue");
    }

    b_curr += packet->getSize();
    queue.push_back(packet);
}

bool ByteQueue::isFull() { return b_curr == b_max; }
