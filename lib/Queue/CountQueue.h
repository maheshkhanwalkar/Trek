#pragma once
#include "Queue.h"

namespace trek {

/**
 * Packet-count bounded queue
 *
 * This queue is bounded by the number of packets that it can hold, that is,
 * there is no implicit size restriction in terms of number of bytes.
 *
 * Use this implementation as an adequate estimator for homogeneous packet
 * scenarios or general congestion evaluation. For a more robust and realistic
 * queue implementation, see ByteQueue.
 */
class CountQueue : public Queue {

public:
    /**
     * Create a packet-count bounded queue
     * @param max - maximum number of packets allowed
     */
    explicit CountQueue(size_t max);

    /**
     * Add a packet to the queue
     * @param packet - packet to add
     * @throws std::runtime_error if the queue is full
     */
    void push_back(std::shared_ptr<Packet> packet) override;

    /**
     * Check whether the queue is full
     * @return true when queue.size() == max, false otherwise
     */
    bool isFull() override;

private:
    size_t max;
};

}
