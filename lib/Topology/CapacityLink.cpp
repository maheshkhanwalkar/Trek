#include "CapacityLink.h"

#include <utility>

using namespace trek;

CapacityLink::CapacityLink(std::shared_ptr<Node> first,
                           std::shared_ptr<Node> second, bool duplex,
                           uint64_t throughput, double slice)
    : Link(std::move(first), std::move(second), duplex), bps(throughput),
      bf_curr(0), bs_curr(0), slice(slice) {}


void CapacityLink::transfer()
{
    if(f_curr) {
        uint64_t bytes = bps * slice / 8;
        bf_curr += bytes;

        // Transfer complete
        if(bf_curr >= f_curr->getSize()) {
            second->add_packet(f_curr);
            f_curr = nullptr;
        }
    }

    if(s_curr) {
        uint64_t bytes = bps * slice / 8;
        bs_curr += bytes;

        // Transfer complete
        if(bs_curr >= s_curr->getSize()) {
            first->add_packet(s_curr);
            s_curr = nullptr;
        }
    }
}
