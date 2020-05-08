project(AddressTest)

set(SOURCES MACAddressTest.cpp)
add_executable(AddressTest ${SOURCES})
target_link_libraries(AddressTest gtest gtest_main Address)

add_test(AddressTest COMMAND ./AddressTest)
