#pragma once
#include "lib/Topology/Node.h"

namespace trek {

/**
 * Transfer link
 *
 * This class represents a general transfer link, which allows connected nodes
 * to communicate with one another.
 *
 * This library supports two general types of transfer links, which are then
 * further broken down into multiple types:
 *
 *   1. Point-transfer links
 *      These links connect two nodes together. This type of link is the basis
 *      of efficient point-to-point transfer interconnects.
 *
 *   2. Bus-based links
 *      This link connects multiple nodes together via a shared bus. This is
 *      used, as the name implies, to simulate bus-based communication.
 *
 * The node itself does not necessarily need to know about the specific details
 * of the underlying interconnect system -- it simply treats the connection as
 * a generic link which it can read from or write to.
 */
class Link {

public:
    /**
     * Check whether the link is busy
     * @param which - requesting node
     * @return true if busy, false otherwise
     */
    virtual bool isBusy(const Node* which) = 0;

    /**
     * Initiate a transfer on the link
     * @param which - originating node
     * @param packet - packet to transfer
    */
    virtual void initiate(const Node* which, std::unique_ptr<Packet> packet)
        = 0;

    /**
     * Perform a packet transfer for the simulation time-slice
     */
    virtual void transfer() = 0;

    /**
     * Destroy the link (default behaviour)
     */
    virtual ~Link() = default;
};

}
