#include "lib/Link/Link.h"
#include "lib/Link/CapacityLink.h"
#include "lib/Link/InstantLink.h"
#include "lib/Packet/DataPacket.h"
#include "gtest/gtest.h"

static inline trek::Node* make_node(int id, bool router)
{
    std::unique_ptr<trek::Queue> queue(new trek::Queue);
    auto* node = new trek::Node(id, router, std::move(queue));

    return node;
}

static inline trek::Packet* make_packet(uint32_t size = 100)
{
    return new trek::DataPacket(0, nullptr, nullptr, nullptr, size);
}

TEST(InstantLinkTest, SingleBusyLink)
{
    std::shared_ptr<trek::Node> first(make_node(0, false));
    std::shared_ptr<trek::Node> second(make_node(1, false));

    trek::Link* link = new trek::InstantLink(first.get(), second.get(), false);

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

    trek::Link* link = new trek::InstantLink(first.get(), second.get(), true);

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
    trek::Link* link = new trek::CapacityLink(first.get(), second.get(), true,1024*8, 1);

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

TEST(CapacityLinkTest, DuplexTest)
{
    std::shared_ptr<trek::Node> first(make_node(0, false));
    std::shared_ptr<trek::Node> second(make_node(1, false));

    // Throughput is in bits per second, but packet size is in bytes
    // Simulation time slice is 1 sec
    trek::Link* link = new trek::CapacityLink(first.get(), second.get(), true, 1024*8, 1);

    ASSERT_FALSE(link->isBusy(first.get()));
    ASSERT_FALSE(link->isBusy(second.get()));

    link->initiate(first.get(), std::unique_ptr<trek::Packet>(make_packet(2*1024+1)));
    ASSERT_TRUE(link->isBusy(first.get()));
    ASSERT_FALSE(link->isBusy(second.get()));

    link->initiate(second.get(), std::unique_ptr<trek::Packet>(make_packet(2*1024-7)));
    ASSERT_TRUE(link->isBusy(first.get()));
    ASSERT_TRUE(link->isBusy(second.get()));

    link->transfer();
    ASSERT_TRUE(link->isBusy(first.get()));
    ASSERT_TRUE(link->isBusy(second.get()));

    link->transfer();
    ASSERT_TRUE(link->isBusy(first.get()));
    ASSERT_FALSE(link->isBusy(second.get()));

    link->transfer();
    ASSERT_FALSE(link->isBusy(first.get()));
    ASSERT_FALSE(link->isBusy(second.get()));

    delete link;
}
