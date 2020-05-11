#pragma once
#include <cstdint>

namespace trek {

/**
 * Packet header
 *
 * This class symbolically represents a packet header, which is a part of any
 * packet, although its contents can vary.
 *
 * This class only encapsulates header size directly, which is necessary for
 * total packet size calculations. Subclasses which extend this base class will
 * contain all the necessary header members required by the protocol(s) they
 * are adhering to.
 */
class Header {
protected:
    /**
     * Create a simulated header of the given size
     * @param size - header size
     */
    explicit Header(uint32_t size);

public:
    /**
     * Get the header size
     * @return the size
     */
    uint32_t getSize() const;

    /**
     * Destroy the header (default behaviour)
     */
    virtual ~Header() = default;

private:
    uint32_t size;
};

}
