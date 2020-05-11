#include "lib/Address/Address.h"
#include "lib/Address/IPv4Address.h"
#include "lib/Packet/Packet.h"
#include "lib/Packet/DataPacket.h"

#include "gtest/gtest.h"

/**
 * Make an IP address
 * @param ip - string representation
 * @return the address instance
 */
static std::unique_ptr<trek::Address> make_addr(std::string ip)
{
    std::unique_ptr<trek::Address> ptr(new trek::IPv4Address(ip));
    return ptr;
}

TEST(PacketTest, BasicCreation)
{
    trek::Packet* pkt = new trek::DataPacket(0, make_addr("10.0.0.1"),
        make_addr("10.0.0.2"), nullptr, 10U);

    ASSERT_EQ(pkt->getSize(), 10U);
    ASSERT_EQ(*pkt->getSrc(), *make_addr("10.0.0.1"));
    ASSERT_EQ(*pkt->getDest(), *make_addr("10.0.0.2"));

    const auto* d_pkt = dynamic_cast<trek::DataPacket*>(pkt);
    ASSERT_FALSE(d_pkt->hasRealPayload());

    d_pkt = nullptr;
    delete pkt;
}

TEST(PacketTest, LabelUpdate)
{
    trek::Packet* pkt = new trek::DataPacket(0, make_addr("10.0.0.1"),
          make_addr("10.0.0.2"), nullptr, 10U);

    ASSERT_EQ(*pkt->getSrc(), *make_addr("10.0.0.1"));
    ASSERT_EQ(*pkt->getDest(), *make_addr("10.0.0.2"));

    pkt->updateSrc(make_addr("192.168.1.10"));
    pkt->updateDest(make_addr("192.168.1.20"));

    ASSERT_EQ(*pkt->getSrc(), *make_addr("192.168.1.10"));
    ASSERT_EQ(*pkt->getDest(), *make_addr("192.168.1.20"));
    ASSERT_EQ(pkt->getHeader(), nullptr);
    ASSERT_EQ(pkt->getSize(), 10U);

    delete pkt;
}

TEST(PacketTest, DataPacket)
{
    std::vector<char> data;
    std::string msg("hello world");

    for(char& i : msg)
        data.emplace_back(i);

    trek::Packet* pkt = new trek::DataPacket(0, make_addr("10.0.0.1"),
         make_addr("10.0.0.2"), nullptr, std::move(data));

    ASSERT_EQ(pkt->getSize(), msg.size());

    const auto* d_pkt = dynamic_cast<trek::DataPacket*>(pkt);
    ASSERT_EQ(d_pkt->payloadAsStr(), msg);

    d_pkt = nullptr;
    delete pkt;
}
