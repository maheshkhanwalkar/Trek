#include "CapacityLink.h"

#include <utility>

using namespace trek;

CapacityLink::CapacityLink(std::weak_ptr<Node> first,
                           std::weak_ptr<Node> second, bool duplex,
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
            std::shared_ptr<Node> s_tmp = second.lock();
            s_tmp->add_packet(std::move(f_curr));

            f_curr = nullptr;
        }
    }

    if(s_curr) {
        uint64_t bytes = bps * slice / 8;
        bs_curr += bytes;

        // Transfer complete
        if(bs_curr >= s_curr->getSize()) {
            std::shared_ptr<Node> f_tmp = first.lock();
            f_tmp->add_packet(std::move(s_curr));

            s_curr = nullptr;
        }
    }
}
