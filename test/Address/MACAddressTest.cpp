#include "lib/Address/MACAddress.h"
#include "gtest/gtest.h"

TEST(MACAddressTest, EqualsDiffClass)
{
    class CustomAddr : public trek::Address {
        std::string asString() override { return std::string(); }

        bool operator==(const trek::Address& rhs) const override {
            (void)rhs;
            return false;
        }
    };

    // Comparison between different address subclasses ==> not equal
    trek::MACAddress one(0xFFAABBCC);
    CustomAddr custom;
    ASSERT_FALSE(one == *(dynamic_cast<trek::Address*>(&custom)));
}

TEST(MACAddressTest, EqualsValue)
{
    trek::MACAddress one(0xFFAABBCC);
    trek::MACAddress two(one);
    ASSERT_TRUE(one == two);

    // Top bits are zero'd out -- equals should hold!
    trek::MACAddress three(0xEEEE0000FFAABBCC);
    ASSERT_TRUE(one == three);

    trek::MACAddress four(0xABC);
    ASSERT_FALSE(one == four);
}

TEST(MACAddressTest, AsString)
{
    trek::MACAddress one(0xAB);
    ASSERT_EQ(one.asString(), "00:00:00:00:00:ab");

    trek::MACAddress two(0xABCDEF);
    ASSERT_EQ(two.asString(), "00:00:00:ab:cd:ef");

    trek::MACAddress three(0xABCDEFAABBCC);
    ASSERT_EQ(three.asString(), "ab:cd:ef:aa:bb:cc");

    // Top bits are automatically zero'd out
    trek::MACAddress four(0xFF00ABCDEFAABBCC);
    ASSERT_EQ(four.asString(), "ab:cd:ef:aa:bb:cc");
}
