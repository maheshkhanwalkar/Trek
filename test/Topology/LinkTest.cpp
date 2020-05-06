#include "gtest/gtest.h"
#include "lib/Topology/Link.h"
#include "lib/Topology/InstantLink.h"
#include "lib/Topology/CapacityLink.h"
#include "lib/Packet/LightPacket.h"

trek::Node* make_node(int id, bool router)
{
    std::unique_ptr<trek::Queue> queue(new trek::Queue);
    trek::Node* node = new trek::Node(id, router, std::move(queue));

    return node;
}

trek::Packet* make_packet(uint32_t size = 100)
{
    trek::Label label{};
    trek::Packet* pkt = new trek::LightPacket(0, size, label);

    return pkt;
}

TEST(InstantLinkTest, SingleBusyLink)
{
    std::shared_ptr<trek::Node> first(make_node(0, false));
    std::shared_ptr<trek::Node> second(make_node(1, false));

    trek::Link* link = new trek::InstantLink(first, second, false);

    ASSERT_FALSE(link->isBusy(first.get()));
    ASSERT_FALSE(link->isBusy(second.get()));

    link->initiate(first.get(), std::unique_ptr<trek::Packet>(make_packet()));

    ASSERT_TRUE(link->isBusy(first.get()));
    ASSERT_TRUE(link->isBusy(second.get()));

    link->transfer();

    ASSERT_FALSE(link->isBusy(first.get()));
    ASSERT_FALSE(link->isBusy(second.get()));

    delete link;
}

TEST(InstantLinkTest, DuplexBusyLink)
{
    std::shared_ptr<trek::Node> first(make_node(0, false));
    std::shared_ptr<trek::Node> second(make_node(1, false));

    trek::Link* link = new trek::InstantLink(first, second, true);

    ASSERT_FALSE(link->isBusy(first.get()));
    ASSERT_FALSE(link->isBusy(second.get()));

    link->initiate(first.get(), std::unique_ptr<trek::Packet>(make_packet()));

    ASSERT_TRUE(link->isBusy(first.get()));
    ASSERT_FALSE(link->isBusy(second.get()));

    link->transfer();

    ASSERT_FALSE(link->isBusy(first.get()));
    ASSERT_FALSE(link->isBusy(second.get()));

    link->initiate(second.get(), std::unique_ptr<trek::Packet>(make_packet()));

    ASSERT_FALSE(link->isBusy(first.get()));
    ASSERT_TRUE(link->isBusy(second.get()));

    link->transfer();

    ASSERT_FALSE(link->isBusy(first.get()));
    ASSERT_FALSE(link->isBusy(second.get()));

    delete link;
}

TEST(CapacityLinkTest, CapacityCheck)
{
    std::shared_ptr<trek::Node> first(make_node(0, false));
    std::shared_ptr<trek::Node> second(make_node(1, false));

    // Throughput is in bits per second, but packet size is in bytes
    // Simulation time slice is 1 sec
    trek::Link* link = new trek::CapacityLink(first, second, true, 1024*8, 1);

    ASSERT_FALSE(link->isBusy(first.get()));
    ASSERT_FALSE(link->isBusy(second.get()));

    link->initiate(first.get(), std::unique_ptr<trek::Packet>(make_packet(2*1024+1)));
    ASSERT_TRUE(link->isBusy(first.get()));

    link->transfer();
    ASSERT_TRUE(link->isBusy(first.get()));

    link->transfer();
    ASSERT_TRUE(link->isBusy(first.get()));

    link->transfer();
    ASSERT_FALSE(link->isBusy(first.get()));

    delete link;
}
