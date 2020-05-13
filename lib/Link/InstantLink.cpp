#include "InstantLink.h"
#include <memory>

using namespace trek;

InstantLink::InstantLink(Node* first, Node* second, bool duplex)
    : PointLink(first, second, duplex)
{

}

void InstantLink::transfer()
{
    // The initiate() call will ensure that when duplex mode is off
    // that at most one of the packet slots will be filled, so no check is
    // performed here

    if(f_curr) {
        second->add_packet(std::move(f_curr));
        f_curr = nullptr;
    }

    if(s_curr) {
        first->add_packet(std::move(s_curr));
        s_curr = nullptr;
    }
}
