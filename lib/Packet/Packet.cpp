#include "Packet.h"

using namespace trek;

/**
 * Get the header size
 * @param header - packet header
 * @return the size
 */
static inline uint32_t header_size(const Header* header)
{
    if(header == nullptr) {
        return 0U;
    } else {
        return header->getSize();
    }
}

Packet::Packet(int id, uint32_t size, std::unique_ptr<Address> src,
   std::unique_ptr<Address> dest, std::unique_ptr<Header> header)
    : id(id), size(size), src(std::move(src)), dest(std::move(dest)),
      header(std::move(header)) { }

uint32_t Packet::getSize() const { return size + header_size(header.get()); }

const Address* Packet::getSrc() const { return src.get(); }
const Address* Packet::getDest() const { return dest.get(); }
const Header* Packet::getHeader() const { return header.get(); }

void Packet::updateSrc(std::unique_ptr<Address> n_src) {
    src = std::move(n_src);
}

void Packet::updateDest(std::unique_ptr<Address> n_dest) {
    dest = std::move(n_dest);
}

void Packet::updateHeader(std::unique_ptr<Header> n_hdr) {
    header = std::move(n_hdr);
}
