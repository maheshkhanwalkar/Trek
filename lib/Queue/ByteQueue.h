#pragma once
#include "Queue.h"

namespace trek {

/**
 * Byte bounded queue
 *
 * This queue is bounded by total size in bytes. Therefore, packet size
 * becomes an important factor in determining how many packets can fit.
 *
 * Use this implementation for simulations with largely variable packet sizes,
 * since this will more accurately depict issues like resource hogging.
 */
class ByteQueue : public Queue {

public:
    /**
     * Construct a new byte bounded queue
     * @param b_max - maximum number of bytes allowed
     */
    explicit ByteQueue(uint64_t b_max);

    /**
     * Add a new packet to the queue
     * @param packet - packet to add
     * @throws std::runtime_error if the queue is full
     */
    void push_back(std::shared_ptr<Packet>&& packet) override;

    /**
     * Check if the queue is full
     * @return true if b_curr == b_max, false otherwise
     */
    bool isFull() override;

private:
    uint64_t b_max, b_curr;
};

}
