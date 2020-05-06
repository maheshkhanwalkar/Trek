#include "lib/Packet/Packet.h"
#include "lib/Packet/LightPacket.h"
#include "lib/Packet/DataPacket.h"
#include "lib/Topology/Node.h"

#include "gtest/gtest.h"
#include <string>

TEST(PacketTest, BasicCreation)
{
    const trek::Label label{};
    trek::Packet* pkt = new trek::LightPacket(0, 10, label);

    ASSERT_EQ(pkt->getSize(), 10U);
    ASSERT_EQ(pkt->getLabel().src.lock(), label.src.lock());
    ASSERT_EQ(pkt->getLabel().dest.lock(), label.dest.lock());

    delete pkt;
}

TEST(PacketTest, LabelUpdate)
{
    const trek::Label label{};
    trek::Packet* pkt = new trek::LightPacket(0, 10, label);

    std::shared_ptr<trek::Node> start(new trek::Node(0, false, nullptr));
    std::shared_ptr<trek::Node> end(new trek::Node(1, true, nullptr));

    trek::Label n_label;

    n_label.src = start;
    n_label.dest = end;
    pkt->setLabel(n_label);

    ASSERT_EQ(pkt->getSize(), 10U);
    ASSERT_EQ(pkt->getLabel().src.lock(), n_label.src.lock());
    ASSERT_EQ(pkt->getLabel().dest.lock(), n_label.dest.lock());
}

TEST(PacketTest, DataPacket)
{
    const trek::Label label{};

    std::vector<char> data;
    std::string msg("hello world");

    for(size_t i = 0; i < msg.size(); i++)
        data.emplace_back(msg.at(i));

    trek::Packet* pkt = new trek::DataPacket(0, std::move(data), label);
    ASSERT_EQ(pkt->getSize(), msg.size());

    trek::DataPacket* d_pkt = dynamic_cast<trek::DataPacket*>(pkt);
    ASSERT_EQ(d_pkt->payloadAsStr(), msg);

    d_pkt = nullptr;
    delete pkt;
}
