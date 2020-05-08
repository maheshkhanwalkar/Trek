#include "MACAddress.h"
#include <iomanip>
#include <sstream>

using namespace trek;

MACAddress::MACAddress(uint64_t address) : address(address & 0xFFFFFFFFFFFF) { }

std::string MACAddress::asString()
{
    // Switch to network (big endian) format
    uint64_t good = htonll(address);
    std::stringstream stream;

    // Skip the two bottom bytes -- since these encode bits 48-63 which are not
    // actually part of the address
    for(size_t i = 2; i < 8; i++) {
        unsigned int byte = (good >> (i * 8)) & 0xFF;
        stream << std::setfill ('0') << std::setw(2) << std::hex << byte;

        // Don't add an extra ':' at the end
        if(i != 7) {
            stream << ":";
        }
    }

    return stream.str();
}

bool MACAddress::operator==(const Address& rhs) const
{
    const MACAddress* other = dynamic_cast<const MACAddress*>(&rhs);

    // Not a MAC address -- not equal
    if(other == nullptr) {
        return false;
    }

    return this->address == other->address;
}
