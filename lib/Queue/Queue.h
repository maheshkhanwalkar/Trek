#pragma once

#include "lib/Packet/Packet.h"

#include <deque>
#include <memory>

namespace trek {

/**
 * Packet queue
 *
 * This class encapsulates the functionality of an unbounded
 * packet queue, implemented using std::deque<Packet>
 *
 * There are no restrictions on the size of the queue, it can continue
 * to grow without bound (obviously limited by system memory)
 *
 */
class Queue {

public:
    /**
     * Add a new packet to the queue
     * @param packet - packet to add
     */
    virtual void push_back(std::shared_ptr<Packet>&& packet);


    /**
     * Peek the front of the queue
     * @return the first packet
     */
    virtual const Packet& peek() const;


    /**
     * Pop the first packet from the queue
     */
    virtual void pop_front();


    /**
     * Check whether the queue is full (for this implementation, always false)
     * @return true if full, false otherwise
     */
    virtual bool isFull();

protected:
    std::deque<std::shared_ptr<Packet> > queue;
};

}
