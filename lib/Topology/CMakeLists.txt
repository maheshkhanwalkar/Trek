project(Topology)

set(SOURCES Node.cpp Link.cpp InstantLink.cpp CapacityLink.cpp)
add_library(Topology ${SOURCES})
