#pragma once

#include "lib/Link/PointLink.h"
#include <cstdint>

namespace trek {

/**
 * Capacity transfer link
 *
 * This class represents a link that can transfer data at a specified
 * throughput, given in bits per second.
 *
 * Therefore, it is possible that certain packets will need multiple calls
 * to transfer() before the link becomes ready again. This calculation is done
 * using the packet size, link throughput, and simulation time-slice.
 */
class CapacityLink : public PointLink {
public:
    /**
     * Create a new capacity link between two nodes
     * @param first - first node
     * @param second - second node
     * @param duplex - can both nodes transmit at the same time?
     * @param throughput - maximum link throughput in bits per second
     * @param slice - simulation time slice in seconds (e.g. 0.001 => 1 ms)
     */
    explicit CapacityLink(Node* first, Node* second, bool duplex,
                          uint64_t throughput, double slice);

    void transfer() override;

private:
    uint64_t bps, bf_curr, bs_curr;
    double slice;
};

}
