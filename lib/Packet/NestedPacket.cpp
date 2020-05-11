#include "NestedPacket.h"

using namespace trek;

static inline uint32_t header_size(const Header* header)
{
    if(header == nullptr) {
        return 0U;
    } else {
        return header->getSize();
    }
}

NestedPacket::NestedPacket(int id, std::unique_ptr<Address> src,
                           std::unique_ptr<Address> dest,
                           std::unique_ptr<Header> header,
                           std::unique_ptr<Packet> child)
    : Packet(id, header_size(header.get()) + child->getSize(), std::move(src),
             std::move(dest), std::move(header)), child(std::move(child)) {}

const Packet* NestedPacket::getChild() const { return child.get(); }
