#pragma once
#include <cstdint>
#include <memory>

#include "lib/Address/Address.h"

namespace trek {

/**
 * Packet
 *
 * This superclass represents a packet that can be transmitted
 * on the network.
 */
class Packet {

public:
    /**
     * Create a new packet
     * @param id - packet id
     * @param size - overall packet size
     * @param src - source address
     * @param dest - destination address
     */
    explicit Packet(int id, uint32_t size, std::unique_ptr<Address> src,
                    std::unique_ptr<Address> dest);

    /**
     * Drop the packet
     *
     * The underlying network has decided to drop (that is, discard) the packet
     * so perform any implementation-specific event handling
     */
    virtual void drop() = 0;

    /**
     * Get the source address
     * @return a const ref to the source address
     */
    const Address& getSrc() const;

    /**
     * Get the destination address
     * @return a const ref to the destination address
     */
    const Address& getDest() const;

    /**
     * Update the source address
     * @param n_src - new source
     */
    void updateSrc(const Address& n_src);

    /**
     * Update the destination address
     * @param n_dest - new destination
     */
    void updateDest(const Address& n_dest);

    /**
     * Get the size of the packet
     * @return the size
     */
    uint32_t getSize() const;

    /**
     * Destroy the packet (default behaviour)
     */
    virtual ~Packet() = default;

protected:
    int id;
    uint32_t size;
    std::unique_ptr<Address> src, dest;
};

}
