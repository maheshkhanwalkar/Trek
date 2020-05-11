#pragma once
#include "Packet.h"

namespace trek {

/**
 * Nested packet
 *
 * This class represents a packet which contains another packet
 * within its payload. This is in contrast with the DataPacket class, which
 * only has data within its payload.
 *
 * For example, the following diagram depicts how the packet nesting is
 * represented physically (in a real packet) vs in this simulation:
 *
 * -------------------------------------------------------------
 * | Ethernet hdr | IP hdr | TCP hdr | Data || Ethernet footer |
 * -------------------------------------------------------------
 *
 * NestedPacket
 * [ header = Ethernet hdr ]
 * [ child =
 *      NestedPacket
 *      [ header = IP hdr ]
 *      [ child =
 *          DataPacket
 *          [ header = TCP hdr]
 *          [ data = Data] ] ]
 *
 * The Ethernet footer (i.e. frame check sequence) is not simulated, but
 * its size can be added to the header for size-accuracy.
 *
 * This packet allows for different layers to handle different parts of the
 * packet, very similar to the OS-level network stack. The packet can be
 * stripped to reveal its inner packet, which can be passed to the right layer
 * of the processing stack.
 *
 * Hence, the framework can support accurate simulation of various protocols
 * at different layers of network communication (e.g. link, network, transport)
 */
class NestedPacket : public Packet {

    /**
     * Create a new nested packet
     * @param id - packet id
     * @param header - packet header
     * @param child - child packet
     */
    explicit NestedPacket(int id, std::unique_ptr<Address> src,
                          std::unique_ptr<Address> dest,
                          std::unique_ptr<Header> header,
                          std::unique_ptr<Packet> child);

    /**
     * Get the child packet
     * @return the child
     */
    const Packet* getChild() const;

private:
    std::unique_ptr<Packet> child;
};

}
