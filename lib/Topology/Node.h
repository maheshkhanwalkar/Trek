#pragma once

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
     */
    explicit Node(int id);

    /**
     * Get the current node's id
     * @return the id
     */
    int getID() const;

private:
    int id;
};

}
