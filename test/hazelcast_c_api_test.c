#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "hazelcast_c_client.h"

#define TEST_MAP_NAME "test-map"

int main(void)
{
    char *errPtr = NULL;

    const char *rawKey = "map_key";
    Hazelcast_Data_t *keyData = NULL;

    const char *rawValue = "map_value";
    Hazelcast_Data_t *valueData = NULL;

    Hazelcast_Data_t *storedData = NULL;

    Hazelcast_ClientConfig_t *clientConfig = Hazelcast_ClientConfig_create();
    assert(clientConfig != NULL);

    Hazelcast_ClientConfig_add_address(clientConfig, "127.0.0.1", 5701);

    Hazelcast_Client_t *client = Hazelcast_Client_create(clientConfig, &errPtr);
    assert(client != NULL);

    if (errPtr != NULL) {
        printf("### ERR Client create failed: %s\n", errPtr);

        goto cleanup;
    }

    // serialize key and value into Data object
    keyData = Hazelcast_Serialization_stringToData(client, rawKey, strlen(rawKey));
    valueData = Hazelcast_Serialization_stringToData(client, rawValue, strlen(rawValue));

    // save new key/value pair
    Hazelcast_Map_set(client, TEST_MAP_NAME, keyData, valueData, 0, &errPtr);

    if (errPtr != NULL) {
        printf("### ERR Failed to store key/value pair in map: %s\n", errPtr);

        goto cleanup;
    }

    // check if key exists in map
    if (Hazelcast_Map_containsKey(client, TEST_MAP_NAME, keyData, &errPtr) == 1) {
        printf("### OK key was found in map.\n");
    } else {
        printf("### ERR key was not found in map.\n");
    }

    if (errPtr != NULL) {
        printf("### ERR Failed to check if key is contained in map: %s\n", errPtr);

        goto cleanup;
    }

    // get number of items in map
    int mapSize = Hazelcast_Map_size(client, TEST_MAP_NAME, &errPtr);

    if (errPtr != NULL) {
        printf("### ERR Failed to get map size.\n");

        goto cleanup;
    }

    printf("### OK map contains %d items\n", mapSize);

    // get key again
    storedData = Hazelcast_Map_get(client, TEST_MAP_NAME, keyData, &errPtr);

    if (errPtr != NULL) {
        printf("### ERR Failed to get data by key from map: %s\n", errPtr);

        goto cleanup;
    }

    char *storedValue = Hazelcast_Serialization_dataToString(client, storedData);

    printf("### OK got value again: '%s' %zu bytes long\n", storedValue, strlen(storedValue));

    Hazelcast_free(storedValue);

    // delete item
    Hazelcast_Map_delete(client, TEST_MAP_NAME, keyData, &errPtr);

    if (errPtr != NULL) {
        printf("### ERR Failed to delete key from map: %s.\n", errPtr);

        goto cleanup;
    }

    // get map size again
    mapSize = Hazelcast_Map_size(client, TEST_MAP_NAME, &errPtr);

    if (errPtr != NULL) {
        printf("### ERR Failed to get map size.\n");

        goto cleanup;
    }

    printf("### OK map contains %d items\n", mapSize);

cleanup:
    Hazelcast_Data_destroy(keyData);
    Hazelcast_Data_destroy(valueData);
    Hazelcast_Data_destroy(storedData);

    Hazelcast_Client_destroy(client);
    Hazelcast_ClientConfig_destroy(clientConfig);

    Hazelcast_resetError(errPtr);

    return 0;
}
