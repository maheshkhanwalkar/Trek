#include "DataPacket.h"

using namespace trek;

DataPacket::DataPacket(int id, std::unique_ptr<Address> src,
                             std::unique_ptr<Address> dest, uint32_t p_size)
    : Packet(id, p_size, std::move(src), std::move(dest)), data() { }

DataPacket::DataPacket(int id, std::unique_ptr<Address> src,
                       std::unique_ptr<Address> dest, uint32_t p_size,
                       std::vector<char>&& data)
    : Packet(id, p_size, std::move(src), std::move(dest)), data(std::move(data))
{
}
