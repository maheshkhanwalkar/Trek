#include "lib/Packet/Packet.h"
#include "lib/Packet/LightPacket.h"
#include "lib/Packet/DataPacket.h"
#include "lib/Topology/Node.h"

#include "gtest/gtest.h"

TEST(PacketTest, BasicCreation)
{
    const trek::Label label{};
    trek::Packet* pkt = new trek::LightPacket(0, 10, label);

    ASSERT_EQ(pkt->getSize(), 10U);
    ASSERT_EQ(pkt->getLabel().src, label.src);
    ASSERT_EQ(pkt->getLabel().dest, label.dest);

    delete pkt;
}

TEST(PacketTest, LabelUpdate)
{
    const trek::Label label{};
    trek::Packet* pkt = new trek::LightPacket(0, 10, label);

    std::shared_ptr<trek::Node> start(new trek::Node(0, false, nullptr));
    std::shared_ptr<trek::Node> end(new trek::Node(1, true, nullptr));

    trek::Label n_label{};

    n_label.src = start.get();
    n_label.dest = end.get();
    pkt->setLabel(n_label);

    ASSERT_EQ(pkt->getSize(), 10U);
    ASSERT_EQ(pkt->getLabel().src, n_label.src);
    ASSERT_EQ(pkt->getLabel().dest, n_label.dest);
}

TEST(PacketTest, DataPacket)
{
    const trek::Label label{};

    std::vector<char> data;
    std::string msg("hello world");

    for(char& i : msg)
        data.emplace_back(i);

    trek::Packet* pkt = new trek::DataPacket(0, std::move(data), label);
    ASSERT_EQ(pkt->getSize(), msg.size());

    auto* d_pkt = dynamic_cast<trek::DataPacket*>(pkt);
    ASSERT_EQ(d_pkt->payloadAsStr(), msg);

    d_pkt = nullptr;
    delete pkt;
}
