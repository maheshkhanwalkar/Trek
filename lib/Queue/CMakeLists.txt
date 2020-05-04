project(Queue)

set(SOURCES Queue.cpp CountQueue.cpp ByteQueue.cpp)

add_library(Queue ${SOURCES})
target_link_libraries(Queue PRIVATE Packet)
