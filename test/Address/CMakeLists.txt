project(AddressTest)

set(SOURCES MACAddressTest.cpp IPv4AddressTest.cpp)
add_executable(AddressTest ${SOURCES})
target_link_libraries(AddressTest gtest gtest_main Address)

add_test(NAME AddressTest COMMAND ./AddressTest)
