project(HazelcastCClient)

cmake_minimum_required(VERSION 2.8)

# external paths
MESSAGE("HAZELCAST_CPP_CLIENT_HOME: " ${HAZELCAST_CPP_CLIENT_HOME})
MESSAGE("GTEST_HOME: "                ${GTEST_HOME})
MESSAGE("HAZELCAST_CPP_CLIENT_LIB: "  ${HAZELCAST_CPP_CLIENT_LIB})

# external dependencies
# marked as "SYSTEM" to ignore warnings from these header files
# see http://stackoverflow.com/questions/1867065/how-to-suppress-gcc-warnings-from-library-headers
include_directories(SYSTEM "${HAZELCAST_CPP_CLIENT_HOME}/external/include")
include_directories(SYSTEM "${HAZELCAST_CPP_CLIENT_HOME}/hazelcast/include")
include_directories(SYSTEM "${HAZELCAST_CPP_CLIENT_HOME}/hazelcast/generated-sources/include")

include_directories("${GTEST_HOME}/googletest/include")
include_directories("${GTEST_HOME}/googlemock/include")

link_directories("${HAZELCAST_CPP_CLIENT_HOME}/build")

link_directories("${GTEST_HOME}/build/googlemock/gtest")
link_directories("${GTEST_HOME}/build/googlemock")

# build
enable_testing()

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-pedantic -Wall -Wextra")

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-pedantic -Wall -Wextra")

# client lib
set(libSources src/hazelcast_c_client.cpp)

add_library(hazelcastCClient ${libSources})

target_link_libraries(hazelcastCClient pthread)
target_link_libraries(hazelcastCClient ${HAZELCAST_CPP_CLIENT_LIB})

# API test
set(testSources test/hazelcast_c_api_test.c)

add_executable(hazelcast_c_api_test ${testSources})
add_test(hazelcast_c_api_test hazelcast_c_api_test)

target_link_libraries(hazelcast_c_api_test hazelcastCClient)
target_link_libraries(hazelcast_c_api_test pthread)
target_link_libraries(hazelcast_c_api_test gmock)
target_link_libraries(hazelcast_c_api_test gtest)
