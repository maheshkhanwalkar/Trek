project(QueueTest)

set(SOURCES QueueTest.cpp)
add_executable(QueueTest ${SOURCES})
target_link_libraries(QueueTest gtest gtest_main Queue)

add_test(NAME QueueTest COMMAND ./QueueTest)
