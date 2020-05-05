#pragma once

#include "Node.h"
#include "lib/Packet/Packet.h"

#include <memory>

namespace trek {

class Link {
public:
    /**
     * Construct a new link between nodes
     * @param first - first node
     * @param second - second node
     * @param duplex - can both nodes send data at the same time?
     */
    explicit Link(std::shared_ptr<Node> first, std::shared_ptr<Node> second,
                  bool duplex);

    /**
     * Get whether the link is busy
     * @param which - requesting node
     * @return true if busy, false otherwise
     */
    virtual bool isBusy(const std::shared_ptr<Node>& which);

    /**
     * Initiate a transfer on the link
     * @param which - originating node
     * @param packet - packet to transfer
     * @throws std::runtime_error if the link is currently busy
     */
    virtual void initiate(const std::shared_ptr<Node>& which,
                          std::shared_ptr<Packet> packet);

    /**
     * Perform a packet transfer for the simulation time-slice
     */
    virtual void transfer() = 0;

    /**
     * Destroy the link (default behaviour)
     */
    virtual ~Link() = default;

protected:
    std::shared_ptr<Node> first, second;
    std::shared_ptr<Packet> f_curr, s_curr;

    bool duplex;
};

}