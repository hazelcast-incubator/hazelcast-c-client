#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "hazelcast_c_client.h"

int main(void) {
    char *err = NULL;

    Hazelcast_ClientConfig_t *clientConfig = Hazelcast_ClientConfig_create();
    assert(clientConfig != NULL);

    Hazelcast_ClientConfig_add_address(clientConfig, "10.1.21.255", 5701);

    Hazelcast_Client_t *client = NULL;

    if (Hazelcast_Client_create(clientConfig, &client, &err) != 0) {
        printf("ERR Client create failed: %s\n", err);
        Hazelcast_free(err); err = NULL;

        goto cleanup;
    }

    /* save int value */
    if (Hazelcast_Map_put_int_int(client, "int_int_map", 10, 100, &err) != 0) {
        printf("ERR Map put failed: %s\n", err);
        Hazelcast_free(err); err = NULL;
    }

    /* get int value */
    int intValue = -1;

    if (Hazelcast_Map_get_int_int(client, "int_int_map", 10, &intValue, &err) != 0) {
        printf("ERR Map get failed: %s\n", err);
        Hazelcast_free(err); err = NULL;
    } else {
        printf("got value from map %d\n", intValue);
    }

    /* save string value */
    if (Hazelcast_Map_put_int_string(client, "int_string_map", 10, "ABC DEF hijklmnop", &err) != 0) {
        printf("ERR Map put failed: %s\n", err);
        Hazelcast_free(err); err = NULL;
    }

    /* get string value */
    char *stringValue = NULL;

    if (Hazelcast_Map_get_int_string(client, "int_string_map", 10, &stringValue, &err) != 0) {
        printf("ERR Map get failed: %s\n", err);
        Hazelcast_free(err); err = NULL;
    } else {
        printf("got value from map %s\n", stringValue);
        free(stringValue);
    }

cleanup:
    Hazelcast_Client_destroy(client);
    Hazelcast_ClientConfig_destroy(clientConfig);

    Hazelcast_free(err); err = NULL;

    return 0;
}
