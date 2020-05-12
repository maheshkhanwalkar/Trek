project(Packet)

set(SOURCES Packet.cpp DataPacket.cpp NestedPacket.cpp)
add_library(Packet ${SOURCES})
target_link_libraries(Packet PRIVATE Address Header)
