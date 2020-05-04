#include "Node.h"

using namespace trek;

Node::Node(int id, bool router) : id(id), router(router) {}
int Node::getID() const { return id; }
bool Node::isRouter() const { return router; }
