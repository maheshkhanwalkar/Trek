#include "LightPacket.h"
#include <iostream>

using namespace trek;

LightPacket::LightPacket(int id, uint32_t size, const Label &label)
    : Packet(id, size, label) {}

void LightPacket::drop()
{
    // Output drop event on stdout
    std::cout << "* LightPacket: pkt no: " << id << " dropped\n";
}
