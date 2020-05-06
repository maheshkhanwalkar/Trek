project(Topology)

set(SOURCES Node.cpp Link.cpp InstantLink.cpp CapacityLink.cpp)
add_library(Topology ${SOURCES})

target_link_libraries(Topology PRIVATE Packet Queue)
