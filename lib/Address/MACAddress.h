#pragma once
#include "Address.h"

#include <string>

namespace trek {

class MACAddress : public PhysAddress {
public:
    /**
     * Construct a new MAC address from raw representation.
     *
     * The address is contained with 64 bits, but is actually 48 bits in size.
     * The top bits will be zero'd out, so anything stored there will be lost.
     *
     * @param address - 48 bit MAC address in host endian format
     */
    explicit MACAddress(uint64_t address);

    /**
     * Get the string representation of the MAC address (e.g. FF:FF:FF:FF:FF:FF)
     * @return the representation
     */
    std::string asString() const override;

    /**
     * Check whether the two addresses are equal
     * @param rhs - other address to compare to
     * @return true if this and rhs are equal, false otherwise
     */
    bool operator==(const Address& rhs) const override;

private:
    uint64_t address;
};

}
