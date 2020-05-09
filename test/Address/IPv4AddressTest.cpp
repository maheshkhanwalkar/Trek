#include "gtest/gtest.h"
#include "lib/Address/IPv4Address.h"

TEST(IPv4AddressTest, EqualsDiffClass)
{
    class CustomAddr : public trek::Address {
        std::string asString() const override { return std::string(); }

        bool operator==(const trek::Address& rhs) const override {
            (void)rhs;
            return false;
        }
    };

    // Comparison between different address subclasses ==> not equal
    trek::IPv4Address one("10.0.0.1");
    CustomAddr custom;
    ASSERT_FALSE(one == *(dynamic_cast<trek::Address*>(&custom)));
}

TEST(IPv4AddressTest, EqualsValue)
{
    trek::IPv4Address one("10.0.0.1");
    trek::IPv4Address two(0x0A000001);
    ASSERT_TRUE(one == two);

    trek::IPv4Address three(0xFF000C24);
    trek::IPv4Address four("255.0.12.36");
    ASSERT_TRUE(three == four);
}

TEST(IPv4AddressTest, AsString)
{
    trek::IPv4Address one(0xFF10BF77);
    ASSERT_TRUE(one.asString() == "255.16.191.119");

    trek::IPv4Address two(0);
    ASSERT_TRUE(two.asString() == "0.0.0.0");

    trek::IPv4Address three("10.0.55.37");
    ASSERT_TRUE(three.asString() == "10.0.55.37");
}
