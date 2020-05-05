#include "InstantLink.h"
#include <memory>

using namespace trek;

InstantLink::InstantLink(std::weak_ptr<Node> first,
                         std::weak_ptr<Node> second, bool duplex)
    : Link(std::move(first), std::move(second), duplex)
{

}

void InstantLink::transfer()
{
    // The initiate() call will ensure that when duplex mode is off
    // that at most one of the packet slots will be filled, so no check is
    // performed here

    if(f_curr) {
        std::shared_ptr<Node> s_tmp = second.lock();
        s_tmp->add_packet(std::move(f_curr));

        f_curr = nullptr;
    }

    if(s_curr) {
        std::shared_ptr<Node> f_tmp = first.lock();
        f_tmp->add_packet(std::move(s_curr));

        s_curr = nullptr;
    }
}
