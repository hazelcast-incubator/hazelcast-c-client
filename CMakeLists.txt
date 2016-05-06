project(HazelcastCClient)

cmake_minimum_required(VERSION 2.8)

MESSAGE("HAZELCAST_CPP_CLIENT_HOME: " ${HAZELCAST_CPP_CLIENT_HOME})

include_directories("${HAZELCAST_CPP_CLIENT_HOME}/external/include")
include_directories("${HAZELCAST_CPP_CLIENT_HOME}/hazelcast/include")
include_directories("${HAZELCAST_CPP_CLIENT_HOME}/hazelcast/generated-sources/include")

link_directories("${HAZELCAST_CPP_CLIENT_HOME}/build")


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

set(libSources hazelcast_c_client.cpp)
set(testSources hazelcast_c_client_test.c)

add_library(hazelcastCClient ${libSources})
add_executable(hazelcastCClientTest ${testSources})

# @TODO create env variable for hazelcast lib?
#HazelcastClient3.7-SNAPSHOT_64.a
target_link_libraries(hazelcastCClient pthread)
target_link_libraries(hazelcastCClient ${HAZELCAST_CPP_CLIENT_LIB})

target_link_libraries(hazelcastCClientTest hazelcastCClient)
