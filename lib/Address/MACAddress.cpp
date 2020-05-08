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

    for(size_t i = 0; i < sizeof(uint64_t) /* 8 bytes */; i++) {
        unsigned char byte = (good >> (i * 8)) & 0xFF;
        stream << std::hex << byte;

        // Don't add an extra ':' at the end
        if(i != sizeof(uint64_t) - 1) {
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
