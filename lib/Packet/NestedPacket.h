#pragma once
#include "Packet.h"

namespace trek {

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
