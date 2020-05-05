#include "gtest/gtest.h"
#include "lib/Topology/Node.h"

TEST(Node, BasicCreation)
{
    trek::Node node(0, true, nullptr);

    ASSERT_TRUE(node.isRouter());
    ASSERT_EQ(node.getID(), 0);
}

