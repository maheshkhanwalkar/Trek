#include "DataPacket.h"

using namespace trek;

DataPacket::DataPacket(int id, std::unique_ptr<Address> src,
                       std::unique_ptr<Address> dest,
                       std::unique_ptr<Header> header, uint32_t p_size)

    : Packet(id, p_size, std::move(src), std::move(dest), std::move(header)),
      data(), equiv() { }

DataPacket::DataPacket(int id, std::unique_ptr<Address> src,
                       std::unique_ptr<Address> dest,
                       std::unique_ptr<Header> header, std::vector<char>&& data)
    : Packet(id, data.size(), std::move(src), std::move(dest),
             std::move(header)), data(std::move(data)),
             equiv(this->data.begin(), this->data.end()) { }

bool DataPacket::hasRealPayload() const { return !data.empty(); }
const std::string& DataPacket::payloadAsStr() const { return equiv; }
