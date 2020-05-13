#include "IPv4Address.h"
#include <sstream>
#include <algorithm>

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
    for(int i = 0; i < 4; i++) {
        size_t next = fmt.find_first_of('.', pos);

        if(next == std::string::npos) {
            // This was not expected -- throw an exception
            if(i != 3) {
                throw std::runtime_error("bad IPv4 address string\n");
            }

            break;
        }

        size_t len = next - pos;
        std::string octet(fmt.substr(pos, len));

        pos += len + 1;

        auto equiv = static_cast<unsigned char>(std::stoi(octet));
        result = (result << 8U) | equiv;
    }

    // Last digit handling
    std::string last(fmt.substr(pos));

    auto equiv = static_cast<unsigned char>(std::stoi(last));
    result = (result << 8U) | equiv;

    return result;
}

IPv4Address::IPv4Address(uint32_t address) : address(address) { }

IPv4Address::IPv4Address(const std::string& address)
    : address(convert(address)) { }


std::string IPv4Address::asString() const
{
    std::stringstream stream;

    for(size_t i = 0; i < sizeof(uint32_t) /* 4 bytes */; i++) {
        unsigned int byte = (address >> (i * 8U)) & 0xFFU;

        // Handle edge case of byte being 0 itself
        if(byte == 0) {
            stream << "0";
        }

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
    const auto* other = dynamic_cast<const IPv4Address*>(&rhs);

    // Not an IPv4 address, so not equal
    if(other == nullptr) {
        return false;
    }

    return this->address == other->address;
}
