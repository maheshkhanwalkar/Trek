#pragma once

#include "lib/Queue/Queue.h"

#include <unordered_map>
#include <memory>

namespace trek {
/**
 * Node representation
 * This class represents a node within the network topology.
 *
 * There are two primary functions carried out:
 *   - Talking on the network
 *   - Talking to client(s)
 *
 * For any particular node, there may be multiple clients that need to send or
 * receive data. These requests are processed by the node and sent out to the
 * network for handling.
 *
 * Therefore, in order to handle client requests, the node will have to talk to
 * the other nodes, i.e. sending and receiving packets.
 */
class Node {
public:
    /**
     * Initialise a new node with a given (unique) id
     * @param id - the node id
     * @param router - is the node a router?
     * @param queue - incoming packet queue to use
     */
    explicit Node(int id, bool router, std::unique_ptr<Queue>&& queue);

    /**
     * Get the current node's id
     * @return the id
     */
    int getID() const;

    /**
     * Get whether the current node is a router
     * @return true if it is, false otherwise
     */
    bool isRouter() const;

    /**
     * Add a packet to the incoming queue
     * @param packet - packet to add
     */
    void add_packet(std::unique_ptr<Packet> packet);

private:
    int id;
    bool router;
    std::unique_ptr<Queue> queue;
};

}
