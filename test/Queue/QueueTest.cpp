#include "lib/Queue/Queue.h"
#include "lib/Queue/CountQueue.h"
#include "lib/Queue/ByteQueue.h"
#include "lib/Packet/LightPacket.h"

#include "gtest/gtest.h"

TEST(QueueTest, BaseQueue)
{
    trek::Queue* queue = new trek::Queue;
    int count = 1000;

    for(int i = 0; i < count; i++) {
        trek::Label label{};
        uint32_t size = static_cast<uint32_t>(2*i + 1);

        std::unique_ptr<trek::Packet> pkt(
            new trek::LightPacket(i, size, label));

        queue->push_back(std::move(pkt));
    }

    ASSERT_EQ(queue->size(), count);

    for(int i = 0; i < count; i++) {
        const trek::Packet& pkt = queue->peek();

        ASSERT_EQ(pkt.getSize(), 2*i+1);
        ASSERT_EQ(pkt.getLabel().src, nullptr);
        ASSERT_EQ(pkt.getLabel().dest, nullptr);

        queue->pop_front();
        ASSERT_EQ(queue->size(), count - i - 1);
    }

    delete queue;
}

TEST(QueueTest, CountQueue)
{
    size_t count = 25;
    trek::Queue* queue = new trek::CountQueue(count);

    unsigned int over = 1000;

    for(unsigned int i = 0; i < over; i++) {
        trek::Label label{};
        uint32_t size = static_cast<uint32_t>(2*i + 1);

        std::unique_ptr<trek::Packet> pkt(
            new trek::LightPacket(static_cast<int>(i), size, label));

        queue->push_back(std::move(pkt));
    }

    ASSERT_NE(queue->size(), over);
    ASSERT_EQ(queue->size(), count);

    unsigned int small = 7;

    for(unsigned int i = 0; i < small; i++) {
        const trek::Packet& pkt = queue->peek();

        ASSERT_EQ(pkt.getSize(), 2*i+1);
        ASSERT_EQ(pkt.getLabel().src, nullptr);
        ASSERT_EQ(pkt.getLabel().dest, nullptr);

        queue->pop_front();
        ASSERT_EQ(queue->size(), count - i - 1);
    }

    unsigned int more = small + 3;
    for(unsigned int i = over; i < over + more; i++) {
        trek::Label label{};
        uint32_t size = static_cast<uint32_t>(2*i + 1);

        std::unique_ptr<trek::Packet> pkt(
            new trek::LightPacket(static_cast<int>(i), size, label));

        queue->push_back(std::move(pkt));
    }

    ASSERT_NE(queue->size(), count + (more - small));
    ASSERT_EQ(queue->size(), count);

    delete queue;
}

TEST(QueueTest, ByteQueue)
{
    uint64_t b_max = 1024;
    trek::Queue* queue = new trek::ByteQueue(b_max);

    int amt = static_cast<int>(b_max);

    for(int i = 0; i < amt; i++) {
        trek::Label label{};
        uint32_t size = 1;

        std::unique_ptr<trek::Packet> pkt(
            new trek::LightPacket(i, size, label));

        queue->push_back(std::move(pkt));
    }

    ASSERT_EQ(queue->size(), b_max);
    queue->clear();
    ASSERT_EQ(queue->size(), 0);

    for(int i = 0; i < amt; i++) {
        trek::Label label{};
        uint32_t size = 2;

        std::unique_ptr<trek::Packet> pkt(
            new trek::LightPacket(i, size, label));

        queue->push_back(std::move(pkt));
    }

    ASSERT_NE(queue->size(), b_max);
    ASSERT_EQ(queue->size(), b_max / 2);

    queue->clear();

    trek::Label label{};

    queue->push_back(std::unique_ptr<trek::Packet>(
        new trek::LightPacket(0, 12, label)));
    queue->push_back(std::unique_ptr<trek::Packet>(
        new trek::LightPacket(1, b_max - 12, label)));
    ASSERT_EQ(queue->size(), 2);

    queue->pop_front();
    ASSERT_EQ(queue->size(), 1);

    queue->push_back(std::unique_ptr<trek::Packet>(
        new trek::LightPacket(2, 13, label)));
    ASSERT_EQ(queue->size(), 1);

    delete queue;
}
