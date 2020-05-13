#include "MACAddress.h"
#include <iomanip>
#include <sstream>
#include <algorithm>

using namespace trek;

MACAddress::MACAddress(uint64_t address) : address(address & 0xFFFFFFFFFFFFULL)
{ }

std::string MACAddress::asString() const
{
    std::stringstream stream;

    // MAC addresses are 48-bit (6 bytes)
    for(size_t i = 0; i < 6; i++) {
        unsigned int byte = (address >> (i * 8U)) & 0xFFU;

        if(byte == 0) {
            stream << "00";
        }

        // Add each hexadecimal digit to the stream [backwards]
        while(byte > 0) {
            unsigned int digit = byte % 0x10U;
            unsigned char value = digit > 9 ? 'a' + (digit - 0xA) : '0' + digit;

            stream << value;
            byte /= 0x10U;
        }

        if(i != 5) {
            stream << ":";
        }
    }

    std::string res(stream.str());
    std::reverse(res.begin(), res.end());

    return res;
}

bool MACAddress::operator==(const Address& rhs) const
{
    const auto* other = dynamic_cast<const MACAddress*>(&rhs);

    // Not a MAC address -- not equal
    if(other == nullptr) {
        return false;
    }

    return this->address == other->address;
}
