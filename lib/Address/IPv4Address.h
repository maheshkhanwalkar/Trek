#pragma once
#include "Address.h"

namespace trek {

/**
 * IPv4 address
 */
class IPv4Address : public NetworkAddress {

public:
    /**
     * Construct an IPv4 address
     * @param address - address in host endian format
     */
    explicit IPv4Address(uint32_t address);

    /**
     * Construct an IPv4 address
     * @param address - address in dotted decimal format (e.g. 0.0.0.0)
     * @throws std::runtime_error if the string format is bad
     */
    explicit IPv4Address(const std::string& address);

    /**
     * Get the dotted decimal representation of the IPv4 address
     * @return the representation
     */
    std::string asString() const override;

    /**
     * Compare two addresses for equality
     * @param rhs - other address to compare against
     * @return true if they are equal, false otherwise
     */
    bool operator==(const Address& rhs) const override;

private:
    uint32_t address;
};

}
