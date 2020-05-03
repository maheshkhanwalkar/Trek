#pragma once
#include <cstdint>

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
     */
    explicit Packet(int id, uint32_t size);

    /**
     * Drop the packet
     *
     * The underlying network has decided to drop (that is, discard) the packet
     * so perform any implementation-specific event handling
     */
    virtual void drop() = 0;

    /**
     * Destroy the packet (default behaviour)
     */
    virtual ~Packet() = default;

protected:
    int id;
    uint32_t size;
};

}
