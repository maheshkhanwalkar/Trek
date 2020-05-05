#include "InstantLink.h"
#include <memory>

using namespace trek;

InstantLink::InstantLink(std::shared_ptr<Node> first,
                         std::shared_ptr<Node> second, bool duplex)
    : Link(std::move(first), std::move(second), duplex)
{

}

void InstantLink::transfer()
{
    // The initiate() call will ensure that when duplex mode is off
    // that at most one of the packet slots will be filled, so no check is
    // performed here

    if(f_curr) {
        second->add_packet(f_curr);
        f_curr = nullptr;
    }

    if(s_curr) {
        first->add_packet(s_curr);
        s_curr = nullptr;
    }
}
