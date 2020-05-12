project(Topology)

set(SOURCES Node.cpp)
add_library(Topology ${SOURCES})

target_link_libraries(Topology PRIVATE Packet Queue Link)
