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

# build settings
enable_testing()

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-pedantic -Wall -Wextra")

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-pedantic -Wall -Wextra")

# client lib
set(libSources src/hazelcast_c_client/client/client_c_api.cpp
    src/hazelcast_c_client/map/RawDataIMapImpl.hpp
    src/hazelcast_c_client/map/map_c_api.cpp
    src/hazelcast_c_client/serialization/serialization_c_api.cpp
    src/hazelcast_c_client/util/errorhandling.cpp)

add_library(hazelcastCClient ${libSources})

target_link_libraries(hazelcastCClient pthread)
target_link_libraries(hazelcastCClient ${HAZELCAST_CPP_CLIENT_LIB})

# test - map API
add_executable(hazelcast_map_api_test test/hazelcast_map_api_test.cpp)
add_test(hazelcast_map_api_test hazelcast_map_api_test)

target_link_libraries(hazelcast_map_api_test hazelcastCClient)
target_link_libraries(hazelcast_map_api_test pthread)
target_link_libraries(hazelcast_map_api_test gmock)
target_link_libraries(hazelcast_map_api_test gtest)

# test - serialization
add_executable(hazelcast_serialization_test test/hazelcast_serialization_test.cpp)
add_test(hazelcast_serialization_test hazelcast_serialization_test)

target_link_libraries(hazelcast_serialization_test hazelcastCClient)
target_link_libraries(hazelcast_serialization_test pthread)
target_link_libraries(hazelcast_serialization_test gmock)
target_link_libraries(hazelcast_serialization_test gtest)
