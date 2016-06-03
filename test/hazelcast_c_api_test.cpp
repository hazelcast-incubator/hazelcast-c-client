#include <stdlib.h>
#include <string.h>

#include "hazelcast_c_client.h"

#include "gtest/gtest.h"

#define HAZELCAST_TEST_SERVER_HOST "127.0.0.1"
#define HAZELCAST_TEST_SERVER_PORT 5701

#define TEST_MAP_NAME "test-map"

TEST(CClientAPI, MapStringzKeyNotFound)
{
    char *errPtr = NULL;

    // client setup
    Hazelcast_ClientConfig_t *clientConfig = Hazelcast_ClientConfig_create();
    Hazelcast_ClientConfig_addAddress(clientConfig, HAZELCAST_TEST_SERVER_HOST, HAZELCAST_TEST_SERVER_PORT);
    Hazelcast_ClientConfig_setLogLevel(clientConfig, HAZELCAST_LOG_LEVEL_SEVERE);

    Hazelcast_Client_t *client = Hazelcast_Client_create(clientConfig, &errPtr);
    ASSERT_STREQ(errPtr, NULL) << "Client create failed.";

    // key not contained
    const char *unknownKey = "unknown key";
    Hazelcast_Data_t *unknownKeyData = Hazelcast_Serialization_stringToData(
        client,
        unknownKey,
        strlen(unknownKey)
    );

    int keyExists = Hazelcast_Map_containsKey(client, TEST_MAP_NAME, unknownKeyData, &errPtr);
    ASSERT_STREQ(errPtr, NULL) << "Failed to check if key is contained in map.";
    ASSERT_EQ(keyExists, 0) << "Key was not stored in map.";

    Hazelcast_Data_t *nullData = Hazelcast_Map_get(client, TEST_MAP_NAME, unknownKeyData, &errPtr);
    ASSERT_STREQ(errPtr, NULL) << "Failed to get NULL key from map.";
    ASSERT_EQ(NULL, nullData) << "Key was not expected to be found in map.";

    // cleanup
    Hazelcast_Client_destroy(client);
    Hazelcast_ClientConfig_destroy(clientConfig);

    Hazelcast_resetError(errPtr);
}

TEST(CClientAPI, MapFunctionsWithStringData)
{
    char *errPtr = NULL;

    const char *rawKey = "map_key";
    Hazelcast_Data_t *keyData = NULL;

    const char *rawValue = "map_value";
    Hazelcast_Data_t *valueData = NULL;

    Hazelcast_Data_t *storedData = NULL;

    // client setup
    Hazelcast_ClientConfig_t *clientConfig = Hazelcast_ClientConfig_create();
    Hazelcast_ClientConfig_addAddress(clientConfig, HAZELCAST_TEST_SERVER_HOST, HAZELCAST_TEST_SERVER_PORT);
    Hazelcast_ClientConfig_setLogLevel(clientConfig, HAZELCAST_LOG_LEVEL_SEVERE);

    Hazelcast_Client_t *client = Hazelcast_Client_create(clientConfig, &errPtr);
    ASSERT_STREQ(errPtr, NULL) << "Client create failed.";

    // serialize key and value into Data object
    keyData = Hazelcast_Serialization_stringToData(client, rawKey, strlen(rawKey));
    valueData = Hazelcast_Serialization_stringToData(client, rawValue, strlen(rawValue));

    // save new key/value pair
    Hazelcast_Map_set(client, TEST_MAP_NAME, keyData, valueData, 0, &errPtr);
    ASSERT_STREQ(errPtr, NULL) << "Failed to store key/value pair in map.";

    // check if key exists in map
    int keyExists = Hazelcast_Map_containsKey(client, TEST_MAP_NAME, keyData, &errPtr);
    ASSERT_STREQ(errPtr, NULL) << "Failed to check if key is contained in map.";
    ASSERT_EQ(keyExists, 1) << "Key was not stored in map.";

    // check map size
    int mapSize = Hazelcast_Map_size(client, TEST_MAP_NAME, &errPtr);
    ASSERT_GT(mapSize, 0) << "No values found in map.";


    storedData = Hazelcast_Map_get(client, TEST_MAP_NAME, keyData, &errPtr);
    ASSERT_STREQ(errPtr, NULL) << "Failed to check if key is contained in map.";

    char *storedValue = Hazelcast_Serialization_dataToString(client, storedData);
    ASSERT_STREQ(storedValue, rawValue) << "Expected value is not equal to stored value.";

    free(storedValue);

    // remove key
    Hazelcast_Map_delete(client, TEST_MAP_NAME, keyData, &errPtr);
    ASSERT_STREQ(errPtr, NULL) << "Failed to delete key from map.";

    // cleanup
    Hazelcast_Data_destroy(keyData);
    Hazelcast_Data_destroy(valueData);
    Hazelcast_Data_destroy(storedData);

    Hazelcast_Client_destroy(client);
    Hazelcast_ClientConfig_destroy(clientConfig);

    Hazelcast_resetError(errPtr);
}

GTEST_API_ int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
