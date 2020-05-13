#include "Bus.h"

using namespace trek;

Bus::Bus(std::vector<const Node*>&& nodes) : nodes(std::move(nodes)),
                                             curr(nullptr) {}

void Bus::add_node(const Node* node) { nodes.push_back(node); }
bool Bus::isBusy(const Node* which __unused) { return curr != nullptr; }

void Bus::initiate(const Node* which, std::unique_ptr<Packet> packet)
{
    if(isBusy(which)) {
        throw std::runtime_error("initiating a transfer on a busy bus");
    }

    // Mark the packet as currently being processed
    this->curr = std::move(packet);
}
