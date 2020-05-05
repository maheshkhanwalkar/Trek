#include "ByteQueue.h"
#include <exception>

using namespace trek;

ByteQueue::ByteQueue(uint64_t b_max) : b_max(b_max), b_curr(0) {}

void ByteQueue::push_back(std::unique_ptr<Packet> packet)
{
    // Drop the packet if the queue is full
    if(b_curr + packet->getSize() == b_max) {
        packet->drop();
        return;
    }

    b_curr += packet->getSize();
    queue.push_back(std::move(packet));
}

bool ByteQueue::isFull() { return b_curr == b_max; }
