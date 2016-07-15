project(HazelcastCClient)

cmake_minimum_required(VERSION 3.1)

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
include(CTest)

if(UNIX)
    set(CTEST_MEMORYCHECK_COMMAND, "valgrind")
    set(CTEST_MEMORYCHECK_COMMAND_OPTIONS, "--trace-children=yes --leak-check=full")
endif()

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra -Wno-deprecated-declarations")

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-pedantic -Wall -Wextra")

# client util lib
set(libUtilSources
    src/hazelcast_c_client/util/string.cpp
    src/hazelcast_c_client/util/errorhandling.cpp
)

add_library(hazelcastCClientUtil SHARED ${libUtilSources})

# client lib
set(libSources
    src/hazelcast_c_client/client/client_c_api.cpp
    src/hazelcast_c_client/map/RawDataIMapImpl.hpp
    src/hazelcast_c_client/map/map_c_api.cpp
    src/hazelcast_c_client/serialization/serialization_c_api.cpp
)

add_library(hazelcastCClient SHARED ${libSources})

target_link_libraries(hazelcastCClient pthread)
target_link_libraries(hazelcastCClient ${HAZELCAST_CPP_CLIENT_LIB})
target_link_libraries(hazelcastCClient hazelcastCClientUtil)

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

# test - util
add_executable(hazelcast_util_test test/hazelcast_util_test.cpp)
add_test(hazelcast_util_test hazelcast_util_test)

target_link_libraries(hazelcast_util_test hazelcastCClientUtil)
target_link_libraries(hazelcast_util_test pthread)
target_link_libraries(hazelcast_util_test gmock)
target_link_libraries(hazelcast_util_test gtest)
