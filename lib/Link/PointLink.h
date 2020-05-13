#pragma once

#include "lib/Link/Link.h"
#include "lib/Packet/Packet.h"
#include "lib/Topology/Node.h"

#include <memory>

namespace trek {

/**
 * Point Transfer Link
 *
 * This class represents a transfer link that connects two nodes within
 * the greater network topology.
 *
 * Transfer links can operate in single or duplex mode. In single mode, only one
 * node can use the link at a time to transfer data. However, in duplex mode,
 * both of the nodes can transfer at the same time.
 *
 * This is an abstract class, so it cannot be used directly. The various
 * subclasses implement different kinds of links, which may be more or less
 * useful, depending on the simulation requirements.
 */
class PointLink : public Link {
public:
    /**
     * Construct a new link between nodes
     * @param first - first node
     * @param second - second node
     * @param duplex - can both nodes send data at the same time?
     */
    explicit PointLink(Node* first, Node* second, bool duplex);

    /**
     * Get whether the link is busy
     * @param which - requesting node
     * @return true if busy, false otherwise
     */
    bool isBusy(const Node* which) override;

    /**
     * Initiate a transfer on the link
     * @param which - originating node
     * @param packet - packet to transfer
     * @throws std::runtime_error if the link is currently busy
     */
    void initiate(const Node* which, std::unique_ptr<Packet> packet) override;

protected:
    Node *first, *second;
    std::unique_ptr<Packet> f_curr, s_curr;

    bool duplex;
};

}
