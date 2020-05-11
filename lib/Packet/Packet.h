#pragma once
#include <cstdint>
#include <memory>

#include "lib/Address/Address.h"
#include "lib/Packet/Header.h"

namespace trek {

/**
 * Packet
 *
 * This superclass represents a packet that can be transmitted
 * on the network.
 */
class Packet {

protected:
    /**
     * Create a new packet
     * @param id - packet id
     * @param size - overall packet size
     * @param src - source address
     * @param dest - destination address
     * @param hdr - packet header
     */
    explicit Packet(int id, uint32_t size, std::unique_ptr<Address> src,
                    std::unique_ptr<Address> dest, std::unique_ptr<Header> hdr);

public:
    /**
     * Get the source address
     * @return a const ref to the source address
     */
    const Address* getSrc() const;

    /**
     * Get the destination address
     * @return a const ref to the destination address
     */
    const Address* getDest() const;

    /**
     * Get the packet header
     * @return the header
     */
    const Header* getHeader() const;

    /**
     * Update the source address
     * @param n_src - new source
     */
    void updateSrc(std::unique_ptr<Address> n_src);

    /**
     * Update the destination address
     * @param n_dest - new destination
     */
    void updateDest(std::unique_ptr<Address> n_dest);

    /**
     * Update the packet header
     * @param n_hdr - new header
     */
    void updateHeader(std::unique_ptr<Header> n_hdr);

    /**
     * Get the size of the packet
     * @return the size
     */
    uint32_t getSize() const;


    virtual void drop() {}

    /**
     * Destroy the packet (default behaviour)
     */
    virtual ~Packet() = default;

protected:
    int id;
    uint32_t size;
    std::unique_ptr<Address> src, dest;
    std::unique_ptr<Header> header;
};

}
