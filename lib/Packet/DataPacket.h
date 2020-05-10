#pragma once
#include "Packet.h"

#include <vector>

namespace trek {

class DataPacket : public Packet {
public:
    // TODO need to add Headers

    /**
     * Construct a data packet with a simulated payload
     *
     * This data packet does not actually contain any data, but instead
     * only simulates it via payload size (p_size)
     *
     * @param id - packet id
     * @param src - source address
     * @param dest - destination address
     * @param p_size - payload size
     */
    explicit DataPacket(int id, std::unique_ptr<Address> src,
                        std::unique_ptr<Address> dest, uint32_t p_size);

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
                        std::unique_ptr<Address> dest, uint32_t p_size,
                        std::vector<char>&& data);

private:
    std::vector<char> data;
};

}
