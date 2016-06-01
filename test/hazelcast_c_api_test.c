#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "hazelcast_c_client.h"

#define TEST_MAP_NAME "test-map"

int main(void)
{
    char *errptr = NULL;

    const char *rawKey = "map_key";
    Hazelcast_Data_t *keyData = NULL;

    const char *rawValue = "map_value";
    Hazelcast_Data_t *valueData = NULL;

    Hazelcast_ClientConfig_t *clientConfig = Hazelcast_ClientConfig_create();
    assert(clientConfig != NULL);

    Hazelcast_ClientConfig_add_address(clientConfig, "10.1.21.255", 5701);

    Hazelcast_Client_t *client = Hazelcast_Client_create(clientConfig, &errptr);
    assert(client != NULL);

    if (errptr != NULL) {
        printf("### ERR Client create failed: %s\n", errptr);

        goto cleanup;
    }

    // serialize key and value into Data object
    keyData = Hazelcast_Serialization_stringToData(client, rawKey, strlen(rawKey));
    valueData = Hazelcast_Serialization_stringToData(client, rawValue, strlen(rawValue));

    // save new key/value pair
    Hazelcast_Map_set(client, TEST_MAP_NAME, keyData, valueData, 0, &errptr);

    if (errptr != NULL) {
        printf("### ERR Failed to store key/value pair in map: %s\n", errptr);

        goto cleanup;
    }

    // check if key exists in map
    if (Hazelcast_Map_containsKey(client, TEST_MAP_NAME, keyData, &errptr) == 1) {
        printf("### OK key was found in map.\n");
    } else {
        printf("### ERR key was not found in map.\n");
    }

    if (errptr != NULL) {
        printf("### ERR Failed to check if key is contained in map: %s\n", errptr);

        goto cleanup;
    }

cleanup:
    Hazelcast_Data_destroy(keyData);
    Hazelcast_Data_destroy(valueData);

    Hazelcast_Client_destroy(client);
    Hazelcast_ClientConfig_destroy(clientConfig);

    Hazelcast_resetError(errptr);

    return 0;
}
