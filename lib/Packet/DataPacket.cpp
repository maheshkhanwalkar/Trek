#include "DataPacket.h"
#include <iostream>

using namespace trek;

DataPacket::DataPacket(int id, std::vector<char>&& payload, const Label &label)
    : Packet(id, payload.size(), label), payload(std::move(payload)),
      p_str(this->payload.begin(), this->payload.end())
{

}

void DataPacket::drop()
{
    // Output drop event on stdout
    std::cout << "* DataPacket: pkt no: " << id << " dropped\n";
}

const std::vector<char>& DataPacket::getPayload() const { return payload; }
const std::string& DataPacket::payloadAsStr() const { return p_str; }
