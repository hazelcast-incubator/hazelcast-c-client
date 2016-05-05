project(HazelcastCClient)

cmake_minimum_required(VERSION 2.8)

# if (DEFINED ENV{GTEST_HOME})
#   set(GTEST_HOME $ENV{GTEST_HOME})
# else()
#   set(GTEST_HOME "/Users/max/Documents/playground/cpp/googletest-master")
# endif()

# MESSAGE("GTEST_HOME: " ${GTEST_HOME})

if (DEFINED ENV{HAZELCAST_CPP_CLIENT_HOME})
  set(HAZELCAST_CPP_CLIENT_HOME $ENV{HAZELCAST_CPP_CLIENT_HOME})
else()
  set(HAZELCAST_CPP_CLIENT_HOME "/Users/max/Documents/playground/cpp/hazelcast-cpp-client")
endif()

MESSAGE("HAZELCAST_CPP_CLIENT_HOME: " ${HAZELCAST_CPP_CLIENT_HOME})


# include_directories("${GTEST_HOME}/googletest/include")
# include_directories("${GTEST_HOME}/googlemock/include")

# link_directories("${GTEST_HOME}/build/googlemock/gtest")
# link_directories("${GTEST_HOME}/build/googlemock")

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
target_link_libraries(hazelcastCClient HazelcastClient3.7-SNAPSHOT_64.a)

target_link_libraries(hazelcastCClientTest hazelcastCClient)
# target_link_libraries(hazelcastCClientTest pthread)
# target_link_libraries(hazelcastCClientTest gmock)
# target_link_libraries(hazelcastCClientTest gtest)
