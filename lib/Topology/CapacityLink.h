#pragma once

#include "Link.h"
#include <cstdint>

namespace trek {

class CapacityLink : public Link {
public:
    /**
     * Create a new capacity link between two nodes
     * @param first - first node
     * @param second - second node
     * @param duplex - can both nodes transmit at the same time?
     * @param throughput - maximum link throughput in bits per second
     * @param slice - simulation time slice in seconds (e.g. 0.001 => 1 ms)
     */
    explicit CapacityLink(std::shared_ptr<Node> first,
                          std::shared_ptr<Node> second, bool duplex,
                          uint64_t throughput, double slice);

    void transfer() override;

private:
    uint64_t bps, bf_curr, bs_curr;
    double slice;
};

}
