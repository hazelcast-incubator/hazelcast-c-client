#include <stdlib.h>
#include <stdio.h>

#include "hazelcast_c_client.h"

int main(void) {
    char *err = NULL;

    printf("creating config\n");
    Hazelcast_ClientConfig_t *clientConfig = Hazelcast_ClientConfig_create();

    printf("adding address");
    Hazelcast_ClientConfig_add_address(clientConfig, "10.1.21.255", 5701);

    printf("connecting");
    Hazelcast_Client_t *client = Hazelcast_Client_create(clientConfig, &err);

    if (err != NULL) {
        printf("ERR Client create failed: %s\n", err);
    }

    Hazelcast_free(err); err = NULL;

    /* save int value */
    Hazelcast_Map_put_int_int(client, "int_int_map", 10, 100, &err);

    if (err != NULL) {
        printf("ERR Map put failed: %s\n", err);
    }

    Hazelcast_free(err); err = NULL;

    /* get int value */
    int intValue = -1;

    if (Hazelcast_Map_get_int_int(client, "int_int_map", 10, &intValue, &err) != 0) {
        printf("ERR Map get failed: %s\n", err);
    } else {
        printf("got value from map %d\n", intValue);
    }

    Hazelcast_free(err); err = NULL;

    /* save string value */
    Hazelcast_Map_put_int_string(client, "int_string_map", 10, "ABC DEF hijklmnop", &err);

    if (err != NULL) {
        printf("ERR Map put failed: %s\n", err);
    }

    Hazelcast_free(err); err = NULL;

    /* get string value */
    char *stringValue = NULL;

    if (Hazelcast_Map_get_int_string(client, "int_string_map", 10, &stringValue, &err) != 0) {
        printf("ERR Map get failed: %s\n", err);
    } else {
        printf("got value from map %s\n", stringValue);
        free(stringValue);
    }

    Hazelcast_free(err); err = NULL;

    /* cleanup */
    Hazelcast_Client_destroy(client);

    printf("destroying config\n");
    Hazelcast_ClientConfig_destroy(clientConfig);

    return 0;
}
