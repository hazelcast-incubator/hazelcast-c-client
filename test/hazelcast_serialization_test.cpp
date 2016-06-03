// Copyright 2016, Max Beutel

#include <assert.h>

#include "hazelcast_c_client/hazelcast_c_client.h"

#include "gtest/gtest.h"

#define HAZELCAST_TEST_SERVER_HOST "127.0.0.1"
#define HAZELCAST_TEST_SERVER_PORT 5701

#define TEST_STRING "test string"
#define TEST_STRING_LEN strlen(TEST_STRING)

#define TEST_INT 123456

TEST(Serialization, StringSerialization) {
    char *errPtr = NULL;

    // client setup
    Hazelcast_ClientConfig_t *clientConfig = Hazelcast_ClientConfig_create();
    Hazelcast_ClientConfig_addAddress(clientConfig, HAZELCAST_TEST_SERVER_HOST, HAZELCAST_TEST_SERVER_PORT);
    Hazelcast_ClientConfig_setLogLevel(clientConfig, HAZELCAST_LOG_LEVEL_SEVERE);

    Hazelcast_Client_t *client = Hazelcast_Client_create(clientConfig, &errPtr);
    assert(client != NULL && "Client create failed.");

    // serialization
    Hazelcast_Data_t *data = Hazelcast_Serialization_stringToData(client, TEST_STRING, TEST_STRING_LEN);
    assert(data != NULL && "Expected serialization to return data.");

    char *deserializedString = Hazelcast_Serialization_dataToString(client, data);
    ASSERT_STREQ(deserializedString, TEST_STRING);
    free(deserializedString);

    // cleanup
    Hazelcast_Data_destroy(data);

    Hazelcast_Client_destroy(client);
    Hazelcast_ClientConfig_destroy(clientConfig);

    Hazelcast_resetError(errPtr);
}

TEST(Serialization, IntSerialization) {
    char *errPtr = NULL;

    // client setup
    Hazelcast_ClientConfig_t *clientConfig = Hazelcast_ClientConfig_create();
    Hazelcast_ClientConfig_addAddress(clientConfig, HAZELCAST_TEST_SERVER_HOST, HAZELCAST_TEST_SERVER_PORT);
    Hazelcast_ClientConfig_setLogLevel(clientConfig, HAZELCAST_LOG_LEVEL_SEVERE);

    Hazelcast_Client_t *client = Hazelcast_Client_create(clientConfig, &errPtr);
    assert(client != NULL && "Client create failed.");

    // serialization
    Hazelcast_Data_t *data = Hazelcast_Serialization_intToData(client, TEST_INT);
    assert(data != NULL && "Expected serialization to return data.");

    int deserializedInt = Hazelcast_Serialization_dataToInt(client, data);
    ASSERT_EQ(deserializedInt, TEST_INT);

    // cleanup
    Hazelcast_Data_destroy(data);

    Hazelcast_Client_destroy(client);
    Hazelcast_ClientConfig_destroy(clientConfig);

    Hazelcast_resetError(errPtr);
}

GTEST_API_ int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
