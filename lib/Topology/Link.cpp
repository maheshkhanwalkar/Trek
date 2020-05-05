#include "Link.h"
#include <exception>
#include <memory>

using namespace trek;

Link::Link(std::weak_ptr<Node> first, std::weak_ptr<Node> second,
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

    std::shared_ptr<Node> f_tmp = first.lock();
    return f_tmp.get() == which ? f_curr != nullptr : s_curr != nullptr;
}

void Link::initiate(const Node* const which, std::unique_ptr<Packet> packet)
{
    if(isBusy(which)) {
        throw std::runtime_error("initiating a transfer on a busy link!");
    }

    std::shared_ptr<Node> f_tmp = first.lock();

    if(f_tmp.get() == which) {
        f_curr = std::move(packet);
    } else {
        s_curr = std::move(packet);
    }
}
