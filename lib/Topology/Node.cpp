#include "Node.h"

using namespace trek;

Node::Node(int id, bool router, std::unique_ptr<Queue>&& queue)
    : id(id), router(router), queue(std::move(queue)) {}

int Node::getID() const { return id; }
bool Node::isRouter() const { return router; }

void Node::add_packet(std::shared_ptr<Packet> packet)
{
    queue->push_back(std::move(packet));
}
