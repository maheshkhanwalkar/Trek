#include "Packet.h"

using namespace trek;

Packet::Packet(int id, uint32_t size, std::unique_ptr<Address> src,
   std::unique_ptr<Address> dest) : id(id), size(size), src(std::move(src)),
                                                dest(std::move(dest)) { }

uint32_t Packet::getSize() const { return size; }

const Address& Packet::getSrc() const { return *src; }
const Address& Packet::getDest() const { return *dest; }

void Packet::updateSrc(const Address& n_src) { *src = n_src; }
void Packet::updateDest(const Address& n_dest) { *dest = n_dest; }
