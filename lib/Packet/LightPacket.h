#pragma once
#include "Packet.h"

namespace trek {

/**
 * Light Packet
 *
 * This class represents a lightweight simulated packet, which is probably
 * sufficient for most statistics-based use cases.
 *
 * The packet itself tracks a total packet size (via Packet) and nothing else.
 *
 * There is no actual data attached to the packet, which makes the
 * implementation very fast, since there is no need to maintain a payload.
 */
class LightPacket : public Packet {
    explicit LightPacket(int id, uint32_t size, const Label& label);
    void drop() override;
};

}
