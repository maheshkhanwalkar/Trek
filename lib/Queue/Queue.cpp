#include "Queue.h"

using namespace trek;

void Queue::push_back(std::unique_ptr<Packet> packet)
{
    queue.push_back(std::move(packet));
}

const Packet& Queue::peek() const { return *queue.at(0); }
void Queue::pop_front() { queue.pop_front(); }
size_t Queue::size() const { return queue.size(); }
void Queue::clear() { queue.clear(); }
bool Queue::isFull() { return false; }
