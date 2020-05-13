project(LinkTest)

set(SOURCES LinkTest.cpp)
add_executable(LinkTest ${SOURCES})

target_link_libraries(LinkTest gtest gtest_main Link Topology)
add_test(NAME LinkTest COMMAND ./LinkTest)
