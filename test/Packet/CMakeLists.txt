project(PacketTest)

set(SOURCES PacketTest.cpp)
add_executable(PacketTest ${SOURCES})
target_link_libraries(PacketTest gtest gtest_main Packet Topology)

add_test(PacketTest COMMAND ./PacketTest)
