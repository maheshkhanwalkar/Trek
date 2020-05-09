#include "IPv4Address.h"
#include <sstream>

using namespace trek;

/**
 * Convert from dotted decimal to integer format
 * @param fmt - dotted decimal IPv4 address
 * @return the equivalent integer address
 */
static uint32_t convert(const std::string& fmt)
{
    size_t pos = 0;
    uint32_t result = 0;

    // Three dots separating four octets
    for(int i = 0; i < 3; i++) {
        size_t next = fmt.find_first_of('.', pos);

        if(next == std::string::npos) {
            throw std::runtime_error("bad IPv4 address string\n");
        }

        std::string octet(pos, next);

        unsigned char equiv = static_cast<unsigned char>(std::stoi(octet));
        result = (result << 8) | equiv;
    }

    return result;
}

IPv4Address::IPv4Address(uint32_t address) : address(address) { }

IPv4Address::IPv4Address(const std::string& address)
    : address(convert(address)) { }


std::string IPv4Address::asString() const
{
    std::stringstream stream;

    for(size_t i = 0; i < sizeof(uint32_t) /* 4 bytes */; i++) {
        unsigned int byte = (address >> (i * 8)) & 0xFF;

        // Add the digits in reverse order
        while(byte > 0) {
            unsigned int digit = byte % 10;
            stream << digit;

            byte /= 10;
        }

        // Don't add an extra dot at the end
        if(i != sizeof(uint32_t) - 1) {
            stream << ".";
        }
    }

    // Reverse the overall string
    std::string copy(stream.str());
    std::reverse(copy.begin(), copy.end());

    return copy;
}

bool IPv4Address::operator==(const Address& rhs) const
{
    const IPv4Address* other = dynamic_cast<const IPv4Address*>(&rhs);

    // Not an IPv4 address, so not equal
    if(other == nullptr) {
        return false;
    }

    return this->address == other->address;
}
