# C Client bindings for Hazelcast

This is a C client for Hazelcast, which wraps the official Hazelcast C++ client, with the aim to provide an low-level but easy to use and safe C API.

C API is supposed to be somewhat similiar to C bindings of [leveldb](https://github.com/google/leveldb/blob/master/include/leveldb/c.h).

The contract is:

  - Just opaque structures are exposed to the client.
  - Errors are represented by a null-terminated c string. NULL means no error.
    All operations that can rause an errr are passed a `char** errptr` as the last argument.
    On success, `errptr` is left unchanged.
    On failure, `errptr` contains an `malloc()`ed  error message (usually the C++ exception message). This message must be freed by the caller!
  - Strings returned from the API are`malloc()`ed and must be freed by the caller!
    Unlike leveldb, the function returns `1` on failure and `0` on success, which should be used for easy success/failure checking.
  - All of the pointer arguments must be non-NULL

WARNING: C client is still early stage and therefore super unstable and most likely buggy.

# Client Code example

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
            printf("Got value from map %s\n", stringValue);
            free(stringValue);
        }

    cleanup:
        Hazelcast_Client_destroy(client);
        Hazelcast_ClientConfig_destroy(clientConfig);

        Hazelcast_free(err); err = NULL;

        return 0;
    }
