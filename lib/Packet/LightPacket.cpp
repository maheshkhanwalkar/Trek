#include "LightPacket.h"
#include <iostream>

using namespace trek;

void LightPacket::drop()
{
    // Output drop event on stdout
    std::cout << "* LightPacket: pkt no: " << id << " dropped\n";
}
