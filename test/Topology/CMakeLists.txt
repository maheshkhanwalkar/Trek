project(NodeTest)

set(SOURCES NodeTest.cpp)
add_executable(NodeTest ${SOURCES})

target_link_libraries(NodeTest gtest gtest_main Topology)
add_test(NodeTest COMMAND ./NodeTest)
