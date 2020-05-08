#pragma once
#include <string>

namespace trek {

/**
 * Address class
 *
 * This class acts as the top-level base class of all types of Internet-related
 * addressing schemes. There are a variety of useful functions specified, which
 * each type of address will implement.
 */
struct Address {
    /**
     * Get the string representation of the address
     * @return the representation
     */
    virtual std::string asString() = 0;

    /**
     * Check whether the two addresses are equal
     * @param rhs - other address to compare against
     * @return true if they are equal, false otherwise
     */
    virtual bool operator==(const Address &rhs) const = 0;

    /**
     * Destroy the address (default behaviour)
     */
    virtual ~Address() = default;
};

/**
 * Physical addresses
 *
 * This class represents all kinds of physical network addresses, that is, an
 * address that is physically associated with a NIC (i.e. MAC address)
 *
 * While most technologies use MAC addresses at the physical layer, for
 * simulation purposes, it may be useful to work with other (or custom) types.
 *
 * All nodes within the network need to have at least one physical address
 * associated with them; however, if the node is multi-homed, then it needs to
 * have a physical address *per* link.
 */
struct PhysAddress : public Address {

};

/**
 * Network layer addresses
 *
 * This class represents all kinds of network layer addresses, which can be
 * assigned (statically or dynamically) to a NIC.
 *
 * The most common are IPv4 and IPv6 addresses, but other schemes can be
 * experimented with in the simulation.
 *
 * These addresses are technically optional -- the simulator will support a
 * purely physical address driven communication scheme (useful for LAN).
 * However, when they are used, a network layer address is needed for each
 * link that a node has.
 */
struct NetworkAddress : public Address {

};

}
