project(Queue)

set(SOURCES Queue.cpp)

add_library(Queue ${SOURCES})
target_link_libraries(Queue PRIVATE Packet)