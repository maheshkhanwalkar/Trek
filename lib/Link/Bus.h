#pragma once
#include "Link.h"

#include <vector>
#include <memory>

namespace trek {

class Bus : public Link {

public:
    /**
     * Create a new empty bus
     */
    explicit Bus() = default;

    /**
     * Create a bus with the provided node
     * @param nodes - nodes to connect via a bus
     */
    explicit Bus(std::vector<const Node*>&& nodes);

    /**
     * Add a node to the bus
     * @param node - node to add [non-owning pointer]
     */
    void add_node(const Node* node);

    /**
     * Get whether the bus is busy
     * @param which - requesting node
     * @return true if busy, false otherwise
     */
    bool isBusy(const Node* which) override;

    /**
     * Initiate a transfer on the bus
     * @param which - requesting node
     * @param packet - packet to transfer
     * @throws std::runtime_error if the link is currently busy
     */
    void initiate(const Node* which, std::unique_ptr<Packet> packet) override;

private:
    std::vector<const Node*> nodes;
    std::unique_ptr<Packet> curr;
};

}
