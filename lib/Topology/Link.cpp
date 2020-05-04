#include "Link.h"
#include <exception>

using namespace trek;

Link::Link(std::shared_ptr<Node> first, std::shared_ptr<Node> second,
           bool duplex) : first(std::move(first)), second(std::move(second)),
                          f_curr(nullptr), s_curr(nullptr), duplex(duplex)
{

}

bool Link::isBusy(const std::shared_ptr<Node>& which)
{
    bool cond = (first == which) || !duplex;
    return cond ? f_curr != nullptr : s_curr != nullptr;
}

void Link::initiate(const std::shared_ptr<Node>& which,
                    std::shared_ptr<Packet> packet)
{
    if(isBusy(which)) {
        throw std::runtime_error("initiating a transfer on a busy link!");
    }

    if(first == which || duplex) {
        f_curr = std::move(packet);
    } else {
        s_curr = std::move(packet);
    }
}

