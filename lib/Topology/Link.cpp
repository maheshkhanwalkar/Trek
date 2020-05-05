#include "Link.h"
#include <exception>
#include <memory>

using namespace trek;

Link::Link(std::shared_ptr<Node> first, std::shared_ptr<Node> second,
           bool duplex) : first(std::move(first)), second(std::move(second)),
                          f_curr(nullptr), s_curr(nullptr), duplex(duplex)
{

}

bool Link::isBusy(const Node* const which)
{
    bool one = f_curr != nullptr || s_curr != nullptr;

    if(one && !duplex) {
        return true;
    }

    return first.get() == which ? f_curr != nullptr : s_curr != nullptr;
}

void Link::initiate(const Node* const which, std::shared_ptr<Packet> packet)
{
    if(isBusy(which)) {
        throw std::runtime_error("initiating a transfer on a busy link!");
    }

    if(first.get() == which) {
        f_curr = std::move(packet);
    } else {
        s_curr = std::move(packet);
    }
}
