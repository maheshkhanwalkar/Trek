#include "PointLink.h"
#include <exception>
#include <memory>

using namespace trek;

PointLink::PointLink(Node* first, Node* second, bool duplex) : first(first),
        second(second), f_curr(nullptr), s_curr(nullptr), duplex(duplex)
{

}

bool PointLink::isBusy(const Node* which)
{
    bool one = f_curr != nullptr || s_curr != nullptr;

    if(one && !duplex) {
        return true;
    }

    return first == which ? f_curr != nullptr : s_curr != nullptr;
}

void PointLink::initiate(const Node* which, std::unique_ptr<Packet> packet)
{
    if(isBusy(which)) {
        throw std::runtime_error("initiating a transfer on a busy link!");
    }

    if(first == which) {
        f_curr = std::move(packet);
    } else {
        s_curr = std::move(packet);
    }
}
