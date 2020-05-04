project(Queue)

set(SOURCES Queue.cpp CountQueue.cpp)

add_library(Queue ${SOURCES})
target_link_libraries(Queue PRIVATE Packet)
