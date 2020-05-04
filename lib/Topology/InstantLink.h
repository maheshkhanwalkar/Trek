#pragma once
#include "Link.h"

namespace trek {

/**
 * Instantaneous transfer link
 *
 * This class represents a link that can transfer any amount of data within
 * a single time-slice. Therefore, all initiated transfers complete within
 * one call to transfer()
 *
 * Real network links do not act this way, so for more realistic simulation,
 * see CapacityLink. However, in cases where link-based bottlenecks are
 * ignored or not present, then this class becomes useful.
 */
class InstantLink : public Link {
public:
    /**
     * Create an instant link between two nodes
     * @param first - first node
     * @param second - second
     * @param duplex - both sides can transmit at the same time
     */
    explicit InstantLink(std::shared_ptr<Node> first,
                         std::shared_ptr<Node> second, bool duplex);

    /**
     * Perform the transfer instantly
     */
    void transfer() override;
};

}
