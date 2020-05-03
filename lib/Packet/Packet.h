#pragma once
#include <cstdint>
#include <memory>

namespace trek {

/**
 * Packet Label
 *
 * This class indicates both the source and destination nodes
 * for a particular packet.
 *
 */
struct Label {
    int src;
    int dest;

    explicit Label(int src, int dest) : src(src), dest(dest) {}
};

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
     * @param label - packet label
     */
    explicit Packet(int id, uint32_t size, const Label& label);

    /**
     * Drop the packet
     *
     * The underlying network has decided to drop (that is, discard) the packet
     * so perform any implementation-specific event handling
     */
    virtual void drop() = 0;

    /**
     * Get the packet label
     * @return a const reference to the label
     */
    const Label& getLabel() const;

    /**
     * Destroy the packet (default behaviour)
     */
    virtual ~Packet() = default;

protected:
    int id;
    uint32_t size;
    std::unique_ptr<Label> label;
};

}
