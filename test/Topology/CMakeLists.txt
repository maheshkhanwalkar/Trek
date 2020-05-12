project(TopologyTest)

set(SOURCES NodeTest.cpp)
add_executable(TopologyTest ${SOURCES})

target_link_libraries(TopologyTest gtest gtest_main Topology)
add_test(TopologyTest COMMAND ./TopologyTest)
