#pragma once
#include "Packet.h"

#include <vector>
#include <string>

namespace trek {

class DataPacket : public Packet {

public:
    /**
     * Initialise a data-carrying packet
     * @param id - packet id
     * @param payload - payload data
     * @param label - packet label
     */
    explicit DataPacket(int id, const std::vector<char>& payload, const Label& label);


    void drop() override;

    /**
     * Get the raw payload data
     * @return the data in a const vector format
     */
    const std::vector<char>& getPayload() const;

    /**
     * Get the payload data as a string
     * @return the equivalent string representation
     */
    const std::string& payloadAsStr() const;

private:
    const std::vector<char> payload;
    const std::string p_str;
};

}