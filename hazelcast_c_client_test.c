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
    Hazelcast_Map_put_int_int(client, "someMap", 10, 100, &err);

    if (err != NULL) {
        printf("ERR Map put failed: %s\n", err);
    }

    Hazelcast_free(err); err = NULL;

    /* cleanup */
    Hazelcast_Client_destroy(client);

    printf("destroying config\n");
    Hazelcast_ClientConfig_destroy(clientConfig);

    return 0;
}
