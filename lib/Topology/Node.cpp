#include "Node.h"

using namespace trek;

Node::Node(int id) : id(id) { }

int Node::getID() const
{
    return id;
}
