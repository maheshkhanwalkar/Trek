#pragma once
#include "Packet.h"

#include <vector>

namespace trek {

class DataPacket : public Packet {
public:
    /**
     * Construct a data packet with a simulated payload
     *
     * This data packet does not actually contain any data, but instead
     * only simulates it via payload size (p_size)
     *
     * @param id - packet id
     * @param src - source address
     * @param dest - destination address
     * @param header - packet header
     * @param p_size - payload size
     */
    explicit DataPacket(int id, std::unique_ptr<Address> src,
                        std::unique_ptr<Address> dest,
                        std::unique_ptr<Header> header, uint32_t p_size);

    /**
     * Construct a data packet with an actual payload
     *
     * There is a real payload represented as a vector<char> which can be
     * interpreted directly or converted to a string if using non-binary data.
     *
     * @param id - packet id
     * @param src - source address
     * @param dest - destination address
     * @param p_size - payload size
     * @param data - payload data
     */
    explicit DataPacket(int id, std::unique_ptr<Address> src,
                        std::unique_ptr<Address> dest,
                        std::unique_ptr<Header> header,
                        std::vector<char>&& data);

    /**
     * Check whether the packet has a real payload
     * @return true if it does, false otherwise
     */
    bool hasRealPayload() const;


    /**
     * Return the string representation of the payload
     * @return the equivalent string
     */
    const std::string& payloadAsStr() const;

private:
    std::vector<char> data;
    std::string equiv;
};

}
